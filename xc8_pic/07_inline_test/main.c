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
#include <stdint.h>
#include <stdio.h>

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

uint32_t globalretvar;
uint8_t inline inline_func_ret8(void)
{
	return globalretvar&0x000000ff;
}
uint16_t inline inline_func_ret16(void)
{
	return globalretvar&0x0000ffff;
}
uint32_t inline inline_func_ret32(void)
{
	return globalretvar;
}
uint32_t inline inline_func_ret32_calc(uint32_t a)
{
	return globalretvar * 10 * a / 10;
}


inline void inline_big(void)
{
	uint32_t localvar;
	localvar = 0xfffff;

}

MDB_UART_PUTCH_DECLARE()


#define PRINT_TEST_1(fun, str) printf( #fun " = " str "\n", fun() )
#define PRINT_TEST_2(fun, str, par1, par1str) printf( #fun "(" par1str ") = " str "\n", par1, fun(par1) )

void main(void)
{
	uint32_t b;
	MDB_UART_INIT();
	
	printf("Startup \n");

	inline_func_with_global_var();
	simple_inline_func();

	inline_func_with_global_var();
	simple_inline_func();

	inline_func_with_global_var();
	simple_inline_func();

	b = 2;
	globalretvar = 33554432;
	PRINT_TEST_1( inline_func_ret8, "%u" );
	PRINT_TEST_1( inline_func_ret16, "%u" );
	PRINT_TEST_1( inline_func_ret32, "%lu" );
	PRINT_TEST_2( inline_func_ret32_calc, "%lu", b, "%lu" );

	b = 10;
	PRINT_TEST_1( inline_func_ret8, "%u" );
	PRINT_TEST_1( inline_func_ret16, "%u" );
	PRINT_TEST_1( inline_func_ret32, "%lu" );
	PRINT_TEST_2( inline_func_ret32_calc, "%lu", b, "%lu" );
	
	while(1) {
	}
}

