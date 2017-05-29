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
#include <usbhid_stdio/usbhid_stdio.h>
#include <cmdline.h>
#include <assert.h>
#include <swSpiWrite.h>
#include <TSL2561.h>
#include <systick.h>
#include <hd44780.h>
#include <ds18x20.h>
#include <ds18x20_ex.h>
#include <pt.h> // prothread
#include <checkmacro.h>
#include <boost/counter.h> // BOOST_PP_COUNTER
#include <interrupt.h> // ATOMIC_CODE
#include <checkmacro.h>
#include <hd44780-config.h>

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

#include "usbhid_stdio/usbhid_stdio.h"

/* ------------------------------------ configuration ------------------------------------ */

#ifndef VERSION
#ifdef GIT_REV_PARSE_HEAD_SHORT
#define VERSION __XSTRING( GIT_REV_PARSE_HEAD_SHORT )
#else
#define VERSION "00.01.00"
#endif
#endif
#pragma CHECKMACRO(1,VERSION)

#define DEBUG_MAIN(pre, printf_args ) do{printf(pre); printf printf_args ; putchar('\n'); }while(0)

/* ------------------------------------ rpm* - reading RPM part -------------------------- */

#define FAN_MAX_NUMBER 4
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
#define rpmPortInit()  BITMASK_CLEAR(TRISA, 0b00000111)
#define rpmPortSet(a)  BITMASK_WRITE(PORTA, 0b00000111, a)

static void rpmInit(void)
{
	// set TRISA bits as inputs
	rpmPortInit();
	// capture first input
	rpmPortSet(0);
	rpmResultpos = 0;

	IPR1bits.CCP1IP = 0;
	IPR1bits.TMR1IP = 0;
	SetTmrCCPSrc( T1_SOURCE_CCP );
	// Capture1 on RC2
	OpenCapture1( C1_EVERY_RISE_EDGE & CAPTURE_INT_ON );
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

	ATOMIC_CODE(
			ret = rpmResult[i].Val;
	);
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

void __interrupt(high_priority) SYS_InterruptHigh(void)
{
	usbStdioInterruptHandler();
}

void __interrupt( low_priority) SYS_InterruptLow(void)
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

#define FAN_CHIP_SELECT_1()     do{ PORT1(FAN_CS1_PORTPIN)                          = 0; }while(0)
#define FAN_CHIP_SELECT_2()     do{                          PORT1(FAN_CS2_PORTPIN) = 0; }while(0)
#define FAN_CHIP_DESELECT_ALL() do{ PORT1(FAN_CS1_PORTPIN) = PORT1(FAN_CS2_PORTPIN) = 1; }while(0)
#define FAN_CHIP_SELECT_INIT()  do{ TRIS1(FAN_CS1_PORTPIN) = TRIS1(FAN_CS2_PORTPIN) = TRIS_OUT; }while(0)

#define FAN_COUNT 4
#define fanSpeedslen 4
static uint16_t fanSpeeds[fanSpeedslen];

static void fanWrite(uint8_t num, uint16_t val)
{
	union WriteCommandRegisterMCP48x2_u {
		struct {
				unsigned char D_lower : 8;
				unsigned char D_upper : 4;
				unsigned char SHDN : 1;
				unsigned char GA : 1;
				unsigned char _dont_care : 1;
				unsigned char AB : 1;
		} v;
		UINT16_VAL byte;
	}
	union WriteCommandRegisterMCP48x2_u wcr = {0};

	STATIC_ASSERT( sizeof(union WriteCommandRegisterMCP48x2_u) == 2 );
	STATIC_ASSERT( sizeof(uint8_t) == 1 );
	STATIC_ASSERT( sizeof(uint16_t) == 2 );
	STATIC_ASSERT( sizeof(uint24_t) == 3 );
	STATIC_ASSERT( sizeof(uint32_t) == 4 );
	assert( num < sizeof(fanSpeeds)/sizeof(*fanSpeeds) );

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
	BITMASK_WRITE(wcr.byte.Val, (uint16_t)0x0fff, val);

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
	__delay_ms(1);
	for(uint8_t i = 0; i < fanSpeedslen; ++i) {
		fanWrite(i, 2500);
	}
}

/* ----------------------------------------ds18b20 ------------------------------------------  */

#define SENSE_DEBUG(printf_args) //DEBUG_MAIN("SENSE:", printf_args)
#define DS18X20_DYNAMIC_COUNT 1
#if DS18X20_DYNAMIC_COUNT
#define DS18X20_MAXSENSORS 2
static struct ds18x20_s senses[DS18X20_MAXSENSORS];
static uint8_t sense_count = 0;
#else
#define DS18X20_MAXSENSORS 4
static struct ds18x20_s senses[DS18X20_MAXSENSORS] = {
		0x28,0xed,0xff,0x5b,0x05,0x00,0x00,0xcd,
		0x28,0xf2,0xdc,0x5b,0x05,0x00,0x00,0x04,
		0x28,0x2d,0xa6,0x5b,0x05,0x00,0x00,0x34,
		0x28,0x4a,0xdc,0x5b,0x05,0x00,0x00,0xa2,
};
static uint8_t sense_count = DS18X20_MAXSENSORS;
#endif
#define DS18B20_RESOLUTION_BITS             12 // 9 or 10 or 11 or 12
#define DS18B20_CONFIG                      __CONCAT(__CONCAT(DS18B20_, DS18B20_RESOLUTION_BITS), _BIT)
#define DS18B20_WAITTIME                    __CONCAT(__CONCAT(DS18B20_TCONV_, DS18B20_RESOLUTION_BITS), BIT)
static int16_t sense_val[DS18X20_MAXSENSORS];

// 28edff5b050000cd , 28f2dc5b05000004 , 282da65b05000034 , 284adc5b050000a2

static void sense_thread()
{
	static struct pt_s sense_pt = pt_init();
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);
	static uint8_t i;

#include <boost/counter_reset.h>
	pt_begin(&sense_pt);

	// disable pullup
	TRIS1(OW_PULLUP_PORTPIN) = TRIS_OUT;
	PORT1(OW_PULLUP_PORTPIN) = 1;

#if DS18X20_DYNAMIC_COUNT
	ATOMIC_BLOCK() {
		sense_count = DS18X20_search_sensors(senses, DS18X20_MAXSENSORS);
		if ( sense_count > DS18X20_MAXSENSORS ) {
			printf("ERROR: sense_count > DS18X20_MAXSENSORS");
		}
	}
#endif

	for ( i = 0; i < sense_count; i++ ) {
		DS18X20_write_scratchpad( senses[i].romcode , 0, 0, DS18B20_CONFIG );
	}

	printf("ds18x20 initialized. %u sensors found.\n", sense_count);
	for ( i = 0; i < sense_count; ++i) {
		printf("ds18x20[%u]\n", i);
		printf(" ^ romcode=\"");
		for(uint8_t j=0;j<OW_ROMCODE_SIZE;++j) {
			printf("%02x", senses[i].romcode[j]);
		}
		printf("\"\n");
		printf(" ^ external power = %x\n", DS18X20_get_power_status(senses[i].romcode));
		uint8_t sp[3];
		DS18X20_read_scratchpad(senses[i].romcode, sp, 3);
		for(uint8_t j=0;j<3;++j) {
			printf(" ^ scratchpad[%u] = 0x%02x\n", j, sp[j]);
		}
	}


	pt_yield(&sense_pt);
#include <boost/counter_inc.h>

	if ( sense_count == 0 ) {
		goto END;
	}

	while(1) {

		// measure temperature for every senses
		for(i = 0; i < sense_count; ++i) {

			SENSE_DEBUG(("Start conversion on %u", i));
			// start the conversion
			if ( DS18X20_start_meas( DS18X20_POWER_PARASITE, senses[i].romcode ) != DS18X20_OK ) {
				// disable this sensor?
			}

			// enable pullup during Convert T
			PORT1(OW_PULLUP_PORTPIN) = 0;

			// wait for conversion
			SYSTICK_TIMEOUT_SET( Tickstop , DS18B20_WAITTIME );
			pt_wait_while( &sense_pt, !SYSTICK_TIMEOUT_ELAPSED(Tickstop, DS18B20_WAITTIME));
#include <boost/counter_inc.h>

			// disable pullup
			PORT1(OW_PULLUP_PORTPIN) = 1;

			if ( DS18X20_read_decicelsius( senses[i].romcode , &sense_val[i] ) != DS18X20_OK ) {
				// disable this sensor?
			}
			SENSE_DEBUG(("read decicelsius from %u = %u", i, sense_val[i]));

			pt_yield(&sense_pt);
#include <boost/counter_inc.h>

		}

		pt_yield(&sense_pt);
#include <boost/counter_inc.h>
	}

END:
	pt_end(&sense_pt);
}

/* ----------------------------------------- hd44780 ---------------------------------------- */

static uint8_t display_custom_msg[16+1] = {0};
static uint8_t display[2][16+1];
static uint8_t display_state_next = 0; /* increment this to update display */
static uint8_t display_state_cur = 0xFF;

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
			sprintf(display, "lm=%u", TSL2561_getLuminosity(2));
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

	++display_state_next;
	display_state_cur = display_state_next;
	return;/* success */

DISPLAY_RESET_STATE:
	*display = '\0';
	display_state_next = 0;
	display_state_cur = 0xFF;
	return;
}

static void display_thread()
{
	static struct pt_s display_pt = pt_init();
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);

#include <boost/counter_reset.h>
	pt_begin(&display_pt);

	// initialization
	hd44780_init();
	printf("hd44780 initialized.\n");

	pt_yield(&display_pt);
#include <boost/counter_inc.h>


	while(1) {

		SYSTICK_TIMEOUT_SET( Tickstop, 2000 );
		pt_wait_while( &display_pt,
				display_state_cur == display_state_next && !SYSTICK_TIMEOUT_ELAPSED( Tickstop, 2000 ) );
#include <boost/counter_inc.h>

		// update hd44780
		hd44780_clrscr_all();
		for(uint8_t col = 0; col < 2; ++col) {

			display_update(display[col]);

			hd44780_set_cursor_rowcol(0, 0, col);
			for(uint8_t i = 0; i < 16; ++i) {
				uint8_t temp = display[col][i];
				if ( temp == '\0' ) {
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

#define LUMINOSITY_DEBUG(printf_args) //DEBUG_MAIN("LUMINOSITY:", printf_args)
static uint16_t luminosity;
static void luminosity_thread()
{
	static struct pt_s luminosity_pt = pt_init();
	static SYSTICK_TIMEOUT_DECLARE(Tickstop);
	static SYSTICK_TIMEOUT_DECLARE(Timeout);

#include <boost/counter_reset.h>
	pt_begin(&luminosity_pt);

	TSL2561_init(TSL2561_ADDR_FLOAT);
	TSL2561_begin();
	printf("TLS2561 initialized.\n");

	pt_yield(&luminosity_pt);
#include <boost/counter_inc.h>

	while(1) {
		TSL2561_getLuminosity_nonblock_start();
		SYSTICK_TIMEOUT_SET(Tickstop, 600);
		LUMINOSITY_DEBUG(("nonblock start tick=%u tickstop=%u", systickGet(), Tickstop));
		pt_wait_while( &luminosity_pt, !SYSTICK_TIMEOUT_ELAPSED( Tickstop, 600 ) );
#include <boost/counter_inc.h>

		uint16_t temp;
		temp = TSL2561_getLuminosity_nonblock_stop(2);
		if ( temp != 0 ) {
			luminosity = temp;
		}
		LUMINOSITY_DEBUG(("noblock stop temp=%u luminosity=%u", temp, luminosity));

		SYSTICK_TIMEOUT_SET(Tickstop, 200);
		LUMINOSITY_DEBUG(("empty wait tick=%u tickstop=%u", systickGet(), Tickstop));
		pt_wait_while( &luminosity_pt, !SYSTICK_TIMEOUT_ELAPSED( Tickstop, 200 ) );
#include <boost/counter_inc.h>

		pt_yield(&luminosity_pt);
#include <boost/counter_inc.h>
	}

	pt_end(&luminosity_pt);
}

/* ---------------------------------------- interaction -------------------------------------- */

uint8_t report_luminosity = 0;
void cmdlineService_callback(void)
{
	uint8_t i;
	char *token;

	// print received string
	printf("R:");
	for( i = 0; i <= cmdline.buffpos; ++i) {
		printf("%c", cmdline.buff[i]);
	}
	printf("\n");

	// parse command line
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
			printf("FAN[%u]=%u\n", i, fanSpeeds[i]);
		}
		for( i = 0; i < sense_count; ++i) {
			printf("ds18x20(%u)=%d\n", i, sense_val[i]);
		}
		for( i = 0; i < 2; ++i) {
			printf("hd44780(%u)=\"%s\"\n", i, display[i]);
		}
		printf("\n");
		break;
	case 'f': {
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
	}	break;
	case 'l': {
		token = strtok(&cmdline.buff[2], " ");
		if ( token == NULL ) {
			printf("%u\n", luminosity);
		} else {
			report_luminosity = atoi(token);
			if ( report_luminosity > 30 ) {
				printf("error report_luminosity=%u must be lower then 30\n", report_luminosity);
				report_luminosity = 0;
			}
			printf("Reporting luminosity every %u seconds\n", report_luminosity);
		}
	}	break;
	case 'd':
		strncpy(display_custom_msg, &cmdline.buff[2], MIN(sizeof(display_custom_msg)/sizeof(*display_custom_msg), cmdline.buffpos));
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
				"l NUM             - report lumination value every NUM seconds\n"
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
	static struct pt_s app_thread_pt = pt_init();
	static uint8_t last;

#include <boost/counter_reset.h>
	pt_begin(&app_thread_pt);

	TRISAbits.RA0 = TRIS_OUT;
	TRISAbits.RA1 = TRIS_OUT;
	TRISAbits.RA2 = TRIS_OUT;
	PORTAbits.RA0 = 0;
	PORTAbits.RA1 = 0;
	PORTAbits.RA2 = 0;

	last = !PORTCbits.RC2;
	printf("RC2=%x\n", PORTCbits.RC2);

	while(1) {
		pt_yield(&app_thread_pt);
#include <boost/counter_inc.h>
		if ( last != PORTCbits.RC2 ) {
			last = PORTCbits.RC2;
			printf("RC2=%x\n", last);
		}
	}
	pt_end(&app_thread_pt);
}


unsigned char pcf8574_hd44780_freepin = 0; // referenced by hd44780-config.h
void diode_thread(void)
{
	static SYSTICK_TIMEOUT_DECLARE(Timeout);

	if ( SYSTICK_TIMEOUT_ELAPSED(Timeout, 1000 ) ) {
		SYSTICK_TIMEOUT_SET(Timeout, 1000);
		pcf8574_hd44780_freepin ^= 0x01;
		PCF8574_WRITE(HD44780_PCF8574, 0x00 | pcf8574_hd44780_freepin);
	}
}

void report_luminosity_thread(void)
{
	static SYSTICK_TIMEOUT_DECLARE(Timeout);
	static uint16_t value = 0;

	if ( report_luminosity ) {
		if ( SYSTICK_TIMEOUT_ELAPSED(Timeout, value) ) {
			value = (uint16_t)report_luminosity*1000;
			SYSTICK_TIMEOUT_SET(Timeout, value);
			printf("\n# luminosity=%u\n", luminosity);
		}
	}
}

/* ----------------------------------------------------------------------------------------- */

void main_preinit(void)
{
	// wait for PLL HS oscillator
	//while( OSCCONbits.OSTS == 0 );
	// set all ports as inputs
	CONFIG_ALL_PORTS_AS_INPUTS();
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

void main(void)
{
	EEPROM_WRITE(0x01,0x01);
	main_preinit();

	TRIS1(USB_BUS_SENSE_PORTPIN) = TRIS_IN;
	usbStdioInitBlocking(1);
	systickInitInterrupt(0);
	smbus_open_master(100000);

	printf("USB Startup completed.\n");
	__delay_ms(4000);
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

		diode_thread();

		report_luminosity_thread();

		usbStdioService();

		cmdlineService_nonblock();

	}
}

