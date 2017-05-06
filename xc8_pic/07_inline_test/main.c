/*
 * main.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>
#include <mdb.h>
#include <stdio.h>

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{    
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

/* ----------------------------------------------------------------------------------------- */

inline unsigned long  inline_func_pro(unsigned long a) 
{
	return a*1000;
}


volatile char a;
inline void inline_func_with_global_var(void)
{
	++a;
	printf("inline func_with_global_var %d \n", a);
}

inline void simple_inline_func(void) {
	static int whatever = 0;
	int k;
	++whatever;
	for(k=0;k<10;++k);
	printf("simple_inline_func %d %d \n", k, whatever);
}

MDB_UART_PUTCH_DECLARE()

void main(void)
{
	unsigned long b = 1000; 
	MDB_UART_INIT();
	
	printf("Startup \n");

	inline_func_with_global_var();
	simple_inline_func();
	inline_func_with_global_var();
	simple_inline_func();
	inline_func_with_global_var();
	simple_inline_func();

	printf(" %lu \n", inline_func_pro(b));
	b += 10000;
	printf(" %lu \n", inline_func_pro(b));
	
	while(1) {
	}
}

