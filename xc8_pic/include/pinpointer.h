/*
 *        File: pin_pointer.h
 *  Created on: 10.05.2017
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

#ifndef PINPOINTER_H_
#define PINPOINTER_H_

/* architecture specific macros ----------------------------------------------------------------------------- */

#ifdef __XC
#include <xc.h> // LOW_BYTE HIGH_BYTE
#pragma warning disable 751 // arithmetic overflow in constant expression
#endif

#ifndef LOW_BYTE
#define LOW_BYTE(x)  ((unsigned char)((x)&0xff))
#endif

#ifndef HIGH_BYTE
#define HIGH_BYTE(x) ((unsigned char)(((x)>>8)&0xff))
#endif

/**
 * Pointers offset
 */
#if _18F2550
#define PINPOINTER_ADDR_PORT ( 0xF80 ) // ( &PORTA )
#define PINPOINTER_ADDR_LAT  ( 0xF89 ) // ( &LATA  )
#define PINPOINTER_ADDR_TRIS ( 0xF92 ) // ( &TRISA )
#else // _18F2550
#define PINPOINTER_ADDR_PORT ( &PORTA )
#define PINPOINTER_ADDR_LAT  ( &LATA  )
#define PINPOINTER_ADDR_TRIS ( &TRISA )
#endif // _18F2550

/* type definition ------------------------------------------------------------------------------------------ */

/**
 * Enumatation definition
 */

#if 1 // PP_USE_16_BITS

enum pinpointer_e {
	// reg=0; for i in A B C D E; do mask=1; for j in 0 1 2 3  4 5 6 7 ; do printf "PP_R${i}${j}=0x%03x," $(( (${reg}<<8)+${mask} )); mask=$((mask<<1)); done; reg=$((reg+1)); echo; done;
	PP_RA0=0x001,PP_RA1=0x002,PP_RA2=0x004,PP_RA3=0x008,PP_RA4=0x010,PP_RA5=0x020,PP_RA6=0x040,PP_RA7=0x080,
	PP_RB0=0x101,PP_RB1=0x102,PP_RB2=0x104,PP_RB3=0x108,PP_RB4=0x110,PP_RB5=0x120,PP_RB6=0x140,PP_RB7=0x180,
	PP_RC0=0x201,PP_RC1=0x202,PP_RC2=0x204,PP_RC3=0x208,PP_RC4=0x210,PP_RC5=0x220,PP_RC6=0x240,PP_RC7=0x280,
	PP_RD0=0x301,PP_RD1=0x302,PP_RD2=0x304,PP_RD3=0x308,PP_RD4=0x310,PP_RD5=0x320,PP_RD6=0x340,PP_RD7=0x380,
	PP_RE0=0x401,PP_RE1=0x402,PP_RE2=0x404,PP_RE3=0x408,PP_RE4=0x410,PP_RE5=0x420,PP_RE6=0x440,PP_RE7=0x480,
};

#define PP_GET_REG_IDX(pp)    HIGH_BYTE(pp)

#define PP_GET_PIN(pp)         LOW_BYTE(pp)

#else // PP_USE_8_BITS

enum pinpointer_e {
	// reg=1; for i in A B C D E; do for j in $(seq 0 7); do printf "PP_R${i}${j} = 0x%02x," $(( ${reg}<<4 | ${j} )); done; reg=${reg+1}; echo; done;
	PP_RA0 = 0x11,PP_RA1 = 0x12,PP_RA2 = 0x13,PP_RA3 = 0x14,PP_RA4 = 0x15,PP_RA5 = 0x16,PP_RA6 = 0x17,PP_RA7 = 0x18,
	PP_RB0 = 0x11,PP_RB1 = 0x12,PP_RB2 = 0x13,PP_RB3 = 0x14,PP_RB4 = 0x15,PP_RB5 = 0x16,PP_RB6 = 0x17,PP_RB7 = 0x18,
	PP_RC0 = 0x11,PP_RC1 = 0x12,PP_RC2 = 0x13,PP_RC3 = 0x14,PP_RC4 = 0x15,PP_RC5 = 0x16,PP_RC6 = 0x17,PP_RC7 = 0x18,
	PP_RD0 = 0x11,PP_RD1 = 0x12,PP_RD2 = 0x13,PP_RD3 = 0x14,PP_RD4 = 0x15,PP_RD5 = 0x16,PP_RD6 = 0x17,PP_RD7 = 0x18,
	PP_RE0 = 0x11,PP_RE1 = 0x12,PP_RE2 = 0x13,PP_RE3 = 0x14,PP_RE4 = 0x15,PP_RE5 = 0x16,PP_RE6 = 0x17,PP_RE7 = 0x18,
};

#define PP_GET_REG_IDX(pp)    ( ( (pp)>>4 ) & 0xf0 )

#define PP_GET_PIN(pp)        ( 1 << ( (pp)&0x0f ) )

#endif

/* private abstract macros ----------------------------------------------------------------------- */

/**
 * Return pointer starting from ADDR with added REG_IDX from pp
 */
//#define PP_GET_REG_PNT(ADDR, pp)         ((unsigned char*)( ADDR + PP_GET_REG_IDX(pp) ))
//speed up:
#define PP_GET_REG_PNT(ADDR, pp)          ((unsigned char*)( (ADDR&0xff00) | ((unsigned char)( LOW_BYTE(ADDR) + PP_GET_REG_IDX(pp) )) ))

/**
 * Get register
 */
#define PP_GET_REG(ADDR, pp)              ( *PP_GET_REG_PNT(ADDR, pp) )

/**
 * Actual pin operation implementation using bit operations
 */
#define PP_BIT_READ(  ADDR, pp)           ( PP_GET_REG(ADDR, pp) &   PP_GET_PIN(pp) ? 1 : 0 )
#define PP_BIT_WRITE( ADDR, pp, VAL)      ( VAL ? PP_BIT_SET(ADDR, pp) : PP_BIT_CLEAR(ADDR, pp) )
#define PP_BIT_CLEAR( ADDR, pp)           ( PP_GET_REG(ADDR, pp) &= ~PP_GET_PIN(pp) )
#define PP_BIT_SET(   ADDR, pp)           ( PP_GET_REG(ADDR, pp) |=  PP_GET_PIN(pp) )
#define PP_BIT_TOGGLE(ADDR, pp)           ( PP_GET_REG(ADDR, pp) ^=  PP_GET_PIN(pp) )

/* public macros --------------------------------------------------------------------------------------- */

/**
 * @param pp variable of pinpointer_t type
 */

/**
 * Returns register address.
 */
#define PP_PORT_PNT( pp)             PP_GET_REG_PNT( PINPOINTER_ADDR_PORT, pp)
#define PP_TRIS_PNT( pp)             PP_GET_REG_PNT( PINPOINTER_ADDR_TRIS, pp)
#define PP_LAT_PNT(  pp)             PP_GET_REG_PNT( PINPOINTER_ADDR_LAT,  pp)

/**
 * Dereference register address. You can normally use these macros for assignment or reads.
 */
#define PP_PORT( pp)                 PP_GET_REG( PINPOINTER_ADDR_PORT, pp)
#define PP_TRIS( pp)                 PP_GET_REG( PINPOINTER_ADDR_TRIS, pp)
#define PP_LAT(  pp)                 PP_GET_REG( PINPOINTER_ADDR_LAT,  pp)

/**
 * Modify GPIO values
 */
#define PP_READ_PIN(   pp)           PP_BIT_READ(   PINPOINTER_ADDR_PORT, pp)
#define PP_WRITE_PIN(  pp, VAL)      PP_BIT_WRITE(  PINPOINTER_ADDR_PORT, pp, VAL )
#define PP_CLEAR_PIN(  pp)           PP_BIT_CLEAR(  PINPOINTER_ADDR_PORT, pp)
#define PP_SET_PIN(    pp)           PP_BIT_SET(    PINPOINTER_ADDR_PORT, pp)
#define PP_TOGGLE_PIN( pp)           PP_BIT_TOGGLE( PINPOINTER_ADDR_PORT, pp)

/**
 * Set pin direction input/output
 */
#define PP_TRIS_READ_PIN(pp)         PP_BIT_READ( PINPOINTER_ADDR_TRIS, pp)
#define PP_IS_PIN_INPUT(pp)          ( PP_BIT_READ( PINPOINTER_ADDR_TRIS, pp) != 0 )
#define PP_IS_PIN_OUTPUT(pp)         ( PP_BIT_READ( PINPOINTER_ADDR_TRIS, pp) == 0 )
#define PP_SET_PIN_AS_INPUT(pp)      PP_BIT_SET(   PINPOINTER_ADDR_TRIS, pp)
#define PP_SET_PIN_AS_OUTPUT(pp)     PP_BIT_CLEAR( PINPOINTER_ADDR_TRIS, pp)

/**
 * Modify LAT values
 */
#define PP_LAT_READ_PIN(   pp)       PP_BIT_READ(   PINPOINTER_ADDR_LAT, pp)
#define PP_LAT_WRITE_PIN(  pp, VAL)  PP_BIT_WRITE(  PINPOINTER_ADDR_LAT, pp, VAL )
#define PP_LAT_CLEAR_PIN(  pp)       PP_BIT_CLEAR(  PINPOINTER_ADDR_LAT, pp)
#define PP_LAT_SET_PIN(    pp)       PP_BIT_SET(    PINPOINTER_ADDR_LAT, pp)
#define PP_LAT_TOGGLE_PIN( pp)       PP_BIT_TOGGLE( PINPOINTER_ADDR_LAT, pp)

/* public typedef declaration ------------------------------------------------------------------- */

/**
 * Typedef declaration
 */
typedef enum pinpointer_e pinpointer_t;

/* unit test PINPOINTER_TEST ------------------------------------------------------------------------------- */

#if defined( PINPOINTER_TEST ) && PINPOINTER_TEST == 1

#ifdef __XC
#pragma warning disable 759 // expression generates no code
#endif

#include <assert.h>

static void pinpointer_test_pre()
{
	TRISBbits.RB7 = 1; assert( TRISBbits.RB7 == 1 );
	TRISBbits.RB7 = 0; assert( TRISBbits.RB7 == 0 );
	PORTBbits.RB7 = 1; assert( PORTBbits.RB7 == 1 );
	TRISBbits.RB6 = 1; assert( TRISBbits.RB6 == 1 );
	TRISBbits.RB6 = 0; assert( TRISBbits.RB6 == 0 );
	PORTBbits.RB6 = 1; assert( PORTBbits.RB6 == 1 );
}

static void pinpointer_test_1(void)
{
	pinpointer_t pp = PP_RB7;
	assert( PP_PORT_PNT(pp) == &PORTB );
	assert( PP_GET_PIN(pp) == 1 << 7 );

#define ADDR PINPOINTER_ADDR_PORT
	void *a = ((unsigned char*)( ADDR + PP_GET_REG_IDX(pp) ));

	TRISBbits.RB7 = 1; assert( PP_TRIS_READ_PIN(pp) != 0 );
	TRISBbits.RB7 = 0; assert( PP_TRIS_READ_PIN(pp) == 0 );
	PP_SET_PIN_AS_INPUT(pp); assert( TRISBbits.RB7 == 1 );
	PP_SET_PIN_AS_OUTPUT(pp); assert( TRISBbits.RB7 == 0 );
	TRISBbits.RB7 = 1; assert( PP_IS_PIN_INPUT(pp) );
	TRISBbits.RB7 = 0; assert( PP_IS_PIN_OUTPUT(pp) );
	PP_SET_PIN_AS_OUTPUT(pp);
	volatile char var;
	PORTBbits.RB7 = 1; assert( PP_READ_PIN(pp) != 0 );
	PORTBbits.RB7 = 0; assert( PP_READ_PIN(pp) == 0 );
	PP_SET_PIN(pp); assert( PORTBbits.RB7 == 1 );
	PP_CLEAR_PIN(pp); assert( PORTBbits.RB7 == 0 );
	PP_WRITE_PIN(pp, 1); assert( PORTBbits.RB7 == 1 );
	PP_WRITE_PIN(pp, 0); assert( PORTBbits.RB7 == 0 );
	var = 1; PP_WRITE_PIN(pp, var); assert( PORTBbits.RB7 == 1 );
	var = 0; PP_WRITE_PIN(pp, var); assert( PORTBbits.RB7 == 0 );
	PP_TOGGLE_PIN(pp); assert( PORTBbits.RB7 == 1 );
	PP_TOGGLE_PIN(pp); assert( PORTBbits.RB7 == 0 );
}


static void pinpointer_test_pnt(pinpointer_t *pp)
{
	volatile char var;

	assert( PP_PORT_PNT(*pp) == &PORTB );
	assert( PP_GET_PIN(*pp) == 1 << 7 );

	TRISBbits.RB7 = 1; assert( PP_TRIS_READ_PIN(*pp) != 0 );
	TRISBbits.RB7 = 0; assert( PP_TRIS_READ_PIN(*pp) == 0 );
	PP_SET_PIN_AS_INPUT(*pp); assert( TRISBbits.RB7 == 1 );
	PP_SET_PIN_AS_OUTPUT(*pp); assert( TRISBbits.RB7 == 0 );
	TRISBbits.RB7 = 1; assert( PP_IS_PIN_INPUT(*pp) );
	TRISBbits.RB7 = 0; assert( PP_IS_PIN_OUTPUT(*pp) );
	PP_SET_PIN_AS_OUTPUT(*pp);
	volatile char var;
	PORTBbits.RB7 = 1; assert( PP_READ_PIN(*pp) != 0 );
	PORTBbits.RB7 = 0; assert( PP_READ_PIN(*pp) == 0 );
	PP_SET_PIN(*pp); assert( PORTBbits.RB7 == 1 );
	PP_CLEAR_PIN(*pp); assert( PORTBbits.RB7 == 0 );
	PP_WRITE_PIN(*pp, 1); assert( PORTBbits.RB7 == 1 );
	PP_WRITE_PIN(*pp, 0); assert( PORTBbits.RB7 == 0 );
	var = 1; PP_WRITE_PIN(*pp, var); assert( PORTBbits.RB7 == 1 );
	var = 0; PP_WRITE_PIN(*pp, var); assert( PORTBbits.RB7 == 0 );
	PP_TOGGLE_PIN(*pp); assert( PORTBbits.RB7 == 1 );
	PP_TOGGLE_PIN(*pp); assert( PORTBbits.RB7 == 0 );
}

static void pinpointer_test_2()
{
	pinpointer_t pp1 = PP_RB7;
	pinpointer_t pp2 = PP_RB6;

	PP_SET_PIN_AS_OUTPUT(pp1);
	PP_SET_PIN_AS_OUTPUT(pp2);
	PP_SET_PIN(pp1);
	PP_WRITE_PIN(pp2, PP_READ_PIN(pp1));
	assert( PP_READ_PIN(pp2) == 1 );
	assert( PP_READ_PIN(pp2) == PP_READ_PIN(pp1) );
	PP_CLEAR_PIN(pp1);
	PP_WRITE_PIN(pp2, PP_READ_PIN(pp1));
	assert( PP_READ_PIN(pp2) == 0 );
	assert( PP_READ_PIN(pp2) == PP_READ_PIN(pp1) );
}

static void pinpointer_test()
{
	static_assert( PP_GET_REG_IDX(PP_RA0) == 0);
	static_assert( PP_GET_PIN(PP_RA0) == 1<<0 );
	static_assert( PP_GET_REG_IDX(PP_RB5) == 1);
	static_assert( PP_GET_PIN(PP_RB5) == 1<<5 );
	static_assert( PP_GET_REG_IDX(PP_RC7) == 2);
	static_assert( PP_GET_PIN(PP_RC7) == 1<<7 );
	static_assert( PP_GET_REG_IDX(PP_RD2) == 3);
	static_assert( PP_GET_PIN(PP_RD2) == 1<<2 );
	static_assert( PP_GET_REG_IDX(PP_RE3) == 4);
	static_assert( PP_GET_PIN(PP_RE3) == 1<<3 );

	{
		const pinpointer_t pp = PP_RB7;
		assert( PP_GET_REG_IDX(pp) == 1 );
		assert( PP_GET_PIN(pp) == 1<<7 );
	}

	pinpointer_test_pre();
	pinpointer_test_1();
	pinpointer_test_2();
	pinpointer_t pp = PP_RB7;
	pinpointer_test_pnt(&pp);
}

#endif // PINPOINTER_TEST

/* EOF PINPOINTER_TEST ------------------------------------------------------------------------------- */

#endif /* PINPOINTER_H_ */
