/*
 * test_systick.c
 *
 *  Created on: 20 lip 2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */
#include "system.h"

#if CFG_TEST == CFG_TEST_SYSTICK

#include <xc.h>

#include <mdb.h>
#include <systick.h>
#include <stdio.h>

#include "xc_ex.h"

#include <stdint.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>


/* ------------------------------------- interrupts ------------------------------ */

void __interrupt(high_priority) SYS_InterruptHigh(void)
{
}

void __interrupt( low_priority) SYS_InterruptLow(void)
{
	systickServiceInterrupt();
}

/* ----------------------------------------------------------------------------------------- */

systick_t globaltick;
uint16_t  globalms;
void test1(void)
{
	globaltick = SYSTICK_MS_TO_SYSTICKS(500);
}
void test2(void)
{
	globalms = XC8PP_LONG_MULTI * (1000)*(500)*(16)/(256);
	globalms = SYSTICK_SYSTICKS_TO_MS(500);
	globalms = SYSTICK_MS_TO_SYSTICKS(500);
}
void test3(uint16_t ms)
{
	globaltick = SYSTICK_MS_TO_SYSTICKS(ms);
}
void test4(systick_t tick)
{
	globalms = SYSTICK_SYSTICKS_TO_MS(tick);
}

void main_test()
{
	systickInitInterrupt(0);

	while(1) {
#define LAZY1(n1) printf("globalms = %u (= %u)\n", globalms, n1)

		test2();
		LAZY1(31250);
		test4(500);
		LAZY1(31250);

		for(unsigned char i=0; i<4; ++i) {
			printf("systick = %u \n", systickGet());
			__delay_ms(100);
		}

		SYSTICK_TIMEOUT_DECLARE(Tickstop);
		while(1) {
			if ( SYSTICK_TIMEOUT_ELAPSED(Tickstop, 500) ) {
				SYSTICK_TIMEOUT_SET(Tickstop, 500);

				printf("systick elapsed = %u \n", systickGet());
			}
		}
	}
}

#endif
