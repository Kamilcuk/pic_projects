/*
 * soft_return_address_stack.h
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#ifndef SOFT_RETURN_ADDRESS_STACK_H_
#define SOFT_RETURN_ADDRESS_STACK_H_

#include <system.h>

/**
 * Software address stack size.
 * Every _push() stores this size in the software address stack:
 * (2 or 3) * <functions in the ReturnAddressStack> + 1
 * ( 2 or 3 is dependent on SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE option )
 */
#ifndef SOFT_RETURN_ADDRESS_STACK_SIZE
#define SOFT_RETURN_ADDRESS_STACK_SIZE 0
#endif

#if SOFT_RETURN_ADDRESS_STACK_SIZE != 0

/**
 * Should we save upper ReturnAddress byte? Should we save TOSH?
 * When this is enabled, we use 24-bit program memory pointers.
 * When this is disabled, we use 16-bit program memory pointers.
 * This can be safely disabled for devices with lower
 *   then 2^16 = 64 Kbytes of program memory
 */
#ifndef SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE
#define SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE 0 /* 0 - disabled, 1 - enabled */
#endif

/**
 * Stores whole ReturnAddressStack to software address stack.
 */
void SoftReturnAddressStack_push(void);

/**
 * Restores ReturnAddressStack from software address stack.
 */
void SoftReturnAddressStack_pop(void);

/**
 * Example: Use like this:
 *
 * void VeryNestedFunction() {
 * 	SoftReturnAddressStack_push();
 * 	// here ReturnAddressStack is 0, STKPTRbits.STKPTR = 0, so we can:
 * 	EvenMoreNestedFunction();
 * 	MaybeSomeOtherFunction();
 * 	SoftReturnAddressStack_pop();
 * }
 *
 */

#endif

#endif /* SOFT_RETURN_ADDRESS_STACK_H_ */
