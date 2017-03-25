/*
 * assert.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef XC8_PIC_INCLUDE_ASSERT_H_
#define XC8_PIC_INCLUDE_ASSERT_H_

#include "system.h"

#ifdef USE_FULL_ASSERT

#include "morse.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)
#define ASSERT_PARAM(expr) do{ \
	if( !(expr) ) \
		for(;;) \
			morse_send_string( STR(__LINE__) ":" STR(expr) ".assert failed:" __FILE__ ":" ); \
}while(0)

#endif

#endif /* XC8_PIC_INCLUDE_ASSERT_H_ */
