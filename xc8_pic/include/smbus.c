/*
 *        File: i2c_ex.c
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

#include <plib/i2c.h> // RestartI2C IdleI2C StartI2C WriteI2C ReadI2C NotAckI2C StopI2C
#include <GenericTypeDefs.h> // UINT16_VAL
#include <smbus.h>
#include <stdint.h>

#define WRITE_BIT 0x00
#define READ_BIT  0x01

void smbus_quick_command(uint8_t addr)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	StopI2C();
}

void smbus_send_byte(uint8_t addr, uint8_t data)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(data);
	StopI2C();
}

uint8_t smbus_receive_byte(uint8_t addr)
{
	uint8_t data;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|READ_BIT);
	data = ReadI2C();
	NotAckI2C();
	StopI2C();
	return data;
}


void smbus_write_byte(uint8_t addr, uint8_t command, uint8_t data)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	WriteI2C(data);
	StopI2C();
}

uint8_t smbus_read_byte(uint8_t addr, uint8_t command)
{
	uint8_t data;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	RestartI2C();
	WriteI2C(addr|READ_BIT);
	data = ReadI2C();
	NotAckI2C();
	StopI2C();
	return data;
}


void smbus_write_word(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	WriteI2C(data_low);
	WriteI2C(data_high);
	StopI2C();
}

uint16_t smbus_read_word(uint8_t addr, uint8_t command)
{
	UINT16_VAL data;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	RestartI2C();
	WriteI2C(addr|READ_BIT);
	data.byte.LB = ReadI2C();
	AckI2C();
	data.byte.HB = ReadI2C();
	NotAckI2C();
	StopI2C();
	return data.Val;
}


uint16_t smbus_process_call(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high)
{
	UINT16_VAL data;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	WriteI2C(data_low);
	WriteI2C(data_high);
	RestartI2C();
	WriteI2C(addr|READ_BIT);
	data.byte.LB = ReadI2C();
	AckI2C();
	data.byte.HB = ReadI2C();
	NotAckI2C();
	StopI2C();
	return data.Val;
}


void smbus_write_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	WriteI2C(pntlen);
	while(pntlen) {
		WriteI2C(*pnt);
		++pnt;
		--pntlen;
	}
	StopI2C();
}

uint8_t smbus_read_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	uint8_t bytecount, min;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	RestartI2C();
	WriteI2C(addr|READ_BIT);
	bytecount = ReadI2C();
	min = bytecount < pntlen ? bytecount : pntlen;
	if ( min ) {
		AckI2C();
		for(;;) {
			*pnt++ = ReadI2C();
			--min;
			if ( min ) {
				break;
			}
			AckI2C();
		}
	}
	NotAckI2C();
	StopI2C();
	return bytecount;
}

