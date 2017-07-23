/*
 *        File: hd44780-config-2xpcf8574.h
 *  Created on: 11.05.2017
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

#ifndef HD44780_CONFIG_2XPCF8574_H_
#define HD44780_CONFIG_2XPCF8574_H_

#include <xc.h> // Nop(); __delay_ms() __delay_us()
#include <pcf8574.h>

#define PCF8574_DATA PCF8574A_ADDR( 0b111 )
#define PCF8574_FLAG PCF8574A_ADDR( 0b101 )

/**
 * Connections:
 *
 * PCF8574_DATA: address 0b101
 * P0 - DB0
 * P1 - DB1
 * P2 - DB2
 * P3 - DB3
 * P4 - DB4
 * P5 - DB5
 * P6 - DB6
 * P7 - DB7
 *
 * PCF8574_FLAG: address 0b111
 * P0 - RS
 * P1 - RW
 * P2 - Enable Controller 1
 *
 */

/* ---------------------------------- global options configuration ------------------------------- */

/**
 * Maximum number of hd44780 displays connected to microcontroller
 */
#define HD44780_NUM_CONTROLLERS   1

/**
 * Number of rows per every hd44780 display
 */
#define HD44780_DISP_ROWS         2

/**
 * number of columns per every hd44780 display
 */
#define HD44780_DISP_COLS        40

/**
 * 4-bit or 8-bit data operation?s
 * @param 0 - 8-bit mode, 1 - 4-bit mode
 */
#define HD44780_MODE_4_BIT        0

/**
 * If disabled, after every operation we check busyflag at max BUSYFLAG_STUCK times.
 * If enabled, after every operation we wait a predefined time.
 * @param 0 - bf checking enabled, 1 - bf checking disabled
 */
#define HD44780_NO_BF_CHECKING    0

/**
 * If enabled, after every character written, we check if the character was properly written.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_CHECK_EVERY_WRITE 1

/**
 * This option only matters, when HD44780_CHECK_EVERY_WRITE is enabled.
 * Check this many times (uint8_t) before giving up checking this display after a write.
 */
#define HD44780_CHECK_EVERY_WRITE_MAX 3

/**
 * Enable counting of characters read or wrote
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_COUNTERS_ENABLE          1

/**
 * Type of hd44780 counter, uint16_t is too short, but good for debugging.
 * @param uint8_t uint16_t uint24_t or uint32_t
 */
#define HD44780_COUNTERS_TYPE     uint16_t

/**
 * Enable the hd44780_check function, which checks
 * and corrects errors on displays.
 * Uses much memory to store whole display state.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_CHECKER           1

/**
 * If enabled, disables the function hd44780_recv()
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_WRITE_ONLY        0

/* -------------------------------- delays configuration -------------------------------- */

/**
 * hd44780 documentation page 24 Return home Execution time = 1.52 ms
 */
#define HD44780_LONG_DELAY()            __delay_ms(2)
/**
 * hd44780 documentation page 24 All others execution time = 37 us + extra 3us for cursor = 40us
 */
#define HD44780_NORMAL_DELAY()          __delay_us(40)

/**
 * delays from hd44780 documentation page 52 - DC Characteristics (VCC = 4.5 to 5.5 V, Ta = –30 to +75°C*3)
 * for PIC18f2550 with XTAL=48Mhz every Nop is 83ns
 *
 * Notice: Data set-up time | t_DSW | 80 ns is not used.
 * The DB0 through DB7 lines are set up before hd44780_capable_callback, which allows to omit this delay completely.
 * Notice: Data hold time | t_H or t_DHR | 10 (or 5) ns is quite short and therefore not used.
 * After data write we return from recv function, data hold time is not needed (there will be several
 * instructions before we change R/W and E lines states.
 * Notice: The microcontroler has it's own I/O "Port Output Rise Time" and "Port Output Fall Time"
 * It's good to add two additional Nop's to the delays, to let the output signal rise (or fall).
 * Notice: I have written the minimum values in comments. However, these are too short for me,
 * Maybe too long cable or whatever. Found out, that it works stable with 2 us.
 */
/**
 * Address set-up time | t_DSW | 40 ns
 */
#define HD44780_ADDRESS_SET_UP_TIME()    __delay_us(2)
/**
 * Enable pulse width (high level) | PW_EH | 230 ns
 */
#define HD44780_ENABLE_PULSE_WIDTH()     __delay_us(2)
/**
 * Data set-up time | t_DSW | 80 ns
 */
#define HD44780_DATA_SET_UP_TIME()       __delay_us(2)
/**
 * Data hold time | t_H or t_DHR | 10 (or 5) ns
 */
#define HD44780_DATA_HOLD_TIME()         __delay_us(2)

/**
 * Additional delay when busyflag checking.or when doing two 4-bit operations
 * Enable cycle time | t_cyclE | 500 ns
 * This value should be at longer then: t_cyclE - PW_EH - t_H =~ 270 ns
 */
#define HD44780_EXTRA_ENABLE_CYCLE_TIME() __delay_us(2)

/**
 * How many times check busyflag, to disable this device
 */
#define HD44780_BUSYFLAG_STUCK          ( 0xffff )

/* -------------------------------- pinout configuration ----------------------------- */

/**
 * User function to initialize port parameters
 */
#define HD44780_INIT_CALLBACK() do { \
		smbus_open_master(100000); \
		PCF8574_WRITE(PCF8574_FLAG, 0xff); \
		PCF8574_WRITE(PCF8574_DATA, 0xff); \
} while(0)

/**
 * Set data lines as outputs
 */
#define HD44780_DATA_OUT_CALLBACK()

/**
 * Set data lines as inputs
 */
#define HD44780_DATA_IN_CALLBACK() do{ \
		PCF8574_WRITE(PCF8574_DATA, 0xff); \
		PCF8574_READ(PCF8574_DATA); \
}while(0)

/**
 * Read DB0 through DB7
 */
#define HD44780_DATA_GET_CALLBACK()             ( PCF8574_READ(PCF8574_DATA) )

/**
 * Sets DB0 through DB7 to data
 * For 8-bit operation the "upper" parameter should be ignored.
 * For 4-bit operation the "upper" parameters says, if we should write
 *  the lower 4-bits of data or the upper 4-bits of data.
 *  If upper = 0, this function should write data&0x0f to DB4 through DB7
 *  If upper = 1, this function should write data>>4   to DB4 through DB7
 */
#define HD44780_DATA_SET_CALLBACK(data, upper)  ( PCF8574_WRITE(PCF8574_DATA, data) )

/**
 * Sets the flags for the controler.
 */
#define HD44780_CAPABLE_CALLBACK(flags)         ( PCF8574_WRITE(PCF8574_FLAG, flags) )

/**
 * enables controler
 * @param flags to set
 * @param ctrl_nr hd44780 controller number to enable
 * Flags to set may be ignored, as they are the same as in hd44780_capabla_callback,
 * however they are passed here to speed up things a bit.
 */
#define HD44780_ENABLE_CALLBACK(flags, ctrl_nr)  ( PCF8574_WRITE(PCF8574_FLAG, flags | 0x04) )

/**
 * Disable all controllers - drives all hd44780 controller Enable pin low
 */
#define HD44780_DISABLE_ALL_CALLBACK(flags)      ( PCF8574_WRITE(PCF8574_FLAG, flags) )

/* ------------------------- flags, that are passed as 'flags' parameter to above functions  ----------------- */

/**
 * Those are the arguments for 'flags' parameter to the functions above
 */

#ifndef HD44780_RS_DATA
#define HD44780_RS_DATA           (0x02)
#endif

#ifndef HD44780_RS_INST
#define HD44780_RS_INST           (0x00)
#endif // HD44780_RS_INST

#ifndef HD44780_RW_READ
#define HD44780_RW_READ           (0x01)
#endif // HD44780_RW_READ

#ifndef HD44780_RW_WRITE
#define HD44780_RW_WRITE          (0x00)
#endif // HD44780_RW_WRITE

#endif /* HD44780_CONFIG_2XPCF8574_H_ */
