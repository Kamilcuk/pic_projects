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

#ifndef PIN_POINTER_H_
#define PIN_POINTER_H_

#include <xc.h> // HIGH_BYTE() LOW_BYTE() PORTA LAT TRISA
#include <bitmask.h> // BITMASK_{READ,WRITE,TOGGLE,...}
#include <cdefs.h> // __CONCAT

/**
 * Pointers offset
 */
#define PINPOINTER_ADDR_PORT ( &PORTA )
#define PINPOINTER_ADDR_LAT  ( &LATA  )
#define PINPOINTER_ADDR_TRIS ( &TRISA )

#if 1 // PP_USE_16_BITS

enum pinPointer_e {
	// reg=1; for i in A B C D E; do mask=1; for j in 0 1 2 3  4 5 6 7 ; do printf "PP_R${i}${j}=0x%03x," $(( (${reg}<<8)+${mask} )); mask=$((mask<<1)); done; reg=$((reg+1)); echo; done;
	PP_RA0=0x101,PP_RA1=0x102,PP_RA2=0x104,PP_RA3=0x108,PP_RA4=0x110,PP_RA5=0x120,PP_RA6=0x140,PP_RA7=0x180,
	PP_RB0=0x201,PP_RB1=0x202,PP_RB2=0x204,PP_RB3=0x208,PP_RB4=0x210,PP_RB5=0x220,PP_RB6=0x240,PP_RB7=0x280,
	PP_RC0=0x301,PP_RC1=0x302,PP_RC2=0x304,PP_RC3=0x308,PP_RC4=0x310,PP_RC5=0x320,PP_RC6=0x340,PP_RC7=0x380,
	PP_RD0=0x401,PP_RD1=0x402,PP_RD2=0x404,PP_RD3=0x408,PP_RD4=0x410,PP_RD5=0x420,PP_RD6=0x440,PP_RD7=0x480,
	PP_RE0=0x501,PP_RE1=0x502,PP_RE2=0x504,PP_RE3=0x508,PP_RE4=0x510,PP_RE5=0x520,PP_RE6=0x540,PP_RE7=0x580,
};
#define PP_GET_REG(WHAT, pp)        (*(unsigned char*)( __CONCAT( PINPOINTER_ADDR_ , WHAT ) + HIGH_BYTE( pp ) ) )
#define PP_GET_PIN(WHAT, pp)        ( LOW_BYTE( pp ) )

#else // PP_USE_8_BITS

enum pinPointer_e {
	// reg=1; for i in A B C D E; do for j in $(seq 0 7); do printf "PP_R${i}${j} = 0x%02x," $(( ${reg}<<4 | ${j} )); done; reg=${reg+1}; echo; done;
	PP_RA0 = 0x11,PP_RA1 = 0x12,PP_RA2 = 0x13,PP_RA3 = 0x14,PP_RA4 = 0x15,PP_RA5 = 0x16,PP_RA6 = 0x17,PP_RA7 = 0x18,
	PP_RB0 = 0x11,PP_RB1 = 0x12,PP_RB2 = 0x13,PP_RB3 = 0x14,PP_RB4 = 0x15,PP_RB5 = 0x16,PP_RB6 = 0x17,PP_RB7 = 0x18,
	PP_RC0 = 0x11,PP_RC1 = 0x12,PP_RC2 = 0x13,PP_RC3 = 0x14,PP_RC4 = 0x15,PP_RC5 = 0x16,PP_RC6 = 0x17,PP_RC7 = 0x18,
	PP_RD0 = 0x11,PP_RD1 = 0x12,PP_RD2 = 0x13,PP_RD3 = 0x14,PP_RD4 = 0x15,PP_RD5 = 0x16,PP_RD6 = 0x17,PP_RD7 = 0x18,
	PP_RE0 = 0x11,PP_RE1 = 0x12,PP_RE2 = 0x13,PP_RE3 = 0x14,PP_RE4 = 0x15,PP_RE5 = 0x16,PP_RE6 = 0x17,PP_RE7 = 0x18,
}
#define PP_GET_REG(WHAT, pp)        (*(unsigned char*)( __CONCAT( PINPOINTER_ADDR_ , WHAT ) + ( pp >> 4 ) ) )
#define PP_GET_PIN(WHAT, pp)        ( 1<<( (pp) & 0x0f ) )

#endif

typedef enum pinPointer_e pinPointer_t;

/**
 * Actual implementation using bit operations
 */
#define PP_READ(  WHAT, pp)           BITMASK_READ( PP_GET_REG( WHAT , pp ) , PP_GET_PIN( WHAT , pp ) )
#define PP_CLEAR( WHAT, pp)          BITMASK_CLEAR( PP_GET_REG( WHAT , pp ) , PP_GET_PIN( WHAT , pp ) )
#define PP_TOGGLE(WHAT, pp)         BITMASK_TOGGLE( PP_GET_REG( WHAT , pp ) , PP_GET_PIN( WHAT , pp ) )
#define PP_SET(   WHAT, pp)            BITMASK_SET( PP_GET_REG( WHAT , pp ) , PP_GET_PIN( WHAT , pp ) )
#define PP_WRITE( WHAT, pp, VAL)     BITMASK_WRITE( PP_GET_REG( WHAT , pp ) , PP_GET_PIN( WHAT , pp ) , VAL )

/**
 * wrappers
 * for j in PORT LAT TRIS; do for i in READ CLEAR TOGGLE SET WRITE; do echo "#define PP_${i}_${j}(pp) PP_${i}(${j}, pp)"; done; echo; done
 */
#define PP_READ_PORT(pp)   PP_READ(PORT, pp)
#define PP_CLEAR_PORT(pp)  PP_CLEAR(PORT, pp)
#define PP_TOGGLE_PORT(pp) PP_TOGGLE(PORT, pp)
#define PP_SET_PORT(pp)    PP_SET(PORT, pp)
#define PP_WRITE_PORT(pp)  PP_WRITE(PORT, pp)

#define PP_READ_LAT(pp)    PP_READ(LAT, pp)
#define PP_CLEAR_LAT(pp)   PP_CLEAR(LAT, pp)
#define PP_TOGGLE_LAT(pp)  PP_TOGGLE(LAT, pp)
#define PP_SET_LAT(pp)     PP_SET(LAT, pp)
#define PP_WRITE_LAT(pp)   PP_WRITE(LAT, pp)

#define PP_READ_TRIS(pp)   PP_READ(TRIS, pp)
#define PP_CLEAR_TRIS(pp)  PP_CLEAR(TRIS, pp)
#define PP_TOGGLE_TRIS(pp) PP_TOGGLE(TRIS, pp)
#define PP_SET_TRIS(pp)    PP_SET(TRIS, pp)
#define PP_WRITE_TRIS(pp)  PP_WRITE(TRIS, pp)

#if 0
void test() {
	pinPointer_t pp1 = PP_RA0;
	pinPointer_t pp2 = PP_RA0;
	PP_CLEAR(LAT, pp1);
	PP_SET(TRIS, pp2);
	PP_WRITE(PORT, pp1, 1);
	PP_TOGGLE(PORT, pp2);
	if ( PP_READ(PORT, pp1) ) {
		PP_CLEAR(PORT, pp2);
	} else {
		PP_SET(PORT, pp2);
	}
}
#endif

#endif /* PIN_POINTER_H_ */
