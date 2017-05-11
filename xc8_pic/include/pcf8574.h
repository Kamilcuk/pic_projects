/*
 *        File: pcf8574.h
 *  Created on: 10.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef PCF8574_H_
#define PCF8574_H_

#include "bit.h"
#include "smbus.h"

typedef unsigned char pcf8574_t;

#define PCF8574_ADDR(A)      ( 0x40 | ( (A) << 1) )
#define PCF8574A_ADDR(A)     ( 0x70 | ( (A) << 1) )

#define PCF8574_READ(addr)         smbus_read_quick(addr)
#define PCF8574_WRITE(addr, byte)  smbus_write_quick(addr, byte)
#define PCF8574_TOGGLE(addr)       smbus_write_quick(addr, ~i2c_read_simple8(PCF8574_ADDRESS(A)))

#define PCF8574_WRITEPIN(state, addr, PIN, VAL) do { \
	BIT_WRITE(state, PIN, VAL); \
	smbus_write_quick(addr, state); \
}while(0)

#define PCF8574_READPIN(state, addr, PIN) \
	( BIT_SET(state, PIN) , smbus_write_quick(addr, state) , BIT_READ( smbus_read_quick(addr), PIN ) )

#define PCF8574_TOGGLEPIN(state, addr, PIN) \
	PCF8574_WRITEPIN(state, addr, PIN, ~PCF8574_READPIN(state, addr, PIN))}while(0)

#endif /* PCF8574_H_ */
