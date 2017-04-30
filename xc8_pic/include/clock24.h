/*
 * clock24.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef CLOCK24_H_
#define CLOCK24_H_

#include <system.h>

#define CLOCK_USE_TIMER0 1

/* ----------------------------------- timer config ------------------------------------- */

#if   defined( CLOCK_USE_TIMER0 )

#define CLOCK_TIMER_IF INTCONbits.TMR0IF
#define CLOCK_TIMER_H              TMR0H
#define CLOCK_TIMER_L              TMR0L
#define CLOCK_TIMER_PRESCALER        256

/**
 * timer for clock24 and initializes clock24 structs
 */
#define clock24InitInterrupt(interruptPriority) do{ \
	OpenTimer0( T0_16BIT & TIMER_INT_ON & T0_PS_1_256 & T0_SOURCE_INT & T0_EDGE_FALL ); \
	INTCON2bits.TMR0IP = interruptPriority; \
	CLOCK_TIMER_H = CLOCK_TIMER_WRITE_VALUE_H; \
	CLOCK_TIMER_L = CLOCK_TIMER_WRITE_VALUE_L; \
}while(0)

#elif defined( CLOCK_USE_TIMER3 )

#include "timers.h"

#define CLOCK_TIMER_IF  PIR2bits.TMR3IF
#define CLOCK_TIMER_H             TMR3H
#define CLOCK_TIMER_L             TMR3L
#define CLOCK_TIMER_PRESCALER         8

/**
 * timer for clock24 and initializes clock24 structs
 */
#define clock24InitInterrupt(interruptPriority) do{ \
	OpenTimer3( T3_16BIT_RW & TIMER_INT_ON & T3_PS_1_8 & T3_SOURCE_INT & T3_SYNC_EXT_OFF ); \
	IPR2bits.TMR3IP = interruptPriority; \
	CLOCK_TIMER_H = CLOCK_TIMER_WRITE_VALUE_H; \
	CLOCK_TIMER_L = CLOCK_TIMER_WRITE_VALUE_L; \
}while(0)

#else
#error TODO: define CLOCK_USE_TIMER x ? implement more timers
#endif

/* ---------------------------------- speed config --------------------------------------- */

#if   _XTAL_FREQ == 48000000 && CLOCK_TIMER_PRESCALER == 8

#define CLOCK_FREQ                    1500000 // (_XTAL_FREQ/(4*CLOCK_TIMER_PRESCALER))
#define CLOCK_TIMER_VALUE               60000 // arbitary chosen
#define CLOCK_TIMER_WRITE_VALUE          5536 // 2^16 - CLOCK_TIMER_VALUE
#define CLOCK_TIMER_WRITE_VALUE_H          21 // CLOCK_TIMER_WRITE_VALUE/2^8
#define CLOCK_TIMER_WRITE_VALUE_L         160 // CLOCK_TIMER_WRITE_VALUE%2^8
#define CLOCK_INTERRUPT_INTERVAL_MS        40 // CLOCK_TIMER_VALUE / CLOCK_FREQ
#define CLOCK_COUNTER_SECOND               25 // 1000 / CLOCK_INTERRUPT_INTERVAL_MS

#elif _XTAL_FREQ == 48000000 && CLOCK_TIMER_PRESCALER == 256

#define CLOCK_FREQ                      46875 // (_XTAL_FREQ/(4*CLOCK_TIMER_PRESCALER))
#define CLOCK_TIMER_VALUE               46875 // arbitary chosen
#define CLOCK_TIMER_WRITE_VALUE         18661 // 2^16 - CLOCK_TIMER_VALUE
#define CLOCK_TIMER_WRITE_VALUE_H          72 // CLOCK_TIMER_WRITE_VALUE/2^8
#define CLOCK_TIMER_WRITE_VALUE_L         229 // CLOCK_TIMER_WRITE_VALUE%2^8
#define CLOCK_INTERRUPT_INTERVAL_MS      1000 // CLOCK_TIMER_VALUE / CLOCK_FREQ
#define CLOCK_COUNTER_SECOND                1 // 1000 / CLOCK_INTERRUPT_INTERVAL_MS

#else
#error TODO: define CLOCK_FREQ and or CLOCK_TIMER_PRESCALER
#endif

/* -------------------------------------------------------------------------------------- */

/**
 *
 */
struct clock24_s {
	unsigned char sec;  //  Seconds [0,59]. - no leap seconds
	unsigned char min;  //  Minutes [0,59].
    unsigned char hour; //  Hour [0,23].
};

/**
 *
 */
extern struct clock24_s clock24;

/**
 *
 * @return clock24 structure
 */
#define clock24Get() clock24

/**
 * Call in interrupt service routine. Handles timer interrupt.
 */
#define clock24ServiceInterrupt() do{ \
	if (CLOCK_TIMER_IF) { \
		CLOCK_TIMER_H = CLOCK_TIMER_WRITE_VALUE_H; \
		CLOCK_TIMER_L = CLOCK_TIMER_WRITE_VALUE_L;\
		clock24ServiceInterrupt_in(); \
		CLOCK_TIMER_IF = 0; \
	} \
}while(0)

/**
 * Internal service interrupt routine, call clock24ServiceInterrupt instead.
 */
void clock24ServiceInterrupt_in(void);

/**
 * the clock24DifftimeSCHAR() function returns the number of seconds elapsed between time clock1 and
 * time clock0 represented as signed char. The return value is capped to signed char maximum values.
 * @param clock1
 * @param clock2
 * @return
 */
signed char clock24DifftimeSCHAR(struct clock24_s clock1, struct clock24_s clock0);

/**
 * prints uut the clock24 using printf
 * @param clock24
 */
void clock24Printf(struct clock24_s clock24);

#endif /* CLOCK24_H_ */
