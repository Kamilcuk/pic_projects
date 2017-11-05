/*
 * test_fifo.c
 *
 *  Created on: 20 lip 2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */

#include "system.h"

#if CFG_TEST == CFG_TEST_UNIT_TESTS

#include "common.h"

#include <stdio.h>
#include <stdint.h>
#include <stdint_ex.h>
#include <plib/timers.h>

#include "hd44780.h"
#define PINPOINTER_TEST 1
#include "pinpointer.h"
#include "fifo.h"

void printf_test()
{
	{
		int8_t a = 0xab;
		printf(" %02x \n", (uint8_t)a);
		printf(" %d \n", a);
	}
	{
		uint8_t a = 0xab;
		printf(" %02x \n", a);
		printf(" %u \n", a);
	}
	{
		int16_t a = 0xabcd;
		printf(" %04x \n", a);
		printf(" %d \n", a);
	}
	{
		uint16_t a = 0xabcd;
		printf(" %04x \n", a);
		printf(" %u \n", a);
	}
	{
		int24_t a = 0xabcdef;
		printf(" %06lx \n", (uint32_t)a);
		printf(" %ld \n", (int32_t)a);
	}
	{
		uint24_t a = 0xabcdef;
		printf(" %06lx \n", (uint32_t)a);
		printf(" %lu \n", (uint32_t)a);
	}
	{
		int32_t a = 0xabcdef12;
		printf(" %08lx \n", a);
		printf(" %ld \n", a);
	}
	{
		uint32_t a = 0xabcdef12;
		printf(" %08lx \n", a);
		printf(" %lu \n", a);
	}
}

#include "printft.h"

void printft_test()
{
	{
		int8_t a = 0xab;
		printft(" %02x \n", (uint16_t)a);
		printft(" %d \n", a);
	}
	{
		uint8_t a = 0xab;
		printft(" %02x \n", a);
		printft(" %u \n", a);
	}
	{
		int16_t a = 0xabcd;
		printft(" %04x \n", a);
		printft(" %d \n", a);
	}
	{
		uint16_t a = 0xabcd;
		printft(" %04x \n", a);
		printft(" %u \n", a);
	}
	{
		int24_t a = 0xabcdef;
		printft(" %06lx \n", (int32_t)a);
		printft(" %ld \n", (int32_t)a);
	}
	{
		uint24_t a = 0xabcdef;
		printft(" %06lx \n", (uint32_t)a);
		printft(" %lu \n", (uint32_t)a);
	}
	{
		int32_t a = 0xabcdef12;
		printft(" %08lx \n", a);
		printft(" %ld \n", a);
	}
	{
		uint32_t a = 0xabcdef12;
		printft(" %08lx \n", a);
		printft(" %lu \n", a);
	}
}


struct {
		uint8_t *name;
		void (*func)();
} tests[] = {
#define _(x) { #x , x }
//		_( printf_test ),
//		_( printft_test ),
//		_( hd44780_unit_tests ),
//		_( hd44780_hw_tests ),
//		_( pinpointer_test ),
//		_( FifoTest ),
#undef _
};

void main_test()
{
	for(uint8_t i=0; i<sizeof(tests)/sizeof(*tests); ++i) {
		COMMON_MAIN_PREINIT();
		printf("Test num %d named \"%s\": Running.\n", i, tests[i].name);
		OpenTimer1( T1_16BIT_RW & TIMER_INT_OFF & T1_PS_1_8 & T1_SOURCE_INT & T1_SYNC_EXT_OFF );
		tests[i].func();
		const uint16_t ticks  = ReadTimer1();
		printf("Test num %d named \"%s\": Succeded in %u ticks.\n", i, tests[i].name, ticks);
	}
	printf("SUCCESS\n");
	printf("QUIT\n");
	for(;;);
}

#endif
