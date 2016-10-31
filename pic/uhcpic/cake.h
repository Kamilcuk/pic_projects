/*
 * cake.h
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2
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
 * 
 */
#ifndef _CAKE_H_
#define _CAKE_H_

#include "types.h"

#define CAKE_INTESTINE_SIZE 64

/* packet 
 * one packet is one cake, group of packet is a basket
 * first three bits of a packet is a mode selector
 * CAKE_FILLING_RAW -> RW_bit indicates reading or writing to device
 * ^ bits 456 - are controller number to read or write to
 * ^ last two bits are flags - RS and tha lst bit is RW
 * when write to lcd the next byte conains char to be written to lcds 
 * CAKE_FILLING_RAW_ALL - like CAKE_FILLING_RAW, only controller number is omitted 
 * CAKE_FILLING_NUM_READ - first byte like CAKE_FILLING_RAW
 * ^ then the secend byte is the number of reads to perform
 * CAKE_FILLING_SET_READ - well, we have enp2, thgough it we transmitt output
 * ^ but it needs to be filled before we will send in token on ep2
 * ^ we could make a control enpodnt but it is hell slow
 * ^ so CAKE_FILLING_SET_READ sets buffer that well be readed on the next in token on endpoint 2
 * */


#define CAKE_RW_BIT       0b00000001
#define CAKE_RS_BIT       0b00000010
#define CAKE_CTRL_NR_BITS 0b00011100
#define CAKE_FILLING_BITS 0b11100000
#define CAKE_FLAG_BITS    ((CAKE_RS_BIT | CAKE_RW_BIT))
#define CAKE_NUMBER_BITS  0b00011111

// packet modes 
#define CAKE_FILLING_RAW 0<<5
#define CAKE_FILLING_ALL_RAW 1<<5
#define CAKE_FILLING_NUM_READ 2<<5
#define CAKE_FILLING_SET_READ 3<<5
#define CAKE_FILLING_GET_CONFIG 4<<5
#define CAKE_FILLING_GET_INFO 5<<5


#define CAKE_CTRL_NR(cake) ((cake&CAKE_CTRL_NR_BITS)>>2)


extern void cake_eat_cake(unsigned char cake);
extern void cake_eat_basket(unsigned char __near *basket, unsigned char cnt);

#endif // _CAKE_H_

