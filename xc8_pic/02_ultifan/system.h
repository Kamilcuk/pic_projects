/*
 * system.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#ifndef SYSTEM_H
#define SYSTEM_H

/*
| PIC18F2550 | description | to |
| ----- | --- | --- |
| left | | |
| RA0 | TACHO channel A out | 4051 A |
| RA1 | TACHO channel B out | 4051 B |
| RA2 | TACHO channel C out | 4051 C |
| RA3 | onewire | DS18B20 |
| RA4 | | |
| RA5 | | |
| RC0 | USB sense in | USB +5V |
| RC1 | | |
| RC2 | TACHO in / CCP1| 4051 X |
| right  | | |
| RB7 | in | button |
| RB6 | out | diode |
| RB5 | out | MCP4812 no. 2 chip select |
| RB4 | out | MCP4812 no. 1 chip select |
| RB3 | software SCK | MCP4812 SCK |
| RB2 | software SDI | MCP4812 SDA |
| RB1 | SCL | TSL2561 SCL |
| RB0 | SDA | TSL2561 SDA |
| RC7 | UART | |
| RC6 | UART | |
*/

#include <system_defaults.h>

#define USBHID_STDIO_ENABLE  1
#define USE_USB_BUS_SENSE_IO 1
#define USB_BUS_SENSE        PORTCbits.RC0
#define USB_INTERRUPT        1
#include <usbhid_stdio/usb_config.h>

#define CMDLINE_ENABLED

#define ASSERT_USE_PRINTF 1

// onewire.h
#include <common.h> // GETPORT() GETTRIS()
#define OW_ONE_BUS
#define OW_PORT       A
#define OW_PIN        0
#define OW_GET_IN()   ( PORT(OW_PORT, OW_PIN) )
#define OW_OUT_LOW()  ( PORT(OW_PORT, OW_PIN) = 0 )
#define OW_OUT_HIGH() ( PORT(OW_PORT, OW_PIN) = 1 )
#define OW_DIR_IN()   ( TRIS(OW_PORT, OW_PIN) = 1 )
#define OW_DIR_OUT()  ( TRIS(OW_PORT, OW_PIN) = 0 )

// swSpiWrite.h
#define SW_SPI_SCK_PORT B
#define SW_SPI_SCK_PIN  3
#define SW_SPI_OUT_PORT B
#define SW_SPI_OUT_PIN  2

#include "../include/smbus.h"
#define TSL2561_read8_callback  smbus_read_byte
#define TSL2561_write8_callback smbus_write_byte
#define TSL2561_read16_callback smbus_read_word

#include <hd44780-config.h>

#define SYSTICK_USE_TIMER 0
#define SYSTICK_TIMER_PRESCALER 32

#endif //SYSTEM_H
