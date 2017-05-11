/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <capture.h>
#include <timers.h>
#include <bitmask.h>
#include <cdefs.h>
#include <cmdline.h>
#include <assert.h>
#include <TSL2561.h>
#include <systick.h>
#include <swSpiWrite.h>
#include <ds18x20.h>
#include <usbhid_stdio/usbhid_stdio.h>
#include <hd44780.h>
#include <ds18x20_ex.h>
#include <onewire.h>
#include <pt.h>
#include <boost/counter.h>

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

#include "usbhid_stdio/usbhid_stdio.h"

/**
| PIC18F2550 | description | to |
| ----- | --- | --- |
| left | | |
| RA0 | TACHO channel A out | 4051 A |
| RA1 | TACHO channel B out | 4051 B |
| RA2 | TACHO channel C out | 4051 C |
| RA3 | onewire | DS18B20 |
| RA4 | | |
| RA5 | | |
| RC0 | USB sense in | USB +5V |
| RC1 | | |
| RC2 | TACHO in / CCP1| 4051 X |
| right  | | |
| RB7 | in | button |
| RB6 | out | diode |
| RB5 | out | MCP4812 no. 2 chip select |
| RB4 | out | MCP4812 no. 1 chip select |
| RB3 | software SCK | MCP4812 SCK |
| RB2 | software SDI | MCP4812 SDA |
| RB1 | SCL | TSL2561 SCL |
| RB0 | SDA | TSL2561 SDA |
| RC7 | UART | |
| RC6 | UART | |
 */

/* ------------------------------------ configuration ------------------------------------ */

#ifndef VERSION
#ifdef GIT_REV_PARSE_HEAD_SHORT
#define VERSION __XSTRING( GIT_REV_PARSE_HEAD_SHORT )
#else
#define VERSION "00.01.00"
#endif
#endif

/* ------------------------------------ rpm* - reading RPM part -------------------------- */

#define FAN_MAX_NUMBER 8
#define RPM_VALUE_UPPER_MAX 32

// temp synchronization variables
volatile struct {
	uint8_t tmpvalueupper;
	bool    synchronized;
} rpmCmpState = {0,0};

static volatile UINT24_VAL rpmResult[FAN_MAX_NUMBER] = {0};
#define rpmResultlen FAN_MAX_NUMBER
static volatile uint8_t rpmResultpos = 0;

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
	// Capture1 on RC2
	OpenCapture1( C1_EVERY_RISE_EDGE & CAPTURE_INT_ON );
	IPR1bits.TMR1IP = 0;
	OpenTimer1( T1_16BIT_RW & TIMER_INT_ON & T1_PS_1_8 & T1_SOURCE_INT & T1_SYNC_EXT_OFF );
}

static void rpmSet(const uint8_t UB, const uint8_t HB, const uint8_t LB)
{
	/* in interrupt */

	//save results
	rpmResult[rpmResultpos].byte.LB = LB;
	rpmResult[rpmResultpos].byte.HB = HB;
	rpmResult[rpmResultpos].byte.UB = UB;

	// increment CMPResultPos
	if ( rpmResultpos < (sizeof(rpmResult)/sizeof(*rpmResult))-1 ) {
		++rpmResultpos;
	} else {
		rpmResultpos = 0;
	}

	// set to measure next port
	rpmPortSet( rpmResultpos );
}

static uint24_t rpmGet(const uint8_t i)
{
	uint24_t ret;

	assert(i < rpmResultlen);

	di();
	ret = rpmResult[i].Val;
	ei();
	return ret;
}

static uint16_t rpmComputeRpm(const uint24_t value)
{
	// SECONDS_IN_MINUTE * _XTAL_FREQ/4 / TIMER_PRESCALER / FAN_PULSES_PER_REVOLUTION =
	// = ( 60 * _XTAL_FREQ/4 /8 /2 )
#define RPM_ROTATION_PER_MINUTE_PER_TIMER_INC ( _XTAL_FREQ /4 /8 /2 *60 )
	return value == 0 ? 0 : RPM_ROTATION_PER_MINUTE_PER_TIMER_INC / value;
}

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
	systickServiceInterrupt();

	// rpm module - CCP1 & TMR1
	if ( PIR1bits.TMR1IF ) {
		++rpmCmpState.tmpvalueupper;
		if ( rpmCmpState.tmpvalueupper > RPM_VALUE_UPPER_MAX ) {
			rpmSet(UINT8_MAX, 0, 0);
			rpmCmpState.synchronized = false;
			rpmCmpState.tmpvalueupper = 0;
		}
		PIR1bits.TMR1IF = 0;
	}
	if ( PIR1bits.CCP1IF ) {
		TMR1 = 0;
		if ( rpmCmpState.synchronized ) {
			rpmSet(rpmCmpState.tmpvalueupper, CCPR1H, CCPR1L);
			rpmCmpState.synchronized = false;
			rpmCmpState.tmpvalueupper = 0;
		} else {
			rpmCmpState.synchronized = true;
		}
		PIR1bits.CCP1IF = 0;
	}
}


/* ------------------- fan module - setting fan speeds using I2C 4802 modules -------------- */

/*| RB5 | out | MCP4812 no. 2 chip select |
  | RB4 | out | MCP4812 no. 1 chip select |*/
#define FAN_CHIP_SELECT_1()     do{PORT(B,4)                 = 0;}while(0)
#define FAN_CHIP_SELECT_2()     do{                PORTBbits.RB5 = 0;}while(0)
#define FAN_CHIP_DESELECT_ALL() do{PORTBbits.RB4 = PORTBbits.RB5 = 1;}while(0)
#define FAN_CHIP_SELECT_INIT()  do{TRISBbits.RB4 = TRISBbits.RB5 = 0;}while(0)

#define fanSpeedslen 4
static uint16_t fanSpeeds[fanSpeedslen];

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

	assert( num < sizeof(fanSpeeds)/sizeof(*fanSpeeds) );
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
	__delay_ms(1); // select stabilize
	SwSpiWrite(wcr.byte.byte.HB);
	SwSpiWrite(wcr.byte.byte.LB);
	__delay_ms(1); // select stabilize
	fanSpeeds[num] = val;

	// deselect all chips
	FAN_CHIP_DESELECT_ALL();
}

static void fanInit(void) {
	FAN_CHIP_SELECT_INIT();
	FAN_CHIP_DESELECT_ALL();
}

/* ----------------------------------------ds18b20 ------------------------------------------  */

#define DS18X20_MAXSENSORS 10
static struct pt_s sense_pt = pt_init();
static struct ds18x20_s senses[DS18X20_MAXSENSORS];
static int16_t sense_val[DS18X20_MAXSENSORS];
static uint8_t sense_count;

static void sense_thread()
{
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);
	uint8_t i;

#include <boost/counter_reset.h>
	pt_begin(&sense_pt);

	// init
	sense_count = DS18X20_search_sensors(senses, (sizeof(senses)/sizeof(*senses)));

	for ( i = 0; i < sense_count; i++ ) {
		DS18X20_write_scratchpad( senses[i].romcode , 0, 0, DS18B20_12_BIT );
	}

	printf("ds18b20 initialized.\n");

	pt_yield(&sense_pt);
#include <boost/counter_inc.h>

	while(1) {

		// measure temperature for every senses
		for(i = 0; i < sense_count; ++i) {

			// start the conversion
			if ( DS18X20_start_meas( DS18X20_POWER_PARASITE, senses[i].romcode ) != DS18X20_OK ) {
				// disable this sensor?
			}

			// wait for conversion
			SYSTICK_TIMEOUT_SET( Tickstop, DS18B20_TCONV_12BIT );
			pt_wait_while( &sense_pt, !SYSTICK_TIMEOUT_ELAPSED( Tickstop ) );
#include <boost/counter_inc.h>

			if ( DS18X20_read_decicelsius( senses[i].romcode , &sense_val[i] ) != DS18X20_OK ) {
				// disable this sensor?
			}

			pt_yield(&sense_pt);
#include <boost/counter_inc.h>

		}
	}

	pt_end(&sense_pt);
}

/* ----------------------------------------- hd44780 ---------------------------------------- */

static struct pt_s display_pt = pt_init();
static uint8_t display_state_next = 0; /* increment this to update display */
static uint8_t display_state_cur = 0xFF;
static uint8_t display_custom_msg[16+1] = {0};
static uint8_t display[2][16+1];

static void display_update(uint8_t *display)
{
	uint8_t this = 0;

	if ( display_state_next < (this += 4) ) {
		switch(display_state_next) {
		case 0:
			strcpy(display, display_custom_msg);
			break;
		case 1:
			strcpy(display, "ULTIFAN");
			break;
		case 2:
			strcpy(display, "V: "VERSION);
			break;
		case 3:
			sprintf(display, "lm=%u\n", TSL2561_getLuminosity(2));
			break;
		default:
			goto DISPLAY_RESET_STATE;
		}

	} else if ( display_state_next < (this += fanSpeedslen) ) {
		uint8_t i = display_state_next - (this - fanSpeedslen);
		sprintf(display, "FAN[%u]: %d", i, fanSpeeds[i]);

	} else if ( display_state_next < (this += rpmResultlen) ) {
		uint8_t i = display_state_next - (this - rpmResultlen);
		sprintf(display, "RPM[%u]: %u", i, rpmComputeRpm(rpmGet(i)));

	} else if ( display_state_next < (this += sense_count) ) {
		uint8_t i = display_state_next - (this - sense_count);
		sprintf(display, "temp[%u]: %d", i, sense_val[i]);

	} else {
		goto DISPLAY_RESET_STATE;
	}

	display_state_cur = display_state_next;
	++display_state_next;
	return;/* success */

DISPLAY_RESET_STATE:
	*display = '\0';
	display_state_next = 0xFF;
	display_state_cur = 0;
	return;
}

static void display_thread()
{
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);

#include <boost/counter_reset.h>
	pt_begin(&display_pt);

	// initialization
	hd44780_init();
	printf("hd44780 initialized.\n");

	pt_yield(&display_pt);
#include <boost/counter_inc.h>

	while(1) {

		SYSTICK_TIMEOUT_SET(Tickstop, 2000);
		pt_wait_while( &display_pt,
				display_state_cur == display_state_next && !SYSTICK_TIMEOUT_ELAPSED(Tickstop) );
#include <boost/counter_inc.h>

		// update hd44780
		hd44780_clrscr();
		for(uint8_t col = 0; col < 2; ++col) {

			display_update(display[col]);

			hd44780_set_cursor_rowcol(0, 0, col);
			for(uint8_t i = 0; i < 16; ++i) {
				uint8_t temp = display[col][i];
				if ( temp == 0 ) {
					break;
				}
				hd44780_write_data(0, temp);
			}
			pt_yield(&display_pt);
#include <boost/counter_inc.h>
		}
	}

	pt_end(&display_pt);
}

/* ------------------------------------------- tls2561 ---------------------------------------- */

static uint16_t luminosity;
static struct pt_s luminosity_pt = pt_init();
static void luminosity_thread()
{
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);

#include <boost/counter_reset.h>
	pt_begin(&luminosity_pt);

	TSL2561_init(TSL2561_ADDR_FLOAT);
	TSL2561_begin();
	printf("TLS2561 initialized.\n");

	pt_yield(&display_pt);
#include <boost/counter_inc.h>

	while(1) {
		SYSTICK_TIMEOUT_SET(Tickstop, TSL2561_getLuminosity_nonblock_start() );

		pt_wait_while( &luminosity_pt, !SYSTICK_TIMEOUT_ELAPSED(Tickstop) );
#include <boost/counter_inc.h>

		luminosity = TSL2561_getLuminosity_nonblock_stop(2);
	}

	pt_end(&luminosity_pt);
}

/* ---------------------------------------- interaction -------------------------------------- */

void cmdlineService_callback(void)
{
	uint8_t i;
	char *token;
	printf("R:");
	for( i = 0; i <= cmdline.buffpos; ++i) {
		printf("%c", cmdline.buff[i]);
	}
	printf("\n");
	switch( cmdline.buff[0] ) {
	case 'i':
		printf(
				"rpmCmpState=%02x %02x\n"
				"rpmResultpos=%u\n"
				"systick=%u\n"
				"luminosity=%u\n"
				,
				rpmCmpState.synchronized, rpmCmpState.tmpvalueupper,
				rpmResultpos,
				systickGet(),
				luminosity
		);
		for( i = 0; i < sizeof(rpmResult)/sizeof(*rpmResult); ++i) {
			UINT24_VAL rpm;
			rpm.Val = rpmGet(i);
			printf("rpmGet(%d) = { %02x%02x%02x } RPM[%u] = %u\n",
					i, rpm.byte.UB, rpm.byte.HB, rpm.byte.LB,
					i, rpmComputeRpm(rpm.Val)
			);
		}
		for( i = 0; i < sizeof(fanSpeeds)/sizeof(*fanSpeeds); ++i) {
			printf("FAN[%u]=%d", i, fanSpeeds[i]);
		}
		for( i = 0; i < sense_count; ++i) {
			printf("ds18x20(%u)=%d\n", i, sense_val[i]);
		}
		for( i = 0; i < 2; ++i) {
			printf("hd44780(%u)=\"%s\"\n", i, display[i]);
		}
		printf("\n");
		break;
	case 'f':
	{
		uint8_t num;
		uint16_t val;

		token = strtok(&cmdline.buff[2], " ");
		if ( token == NULL ) {
			goto NOT_ENOUGH_ARGUMENTS;
		}
		num = (uint8_t)atoi(token);

		token = strtok(NULL, " ");
		if ( token == NULL ) {
			goto NOT_ENOUGH_ARGUMENTS;
		}
		val = atoi(token);

		if ( num >= FAN_MAX_NUMBER ) {
			printf("error NUM=%u must be lower then " __XSTRING( FAN_MAX_NUMBER ) "\n", num);
			break;
		}
		if ( val >= 4096 ) {
			printf("error VAL=%u must be lower then 4096\n", val);
			break;
		}

		fanWrite(num, val);
	}
		break;
	case 'l':
		printf("%u\n", luminosity);
		break;
	case 'd':
		strncpy(display_custom_msg, &cmdline.buff[2], MIN(sizeof(display_custom_msg), cmdline.buffpos));
		break;
	case 'r':
		++display_state_cur;
		break;
	case 'h': case 'H': case 'v': case 'V': // usage and version
		printf(
				"\n"
				"Version information:\n"
				"ultifan pic firmware\n"
				"Type=ultifan\n"
				"Version=" VERSION "\n"
				"Author=Kamil Cukrowski\n"
				"Available commands: \n"
				"i                 - print current configuration\n"
				"f NUM VAL         - set fan number num to VAL voltage in percent\n"
				"l                 - get lumination value from TSL2560\n"
				"d <msg>           - set custom hd44780 msg"
				"r                 - print hd44780 next screen"
				"\n"
		);
		/* no break */
	default:
		cmdlineService_standard();
		break;
	}
	return;
NOT_ENOUGH_ARGUMENTS:
	printf("error Not enough arguments\n");
	return;
}

/* ----------------------------------------------------------------------------------------- */

void app_thread(void)
{

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
	// start i2c 100kHz
	smbus_open_master(100000);
}

void main(void)
{
	main_preinit();

	usbStdioInitBlocking(1);
	systickInitInterrupt(0);

	__delay_ms(500);
	printf("USB Startup completed.\n");

	rpmInit();
	printf("rpm initialized.\n");

	fanInit();
	printf("fan initialized.\n");

	while(1) {

		display_thread();

		sense_thread();

		luminosity_thread();

		app_thread();

		usbStdioService();

		cmdlineService_nonblock();

	}
}

