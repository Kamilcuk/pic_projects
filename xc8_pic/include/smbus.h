/*
 *        File: i2c_ex.h
 *  Created on: 06.05.2017
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

#ifndef SMBUS_H_
#define SMBUS_H_

#include <xc_ex.h>  // FUCK_XC8_CAST_TO_LONG

#include <plib/i2c.h> // for smbus_open_master
#include <stdint.h>

/**
 * documentation: http://smbus.org/specs/smbus20.pdf
 */

/**
 * plib, open i2c as master
 */
#define smbus_open_master(clock_speed_in_herz) do{ \
	CloseI2C(); \
	OpenI2C(MASTER, SLEW_OFF); \
	SSPADD = FUCK_XC8_CAST_TO_LONG * ( ( _XTAL_FREQ / 4 / (clock_speed_in_herz) ) - 1 ); \
	IdleI2C(); \
}while(0);

/**
 * 5.5.1. Quick command
 */
void smbus_quick_command(uint8_t addr);

/**
 * 5.5.2. Send byte
 */
void smbus_send_byte(uint8_t addr, uint8_t data);
/**
 * 5.5.3. Receive byte
 */
uint8_t smbus_receive_byte(uint8_t addr);

/**
 * 5.5.4. Write byte/word
 */
void smbus_write_byte(uint8_t addr, uint8_t command, uint8_t data);
/**
 * 5.5.5. Read byte/word
 */
uint8_t smbus_read_byte(uint8_t addr, uint8_t command);

/**
 * 5.5.4. Write byte/word
 */
void smbus_write_word(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high);
/**
 * 5.5.5. Read byte/word
 */
uint16_t smbus_read_word(uint8_t addr, uint8_t command);

/**
 * 5.5.6. Process call
 */
uint16_t smbus_process_call(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high);

/**
 * 5.5.7. Block write/read
 */
void smbus_write_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen);
/**
 * 5.5.7. Block write/read
 * Returns number bytes read
 */
uint8_t smbus_read_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen);




#endif /* SMBUS_H_ */
