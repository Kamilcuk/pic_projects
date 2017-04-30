/*
 * main.c
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <cmdline.h>
#include <soft_return_address_stack.h>
#include <reset_vector.h>

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

#include "usbhid_stdio/usbhid_stdio.h"

/* ------------------------------------- interrupts ------------------------------ */

RESET_VECTOR_DECLARE       ( SYS_InterruptReset )
{
	RESET_VEC_clear_flags();
}

void interrupt high_priority SYS_InterruptHigh(void)
{    
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

/* ----------------------------------------------------------------------------------------- */

// this is insaine

uint16_t calllevel = 0;

static const uint8_t printfstr[] = "%u\n";
void f_PRE() {
	printf(printfstr, calllevel);
	++calllevel;
	__delay_ms(50);
}
void f_POST() {
	__delay_ms(50);
	--calllevel;
	printf(printfstr, calllevel);
}
#define FUNCBODY( name1, name2 )\
	f_PRE();\
	f ## name2();\
	f_POST();

#define FUNC( name1, name2 ) \
	void f ## name2();\
	void f ## name1(){\
		FUNCBODY( name1 , name2 )\
	}

#define FUNC_SAVE( name1, name2 ) \
	void f ## name2();\
	void f ## name1(){\
		SoftReturnAddressStack_push(); \
		FUNCBODY( name1 , name2 )\
		SoftReturnAddressStack_pop(); \
	}

#define FUNCS_10( name1 , name2 ) \
		FUNC( name1 ## 0, name1 ## 1 ) \
		FUNC( name1 ## 1, name1 ## 2 ) \
		FUNC( name1 ## 2, name1 ## 3 ) \
		FUNC( name1 ## 3, name1 ## 4 ) \
		FUNC( name1 ## 4, name1 ## 5 ) \
		FUNC( name1 ## 5, name1 ## 6 ) \
		FUNC( name1 ## 6, name1 ## 7 ) \
		FUNC( name1 ## 7, name1 ## 8 ) \
		FUNC( name1 ## 8, name1 ## 9 ) \
		FUNC_SAVE(name1 ## 9, name2 ## 0)

void f_1() {
	printf("<- f_START()\n" );
	void f0000();
	f0000();
}
FUNCS_10( 000 , 001 )
FUNCS_10( 001 , 002 )
FUNCS_10( 002 , 003 )
FUNCS_10( 003 , 004 )
FUNCS_10( 004 , 005 )
FUNCS_10( 005 , 006 )
FUNCS_10( 006 , 007 )
FUNCS_10( 007 , 008 )
FUNCS_10( 008 , 009 )
FUNCS_10( 009 , 010 )
FUNCS_10( 010 , 011 )
FUNCS_10( 011 , 012 )
FUNCS_10( 012 , 013 )
FUNCS_10( 013 , 014 )
FUNCS_10( 014 , 015 )
FUNCS_10( 015 , 016 )
FUNCS_10( 016 , 017 )
FUNCS_10( 017 , 018 )
FUNCS_10( 018 , 019 )
FUNCS_10( 019 , 020 )
void f0200() {
	printf("<- f_END()\n" );
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

void main(void)
{
	main_preinit();

	usbStdioInitBlocking(1);

	__delay_ms(500);\
	printf("Startup completed.\n");

	while(1) {
		f_1();
	}
}

