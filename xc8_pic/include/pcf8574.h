/*
 *        File: pcf8574.h
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

#ifndef PCF8574_H_
#define PCF8574_H_

#include "bit.h"
#include "smbus.h"

typedef unsigned char pcf8574_t;

#define PCF8574_ADDR(A)      ( 0x40 | ( (A) << 1) )
#define PCF8574A_ADDR(A)     ( 0x70 | ( (A) << 1) )

#define PCF8574_READ(addr)         smbus_receive_byte(addr)
#define PCF8574_WRITE(addr, byte)  smbus_send_byte(addr, byte)
#define PCF8574_TOGGLE(addr)       PCF8574_WRITE(addr, ~PCF8574_READ(addr))

#define PCF8574_WRITEPIN(state, addr, PIN, VAL) do { \
	BIT_WRITE(state, PIN, VAL); \
	smbus_send_byte(addr, state); \
}while(0)

#define PCF8574_READPIN(state, addr, PIN) \
	( BIT_SET(state, PIN) , smbus_send_byte(addr, state) , BIT_READ( smbus_receive_byte(addr), PIN ) )

#define PCF8574_TOGGLEPIN(state, addr, PIN) \
	PCF8574_WRITEPIN(state, addr, PIN, ~PCF8574_READPIN(state, addr, PIN))}while(0)

#endif /* PCF8574_H_ */
