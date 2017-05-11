/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <cmdline.h>

#include <hd44780.h>
#include <common.h>
#include <bit.h>

#include "usbhid_stdio/usbhid_stdio.h"

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{    
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

/* ---------------------------------------- interaction -------------------------------------- */

void cmdlineService_callback(void)
{
	switch(cmdline.buff[0]) {
	case 'h': case 'H': case 'v': case 'V': // usage and version
		printf(
				"\n"
				"This is HD44780 test firmware\n"
				"\n"
		);
		/* no break */
	default:
		cmdlineService_standard();
		break;
	}
}

/* ----------------------------------------------------------------------------------------- */

void main_preinit(void)
{
	// set all ports as inputs
	PORTA = PORTB = PORTC = 0x00;
	TRISA = TRISB = TRISC = 0xff;
	LATA = LATB = LATC = 0x00;
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

extern unsigned char hd44780_checker_curpos[HD44780_NUM_CONTROLLERS];
uint8_t str[82] = "Czesc Eliza! Kocham Cie! The quick brown fox jumps over the lazy dog ,./'; []-=\\";

void main_test1(void)
{
	hd44780_clrscr_all();
	for(uint8_t j = 0; j<HD44780_NUM_CONTROLLERS; ++j) {
		uint8_t c, i = 0;
		for(; i < ARRAY_SIZE(str)-1 && (c = str[i]); ++i) {
			hd44780_write_data(j, c);
		}
		printf("checker curpos: %u =? %u =? %x\n", hd44780_checker_curpos[j], i, hd44780_get_rawcurpos(j));
	}

#define TEST_PRINTF(printf_arg) printf printf_arg
#define TEST_DISPLAY 0
	hd44780_set_rawcurpos(TEST_DISPLAY, hd44780_curpos_to_raw(0));
	TEST_PRINTF(("checker curpos: %u =? 0 =? %x\n", hd44780_checker_curpos[TEST_DISPLAY], hd44780_get_rawcurpos(TEST_DISPLAY)));
	printf("Recv 1line:");
	for(uint8_t i=0;i<20;++i) {
		printf("%c", hd44780_read_data(TEST_DISPLAY));
	}
	printf("\n");

	uint8_t curposs[] = { 0, 10, 20, 30, 40, 50, 60, 70, 39, 79 };
	for(uint8_t i=0;i<ARRAY_SIZE(curposs);++i) {
		uint8_t curpos = curposs[i];
		uint8_t rawcurpos = hd44780_curpos_to_raw(curpos);
		uint8_t row = hd44780_row_from_rawcurpos(rawcurpos);
		uint8_t col = hd44780_col_from_rawcurpos(rawcurpos);

		TEST_PRINTF(("curpos=%u rawcurpos=0x%x rowcol=%u,%u rowcol_to_rawcurpos=%u from_raw=%u to_raw_from_raw=0x%x\n",
				curpos,
				rawcurpos,
				row, col,
				hd44780_rowcol_to_rawcurpos(row, col),
				hd44780_curpos_from_raw(rawcurpos),
				hd44780_curpos_to_raw(hd44780_curpos_from_raw(rawcurpos))
		));
		hd44780_set_rawcurpos(TEST_DISPLAY, rawcurpos);
		rawcurpos = hd44780_get_rawcurpos(TEST_DISPLAY);
		TEST_PRINTF(("checker curpos: %u =? %u =? %u =? 0x%x\n",
				hd44780_checker_curpos[TEST_DISPLAY], curposs[i], hd44780_curpos_from_raw(rawcurpos), rawcurpos));
		hd44780_write_data(TEST_DISPLAY, '|');
	}
	TEST_PRINTF(("checker curpos: %u =? 0 =? %x\n", hd44780_checker_curpos[TEST_DISPLAY], hd44780_get_rawcurpos(TEST_DISPLAY)));

	hd44780_set_rawcurpos(TEST_DISPLAY, 0x40);
	printf("Recv 2line:");
	for(uint8_t i=0;i<10;++i) {
		printf("%c", hd44780_read_data(TEST_DISPLAY));
	}
	printf("\n");

	for(uint8_t i=0;i<HD44780_NUM_CONTROLLERS; ++i) {
		printf("hd44780_checker_state[%u]:\"", i);
		for(uint8_t j=0; j<HD44780_DISP_SIZE;++j) {
			printf("%c", hd44780_checker_state[i][j]);
		}
		printf("\"\n");
	}

	printf("Checker!\n");
	hd44780_checker_check();

	// rotate str
	unsigned char temp = str[0];
	for(uint8_t i=0;i<80;++i) {
		str[i] = str[i+1];
	}
	str[79] = temp;
	str[81] = '\0';

#if HD44780_COUNTERS
	for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
		printf("hd[%u] nobfcheck:%u write:%u read:%u bfchecks:%u errors:%u\n",
				i,
#if !HD44780_NO_BF_CHECKING
				BIT_READ(hd44780.nobfcheck,i),
#else
				1,
#endif
				hd44780.write_count[i],
				hd44780.read_count[i],
#if !HD44780_NO_BF_CHECKING
				hd44780.bfchecks_count[i],
#else
				0,
#endif
				hd44780.errors_count[i]
		);
	}
	printf("\n");
	printf("\n");
#endif

	__delay_ms(1000);
}

void main(void)
{
	main_preinit();

	usbStdioInitBlocking(1);

	__delay_ms(500);
	printf("usb startup completed\n");

	hd44780_init();
	printf("hd44780_init() completed\n");

	while(1) {
		main_test1();
		cmdlineService_nonblock();
	}
}

