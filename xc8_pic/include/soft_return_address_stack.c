/*
 * return_address_stack.c
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#include "soft_return_address_stack.h"


#if defined( SOFT_RETURN_ADDRESS_STACK_SIZE ) && SOFT_RETURN_ADDRESS_STACK_SIZE > 0

#include <GenericTypeDefs.h>
#include <xc.h>

/**
 * Software return address stack with SOFT_RETURN_ADDRESS_STACK_SIZE size.
 * The stack consist of saved values of packages like:
 * TOSL , TOSH , TOSU , [ TOSL , TOSH , TOSU , ... ] NUMBER_OF_TOS?_VALUES
 */
static UINT8 addrstack[SOFT_RETURN_ADDRESS_STACK_SIZE];

/**
 * State variable, using pointer for faster addrstack reference
 */
static UINT8 *addrstack_pnt = addrstack;

void SoftReturnAddressStack_push(void)
{
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;
	--STKPTRbits.STKPTR;

	// we need to save this many ReturnAdresses
	const unsigned char stkptr = STKPTRbits.STKPTR;

	while( STKPTRbits.STKPTR != 0 ) {

		// save ReturnAdresses
		*addrstack_pnt = TOSL;
		++addrstack_pnt;
		*addrstack_pnt = TOSH;
		++addrstack_pnt;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
		*addrstack_pnt = TOSU;
		++addrstack_pnt;
#endif

		--STKPTRbits.STKPTR;
	}

	// remember how many ReturnAddresses we saved
	*addrstack_pnt = stkptr;
	++addrstack_pnt;

	// restore our ReturnAddress
	++STKPTRbits.STKPTR;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

void SoftReturnAddressStack_pop(void)
{
	/*
	 * NOTICE:
	 * restoring TOS? register MUST be done using movwl instruction.
	 * Using movff does not work!
	 */
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;
	--STKPTRbits.STKPTR;

	// first char is length of ReturnAddresses we saved
	--addrstack_pnt;
	unsigned char stkptr = *addrstack_pnt;

	// restore ReturnAddresses
	while( stkptr != 0 ) {

		// STKPTR is first incremented
		++STKPTRbits.STKPTR;
		--stkptr;

		// restore ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSU = WREG;
#endif
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSH = WREG;
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSL = WREG;
	}

	// restore our ReturnAddress
	++STKPTRbits.STKPTR;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

#endif

#if 0
void SoftReturnAddressStack_save(uint8_t *pnt, uint8_t *len)
{
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;
	--STKPTRbits.STKPTR;

	*len = STKPTRbits.STKPTR;

	while( STKPTRbits.STKPTR != 0 ) {

		// save ReturnAdresses
		*pnt = TOSL;
		++pnt;
		*pnt = TOSH;
		++pnt;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
		*pnt = TOSU;
		++pnt;
#endif

		--STKPTRbits.STKPTR;
	}

	// restore our ReturnAddress
	++STKPTRbits.STKPTR;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();

}

void SoftReturnAddressStack_load(uint8_t *pnt, uint8_t stkptr)
{
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;

	STKPTRbits.STKPTR = 0;

	pnt += stkptr * SOFT_RETURN_ADDRESS_BYTES_LEN;

	// restore ReturnAddresses
	while( stkptr != 0 ) {

		// STKPTR is first incremented
		++STKPTRbits.STKPTR;
		--stkptr;

		// restore ReturnAddress
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
		--pnt;
		WREG = *pnt;
		TOSU = WREG;
#endif
		--pnt;
		WREG = *pnt;
		TOSH = WREG;
		--pnt;
		WREG = *pnt;
		TOSL = WREG;
	}

	// restore our ReturnAddress
	++STKPTRbits.STKPTR;
#if SOFT_RETURN_ADDRESS_SAVE_UPPER_BYTE == 1
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}
#endif
