/*
 * system.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <system_defaults.h>
#include <common.h> // PORT() TRIS()

/*
| PIC18F2550 | description | to |
| ----- | --- | --- |
| left | | |
| RA0 | TACHO channel A out | 4051 A |
| RA1 | TACHO channel B out | 4051 B |
| RA2 | TACHO channel C out | 4051 C |
| RA3 | onewire | pull-up transistor |
| RA4 | onewire | data DS18B20 |
| RA5 | out | MCP4812 no. 1 chip select |
| RC0 | USB sense in | USB +5V |
| RC1 | out | MCP4812 no. 2 chip select |
| RC2 | TACHO in / CCP1 | 4051 Z |
| right  | | |
| RB7 | in | button |
| RB6 | in | button |
| RB5 | in | button |
| RB4 | in | button |
| RB3 | soft SPI SCK | MCP4812 SCK |
| RB2 | soft SPI SDI | MCP4812 SDA |
| RB1 | I2C SCL | TSL2561 SCL |
| RB0 | I2C SDA | TSL2561 SDA |
| RC7 | UART | |
| RC6 | UART | |
*/

#define OW_PULLUP_PORTPIN       A,3 // onewire.h
#define OW_DATA_PORTPIN         A,4 // onewire.h
#define FAN_CS1_PORTPIN         A,5

#define USB_BUS_SENSE_PORTPIN   C,0
#define FAN_CS2_PORTPIN         C,1

#define SW_SPI_SCK_PORTPIN      B,3 // swSpiWrite.h
#define SW_SPI_OUT_PORTPIN      B,2 // swSpiWrite.h


// usb
//#define USE_USB_BUS_SENSE_IO  1
//#define USB_BUS_SENSE         PORT1(USB_BUS_SENSE_PORTPIN)
#define USBHID_STDIO_ENABLE   1
#define USB_INTERRUPT         1
#include <usbhid_stdio/usb_config.h>

#define CMDLINE_ENABLED

#define ASSERT_USE_PRINTF 1

// onewire.h
#include <common.h> // GETPORT() GETTRIS()
#define OW_ONE_BUS
#define OW_GET_IN()           ( PORT1(OW_DATA_PORTPIN) )
#define OW_OUT_LOW()          ( PORT1(OW_DATA_PORTPIN) = 0 )
#define OW_OUT_HIGH()         ( PORT1(OW_DATA_PORTPIN) = 1 )
#define OW_DIR_IN()           ( TRIS1(OW_DATA_PORTPIN) = TRIS_IN )
#define OW_DIR_OUT()          ( TRIS1(OW_DATA_PORTPIN) = TRIS_OUT )

#include <smbus.h>
#define TSL2561_read8_callback  smbus_read_byte
#define TSL2561_write8_callback smbus_write_byte
#define TSL2561_read16_callback smbus_read_word

#define SYSTICK_USE_TIMER 0
#define SYSTICK_TIMER_PRESCALER 4

#endif //SYSTEM_H
