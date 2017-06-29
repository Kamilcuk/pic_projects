/*
 * return_address_stack.c
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#include <return_address_stack.h>


#if defined( RETURN_ADDRESS_STACK_STATIC_SIZE ) && RETURN_ADDRESS_STACK_STATIC_SIZE > 0

#include <GenericTypeDefs.h>
#include <xc.h>

#if RETURN_ADDRESS_BYTES_LEN == 3
#define RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE 1
#else
#define RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE 0
#endif

/**
 * Software return address stack with SOFT_RETURN_ADDRESS_STACK_SIZE size.
 * The stack consist of saved values of packages like:
 * TOSL , TOSH , TOSU , [ TOSL , TOSH , TOSU , ... ] NUMBER_OF_TOS?_VALUES
 */
static UINT8 addrstack[RETURN_ADDRESS_STACK_STATIC_SIZE];

/**
 * State variable, using pointer for faster addrstack reference
 */
static UINT8 *addrstack_pnt = addrstack;

void ReturnAddressStack_staticPush(void)
{
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;
	ReturnAddressStack_dec();

	// we need to save this many ReturnAdresses
	const unsigned char stkptr = STKPTRbits.STKPTR;

	for(uint8_t i = stkptr; i; --i) {

		// save ReturnAdresses
		*addrstack_pnt = TOSL;
		++addrstack_pnt;
		*addrstack_pnt = TOSH;
		++addrstack_pnt;
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
		*addrstack_pnt = TOSU;
		++addrstack_pnt;
#endif

		ReturnAddressStack_dec();
	}

	// remember how many ReturnAddresses we saved
	*addrstack_pnt = stkptr;
	++addrstack_pnt;

	// restore our ReturnAddress
	ReturnAddressStack_inc();
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

void ReturnAddressStack_staticPop(void)
{
	/*
	 * NOTICE:
	 * restoring TOS? register MUST be done using movwl instruction.
	 * Using movff does not work!
	 */
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	UINT24_VAL myret;
#else
	UINT16_VAL myret;
#endif

	di();

	// store our ReturnAddress
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	myret.byte.UB = TOSU;
#endif
	myret.byte.HB = TOSH;
	myret.byte.LB = TOSL;
	ReturnAddressStack_dec();

	// first char is length of ReturnAddresses we saved
	--addrstack_pnt;
	unsigned char stkptr = *addrstack_pnt;

	// restore ReturnAddresses
	while( stkptr != 0 ) {

		// STKPTR is first incremented
		ReturnAddressStack_inc();
		--stkptr;

		// restore ReturnAddress
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
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
	ReturnAddressStack_inc();
#if RETURN_ADDRESS_STACK_SAVE_UPPER_BYTE
	WREG = myret.byte.UB;
	TOSU = WREG;
#endif
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

#endif // defined( RETURN_ADDRESS_STACK_STATIC_SIZE ) && RETURN_ADDRESS_STACK_STATIC_SIZE > 0
