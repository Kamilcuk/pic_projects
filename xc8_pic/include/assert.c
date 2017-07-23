/*
 *        File: assert.c
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
 */
#include <system.h> // configuration - ASSERT_USE_*

#include <assert.h>
#include <return_address_stack.h> // ReturnAddressStack_Clear

#include <xc.h> // __delay_ms

#if defined( ASSERT_USE_MORSE )

#include "morse.h" // morse_send_string morse_send_char
#include <stdio.h> // sprintf

void __assert(const char *__assertion, const char *__file, int __line)
{
	char __line_buff[6];
	sprintf(__line_buff, "%u", __line);

	ReturnAddressStack_clear();
	for(;;) {
		morse_send_char('(');
		morse_send_string(__line_buff);
		morse_send_char(':');
		morse_send_string(__file);
		morse_send_char(':');
		morse_send_string(__assertion);
		morse_send_char(')');
		__delay_ms(100);
	}
}


#else // if defined( ASSERT_USE_PRINTF )

#include <stdio.h> // cputs sprintf

void __assert(const char *__assertion, const char *__file, unsigned int __line)
{
	char __line_buff[6];
	sprintf(__line_buff, "%u", __line);

	ReturnAddressStack_clear();
	for(;;) {
		cputs("assert failed: ");
		cputs(__line_buff);
		cputs(" line ");
		cputs(__file);
		cputs(": \"");
		cputs(__assertion);
		cputs("\"\n");
		__delay_ms(100);
	}
}

#endif

#ifdef __XC8

void _fassert(int line, const char * file, const char *exp)
{
	__assert(exp, file, line);
}

#endif // __XC8
