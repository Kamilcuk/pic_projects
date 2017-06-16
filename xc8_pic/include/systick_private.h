/*
 *        File: systick_private.h
 *  Created on: 07.05.2017
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

#define SYSTICK_CALC_MULTI                   ( SYSTICK_CALC_ADDITIONAL_RESOLUTION * SYSTICK_TIMER_VALUE * 4 / _XTAL_FREQ )

#if SYSTICK_CALC_MULTI == 1

#define SYSTICK_CALC_TICK_DURATION_ADD_RES   SYSTICK_TIMER_PRESCALER

#define SYSTICK_CALC_TICK_FREQ_ADD_RES       ( SYSTICK_CALC_ADDITIONAL_RESOLUTION / SYSTICK_TIMER_PRESCALER )

#else // SYSTICK_CALC_MULTI == 1

#define SYSTICK_CALC_TICK_DURATION_ADD_RES \
	XC8PP_LONG( SYSTICK_TIMER_PRESCALER * SYSTICK_CALC_ADDITIONAL_RESOLUTION * SYSTICK_TIMER_VALUE * 4 / _XTAL_FREQ )

#define SYSTICK_CALC_TICK_FREQ_ADD_RES     \
	XC8PP_LONG( SYSTICK_TICK_FREQ * SYSTICK_CALC_ADDITIONAL_RESOLUTION )

#endif // SYSTICK_CALC_MULTI == 1


/**
 * Converts x seconds to systicks with specified seconds resolution.
 * Example: SYSTICK_SEC_TO_SYSTICKS_RES(123, 1000) - converts 123 miliseconds to systicks
 * Example: SYSTICK_SEC_TO_SYSTICKS_RES(123,    1) - converts 123 seconds to systicks
 */
#define SYSTICK_SEC_TO_SYSTICKS_RES( x, resolution ) \
	XC8PP_LONG( (x) * (SYSTICK_CALC_TICK_FREQ_ADD_RES) / (resolution) )

/**
 * Converts x systicks to seconds with specified seconds resolution.
 * Example: SYSTICK_SYSTICKS_TO_SEC_RES(123, 1000) - converts 123 systicks to miliseconds
 * Example: SYSTICK_SYSTICKS_TO_SEC_RES(123,    1) - converts 123 systicks to seconds
 */
#define SYSTICK_SYSTICKS_TO_SEC_RES( x, resolution ) \
	XC8PP_LONG( (SYSTICK_CALC_TICK_DURATION_ADD_RES) * (resolution) * (x) / (SYSTICK_CALC_ADDITIONAL_RESOLUTION) )

#endif /* SYSTICK_PRIVATE_H_ */
