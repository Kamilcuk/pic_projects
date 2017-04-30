/*
 * main.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{    
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

/* ----------------------------------------------------------------------------------------- */

volatile char a;
inline void inline_func_with_global_var(void)
{
	// set all ports as inputs
	PORTA = PORTB = PORTC = 0x00;
	TRISA = TRISB = TRISC = 0xff;
	LATA = LATB = LATC = 0x00;
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;

	for(int i=0;i<10;++i) {
		a=i;
	}
}

inline void simple_inline_func(void) {
	static whatever = 0;
	whatever = 1;
	for(int k=0;k<10;++k);
}

void main(void)
{
	inline_func_with_global_var();
	simple_inline_func();
	inline_func_with_global_var();
	simple_inline_func();
	inline_func_with_global_var();
	simple_inline_func();
	
	while(1) {
	}
}

