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
#include <pic18fregs.h>

// #define HD44780_WRITE_ONLY 1
#define HD44780_COUNTERS 1
#define HD44780_CHECKER 1
#define ROWS_PER_CTRL 2 /* number of rows every hd44780 has */
#define DISP_COLS 40  /* number of columns every hd44780 has */

 /* my port connection
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
 * 
 * if you want to make changes to these above,
 * just change hd44780_capable, hd44780_enable, and hd44780_disable functions
 * and also defines below -> RS_DATA RS_INST, RW_READ RW_WRITE
 * */

/* 
 * delays 
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
 * * delays when NO busyflag checking - 
 * * LONG_DELAY - after "Return Home" instruction - 1.52ms
 * * NORMAL_DELAY - after all the other instructions - 37us 
 * * at 48MHz TCY = 4/48Mhz = 1/12 us = 83.3 ns
 */
#ifndef Nop
#define Nop() do{ __asm nop __endasm; } while(0)
#endif
#define ADDRESS_SET_UP_TIME()   do { Nop(); } while(0) /* 80 ns for hd44780 */
#define ENABLE_PULSE_WIDTH()    do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0) /* 480 ns for hd44780 */
#define DATA_HOLD_TIME()        do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0) /* 10ns for hd44780 */
#define READ_EXTRA_DELAY()      do { Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); } while(0)
#define BUSYFLAG_DELAY()        do { Nop(); }while(0)
#define BUSYFLAG_STUCK          ((0xffff)) /* how many times to check busyflag to go on */
#define LONG_DELAY() delay10ktcy(2) /* 2*10000*1/12us = 1,66 ms > 1.52ms*/
#define NORMAL_DELAY() delay100tcy(5) /* 5*100*1/12us = 41,6 us > 40us*/

#define _hd44780_data_forward_() TRISB=0x00; /* set port for writing to port */
#define _hd44780_data_reverse_() TRISB=0xFF; /* set port for reading from port */
#define _hd44780_data_set_(y) PORTB=(y); /* set a specifed DB0 to DB7 bits */
#define _hd44780_data_get_() ((PORTB)) /* read DB0 to DB7  */
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


/* -------------- bum du bi tsss ----------------- */
#define IS_RS_INST(flags) (( !( flags&0x02 ) ))
#define RS_DATA     (0x02)
#define RS_INST     (0x00)
#define RW_READ     (0x01)
#define RW_WRITE    (0x00)


#endif // _HD44780_CONFIG_H_
