/*
 *        File: i2c_ex.h
 *  Created on: 06.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef I2C_EX_H_
#define I2C_EX_H_

#include <plib/i2c.h>

#include <stdint.h>

#define i2c_open_master(clock_speed_in_herz) do{ \
	CloseI2C(); \
	OpenI2C(MASTER, SLEW_OFF); \
	SSPADD = ( ( ( _XTAL_FREQ / 4 ) / ( clock_speed_in_herz ) ) - 1 ); \
	IdleI2C(); \
}while(0);

void i2c_read(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen);

uint8_t i2c_read8(uint8_t addr, uint8_t command);

uint16_t i2c_read16(uint8_t addr, uint8_t command);

void i2c_write(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen);

void i2c_write8(uint8_t addr, uint8_t command, uint8_t data);

void i2c_write16(uint8_t addr, uint8_t command, uint8_t data_low, uint8_t data_high);

#endif /* I2C_EX_H_ */
