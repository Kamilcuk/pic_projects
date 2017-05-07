/*
 *        File: systick_private.h
 *  Created on: 07.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

/* ---------------------------- SYSTICK convert to seconds and back macros ----------------------------
 * Calculation optimized for use with XC8 preprocessor, so it doesn't overflow when calculating.
 */

/*
 * Additional resolution for converting SYSTICKS_TO_SEC and SEC_TO_SYSTICKS.
 * The calculations are multiplicited by ADDITIONAL_RESOLUTION and then divided by ADDITIONAL_RESOLUTION again.
 * When _XTAL_FREQ=480000000, ADDITIONAL_RESOLUTION=256 and TIMER_VALUE=46875 then CALC_MULTI below is equal 1.
 */
#define SYSTICK_CALC_ADDITIONAL_RESOLUTION 256

#define SYSTICK_CALC_MULTI                 ( SYSTICK_CALC_ADDITIONAL_RESOLUTION * SYSTICK_TIMER_VALUE * 4 / _XTAL_FREQ )

#if SYSTICK_CALC_MULTI == 1

#define SYSTICK_CALC_TICK_DURATION_ADD_RES SYSTICK_TIMER_PRESCALER

#define SYSTICK_CALC_TICK_FREQ_ADD_RES     ( SYSTICK_CALC_ADDITIONAL_RESOLUTION / SYSTICK_TIMER_PRESCALER )

#else

#define SYSTICK_CALC_TICK_DURATION_ADD_RES \
	( SYSTICK_TIMER_PRESCALER * SYSTICK_CALC_ADDITIONAL_RESOLUTION * SYSTICK_TIMER_VALUE * 4 / _XTAL_FREQ )

#define SYSTICK_CALC_TICK_FREQ_ADD_RES     ( SYSTICK_TICK_FREQ * SYSTICK_CALC_ADDITIONAL_RESOLUTION )

#endif

/**
 * In stupid xc8:
 * If an "static" equation has no numbers higher then "int" (2^16), then equations are done with int resolution.
 * Example:
 *  uint16_t a = ( 500*256/256 );
 *    gives a = 0;
 * However adding a stupid ( bignumer/bignumer ) devision "upscales" the (preprocessor?) resolution to long
 * Examples:
 *  uint16_t a = ( 100000/100000 * 500*256/256 );
 *    gives a = 500;
 */
#define SYSTICK_CALC_FUCK_XC8_BIG_NUMBER   1073741824 // = 2^30
#define SYSTICK_CALC_FUCK_XC8_CAST_TO_LONG ( SYSTICK_CALC_FUCK_XC8_BIG_NUMBER / SYSTICK_CALC_FUCK_XC8_BIG_NUMBER )

/**
 * Converts x seconds to systicks with specified seconds resolution.
 * Example: SYSTICK_SEC_TO_SYSTICKS_RES(123, 1000) - converts 123 miliseconds to systicks
 * Example: SYSTICK_SEC_TO_SYSTICKS_RES(123, 1000) - converts 123 seconds to systicks
 */
#define SYSTICK_SEC_TO_SYSTICKS_RES( x, resolution ) \
	( SYSTICK_CALC_FUCK_XC8_CAST_TO_LONG * \
			(x) * (SYSTICK_CALC_TICK_FREQ_ADD_RES) / (resolution) )

/**
 * Converts x systicks to seconds with specified seconds resolution.
 * Example: SYSTICK_SYSTICKS_TO_SEC_RES(123, 1000) - converts 123 systicks to miliseconds
 * Example: SYSTICK_SYSTICKS_TO_SEC_RES(123, 1)    - converts 123 systicks to seconds
 */
#define SYSTICK_SYSTICKS_TO_SEC_RES( x, resolution ) \
	( SYSTICK_CALC_FUCK_XC8_CAST_TO_LONG * \
			(SYSTICK_CALC_TICK_DURATION_ADD_RES) * (resolution) * (x) / (SYSTICK_CALC_ADDITIONAL_RESOLUTION) )

#endif /* SYSTICK_PRIVATE_H_ */
