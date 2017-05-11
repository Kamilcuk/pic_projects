/*
 *        File: i2c_ex.c
 *  Created on: 06.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <plib/i2c.h> // RestartI2C IdleI2C StartI2C WriteI2C ReadI2C NotAckI2C StopI2C
#include <GenericTypeDefs.h> // UINT16_VAL
#include <smbus.h>
#include <stdint.h>

#define WRITE_BIT 0x00
#define READ_BIT  0x01

void smbus_write_quick(uint8_t addr, uint8_t data)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(data);
	StopI2C();
}

uint8_t smbus_read_quick(uint8_t addr)
{
	uint8_t data;
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	data = ReadI2C();
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


void smbus_read_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	RestartI2C();
	WriteI2C(addr|READ_BIT);
	getsI2C(pnt, pntlen);
	NotAckI2C();
	StopI2C();
}

void smbus_write_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	IdleI2C();
	StartI2C();
	WriteI2C(addr|WRITE_BIT);
	WriteI2C(command);
	while(pntlen) {
		WriteI2C(*pnt);
		++pnt;
		--pntlen;
	}
	StopI2C();
}
