/*
 *        File: interrupt.h
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
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
