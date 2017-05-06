/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <system.h> // configuration SYSTICK_USE_TIMER , SYSTICK_TIMER_PRESCALER , systick_t

#ifndef SYSTICK_USE_TIMER
#define SYSTICK_USE_TIMER 0
#endif

#include <timers.h> // OpenTimerX
#include <cdefs.h>  // __CONCAT(x,y)

/* ----------------------------------- timer configuration ------------------------------------- */

#ifndef SYSTICK_TIMER_PRESCALER
#if    SYSTICK_USE_TIMER == 0
#define SYSTICK_TIMER_PRESCALER         16
#else
#define SYSTICK_TIMER_PRESCALER          8
#endif
#endif

#if   SYSTICK_USE_TIMER == 0

#define SYSTICK_TIMER_IF INTCONbits.TMR0IF
#define SYSTICK_TIMER_H              TMR0H
#define SYSTICK_TIMER_L              TMR0L

/**
 * timer for systick and initializes systick structs
 */
#define systickInitInterrupt(interruptPriority) do{ \
	OpenTimer0( T0_16BIT & __CONCAT(T0_PS_1_, SYSTICK_TIMER_PRESCALER) & T0_SOURCE_INT & T0_EDGE_FALL & TIMER_INT_ON); \
	INTCON2bits.TMR0IP = interruptPriority; \
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L; \
}while(0)

#elif SYSTICK_USE_TIMER == 3

#define SYSTICK_TIMER_IF  PIR2bits.TMR3IF
#define SYSTICK_TIMER_H             TMR3H
#define SYSTICK_TIMER_L             TMR3L

/**
 * timer for systick and initializes systick structs
 */
#define systickInitInterrupt(interruptPriority) do{ \
	OpenTimer3( T3_16BIT_RW &  __CONCAT(T3_PS_1_, SYSTICK_TIMER_PRESCALER) & T3_SOURCE_INT & T3_SYNC_EXT_OFF & TIMER_INT_ON ); \
	IPR2bits.TMR3IP = interruptPriority; \
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L; \
}while(0)

#else
#error TODO: define SYSTICK_USE_TIMER == {0,1,2,3} ? or implement more timers or implement polling method, i dont know
#endif

/* ---------------------------------- speed config --------------------------------------- */

#define SYSTICK_FREQ                      ( _XTAL_FREQ / ( 4  * SYSTICK_TIMER_PRESCALER ) )
#define SYSTICK_TIMER_VALUE               46875 // arbitary chosen, equal SYSTICK_FREQ when PRESCALER=256
#define SYSTICK_TIMER_WRITE_VALUE         ( (2^16) - SYSTICK_TIMER_VALUE )
#define SYSTICK_TIMER_WRITE_VALUE_H       ( ( SYSTICK_TIMER_WRITE_VALUE >> 8 ) & 0xff )
#define SYSTICK_TIMER_WRITE_VALUE_L       ( ( SYSTICK_TIMER_WRITE_VALUE >> 0 ) & 0xff )

#define SYSTICK_TICK_FREQ                 ( SYSTICK_FREQ / SYSTICK_TIMER_VALUE )
#define SYSTICK_TICK_RESOLUTION_SEC       ( SYSTICK_TIMER_VALUE               / SYSTICK_FREQ )
#define SYSTICK_TICK_RESOLUTION_MILISEC   ( SYSTICK_TIMER_VALUE * 1000        / SYSTICK_FREQ )
#define SYSTICK_TICK_RESOLUTION_MICROSEC  ( SYSTICK_TIMER_VALUE * 1000 * 1000 / SYSTICK_FREQ )
#define SYSTICK_MAX_VALUE_SEC             ( ( 2 ^ ( sizeof(systick_t) * 8 ) ) * SYSTICK_TICK_RESOLUTION_SEC )

/* ---------------------------- SYSTICK convert to seconds and back macros ----------------------------
 * Calculation where optimized for use with XC8 preprocessor, so it doesn't overflow when calculating
 */

// when SYSTICK_TICK_RESOLUTION_SEC is lower then 0.001, to correct calculation using integer value we need to multiply to have better resolution
#if   SYSTICK_TICK_FREQ <=  16
#define SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION      1
#elif SYSTICK_TICK_FREQ <=  32
#define SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION     10
#elif SYSTICK_TICK_FREQ <= 128
#define SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION    100
#elif SYSTICK_TICK_FREQ <= 256
#define SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION   1000
#else
#error WHAT THE HELL ? HOW DID I GET HERE ?
#endif

#define SYSTICK_SEC_TO_SYSTICKS_TYPE(x, resolution, type) ((type)( \
		( (type)( SYSTICK_TICK_FREQ ) * (type)(x) ) / (type)(resolution) \
))
#define SYSTICK_SYSTICKS_TO_SEC_TYPE(x, resolution, type, additional_resolution) (type)( \
		( \
				(type)( \
						(type)( SYSTICK_TICK_RESOLUTION_SEC * (resolution) * (additional_resolution) ) * (type)(x) \
				) / \
				(type)(additional_resolution) \
		) \
)


/**
 * Public macros for converting SYSTICK to and from seconds and miliseconds.
 */
#define SYSTICK_S_TO_SYSTICKS(x)          SYSTICK_SEC_TO_SYSTICKS_TYPE(x,    1, unsigned int)
#define SYSTICK_SYSTICKS_TO_S(x)          SYSTICK_SYSTICKS_TO_SEC_TYPE(x,    1, unsigned int, SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION*1000)
#define SYSTICK_MS_TO_SYSTICKS(x)         SYSTICK_SEC_TO_SYSTICKS_TYPE(x, 1000, unsigned int)
#define SYSTICK_SYSTICKS_TO_MS(x)         SYSTICK_SYSTICKS_TO_SEC_TYPE(x, 1000, unsigned int, SYSTICK_SYSTICKS_TO_MS_ADDITIONAL_RESOLUTION)

/**
 * Public macros for converting SYSTICK to and from seconds and miliseconds.
 * Those macros do not cast values to unsigned int.
 */
#define SYSTICK_S_TO_SYSTICKS_STATIC(x)   ( SYSTICK_FREQ / SYSTICK_TIMER_VALUE * x )
#define SYSTICK_SYSTICKS_TO_S_STATIC(x)   ( SYSTICK_TIMER_VALUE * x / SYSTICK_FREQ )
#define SYSTICK_MS_TO_SYSTICKS_STATIC(x)  ( SYSTICK_FREQ / SYSTICK_TIMER_VALUE * x / 1000 )
#define SYSTICK_SYSTICKS_TO_MS_STATIC(x)  ( SYSTICK_TIMER_VALUE * x / SYSTICK_FREQ * 1000 )

/* -------------------------- systick compare macros and handle overflow while comparing ------------------- */

/**
 * compare with this margin
 */
#define SYSTICK_EQUAL_MARGIN SYSTICK_MS_TO_SYSTICKS_STATIC(100)

/**
 * SYSTICK_EQUAL checks if two systicks are equal to each other, with specified margin.
 * Margin is equal to 100ms, so you need to run this function at least 10 times per second.
 * If you pass systickGet() as parameter, it should be the first parameter (x1).
 */
#if     SYSTICK_EQUAL_MARGIN != 0
#define SYSTICK_EQUAL(x1, x0) ( \
		( (x0) > (x1) ) ? \
				( (systick_t)( (x0) - (x1) ) <= (systick_t)(SYSTICK_EQUAL_MARGIN) ) : \
				( (systick_t)( (x1) - (x0) ) <= (systick_t)(SYSTICK_EQUAL_MARGIN) ) \
)
#else
#define SYSTICK_EQUAL(x1, x0)   ( (x0) == (x1) )
#endif

/**
 * SYSTICK_COMAPRE - not equal
 */
#define SYSTICK_COMPARE(x1, x0)  ( ! SYSTICK_EQUAL( x1 , x0 ) )

/* -------------------------------------------- public defines -------------------------------------------------- */

/**
 * systick_t datatype
 * It can hold up to SYSTICK_MAX_VALUE_SEC seconds until it overflows.
 * One systick equals SYSTICK_TICK_RESOLUTION_SEC seconds.
 * Define systick_t in system.h with different type
 * 	to measure more seconds with greater/smaller accuracy.
 */
#ifndef systick_t
typedef unsigned int systick_t;
#define systick_t systick_t
#endif

/**
 *
 * @return return systick counter value
 */
#define systickGet() systick_counter

/**
 * Call in interrupt service routine. Handles timer interrupt.
 */
#define systickServiceInterrupt() do{ \
	if (SYSTICK_TIMER_IF) { \
		systickServiceInterrupt_in(); \
	} \
}while(0)

/**
 *
 */
#define systickServiceInterrupt_in() do {\
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L;\
	++systick_counter; \
}while(0)


/* ---------------------------------------- private extern counter ---------------------------------------- */

/**
 * Private systick counter used in increments.
 */
extern volatile systick_t systick_counter;

/* ------------------------------------------- additional functions   -------------------------------------- */

/* ------------------------------------------- timeout implementation ----------------------------------------- */

#define SYSTICK_TIMEOUT_INIT(varname) systick_t varname = 0
#define SYSTICK_TIMEOUT_SET(varname, ms) do{ varname = systickGet() + SYSTICK_MS_TO_SYSTICKS(ms); }while(0)
#define SYSTICK_TIMEOUT_ELAPSED(varname) ( SYSTICK_EQUAL(systicGet(), varname) )

#endif /* SYSTICK_H_ */
