/*
 *        File: hd44780-config.h
 *  Created on: 10.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef HD44780_CONFIG_H_
#define HD44780_CONFIG_H_

#include <xc.h> // Nop(); __delay_ms() __delay_us()
#include <pcf8574.h>
#include <bit.h>

#define PCF8574_DATA  PCF8574A_ADDR(0x00)
#define PCF8574_FLAGS PCF8574A_ADDR(0x01)

/* ---------------------------------- global options configuration ------------------------------- */

/**
 * Maximum number of hd44780 displays connected to microcontroller
 */
#define HD44780_NUM_CONTROLLERS  1

/**
 * Number of rows per every hd44780 display
 */
#define HD44780_DISP_ROWS        2

/**
 * number of columns per every hd44780 display
 */
#define HD44780_DISP_COLS       16

/**
 * Enable counting of characters read or wrote
 * @param defined-enabled or undefined-disabled
 */
//#define HD44780_COUNTERS        1

/**
 * Enable the hd44780_check function, which checks
 * and corrects errors on displays.
 * Uses much memory to store whole display state.
 */
//#define HD44780_CHECKER         1

/**
 * If defined, disables the function hd44780_recv()
 * @param defined-enabled or undefined-disabled
 */
//#define HD44780_WRITE_ONLY      1

/**
 * If not defined, after every operation we check busyflag at max BUSYFLAG_STUCK times.
 * If defined, after every operation we wait a predefined time.
 * @param defined-enabled or undefined-disabled
 */
//#define HD44780_NO_BF_CHECKING  1

/**
 * If defined, after every character written, we check if the character was properly written.
 * @param defined-enabled or undefined-disabled
 */
//#define HD44780_CHECK_EVERY_WRITE 1 // not YET IMPLEMENTED!

/**
 * If defined, after every character written, we check if the character was properly written.
 * @param defined-enabled or undefined-disabled
 */
//#define HD44780_CHECK_EVERY_WRITE_MAX 1 // not YET IMPLEMENTED!

/* -------------------------------- delays configuration -------------------------------- */

/**
 * hd44780 documentation page 24 Return home Execution time = 1.52 ms
 */
#define HD44780_LONG_DELAY()            __delay_us(1520)
/**
 * hd44780 documentation page 24 All others execution time = 37 us
 */
#define HD44780_NORMAL_DELAY()          __delay_us(37)

/**
 * delays from hd44780 documentation page 52 - DC Characteristics (VCC = 4.5 to 5.5 V, Ta = –30 to +75°C*3)
 * for PIC18f2550 with XTAL=48Mhz every Nop is 83ns
 *
 * Notice: Data set-up time | t_DSW | 80 ns is not used.
 * The DB0 through DB7 lines are set up before hd44780_capable_callback, which allows to omit this delay completly.
 * Notice: Data hold time | t_H or t_DHR | 10 (or 5) ns is quite short and therefore not used.
 * After data write we return from recv function, data hold time is not needed (there will be seferal
 * instructions before we change R/W and E lines states.
 */
/**
 * Address set-up time | t_DSW | 40 ns
 */
#define HD44780_ADDRESS_SET_UP_TIME()   do { Nop(); } while(0)
/**
 * Enable pulse width (high level) | PW_EH | 230 ns
 */
#define HD44780_ENABLE_PULSE_WIDTH()    do { Nop();Nop();Nop(); } while(0)
/**
 * Data set-up time | t_DSW | 80 ns
 */
#define HD44780_DATA_SET_UP_TIME()
/**
 * Data hold time | t_H or t_DHR | 10 (or 5) ns
 */
#define HD44780_DATA_HOLD_TIME()
/**
 * Data delay time | t_DDR | 160 ns
 */
#define HD44780_DATA_DELAY_TIME()       do { Nop();Nop(); } while(0)

/**
 * How many times check busyflag, to disable this device
 */
#define HD44780_BUSYFLAG_STUCK          ((0xffff))

/* -------------------------------- pinout configuration ----------------------------- */

/**
 * User function to initialize port parameters
 */
#define HD44780_INIT_CALLBACK()

/**
 * Set data lines as outputs
 */
#define HD44780_DATA_OUT_CALLBACK()            PCF8574_WRITE(PCF8574_DATA, 0xff)
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
#define HD44780_DATA_GET_CALLBACK()            PCF8574_READ(PCF8574_DATA)
/**
 * Set DB0 through DB7
 */
#define HD44780_DATA_SET_CALLBACK(data, lower) PCF8574_WRITE(PCF8574_DATA, data)
/**
 * Read DB7 - busyflag
 */
#define HD44780_DATA_GET_BUDYFLAG_CALLBACK()   BIT_READ(PCF8574_READ(PCF8574_DATA), 7)

/**
 * Sets the flags for the controler.
 * This function should wait for ADDRESS_SET_UP_TIME before continuing.
 */
#define HD44780_CAPABLE_CALLBACK(flags)        PCF8574_WRITE(PCF8574_FLAGS, 0xf8 | flags)

/**
 * Enables all controllers - drives all hd44780 controller Enable pin high
 * @param flags to set
 */
#define HD44780_ENABLE_ALL_CALLBACK(flags)     PCF8574_WRITE(PCF8574_FLAGS, 0xfc | flags)

/**
 * Disable all controllers - drives all hd44780 controller Enable pin low
 */
#define HD44780_DISABLE_ALL_CALLBACK(flags)    PCF8574_WRITE(PCF8574_FLAGS, 0xf8 | flags)


/* ------------------------- flags, that are passed as 'flags' parameter to above functions  ----------------- */

/**
 * Those are the arguments for 'flags' parameter to the functions above
 */
#define HD44780_RS_DATA           (0x02)
#define HD44780_RS_INST           (0x00)
#define HD44780_RW_READ           (0x01)
#define HD44780_RW_WRITE          (0x00)
#define HD44780_IS_RS_INST(flags) ( !( flags&0x02 ) )


#endif // _HD44780_CONFIG_H_
