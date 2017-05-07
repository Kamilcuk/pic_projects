/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <mdb.h>
#include <systick.h>
#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{
}

void interrupt  low_priority SYS_InterruptLow(void)
{
	systickServiceInterrupt();
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

systick_t globaltick;
uint16_t  globalms;
void test1(void)
{
	globaltick = SYSTICK_MS_TO_SYSTICKS(500);
}
void test2(void)
{
	globalms = (1000)*(500)*(16)/(256);
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

MDB_UART_PUTCH_DECLARE()
void main(void)
{
	main_preinit();
	MDB_UART_INIT();
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
			if ( SYSTICK_TIMEOUT_ELAPSED(Tickstop) ) {
				SYSTICK_TIMEOUT_SET(Tickstop, 500);

				printf("systick elapsed = %u \n", systickGet());
			}
		}
	}
}

