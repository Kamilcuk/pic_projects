/*
 *        File: pin_pointer.h
 *  Created on: 10.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef PIN_POINTER_H_
#define PIN_POINTER_H_

#include <xc.h> // HIGH_BYTE , LOW_BYTE

/*
 * do not use that, very cpu and memory expensive
 */

enum pinPointer_e {
	PP_RA0=0x101,PP_RA1=0x102,PP_RA2=0x104,PP_RA3=0x108,PP_RA4=0x110,PP_RA5=0x120,PP_RA6=0x140,PP_RA7=0x180,
	PP_RB0=0x201,PP_RB1=0x202,PP_RB2=0x204,PP_RB3=0x208,PP_RB4=0x210,PP_RB5=0x220,PP_RB6=0x240,PP_RB7=0x280,
	PP_RC0=0x301,PP_RC1=0x302,PP_RC2=0x304,PP_RC3=0x308,PP_RC4=0x310,PP_RC5=0x320,PP_RC6=0x340,PP_RC7=0x380,
	PP_RD0=0x401,PP_RD1=0x402,PP_RD2=0x404,PP_RD3=0x408,PP_RD4=0x410,PP_RD5=0x420,PP_RD6=0x440,PP_RD7=0x480,
	PP_RE0=0x501,PP_RE1=0x502,PP_RE2=0x504,PP_RE3=0x508,PP_RE4=0x510,PP_RE5=0x520,PP_RE6=0x540,PP_RE7=0x580,
};

#define PINPOINTER_ADDR_PORT 0xF80
#define PINPOINTER_ADDR_LAT  0xF89
#define PINPOINTER_ADDR_TRIS 0xF92

#define PP_OPS(what, PP, OPS) \
	(*(unsigned char*)( PINPOINTER_ADDR_ ## what + HIGH_BYTE( PP ) ) OPS LOW_BYTE( PP ) )

#define PP_READ(what, PP)   PP_OPS(what, PP, &    )
#define PP_CLEAR(what, PP)  PP_OPS(what, PP, &= ~ )
#define PP_TOGGLE(what, PP) PP_OPS(what, PP, ^=   )
#define PP_SET(what, PP)    PP_OPS(what, PP, |=   )

#endif /* PIN_POINTER_H_ */
