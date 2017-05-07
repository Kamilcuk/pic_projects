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

#include "i2c_ex.h"

#include <plib/i2c.h>
#include <GenericTypeDefs.h>

#define WRITE_BIT 0x00
#define READ_BIT  0x01

/* ------------------------------------------------------------ */

static void i2c_start_write_command(uint8_t addr, uint8_t command)
{
	IdleI2C();

	StartI2C();

	WriteI2C((addr<<1)|WRITE_BIT);

	WriteI2C(command);
}

/* ------------------------------------------------------------ */

void i2c_read(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	i2c_start_write_command(addr, command);

	RestartI2C();

	WriteI2C((addr<<1)|READ_BIT);

	getsI2C(pnt, pntlen);

	NotAckI2C();

	StopI2C();
}

uint8_t i2c_read8(uint8_t addr, uint8_t command)
{
	uint8_t data;

	i2c_start_write_command(addr, command);

	RestartI2C();

	WriteI2C((addr<<1)|READ_BIT);

	data = ReadI2C();

	NotAckI2C();

	StopI2C();

	return data;
}

uint16_t i2c_read16(uint8_t addr, uint8_t command)
{
	UINT16_VAL data;

	i2c_start_write_command(addr, command);

	RestartI2C();

	WriteI2C((addr<<1)|READ_BIT);

	data.byte.LB = ReadI2C();
	AckI2C();

	data.byte.HB = ReadI2C();
	NotAckI2C();

	StopI2C();

	return data.Val;
}

void i2c_write(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen)
{
	i2c_start_write_command(addr, command);

	while(pntlen) {
		WriteI2C(*pnt);
		++pnt;
		--pntlen;
	}

	StopI2C();
}

void i2c_write8(uint8_t addr, uint8_t command, uint8_t data)
{
	i2c_start_write_command(addr, command);

	WriteI2C(data);

	StopI2C();
}

void i2c_write16(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high)
{
	i2c_start_write_command(addr, command);

	WriteI2C(data_low);

	WriteI2C(data_high);

	StopI2C();
}
