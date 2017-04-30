/*
 * assert.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef XC8_PIC_INCLUDE_ASSERT_H_
#define XC8_PIC_INCLUDE_ASSERT_H_

#include <system.h>

#if  defined( USE_ASSERT_MORSE )

#include "morse.h" // morse_send_string
#include "cdefs.h" // __XSTRING

#define assert(expr) do{ if(!(expr)) { \
	for(;;) { \
		morse_send_string(__XSTRING(__LINE__) ":" __XSTRING(expr) ".assert failed:" __XSTRING(__FILE__) ":" ); \
	} \
} }while(0)

#elif defined( USE_ASSERT_PRINTF )

#include <stdio.h> // putchar

#define assert(expr) do{ \
	if(!(expr)) { \
		for(unsigned char _a_i = 3; _a_i; --_a_i) { \
			static const unsigned char _a_str[] = \
"assert failed:" __XSTRING(__FILE__) ":" __XSTRING(__LINE__) ":" __XSTRING(expr) ".\n" ;\
			const unsigned char *_a_pnt = _a_str; \
			unsigned char _a_c; \
			for(;;) { \
				_a_c = *_a_pnt; \
				if ( !_a_c ) { \
					break; \
				} \
				putchar(_a_c); \
				++_a_pnt; \
			} \
		} \
		for(;;); \
	} \
}while(0)

#else

#define assert(expr)

#endif

#endif /* XC8_PIC_INCLUDE_ASSERT_H_ */
