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
#include <stdbool.h>
#include <stdint.h>

#include <xc_ex.h> // XC8PP_LONG(x)

/* ----------------------------------- timer configuration ------------------------------------- */

// default timer
#ifndef SYSTICK_USE_TIMER
#define SYSTICK_USE_TIMER                0
#endif // SYSTICK_USE_TIMER

// default prescaler
#ifndef SYSTICK_TIMER_PRESCALER
#if    SYSTICK_USE_TIMER == 0
#define SYSTICK_TIMER_PRESCALER         16
#else // SYSTICK_USE_TIMER == 0
#define SYSTICK_TIMER_PRESCALER          8
#endif // SYSTICK_USE_TIMER == 0
#endif // SYSTICK_TIMER_PRESCALER

#if   SYSTICK_USE_TIMER == 0

#define SYSTICK_TIMER_IF  INTCONbits.TMR0IF
#define SYSTICK_TIMER_IP INTCON2bits.TMR0IP
#define SYSTICK_TIMER_H              TMR0H
#define SYSTICK_TIMER_L              TMR0L
#define systickInitInterrupt_OpenTimer() do{ \
	OpenTimer0( T0_16BIT & __CONCAT(T0_PS_1_, SYSTICK_TIMER_PRESCALER) & T0_SOURCE_INT & T0_EDGE_FALL & TIMER_INT_ON); \
}while(0)

#elif SYSTICK_USE_TIMER == 1

#define SYSTICK_TIMER_IF    PIR1bits.TMR1IF
#define SYSTICK_TIMER_IP    IPR1bits.TMR1IP
#define SYSTICK_TIMER_H              TMR1H
#define SYSTICK_TIMER_L              TMR1L
#define systickInitInterrupt_OpenTimer() do{ \
	OpenTimer1( T1_16BIT_RW &  __CONCAT(T1_PS_1_, SYSTICK_TIMER_PRESCALER) & T1_SOURCE_INT & T1_SYNC_EXT_OFF & TIMER_INT_ON ); \
}while(0)

#elif SYSTICK_USE_TIMER == 3

#define SYSTICK_TIMER_IF    PIR2bits.TMR3IF
#define SYSTICK_TIMER_IP    IPR2bits.TMR3IP
#define SYSTICK_TIMER_H              TMR3H
#define SYSTICK_TIMER_L              TMR3L
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
#define SYSTICK_TIMER_WRITE_VALUE         ( 0xffff - SYSTICK_TIMER_VALUE )
#define SYSTICK_TIMER_WRITE_VALUE_H       ( ( SYSTICK_TIMER_WRITE_VALUE >> 8 ) & 0xff )
#define SYSTICK_TIMER_WRITE_VALUE_L       ( ( SYSTICK_TIMER_WRITE_VALUE      ) & 0xff )

#define SYSTICK_TICK_FREQ                           ( SYSTICK_FREQ               / SYSTICK_TIMER_VALUE )
#define SYSTICK_TICK_DURATION_SEC                   ( SYSTICK_TIMER_VALUE               / SYSTICK_FREQ )
#define SYSTICK_TICK_DURATION_MILISEC     XC8PP_LONG( SYSTICK_TIMER_VALUE * 1000        / SYSTICK_FREQ )
#define SYSTICK_TICK_DURATION_MICROSEC    XC8PP_LONG( SYSTICK_TIMER_VALUE * 1000 * 1000 / SYSTICK_FREQ )
#define SYSTICK_MAX_DURATION_SEC          XC8PP_LONG( SYSTICK_MAX_VALUE   *  SYSTICK_TICK_DURATION_SEC )

#define SYSTICK_MAX_VALUE                 XC8PP_LONG( 2^(sizeof(systick_t)*8) )

#include "systick_private.h" // include after configuration // SYSTICK_SEC_TO_SYSTICKS_RES SYSTICK_SYSTICKS_TO_SEC_RES

/* --------------------------------- S to SYSTICK and back ------------------------------------ */


/* ---------------------------------------- public defines -------------------------------------------------- */

/**
 * Public macros for converting SYSTICK to and from seconds and miliseconds.
 */
#define SYSTICK_S_TO_SYSTICKS(x)          SYSTICK_SEC_TO_SYSTICKS_RES( x,    1 )
#define SYSTICK_SYSTICKS_TO_S(x)          SYSTICK_SYSTICKS_TO_SEC_RES( x,    1 )
#define SYSTICK_MS_TO_SYSTICKS(x)         SYSTICK_SEC_TO_SYSTICKS_RES( x, 1000 )
#define SYSTICK_SYSTICKS_TO_MS(x)         SYSTICK_SYSTICKS_TO_SEC_RES( x, 1000 )

/**
 * systick_t datatype
 * It can hold up to SYSTICK_MAX_VALUE_SEC seconds until it overflows.
 * One systick equals SYSTICK_TICK_RESOLUTION_SEC seconds.
 * Define systick_t in system.h with different type
 * 	to measure more seconds with greater/smaller accuracy.
 */
#ifndef systick_t
typedef uint16_t systick_t;
#define systick_t systick_t
#endif

/**
 * Stores current tick, gets incremented in interrupt.
 * Interrupts should be disabled, when reading/setting this variable.
 * Use systickGet to return it's value.
 */
extern volatile systick_t systick_counter;

/**
 * Call in interrupt service routine. Handles timer interrupt.
 */
#define systickServiceInterrupt() do{ \
	if ( SYSTICK_TIMER_IF ) { \
		systickServiceInterruptIncrement(); \
		SYSTICK_TIMER_IF = 0; \
	} \
}while(0)

/**
 * inside of the interrupt routine
 */
#define systickServiceInterruptIncrement() do { \
	SYSTICK_TIMER_H = SYSTICK_TIMER_WRITE_VALUE_H; \
	SYSTICK_TIMER_L = SYSTICK_TIMER_WRITE_VALUE_L; \
	++systick_counter; \
}while(0)

/**
 *
 * @return return systick counter value
 */
systick_t systickGet(void);

/**
 * Compare Tickstop with current systick. MaxMargin is used to protect against overflow.
 * @param Tickstop
 * @param MaxMargin
 * @return true, if Tickstop is greater then current tick or current tick is greater then Tickstop+MaxMargin
 */
bool systickElapsed(systick_t Tickstop, systick_t MaxMargin);

/**
 * Compare Tickstop with current systick
 * @param Tickstop
 * @return true, if Tickstop is greater then current tick
 */
bool systickElapsed_unsafe(systick_t Tickstop);

/* ------------------------------------------- timeout implementation -------------------------------- */

#define SYSTICK_TIMEOUT_DECLARE(varname) \
	systick_t varname = 0
#define SYSTICK_TIMEOUT_SET(varname, ms) \
	( varname = (systick_t)(systickGet() + SYSTICK_MS_TO_SYSTICKS(ms)) )
#define SYSTICK_TIMEOUT_ELAPSED_UNSAFE(varname) \
	( systickElapsed_unsafe(varname) )
#define SYSTICK_TIMEOUT_ELAPSED(varname, ms) \
	( systickElapsed(varname, SYSTICK_MS_TO_SYSTICKS(ms) ) )

/* ------------------------------------------- timeout examples ----------------------------------------------- */

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
		if ( systickElapsed(Tickstop, SYSTICK_MS_TO_SYSTICKS(500)) ) {
			Tickstop = systickGet() + SYSTICK_MS_TO_SYSTICKS(500);
			Task();
		}
	}
}
 *
 * or with Timeout_ implementation: (preferred)
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

/* ------------------------------------------- systick protothread integration ------------------- */

#define PT_SYSTICK_DELAY_DECLARE(varname) static SYSTICK_TIMEOUT_DECLARE(varname)
#define PT_SYSTICK_DELAY(pt, varname, ms) do { \
		SYSTICK_TIMEOUT_SET(varname, ms); \
		pt_wait_while(pt, !SYSTICK_TIMEOUT_ELAPSED(varname, ms)); \
	}while(0)
#define pt_systick_delay(pt, varname, ms) PT_SYSTICK_DELAY(pt, varname, ms)

/* ------------------------------------------- eof ----------------------------------------------- */

#endif /* SYSTICK_H_ */
