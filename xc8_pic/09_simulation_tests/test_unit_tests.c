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
#include <plib/timers.h>

#include "hd44780.h"
#define PINPOINTER_TEST 1
#include "pinpointer.h"
#include "fifo.h"

struct {
		uint8_t *name;
		void (*func)();
} tests[] = {
#define _(x) { #x , x }
		_( hd44780_unit_tests ),
		_( hd44780_hw_tests ),
		_( pinpointer_test ),
		_( FifoTest ),
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
	printf("SUCCESS!");
	for(;;);
}

#endif
