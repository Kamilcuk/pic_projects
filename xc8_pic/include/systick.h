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

#include <cdefs.h>  // __CONCAT(x,y)
#include <timers.h> // OpenTimerX

/* ----------------------------------- timer configuration ------------------------------------- */

// default timer
#ifndef SYSTICK_USE_TIMER
#define SYSTICK_USE_TIMER 1
#endif

// default prescaler
#ifndef SYSTICK_TIMER_PRESCALER
#if    SYSTICK_USE_TIMER == 0
#define SYSTICK_TIMER_PRESCALER         16
#else
#define SYSTICK_TIMER_PRESCALER          8
#endif
#endif

#if   SYSTICK_USE_TIMER == 0

#define SYSTICK_TIMER_IF  INTCONbits.TMR0IF
#define SYSTICK_TIMER_IP INTCON2bits.TMR0IP
#define SYSTICK_TIMER_H              TMR0H
#define SYSTICK_TIMER_L              TMR0L

#define systickInitInterrupt_OpenTimer() do{ \
	OpenTimer0( T0_16BIT & __CONCAT(T0_PS_1_, SYSTICK_TIMER_PRESCALER) & T0_SOURCE_INT & T0_EDGE_FALL & TIMER_INT_ON); \
}while(0)

#elif SYSTICK_USE_TIMER == 1

#define SYSTICK_TIMER_IF  PIR1bits.TMR1IF
#define SYSTICK_TIMER_IP  IPR1bits.TMR1IP
#define SYSTICK_TIMER_H            TMR1H
#define SYSTICK_TIMER_L            TMR1L
#define systickInitInterrupt_OpenTimer() do{ \
	OpenTimer1( T1_16BIT_RW &  __CONCAT(T1_PS_1_, SYSTICK_TIMER_PRESCALER) & T1_SOURCE_INT & T1_SYNC_EXT_OFF & TIMER_INT_ON ); \
}while(0)

#elif SYSTICK_USE_TIMER == 3

#define SYSTICK_TIMER_IF  PIR2bits.TMR3IF
#define SYSTICK_TIMER_IP  IPR2bits.TMR3IP
#define SYSTICK_TIMER_H            TMR3H
#define SYSTICK_TIMER_L            TMR3L

#define systickInitInterrupt_OpenTimer() do{ \
	OpenTimer3( T3_16BIT_RW &  __CONCAT(T3_PS_1_, SYSTICK_TIMER_PRESCALER) & T3_SOURCE_INT & T3_SYNC_EXT_OFF & TIMER_INT_ON ); \
}while(0)

#else
#error TODO: define SYSTICK_USE_TIMER == 2 ? or implement more timers or implement polling method, i dont know
#endif

/**
 * timer for systick and initializes systick structs
 * @param interruptPriority 0 - low interrupt, 1 - high interrupt
 */
#define systickInitInterrupt(interruptPriority) do{ \
	systickInitInterrupt_OpenTimer(); \
	SYSTICK_TIMER_IP = interruptPriority; \
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L; \
}while(0)

/* ---------------------------------- const configuration --------------------------------------- */

#ifndef SYSTICK_TIMER_VALUE
#if _XTAL_FREQ == 48000000
#define SYSTICK_TIMER_VALUE               46875 // = (_XTAL_FREQ=48000000) / 1024
#else
#error Choose SYSTICK_TIMER_VALUE for _XTAL_FREQ != 48000000
#endif
#endif

#define SYSTICK_FREQ                      ( _XTAL_FREQ / ( 4  * SYSTICK_TIMER_PRESCALER ) )
#define SYSTICK_TIMER_WRITE_VALUE         ( (0xffff) - SYSTICK_TIMER_VALUE )
#define SYSTICK_TIMER_WRITE_VALUE_H       ( ( SYSTICK_TIMER_WRITE_VALUE >> 8 ) & 0xff )
#define SYSTICK_TIMER_WRITE_VALUE_L       ( ( SYSTICK_TIMER_WRITE_VALUE      )        )

#define SYSTICK_TICK_FREQ                 ( SYSTICK_FREQ               / SYSTICK_TIMER_VALUE )
#define SYSTICK_TICK_DURATION_SEC         ( SYSTICK_TIMER_VALUE               / SYSTICK_FREQ )
#define SYSTICK_TICK_DURATION_MILISEC     ( SYSTICK_TIMER_VALUE * 1000        / SYSTICK_FREQ )
#define SYSTICK_TICK_DURATION_MICROSEC    ( SYSTICK_TIMER_VALUE * 1000 * 1000 / SYSTICK_FREQ )
#define SYSTICK_MAX_DURATION_SEC          ( ( 2 ^ ( sizeof(systick_t) * 8 ) ) * SYSTICK_TICK_RESOLUTION_SEC )

#include "systick_private.h" // include after configuration // SYSTICK_SEC_TO_SYSTICKS_RES SYSTICK_SYSTICKS_TO_SEC_RES

/* --------------------------------- S to SYSTICK and back ------------------------------------ */

/**
 * Public macros for converting SYSTICK to and from seconds and miliseconds.
 */
#define SYSTICK_S_TO_SYSTICKS(x)          SYSTICK_SEC_TO_SYSTICKS_RES( x,    1 )
#define SYSTICK_SYSTICKS_TO_S(x)          SYSTICK_SYSTICKS_TO_SEC_RES( x,    1 )
#define SYSTICK_MS_TO_SYSTICKS(x)         SYSTICK_SEC_TO_SYSTICKS_RES( x, 1000 )
#define SYSTICK_SYSTICKS_TO_MS(x)         SYSTICK_SYSTICKS_TO_SEC_RES( x, 1000 )

/* -------------------------- systick compare macros and handle overflow while comparing ------------------- */

/**
 * compare with this margin - 100 miliseconds
 */
#ifndef SYSTICK_EQUAL_MARGIN
#define SYSTICK_EQUAL_MARGIN SYSTICK_MS_TO_SYSTICKS( 100 )
#endif

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
	if ( SYSTICK_TIMER_IF ) { \
		systickServiceInterrupt_in(); \
		SYSTICK_TIMER_IF = 0; \
	} \
}while(0)

/**
 * inside of the interrupt routine
 */
#define systickServiceInterrupt_in() do { \
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L; \
	++systick_counter; \
}while(0)


/* ---------------------------------------- private extern counter ---------------------------------------- */

/**
 * Private systick counter used in increments.
 */
extern volatile systick_t systick_counter;

/* ------------------------------------------- additional functions   -------------------------------------- */

/* ------------------------------------------- timeout implementation ----------------------------------------- */

#define SYSTICK_TIMEOUT_DECLARE(varname) systick_t varname = systickGet()
#define SYSTICK_TIMEOUT_SET(varname, ms) do{ varname = systickGet() + SYSTICK_MS_TO_SYSTICKS(ms); }while(0)
#define SYSTICK_TIMEOUT_ELAPSED(varname) ( SYSTICK_EQUAL( systickGet(), varname ) )

/* ------------------------------------------- examples ----------------------------------------------------- */

/** examples
 *
 *
 * main initialization:
void interrupt high_priority SYS_InterruptHigh(void) {
	systickServiceInterrupt();
}
void main() {
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	systickInitInterrupt(0);
	// USER CODE HERE
}
 *
 *
 * timeout example:
void execute_Task_every_500_miliseconds() {
	systick_t Tickstop = 0;
	while(1) {
		if ( SYSTICK_EQUAL(systickGet(), Tickstop) ) {
			Tickstop = systickGet() + SYSTICK_MS_TO_SYSTICKS(500);
			Task();
		}
	}
}
 *
 * or with Timeout_ implementation:
void execute_Task_every_500_miliseconds() {
	SYSTICK_TIMEOUT_DECLARE(Tickstop);
	while(1) {
		if ( SYSTICK_TIMEOUT_ELAPSED(Tickstop) ) {
			SYSTICK_TIMEOUT_SET(Tickstop, 500);
			Task();
		}
	}
}
 */

#endif /* SYSTICK_H_ */
