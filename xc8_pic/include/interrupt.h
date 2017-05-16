/*
 *        File: interrupt.h
 *  Created on: 08.05.2017
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
 *
 *
 * based on http://comments.gmane.org/gmane.comp.compilers.sdcc.user/3915
 * response from Raphael Neider thank you
 */
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#ifdef __XC8
#include <xc.h> // _INTCONbits
#else
#ifdef _18FXXK42_FAMILY_
#define _INTCONbits INTCON0bits
#else
#define _INTCONbits INTCONbits
#endif
#endif

#include <stdbool.h>

/**
 * Saves INTCON interrupt bit to variable VAR
 */
#define ATOMIC_INTCON_SAVE(VAR)    VAR = (_INTCONbits.GIE)
/**
 * Disables interrupt bits
 */
#define ATOMIC_INTCON_DISABLE()    _INTCONbits.GIE = 0
/**
 * Restores INTCON interrupt bit from our variable
 */
#define ATOMIC_INTCON_LOAD(VAR)    _INTCONbits.GIE = VAR

/*
 * Notice:
 * Instructions inside ATOMIC_* can't touch INTCON register (isn't that obvious ?)
 */

/**
 * Execute code passed as 'CODE' parameter atomically
 * This method is preferable over ATOMIC_BLOCK() as it is one compare instruction faster.
 */
#define ATOMIC_CODE(CODE) do { \
  const bool ATOMIC_INTCON_SAVE(_ATOMIC_VAR); \
  ATOMIC_INTCON_DISABLE(); \
  do { CODE } while (0); \
  ATOMIC_INTCON_LOAD(_ATOMIC_VAR); \
} while(0)

/**
 * Execute next block of code atomically
 */
#define ATOMIC_BLOCK() \
		for(bool ATOMIC_INTCON_SAVE(_ATOMIC_VAR), _ToDo=(ATOMIC_INTCON_DISABLE(), 1); \
		_ToDo; \
		_ToDo=0, ATOMIC_INTCON_LOAD(_ATOMIC_VAR))
/**
 * Break out of ATOMIC_BLOCK of code
 */
#define ATOMIC_BLOCK_BREAK() ( ATOMIC_INTCON_LOAD(_ATOMIC_VAR), break )
/**
 * Break out of ATOMIC_BLOCK of code
 */
#define ATOMIC_BLOCK_RETURN(_Value) return (ATOMIC_INTCON_LOAD(_ATOMIC_VAR), _Value)

#endif // INTERRUPT_H_
