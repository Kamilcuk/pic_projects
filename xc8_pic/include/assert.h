/*
 * assert.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef XC8_PIC_INCLUDE_ASSERT_H_
#define XC8_PIC_INCLUDE_ASSERT_H_

#include <system.h> // configuration - ASSERT_USE_*

#include "cdefs.h" // __XSTRING

#if defined( ASSERT_USE_MORSE ) || defined( ASSERT_USE_PRINTF )

#define assert(expr) if(!(expr)) { _my_assert(__XSTRING(__LINE__), __FILE__, __XSTRING(expr)); }

#else

#define assert(expr)

#endif

void _my_assert(const unsigned char *line, const unsigned char *file, const unsigned char *exp);

#endif /* XC8_PIC_INCLUDE_ASSERT_H_ */
