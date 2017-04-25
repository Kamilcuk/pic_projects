/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>
#include "capture.h"
#include "timers.h"
#include "common.h"
#include "cdefs.h"
#include "pt.h"
#include "cmdline.h"
#include "assert.h"
#include "TSL2561.h"
#include "systick.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>
#include <spi.h>

#include "usbhid_stdio/usbhid_stdio.h"

/* ------------------------------------- configuration ------------------------------ */

#define FUN_MAX_NUMBER 4

/* ------------------------------------ rpm* - reading RPM part -------------------------- */

#define RPM_VALUE_HIGH_MAX 32

// temp synchronization variables
volatile struct {
	uint8_t tmpvaluehigh;
	bool synchronized : 1;
} rpmCmpState = {0,0};

volatile UINT24_BITS rpmResult[FUN_MAX_NUMBER] = {0};

volatile UINT8 rpmResultpos = 0;

// 4051 connections - choosing fan rpm input
#define rpmPortInit()    BITMASK_SET(TRISA, 0b11100000)
#define rpmPortSet(a)  BITMASK_WRITE(PORTA, 0b11100000, a<<5)

static void rpmInit(void)
{
	// set TRISA bits as inputs
	rpmPortInit();
	// capture first input
	rpmPortSet(0);
	rpmResultpos = 0;

	SetTmrCCPSrc( T1_CCP1_T3_CCP2 );
	IPR1bits.CCP1IP = 0;
	// apture1 on RC2
	OpenCapture1( C1_EVERY_RISE_EDGE & CAPTURE_INT_ON );
	IPR1bits.TMR1IP = 0;
	OpenTimer1( T1_16BIT_RW & TIMER_INT_ON & T1_PS_1_8 & T1_SOURCE_INT & T1_SYNC_EXT_OFF );
}

static void rpmSet(const UINT8 UB, const UINT8 HB, const UINT8 LB)
{
	assert( rpmResultpos < sizeof(rpmResult)/sizeof(*rpmResult) );

	//save results
	rpmResult[rpmResultpos].byte.LB = LB;
	rpmResult[rpmResultpos].byte.HB = HB;
	rpmResult[rpmResultpos].byte.UB = UB;

	// increment CMPResultPos
	if ( rpmResultpos < sizeof(rpmResult)/sizeof(*rpmResult)-1 ) {
		++rpmResultpos;
	} else {
		rpmResultpos = 0;
	}

	// set to measure next port
	rpmPortSet( rpmResultpos );
}

static UINT24 rpmGet(UINT8 i)
{
	UINT24 ret;
	assert( i < sizeof(rpmResult)/sizeof(*rpmResult) );
	di();
	ret = rpmResult[i].Val;
	ei();
	return ret;
}

static UINT16 rpmComputeRpm(const UINT24 value)
{
	// SECONDS_IN_MINUTE * _XTAL_FREQ/4 / TIMER_PRESCALER / FAN_PULSES_PER_REVOLUTION = ( 60 * _XTAL_FREQ/4 /8 /2 )
#define RPM_ROTATION_PER_MINUTE_PER_TIMER_INC 45000000 // ( 60 * _XTAL_FREQ/4 /8 /2 )
	uint16_t ret;
	// sanity
	if ( value == 0 ) {
		return 0;
	}
	// calculations
	ret = (UINT16)((double)RPM_ROTATION_PER_MINUTE_PER_TIMER_INC / (double)value);
	// return
	return ret;
}

/* ------------------- fan module - setting fan speeds using I2C 4802 modules -------------- */

#define FAN_CHIP_SELECT_1() do{PORTBbits.RB3 = 0;}while(0)
#define FAN_CHIP_SELECT_2() do{PORTBbits.RB2 = 0;}while(0)
#define FAN_CHIP_DESELECT_ALL() do{PORTBbits.RB3 = PORTBbits.RB2 = 1;}while(0)
#define FAN_CHIP_SELECT_INIT() do{ TRISBbits.RB2 = TRISBbits.RB3 = 0;}while(0)

#define SW_SPI_DOUT_PIN       PORTBbits.RB7
#define TRIS_SW_SPI_DOUT_PIN  TRISBbits.TRISB7
#define SW_SPI_SCK_PIN        PORTBbits.RB6
#define TRIS_SW_SPI_SCK_PIN   TRISBbits.TRISB6

void SwSpiInit(void)
{
	TRIS_SW_SPI_DOUT_PIN = TRIS_SW_SPI_SCK_PIN = 0;
}
char SwSpiWrite(char input)
{
	char BitCount;                  // Bit counter
    BitCount = 8;                   // Do 8-bits

	// SCK idles low
	// Data output after falling edge of SCK
	// Data sampled before rising edge of SCK
	SW_SPI_DOUT_PIN = 0;                // Set Dout to MSB of data
    if(input&0x80)
    	SW_SPI_DOUT_PIN = 1;
    Nop();                          // Adjust for jitter
    Nop();
    do                              // Loop 8 times
    {
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        SW_SCK_PIN = 1;         // Set the SCK pin
        input = input << 1;
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();                  // Produces a 50% duty cycle clock
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        SW_SCK_PIN = 0;         // Clear the SCK pin
        SW_DOUT_PIN = 0;        // Set Dout to the next bit according to
        if(input&0x80)          // the MSB of data
                SW_DOUT_PIN = 1;
        BitCount--;             // Count iterations through loop
    } while(BitCount);
}

static void fanWrite(UINT8 num, UINT16 val)
{
	struct WriteCommandRegisterMCP48x2_s {
		unsigned char D_lower : 8;
		unsigned char D_upper : 4;
		unsigned char SHDN : 1;
		unsigned char GA : 1;
		unsigned char _dont_care : 1;
		unsigned char AB : 1;
	};
	union {
		struct WriteCommandRegisterMCP48x2_s v;
		UINT16_VAL byte;
	} wcr = {0};

	assert( num < 3 );
	assert( sizeof(struct WriteCommandRegisterMCP48x2_s) == 2 );
	assert( sizeof(wcr) == 2 );

	// deselect all chips
	FAN_CHIP_DESELECT_ALL();

	// slave select
	switch(num) {
	case 0:
		// DAC_A or DAC_B selection bit
		wcr.v.AB = 0;
		// chip select
		FAN_CHIP_SELECT_1();
		break;
	case 1:
		// DAC_A or DAC_B selection bit
		wcr.v.AB = 1;
		// chip select
		FAN_CHIP_SELECT_1();
		break;
	case 2:
		// DAC_A or DAC_B selection bit
		wcr.v.AB = 0;
		// chip select
		FAN_CHIP_SELECT_2();
		break;
	case 3:
		// DAC_A or DAC_B selection bit
		wcr.v.AB = 1;
		// chip select
		FAN_CHIP_SELECT_2();
		break;

	}

	wcr.v._dont_care = 1;
	wcr.v.GA = 0;
	wcr.v.SHDN = 1;
	BITMASK_WRITE((UINT16)wcr.byte.Val, (UINT16)0x0fff, val);

	// actual write
	__delay_ms(1);
	SwSpiWrite(wcr.byte.byte.HB);
	SwSpiWrite(wcr.byte.byte.LB);
	__delay_ms(1);

	// deselect all chips
	FAN_CHIP_DESELECT_ALL();
}

static void fanInit(void) {
	FAN_CHIP_SELECT_INIT();
	FAN_CHIP_DESELECT_ALL();
	SwSpiInit();

	// write 0 fan speed to all fans
	//for(uint8_t i=0;i<FUN_MAX_NUMBER;++i) {
	//	fanWrite(i, 0xff);
	//}
}


/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{    
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
	usbStdioInterruptHandler();

	systickServiceInterrupt();

	// rpm module - CCP1 & TMR1
	if ( PIR1bits.TMR1IF ) {
		++rpmCmpState.tmpvaluehigh;
		if ( rpmCmpState.tmpvaluehigh > RPM_VALUE_HIGH_MAX ) {
			rpmSet(UINT8_MAX, 0, 0);
			rpmCmpState.synchronized = false;
			rpmCmpState.tmpvaluehigh = 0;
		}
		PIR1bits.TMR1IF = 0;
	}
	if ( PIR1bits.CCP1IF ) {
		TMR1 = 0;
		if ( rpmCmpState.synchronized ) {
			rpmSet(rpmCmpState.tmpvaluehigh, CCPR1H, CCPR1L);
			rpmCmpState.synchronized = false;
			rpmCmpState.tmpvaluehigh = 0;
		} else {
			rpmCmpState.synchronized = true;
		}
		PIR1bits.CCP1IF = 0;
	}
}

/* -------------------------- functions -------------------------------------- */

#define TLS2561_CHIP_SELECT()      do{ PORTBbits.RB4 = 1; }while(0)
#define TLS2561_CHIP_DESELECT()    do{ PORTBbits.RB4 = 0; }while(0)
#define TLS2561_CHIP_SELECT_INIT() do{ TRISBbits.RB4 = 0; }while(0)

/* ---------------------------------------- interaction -------------------------------------- */

void cmdlineService_callback(void)
{
	uint8_t i;
	char *token;
	printf("R:");
	for(i=0;i<=cmdline.buffpos;++i) {
		printf("%c", cmdline.buff[i]);
	}
	printf("\n");
	switch(cmdline.buff[0]) {
	case 'i':
		printf(
				"sizeof(CMPresult)=%u sizeof(*CMPresult)=%u\n"
				"rpmCmpState=%02x %02x\n"
				"rpmResultpos=%u\n"
				"systick=%u\n"
				,
				sizeof(rpmResult), sizeof(*rpmResult),
				rpmCmpState.synchronized, rpmCmpState.tmpvaluehigh,
				rpmResultpos,
				systickGet()
		);
		for(i=0;i<sizeof(rpmResult)/sizeof(*rpmResult);++i) {
			UINT24_BITS rpm;
			rpm.Val = rpmGet(i);
			printf("rpmGet(%d) = { %02x%02x%02x } RPM[%u] = %u\n",
					i, rpm.byte.UB, rpm.byte.HB, rpm.byte.LB,
					i, rpmComputeRpm(rpm.Val)
			);
		}
		printf("\n");
		break;
	case 'f':
	{
		uint8_t num;
		uint16_t val;

		token = strtok(&cmdline.buff[1], " ");
		if ( token == NULL ) {
			goto NOT_ENOUGH_ARGUMENTS;
		}
		num = (uint8_t)atoi(token);

		token = strtok(NULL, " ");
		if ( token == NULL ) {
			goto NOT_ENOUGH_ARGUMENTS;
		}
		val = atoi(token);

		if ( num >= FUN_MAX_NUMBER ) {
			printf("error NUM=%u must be lower then %u\n", num, FUN_MAX_NUMBER);
			break;
		}
		if ( val >= 0x0fff ) {
			printf("error VAL=%u must be lower then 4096\n", val);
			break;
		}

		fanWrite(num, val);
	}
		break;
NOT_ENOUGH_ARGUMENTS:
		printf("error Not enough arguments.\n");
		break;

	case 'l':
		TLS2561_CHIP_SELECT();
		printf("%u\n", TSL2561_getLuminosity(2));
		TLS2561_CHIP_DESELECT();
		break;
	case 'h': case 'H': case 'v': case 'V': // usage and version
		printf(
				"\n"
				"Version information:\n"
				"ultifan pic firmware\n"
				"Type=ultifan\n"
				"Version=0.1.1\n"
				"Author=Kamil Cukrowski\n"
				"Available commands: \n"
				" i                 - print current configuration\n"
				" f NUM VAL         - set fan number num to VAL voltage in percent\n"
				" l                 - get lumination value from TSL2560\n"
				"\n"
		);
		/* no break */
	default:
		cmdlineService_standard();
		break;
	}
}

/* ----------------------------------------------------------------------------------------- */

void applicationThread(void)
{
	static systick_t next;
	systick_t now = systickGet();
	static bool first_run = true;
	if ( first_run || SYSTICK_EQUAL(now, next) ) {
		first_run = false;
		next = now + SYSTICK_S_TO_SYSTICKS(5);
		printf("\n10 seconds: now=%u next=%u\n", now, next);
	}
}

/* ----------------------------------------------------------------------------------------- */

void main_preinit(void)
{
	// wait for PLL HS oscillator
	//while( OSCCONbits.OSTS == 0 );
	// set all ports as inputs
	PORTA = PORTB = PORTC = 0x00;
	TRISA = TRISB = TRISC = 0xff;
	LATA = LATB = LATC = 0x00;
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

void main(void)
{
	main_preinit();

	usbStdioInitBlocking(1);

	__delay_ms(500);
	printf("USB Startup completed.\n");

	systickInitInterrupt(0);
	rpmInit();
	printf("rpm completed.\n");

	TLS2561_CHIP_SELECT_INIT();
	TLS2561_CHIP_SELECT();
	TSL2561_init(TSL2561_ADDR_FLOAT);
	TSL2561_begin();
	TLS2561_CHIP_DESELECT();
	printf("TLS2561 completed.\n");

	fanInit();
	printf("fan completed.\n");

	printf("Startup completed.\n");

	while(1) {
		applicationThread();

		cmdlineServiceThread();
	}
}

