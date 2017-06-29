/*
 * soft_return_address_stack.h
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#ifndef RETURN_ADDRESS_STACK_H_
#define RETURN_ADDRESS_STACK_H_

#include <system.h>
#include <GenericTypeDefs.h>
#include <stdint.h>
#include <cdefs.h>

/**
 * use PCLATU register or not?
 */
#if _ROMSIZE > 0x8000
#define RETURN_ADDRESS_BYTES_LEN 3
#else
#define RETURN_ADDRESS_BYTES_LEN 2
#endif


/**
 * Software address stack size.
 * Every _push() stores this size in the software address stack:
 * (2 or 3) * <functions in the ReturnAddressStack> + 1
 * ( 2 or 3 is dependent on SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE option )
 */
#ifndef RETURN_ADDRESS_STACK_STATIC_SIZE
#define RETURN_ADDRESS_STACK_STATIC_SIZE 0
#endif

#if RETURN_ADDRESS_STACK_STATIC_SIZE != 0

/**
 * Stores whole ReturnAddressStack to software address stack.
 */
void ReturnAddressStack_staticPush(void);

/**
 * Restores ReturnAddressStack from software address stack.
 */
void ReturnAddressStack_staticPop(void);

/**
 * Example: Use like this:
 *
 * void VeryNestedFunction() {
 * 	ReturnAddressStack_staticPush();
 * 	// here ReturnAddressStack is 0, STKPTRbits.STKPTR = 0, so we can:
 * 	EvenMoreNestedFunction();
 * 	MaybeSomeOtherFunction();
 * 	ReturnAddressStack_staticPop();
 * }
 *
 */

#endif

/**
 * increment ReturnAdressStack pointer
 */
void ReturnAddressStack_inc(void);
#define ReturnAddressStack_inc() asm(" push")

/**
 * decrement ReturnAdressStack pointer
 */
void ReturnAddressStack_dec(void);
#define ReturnAddressStack_dec() asm(" pop")

/**
 * save ReturnAddressStack to place pointed by pnt
 */
void ReturnAddressStack_pntSave(uint8_t *pnt, uint8_t /*reference*/ stkptr);
#if RETURN_ADDRESS_BYTES_LEN == 2
#define ReturnAddressStack_pntSave( pnt , stkptr ) do{ \
	uint8_t *_pnt = (pnt); \
	(stkptr) = STKPTRbits.STKPTR; \
	while( STKPTRbits.STKPTR != 0 ) { \
		*_pnt = TOSL; \
		++_ptr; \
		*_pnt = TOSH; \
		++_ptr; \
		ReturnAddressStack_dec(); \
	} \
}while(0)
#endif

/**
 * load ReturnAddressStack from place pointed by pnt
 */
void ReturnAddressStack_pntLoad(uint8_t *pnt, uint8_t stkptr);
#if RETURN_ADDRESS_BYTES_LEN == 2
#define ReturnAddressStack_pntLoad( pnt , stkptr ) do{\
	uint8_t *_pnt = (pnt); \
	uint8_t _stkptr = (stkptr); \
	STKPTRbits.STKPTR = 0; \
	_pnt += _stkptr * RETURN_ADDRESS_BYTES_LEN; \
	while( _stkptr ) { \
		--_stkptr; \
		ReturnAddressStack_inc(); \
		--_pnt; \
		WREG = *_pnt; \
		TOSH = WREG; \
		--_pnt; \
		WREG = *_pnt; \
		TOSL = WREG; \
	} \
}while(0)
#endif

/**
 * clear all ReturnAddressStack
 */
void ReturnAddressStack_clear(void);
#define ReturnAddressStack_clear() do{ \
	for(uint8_t optimize = STKPTRbits.STKPTR; optimize; --optimize) { \
		asm(" pop"); \
	} \
}while(0)

#if RETURN_ADDRESS_BYTES_LEN == 2

#define ReturnAddressStack_stackSave() do { \
	asm("movff	STKPTR,POSTDEC2"); \
	while( STKPTRbits.STKPTR != 0 ) { \
		asm("movff	TOSH,POSTDEC2"); \
		asm("movff	TOSL,POSTDEC2"); \
		ReturnAddressStack_dec(); \
	} \
} while(0)

#define ReturnAddressStack_stackLoad() do { \
	uint8_t stkptr; \
	asm("movf	PREINC2,W,ACCESS"); \
	stkptr = WREG; \
	STKPTRbits.STKPTR = 0; \
	while( stkptr ) { \
		--stkptr; \
		ReturnAddressStack_inc(); \
		asm("movf	PREINC2,W,ACCESS"); \
		asm("movwf	TOSL,ACCESS"); \
		asm("movf	PREINC2,W,ACCESS"); \
		asm("movwf	TOSH,ACCESS"); \
	} \
} while(0)

#endif

#endif /* RETURN_ADDRESS_STACK_H_ */
