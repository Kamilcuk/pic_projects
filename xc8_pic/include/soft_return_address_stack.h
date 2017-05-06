/*
 * soft_return_address_stack.h
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#ifndef SOFT_RETURN_ADDRESS_STACK_H_
#define SOFT_RETURN_ADDRESS_STACK_H_

#include <system.h>
#include <GenericTypeDefs.h>
#include <stdint.h>

/**
 * Software address stack size.
 * Every _push() stores this size in the software address stack:
 * (2 or 3) * <functions in the ReturnAddressStack> + 1
 * ( 2 or 3 is dependent on SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE option )
 */
#ifndef SOFT_RETURN_ADDRESS_STACK_SIZE
#define SOFT_RETURN_ADDRESS_STACK_SIZE 0
#endif

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
 * length in bytes of return address
 */
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE != 0
#define SOFT_RETURN_ADDRESS_BYTES_LEN 3
#else
#define SOFT_RETURN_ADDRESS_BYTES_LEN 2
#endif

#if SOFT_RETURN_ADDRESS_STACK_SIZE != 0

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


void SoftReturnAddressStack_save(uint8_t *ptr, uint8_t *stkptr);
#define SoftReturnAddressStack_save( ptr , stkptr ) do{ \
	uint8_t *_ptr = (ptr); \
	(stkptr) = STKPTRbits.STKPTR; \
	while( STKPTRbits.STKPTR != 0 ) { \
		*_ptr = TOSL; \
		++_ptr; \
		*_ptr = TOSH; \
		++_ptr; \
		--STKPTRbits.STKPTR; \
	} \
}while(0)


void SoftReturnAddressStack_load(uint8_t *pnt, uint8_t stkptr);
#define SoftReturnAddressStack_load( ptr , stkptr ) do{\
	uint8_t *_ptr = (ptr); \
	uint8_t _stkptr = (stkptr); \
	STKPTRbits.STKPTR = 0; \
	_ptr += _stkptr * SOFT_RETURN_ADDRESS_BYTES_LEN; \
	while( _stkptr != 0 ) { \
		--_stkptr; \
		++STKPTRbits.STKPTR; \
		--_ptr; \
		WREG = *_ptr; \
		TOSH = WREG; \
		--_ptr; \
		WREG = *_ptr; \
		TOSL = WREG; \
	} \
}while(0)

#endif /* SOFT_RETURN_ADDRESS_STACK_H_ */
