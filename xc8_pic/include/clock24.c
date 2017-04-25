/*
 * clock24.c
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "clock24.h"

#include <limits.h>
#include <stdio.h>

struct clock24_s clock24 = {0,0,0};

static void clock24Increment(void)
{
	if ( clock24.sec < 60-1 ) {
		++clock24.sec;
	} else {
		clock24.sec = 0;
		if ( clock24.min < 60-1 ) {
			++clock24.min;
		} else {
			clock24.min = 0;
			if ( clock24.hour < 24-1 ) {
				++clock24.hour;
			} else {
				clock24.hour = 0;
			}
		}
	}
}

void clock24ServiceInterrupt_in(void)
{
#if CLOCK_COUNTER_SECOND == 1
	clock24Increment();
#else
	static unsigned char clockIntCounter = 0;

	if ( clockIntCounter < CLOCK_COUNTER_SECOND-1 ) {
		++clockIntCounter;
	} else {
		clockIntCounter = 0;
		clock24Increment();
	}
#endif
}

signed char clock24DifftimeSCHAR(struct clock24_s clock1, struct clock24_s clock0)
{
	signed char secdiff;
	if ( clock1.hour != clock0.hour ) {
		return (signed char)( clock1.hour > clock0.hour ? SCHAR_MAX : SCHAR_MIN );
	}
	secdiff = (signed char)(((signed char)clock0.sec) - ((signed char)clock1.sec));
	if ( clock1.min != clock0.min ) {
		signed char mindiff;
		signed char sign;
		if ( clock1.min > clock0.min ) {
			mindiff = (signed char)(((signed char)clock1.min) - ((signed char)clock0.min));
			sign = +1;
		} else {
			mindiff = (signed char)(((signed char)clock0.min) - ((signed char)clock1.min));
			sign = -1;
		}
		unsigned int temp = (mindiff * 60) + secdiff;
		return (signed char)(
				( temp > SCHAR_MAX ) ?
						( sign == +1 ? SCHAR_MAX : SCHAR_MIN )
						:
						( sign == +1 ? (signed char)temp : -(signed char)temp )
		);
	}
	return secdiff;
}

void clock24Printf(struct clock24_s clock24)
{
	printf("clock24: %u:%u:%u\n",
			clock24.hour, clock24.min, clock24.sec);
}

void clock24_main_test(void)
{

#define LAZY( h1, m1, s1, h0, m0, s0, val ) do{ \
		struct clock24_s t1 = {s1, m1, h1}; \
		struct clock24_s t2 = {s0, m0, h0}; \
		printf("clock24DifftimeSCHAR("#h1":"#m1":"#s1" , "#h0":"#m0":"#s0") = %d ==? %d \n", clock24DifftimeSCHAR( t1, t2 ), val ); \
} while(0)

		LAZY(0,0,0, 1,0,0, -128);
		LAZY(1,0,0, 1,0,0, 0);
		LAZY(2,0,0, 1,0,0, 127);
		LAZY(1,1,0, 1,0,0, 60);
		LAZY(1,1,0, 1,2,0, -60);
		LAZY(1,1,1, 1,1,0, -1);
		LAZY(1,1,1, 1,1,2, 1);
		LAZY(1,0,1, 1,1,2, -61);
		LAZY(1,2,1, 1,1,1, 60);
		LAZY(1,10,20, 1,1,10, 127);
		LAZY(1,1,10, 1,10,20, -128);
		LAZY(1,2,10, 1,3,20, -70);
		LAZY(1,3,10, 1,2,20, 70);
#undef LAZY

}
