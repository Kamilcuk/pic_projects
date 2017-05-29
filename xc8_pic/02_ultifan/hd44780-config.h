/*
 * hd44780-config.h
 *
 * 2013 Kamil Cukrowski <kamil@dyzio.pl>
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
 *
 *
 */
#ifndef _HD44780_CONFIG_DEFAULT_H_
#define _HD44780_CONFIG_DEFAULT_H_ 1

#include <xc.h> // Nop(); __delay_ms() __delay_us()
#include <pcf8574.h>

#define HD44780_PCF8574    PCF8574A_ADDR(0b000)
#define HD44780_PCF8574_EX PCF8574A_ADDR(0b111)

/*
 * P0 - DB4
 * P1 - DB5
 * P2 - DB6
 * P3 - DB7
 * P4 - RW
 * P5 - RS
 * P6 - Enable
 * P7 - diode
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
 * 4-bit or 8-bit data operation?
 * defined-4-bit, undefined-8bit
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_MODE_4_BIT        1

/**
 * If disabled, after every operation we check busyflag at max BUSYFLAG_STUCK times.
 * If enabled, after every operation we wait a predefined time.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_NO_BF_CHECKING    1

/**
 * If enabled, after every character written, we check if the character was properly written.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_CHECK_EVERY_WRITE 0

/**
 * This option only matters, when HD44780_CHECK_EVERY_WRITE is enabled.
 * Check this many times (uint8_t) before giving up checking this display after a write.
 */
#define HD44780_CHECK_EVERY_WRITE_MAX 3

/**
 * Enable counting of characters read or wrote
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_COUNTERS          0

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
#define HD44780_CHECKER           0

/**
 * If enabled, disables the function hd44780_recv()
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_WRITE_ONLY        1

/**
 * How many times check busyflag, to stop checking busyflag on this controller
 */
#define HD44780_BUSYFLAG_STUCK          ( 0xffff )

/* -------------------------------- pinout configuration ----------------------------- */

extern unsigned char pcf8574_hd44780_freepin; // shuold be 0x01(ON) or 0x00(off)

/**
 * User function to initialize port parameters
 */
#define HD44780_INIT_CALLBACK() do{ \
		PCF8574_WRITE(HD44780_PCF8574, 0x00 | pcf8574_hd44780_freepin); \
		PCF8574_WRITE(HD44780_PCF8574_EX, 0x00); \
}while(0)

/**
 * Set data lines as outputs and set address (RS and RW) lines
 */
#define HD44780_ADDRESS_SET_WRITE_CALLBACK(flags) do{ \
		PCF8574_WRITE(HD44780_PCF8574, flags | pcf8574_hd44780_freepin); \
}while(0)

/**
 * Set data lines as inputs and set address (RS and RW) lines
 */
#define HD44780_ADDRESS_SET_READ_CALLBACK(flags)     do { \
		PCF8574_WRITE(HD44780_PCF8574, flags | 0xf0 | pcf8574_hd44780_freepin); PCF8574_READ(HD44780_PCF8574); \
}while(0)

/*
 * In 8-bit mode: Read DB0 through DB7
 * In 4-bit mode: Read DB4 through DB7. Output as lower bits.
 */
//#define HD44780_DATA_GET_CALLBACK()            ( ( PCF8574_READ(HD44780_PCF8574) & 0xf0 ) >> 4 )

/**
 * Set DB0 through DB7.
 * @param flags parameter same as passed to ADDRESS_SET function. May be ignored.
 * @data Data to set.
 * @upper For 8-bit mode may be ignored.
 *   For 4-bit:
 *     If upper = 0 then set data&0x0f to DB4 through DB7
 *     If upper = 1 then set data>>4   to DB4 through DB7
 */
#define HD44780_DATA_SET_CALLBACK(flags, data, upper) \
		PCF8574_WRITE(HD44780_PCF8574, (((upper)?(data<<4):(data))&0xf0) | flags | pcf8574_hd44780_freepin)

/**
 * Enables specific controler
 * @param flags parameter same as passed to ADDRESS_SET function. May be ignored.
 * @param ctrl_nr controller number to enable
 */
#define HD44780_ENABLE_CALLBACK(flags, ctrl_nr) do{ \
		PCF8574_WRITE(HD44780_PCF8574, flags | HD44780_ENABLE_CTRL | pcf8574_hd44780_freepin); \
		PCF8574_WRITE(HD44780_PCF8574_EX, 0xff); \
}while(0)

/**
 * Disable all controllers - drives all hd44780 controller Enable pin low
 * @param flags parameter same as passed to ADDRESS_SET function. May be ignored.
 */
#define HD44780_DISABLE_ALL_CALLBACK(flags) do{ \
		PCF8574_WRITE(HD44780_PCF8574, flags | HD44780_DISABLE_CTRL | pcf8574_hd44780_freepin); \
		PCF8574_WRITE(HD44780_PCF8574_EX, 0x00); \
}while(0)


/* ------------------------- flags, that are passed as 'flags' parameter to above functions  ----------------- */

/**
 * Those are the arguments for 'flags' parameter to the functions above
 */
#define HD44780_RS_DATA           (0x08)
#define HD44780_RS_INST           (0x00)
#define HD44780_RW_READ           (0x02)
#define HD44780_RW_WRITE          (0x00)
#define HD44780_ENABLE_CTRL       (0x04)
#define HD44780_DISABLE_CTRL      (0x00)
#define HD44780_FREEPIN_ON        (0x01)
#define HD44780_FREEPIN_OFF       (0x00)

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
#define HD44780_ADDRESS_SET_UP_TIME() __delay_ms(1)
/**
 * Enable pulse width (high level) | PW_EH | 230 ns
 */
#define HD44780_ENABLE_PULSE_WIDTH() __delay_ms(1)
/**
 * Data set-up time | t_DSW | 80 ns
 */
#define HD44780_DATA_SET_UP_TIME()   __delay_ms(1)
/**
 * Data hold time | t_H or t_DHR | 10 (or 5) ns
 */
#define HD44780_DATA_HOLD_TIME()      __delay_ms(1)

/**
 * Additional delay when busyflag checking.or when doing two 4-bit operations
 * Enable cycle time | t_cyclE | 500 ns
 * This value should be at longer then: t_cyclE - PW_EH - t_H =~ 270 ns
 */
#define HD44780_EXTRA_ENABLE_CYCLE_TIME() __delay_ms(1)

#endif // _HD44780_CONFIG_DEFAULT_H_
