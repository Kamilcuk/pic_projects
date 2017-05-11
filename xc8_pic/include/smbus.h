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

#ifndef SMBUS_H_
#define SMBUS_H_

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
	SSPADD = ( ( ( _XTAL_FREQ / 4 ) / ( clock_speed_in_herz ) ) - 1 ); \
	IdleI2C(); \
}while(0);

/**
 * 5.5.2. Send byte
 */
void smbus_write_quick(uint8_t addr, uint8_t data);
/**
 * 5.5.3. Receive byte
 */
uint8_t smbus_read_quick(uint8_t addr);

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
void smbus_read_block(uint8_t addr, uint8_t command, uint8_t *pnt, uint8_t pntlen);




#endif /* SMBUS_H_ */
