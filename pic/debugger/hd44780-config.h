/*
 * hd44780-config.h
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */
#ifndef _HD44780_CONFIG_H_
#define _HD44780_CONFIG_H_

#include "types.h"

 /* ports connection
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
 * -pin 6 - controller 6 Enable pin/EUSART
 * -pin 7 - controller 7 Enable pin/EUSART
 * 
 * 
 * if you want to make changes to these above,
 * just change hd44780_capable, hd44780_enable, and hd44780_disable functions
 * and also defines below -> RS_DATA RS_INST, RW_READ RW_WRITE
 * */

/* delays 
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
 * */

#define NOP() __asm nop __endasm

/* usually after addresss set up time comes some calculation, which must be at least 80 ns long.. 
 * so no need to wait for anything */
#define ADDRESS_SET_UP_TIME()   do { /*NOP();*/ } while(0) /* 80 ns for hd44780 */

/* _hd44780_disable_(flags, takes two instruction to run and then wait, so we dont need to wait 6 nops
 * but only 4 */
#define ENABLE_PULSE_WIDTH()    do { /*NOP(); NOP();*/ NOP(); NOP(); NOP(); NOP(); } while(0) /* 480 ns for hd44780 */

/* every time DATA_HOLD_TIME() is executed there is a bunch of code before the next ENABLE PULSE will come
 * so no need to wait for anything */
#define DATA_HOLD_TIME()        do { /*NOP(); NOP(); NOP(); NOP(); NOP(); NOP();*/ } while(0) /* 10ns for hd44780 */

/* extra delay when reading from lcd - placed after hd44780_enable, before hd44780_disable */
#define READ_EXTRA_DELAY()     do { NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); } while(0)

/* delay between BF checks */
#define BUSYFLAG_DELAY()        do { ; } while(0)

/* how many times check busyflag to get stuck? */
#define BUSYFLAG_STUCK          ((0xffff))


#define RS_DATA     (0x02)
#define RS_INST     (0x00)
#define RW_READ     (0x01)
#define RW_WRITE    (0x00)

/* placeholders */
#define PDEBUG_hd44780( ... )
#define PWARN( ... )

#endif // _HD44780_CONFIG_H_
