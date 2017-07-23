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

/* architecture specific ------------------------------------------------------------- */

#ifdef __XC
#include <xc.h> // Nop(); __delay_ms() __delay_us()
#endif

#ifndef Nop
#define Nop() __asm("nop");
#endif
#ifndef __delay_ms
#error
#endif
#ifndef __delay_us
#error
#endif

/* documentation ----------------------------------------------------------------------- */

/*
 * -------------------------- documentation -----------------------------
 *
 * microprocessor: PIC18F2550 with _XTAL = 48000000 :
 * hd44780 documentation: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *
 *  -------------------------------- connections:  --------------------------------
 * port a - 7 pins
 * -pin 0 - controller 0 Enable pin
 * -pin 1 - controller 1 Enable pin
 * -pin 2 - controller 2 Enable pin
 * -pin 3 - controller 3 Enable pin
 * -pin 4 - controller 4 Enable pin
 * -pin 5 - controller 5 Enable pin
 * -pin 6 - used for CLK
 * // pin7 does not exists
 * port B - 8 pins
 * -pin 0 to 7 used for DB0 to DB7
 * port C - 7 pins
 * -pin 0 - R/W
 * -pin 1 - RS
 * -pin 2 - unused
 * // pin 3 does not exits
 * -pin 4 - USB D-
 * -pin 5 - USB D+
 * -pin 6 - controller 6 Enable pin
 * -pin 7 - controller 7 Enable pin
 * 
 * -------------------------------- delays: --------------------------------
 * on current config with PLL every instruction is runned in 83.3 ns
 * so every wait needs to be an multiplication of 83.3 ns :D 
 *
 * ok, so how a operation looks like. lets get in two examples:
 * 
 * start: ENABLE is down! (must be)
 * 
 * write operation (whole cycle):
 * -> set RS , set R/W and set DB0 to DB7 - to desired states
 * -> ADDRESS_SET_UP_TIME(); -> wait 60 ns -> rounded to 83.3 ns -> wait for one operation (83ns)
 * -> set ENABLE high
 * -> ENABLE_PULSE_WIDTH(); -> wait 450 ns -> rounded to 83.3 ns -> wait for six operatinons (480ns)
 * -> set ENABLE low
 * -> DATA_HOLD_TIME(); -> wait for cycle to end 
 *			\ one cycle is 1 ms, but we waited 560 ns already, so we need to wait only for 440 -> rounded to six operations
 * 
 * read operation (whole cycle):
 * -> set RS , set R/W - to desired states
 * -> ADDRESS_SET_UP_TIME(); -> wait 60 ns -> rounded to 83.3 ns -> wait for one operation (83ns)
 * -> set ENABLE high
 * -> ENABLE_PULSE_WIDTH(); -> wait 450 ns -> rounded to 83.3 ns -> wait for six operations (480ns)
 * -> read DB0 to DB7
 * -> set ENABLE low
 * -> DATA_HOLD_TIME(); -> wait for cycle to end 
 *			\ one cycle is 1 ms, but we waited 560 ns already, so we need to wait only for 440 -> rounded to six operations
 * 
 * 
 * delays without busyflag checking:
 * -> LONG_DELAY - after "Return Home" instruction - 1.52ms
 * -> NORMAL_DELAY - after all the other instructions - 37us
 */


/* ---------------------------------- global options configuration ------------------------------- */

/**
 * Maximum number of hd44780 displays connected to microcontroller
 */
#define HD44780_NUM_CONTROLLERS              3

/**
 * Number of rows per every hd44780 display
 */
#define HD44780_DISP_ROWS                    2

/**
 * number of columns per every hd44780 display
 */
#define HD44780_DISP_COLS                    40

/**
 * 4-bit or 8-bit data operation?
 * defined-4-bit, undefined-8bit
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_MODE_4_BIT                    0

/**
 * If enabled, after every character written, we check if the character was properly written.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_CHECK_EVERY_WRITE             1

/**
 * This option only matters, when HD44780_CHECK_EVERY_WRITE is enabled.
 * Check this many times (uint8_t) before giving up checking this display after a write.
 */
#define HD44780_CHECK_EVERY_WRITE_MAX         3

/**
 * Enable counting of characters read or wrote
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_COUNTERS_ENABLED              1

/**
 * Type of hd44780 counter, uint16_t is too short, but good for debugging.
 * @param uint8_t uint16_t uint24_t or uint32_t
 */
#define HD44780_COUNTERS_TYPE                 uint16_t

/**
 * If enabled, disables the function hd44780_recv()
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_READ_ENABLED                   1

/**
 * If disabled, after every operation we check busyflag at max (if defined)BUSYFLAG_STUCK times.
 * If enabled, after every operation we wait a predefined time.
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_BF_CHECKING_ENABLED            1

/**
 * If enabled, user code may disable busyflag checking for specified controllers
 * @param 0 - disabled, 1 - enabled
 */
#define HD44780_BF_CHECKING_OPTIONAL           1

/**
 * How many times check busyflag, to stop checking busyflag on this controller
 */
#define HD44780_BF_CHECKING_COUNT_MAX          0xffff

/* low-level implementation ------------------------------------------------------------------------ */

/**
 * FLAG_RS parameter
 */
enum HD44780_FLAG_RS_e {
	HD44780_FLAG_RS_DATA = 0x02,
	HD44780_FLAG_RS_INST = 0x00,
};

/**
 * FLAG_RW parameter
 */
enum HD44780_FLAG_RW_e {
	HD44780_FLAG_RW_READ = 0x01,
	HD44780_FLAG_RW_WRITE = 0x00,
};

/**
 * User function to initialize port parameters
 */
#define HD44780_INIT_CALLBACK() do { \
	PORTA=LATA=TRISA=0x00; \
	PORTB=LATB=TRISB=0x00; \
	PORTC=LATC=TRISC=0x00; \
} while(0)

/**
 * Set data lines as outputs and set address (RS and RW) lines
 * @param FLAG_RS HD44780_FLAG_RS_INST or HD44780_FLAG_RS_DATA
 * @param FLAG_RW is equal to HD44780_FLAG_RW_READ
 */
#define HD44780_ADDRESS_SET_READ_CALLBACK(FLAG_RW, ctrl, FLAG_RS)     do{ TRISB = 0x00; PORTC = FLAG_RS | FLAG_RW; }while(0)

/**
 * Set data lines as inputs and set address (RS and RW) lines
 * @param FLAG_RS HD44780_FLAG_RS_INST or HD44780_FLAG_RS_DATA
 * @param FLAG_RW is equal to HD44780_FLAG_RW_READ
 */
#define HD44780_ADDRESS_SET_WRITE_CALLBACK(FLAG_RW, ctrl, FLAG_RS)    do{ TRISB = 0xFF; PORTC = FLAG_RS | FLAG_RW; }while(0)

/**
 * In 8-bit mode: Read DB0 through DB7
 * In 4-bit mode: Read DB4 through DB7. Output as lower bits.
 * @param FLAG_RS HD44780_FLAG_RS_INST or HD44780_FLAG_RS_DATA
 * @param FLAG_RW HD44780_FLAG_RW_READ or HD44780_FLAG_RW_WRITE
 */
#if !HD44780_MODE_4_BIT
#define HD44780_DATA_GET_CALLBACK(FLAG_RW, ctrl, FLAG_RS)             ( PORTB )
#else
#define HD44780_DATA_GET_CALLBACK(FLAG_RW, ctrl, FLAG_RS)             ( (PORTB) >> 4 )
#endif

/**
 * Set DB0 through DB7.
 * @param flags parameter same as passed to ADDRESS_SET function. May be ignored.
 * @data Data to set.
 */
#if !HD44780_MODE_4_BIT
#define HD44780_DATA_SET_CALLBACK(FLAG_RW, ctrl, FLAG_RS, data)       ( PORTB = (data) )
#else
#define HD44780_DATA_SET_CALLBACK(FLAG_RW, ctrl, FLAG_RS, data)       ( PORTB = (data<<4) )
#endif

/**
 * Enables specific controler
 * @param FLAG_RS HD44780_FLAG_RS_INST or HD44780_FLAG_RS_DATA
 * @param FLAG_RW HD44780_FLAG_RW_READ or HD44780_FLAG_RW_WRITE
 * @param ctrl_nr controller number to enable
 */
#define HD44780_ENABLE_CALLBACK(FLAG_RW, ctrl, FLAG_RS) do { \
	unsigned char _n = ( (ctrl) == 7 ) ? 1 : ( 2<<(ctrl) ); \
	PORTA = _n & 0x3f; \
	PORTC = ( _n & 0xc0 ) | (FLAG_RS) | (FLAG_RW); \
} while(0);

/**
 * Disable all controllers - drives all hd44780 controller Enable pin low
 * @param FLAG_RS HD44780_FLAG_RS_INST or HD44780_FLAG_RS_DATA
 * @param FLAG_RW HD44780_FLAG_RW_READ or HD44780_FLAG_RW_WRITE
 */
#define HD44780_DISABLE_ALL_CALLBACK(FLAG_RW, FLAG_RS) do { \
	PORTA = 0x00; \
	PORTC = FLAG_RS | FLAG_RW; \
} while(0)

/* delays configuration --------------------------------------------------------------------- */

/**
 * hd44780 documentation page 24 Return home Execution time = 1.52 ms
 */
#define HD44780_LONG_DELAY()              __delay_ms(2)
/**
 * hd44780 documentation page 24 All others execution time = 37 us + extra 3us for cursor = 40us
 */
#define HD44780_NORMAL_DELAY()            __delay_us(40)

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
#define HD44780_ADDRESS_SET_UP_TIME()      __delay_us(2)
/**
 * Enable pulse width (high level) | PW_EH | 230 ns
 */
#define HD44780_ENABLE_PULSE_WIDTH()       __delay_us(2)
/**
 * Data set-up time | t_DSW | 80 ns
 */
#define HD44780_DATA_SET_UP_TIME()         __delay_us(2)
/**
 * Data hold time | t_H or t_DHR | 10 (or 5) ns
 */
#define HD44780_DATA_HOLD_TIME()           __delay_us(2)

/**
 * Additional delay when busyflag checking.or when doing two 4-bit operations
 * Enable cycle time | t_cyclE | 500 ns
 * This value should be at longer then: t_cyclE - PW_EH - t_H =~ 270 ns
 */
#define HD44780_EXTRA_ENABLE_CYCLE_TIME()  __delay_us(2)

#endif // _HD44780_CONFIG_DEFAULT_H_
