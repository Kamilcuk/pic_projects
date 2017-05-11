/*
 *        File: assert.c
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <assert.h>

#include <system.h> // configuration - ASSERT_USE_*
#include <xc.h> // __delay_ms
#include <soft_return_address_stack.h> // ReturnAddressStack_Clear

#if defined( ASSERT_USE_MORSE )

#include "morse.h" // morse_send_string morse_send_char

void _my_assert(const unsigned char *line, const unsigned char *file, const unsigned char *exp)
{
	ReturnAddressStack_Clear();
	for(;;) {
		morse_send_char('(');
		morse_send_string(line);
		morse_send_char(':');
		morse_send_string(file);
		morse_send_char(':');
		morse_send_string(exp);
		morse_send_char(')');
		__delay_ms(100);
	}
}


#elif defined( ASSERT_USE_PRINTF )

#include <stdio.h> // cputs

void _my_assert(const unsigned char *line, const unsigned char *file, const unsigned char *exp)
{
	ReturnAddressStack_Clear();
	for(;;) {
		cputs("assert failed: ");
		cputs(line);
		cputs(" line ");
		cputs(file);
		cputs(": \"");
		cputs(exp);
		cputs("\"\n");
		__delay_ms(100);
	}
}

#endif
