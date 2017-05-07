/*
 * hd44780-config.h
 * 
 * 2013 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 * 
 * 
 */
#ifndef _HD44780_CONFIG_H_
#define _HD44780_CONFIG_H_ 1

#include <xc.h> // Nop(); __delay_ms() __delay_us()

/* ---------------------------------- global options configuration ------------------------------- */

#define HD44780_NUM_CONTROLLERS  1 /* MAX number of hd44780 displays per every usb device */
#define HD44780_DISP_ROWS        2 /* number of rows    in single HD44780 display */
#define HD44780_DISP_COLS       16 /* number of columns in single HD44780 display */

#define HD44780_COUNTERS        1
#define HD44780_CHECKER         1
//#define HD44780_WRITE_ONLY      1 /* disable writing functions */
//#define HD44780_NO_BF_CHECKING  1 /* dont check busyflag - use sleep/wait delay */

/* -------------------------------- delays configuration -------------------------------- */

#define ADDRESS_SET_UP_TIME()   do { Nop(); } while(0) /* 80 ns for hd44780 */
#define ENABLE_PULSE_WIDTH()    do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0) /* 480 ns for hd44780 */
#define DATA_HOLD_TIME()        do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0) /* 10ns for hd44780 */
#define READ_EXTRA_DELAY()      do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0)
#define BUSYFLAG_DELAY()        do { Nop(); }while(0)
#define BUSYFLAG_STUCK          ((0xffff)) /* for how long to stuck checking busyflag */
#define LONG_DELAY()            __delay_us(1666)
#define NORMAL_DELAY()          __delay_us(40)

/* -------------------------------- pinout configuration ----------------------------- */

#define _hd44780_init_callback_() do { \
	ADCON0=0x00; ADCON1=0x0f; CMCON=0x07; \
	PORTA=LATA=TRISA=0x00; \
	PORTB=LATB=TRISB=0x00; \
	PORTC=LATC=TRISC=0x00; \
} while(0)

#define _hd44780_data_forward_()      TRISB=0x00; /* set port for writing to port */
#define _hd44780_data_reverse_()      TRISB=0xFF; /* set port for reading from port */
#define _hd44780_data_set_(y)         PORTB=(y); /* set a specifed DB0 to DB7 bits */
#define _hd44780_data_get_()          ((PORTB)) /* read DB0 to DB7  */
#define _hd44780_data_get_busyflag_() ((PORTBbits.RB7)) /* read only busyflag */

/* sets the flags/data for the controler */
#define _hd44780_capable_(flags) \
do { \
	PORTC = flags; \
	ADDRESS_SET_UP_TIME(); \
} while(0)

/* enables controler */
#define _hd44780_enable_(flags, ctrl_nr) \
do { \
	unsigned char n; \
	n = (ctrl_nr == 7) ? (1) : ( (0x02)<<(ctrl_nr) ); \
	PORTA = n&0x3f; \
	PORTC = ( n&0xc0 ) | flags; \
	ENABLE_PULSE_WIDTH(); \
} while(0);

/* enables all controllers */
#define _hd44780_enable_all_(flags) \
do { \
	PORTA = 0x3f; \
	PORTC = 0xc0 | flags; \
	ENABLE_PULSE_WIDTH(); \
} while(0)

/* disables controler */
#define _hd44780_disable_(flags) \
do { \
	PORTA = 0x00; \
	PORTC = flags; \
	DATA_HOLD_TIME(); \
} while(0)


/* ------------------------- flags, that are passed as 'flags' parameter to above functions  ----------------- */

#define HD44780_IS_RS_INST(flags) (( !( flags&0x02 ) ))
#define HD44780_RS_DATA           (0x02)
#define HD44780_RS_INST           (0x00)
#define HD44780_RW_READ           (0x01)
#define HD44780_RW_WRITE          (0x00)


#endif // _HD44780_CONFIG_H_
