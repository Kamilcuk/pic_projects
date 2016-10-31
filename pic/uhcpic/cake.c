/*
 * cake.c
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
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
#include <pic18f2550.h>
#include "cake.h"
#include "hd44780/hd44780.h"
#include "hd44780-config.h"
#include "types.h"
#include "usb_ep2.h" // our output

#define min(x, y) ((((x)>(y))?(y):(x)))

static unsigned char intestine_cnt = 0;
static unsigned char __near intestine[CAKE_INTESTINE_SIZE];

/* mode definitions */
enum {
	NORMAL,
	RAW_WRITE,
	RAW_WRITE_ALL,
	NUM_READ,
	GET_INFO,
};

static unsigned char input_state = NORMAL;
static unsigned char bite;

/* inline for better performance */
extern inline void cake_eat_cake(unsigned char cake)
{
	switch(input_state) {
	case NORMAL:
		switch (cake&CAKE_FILLING_BITS) {
			case CAKE_FILLING_RAW:
				if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
					// receive operation
					if (intestine_cnt >= CAKE_INTESTINE_SIZE) // our recv buffer is full
						return;
					intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(cake), cake&CAKE_FLAG_BITS);
					intestine_cnt++;
				} else {
					// send operation
					input_state = RAW_WRITE;
					bite = cake;
				}
				break;
			case CAKE_FILLING_ALL_RAW:
				if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
					// receive operation from all lcds
					if (intestine_cnt > (CAKE_INTESTINE_SIZE-MAX_NUM_CONTROLLERS) )
						return;
					//printf("A%x|", intestine_cnt);
					/* bite used as loop counter */
					for (bite=0; bite<MAX_NUM_CONTROLLERS; bite++) {
						intestine[intestine_cnt] = hd44780_recv(bite, cake&CAKE_FLAG_BITS);
						intestine_cnt++;
					}
				} else {
					// send operation
					input_state = RAW_WRITE_ALL;
					bite = cake;
				}
				break;
			case CAKE_FILLING_SET_READ:
				USB_EP2_set(intestine, intestine_cnt);
				intestine_cnt = 0;
				break;
			case CAKE_FILLING_NUM_READ:
				bite = cake;
				input_state  = NUM_READ;
				break;
			case CAKE_FILLING_GET_CONFIG:
				if ( intestine_cnt+8 >= CAKE_INTESTINE_SIZE )
					return;
				intestine[intestine_cnt++] = DISP_COLS;
				intestine[intestine_cnt++] = DISP_ROWS;
				intestine[intestine_cnt++] = MAX_NUM_CONTROLLERS;
				intestine[intestine_cnt++] = ROWS_PER_CTRL;
				intestine[intestine_cnt++] = sizeof(lcddev);
				intestine[intestine_cnt++] = lcddev.disabled;
				intestine[intestine_cnt++] = 0;
				intestine[intestine_cnt++] = 0;
				break;
			case CAKE_FILLING_GET_INFO:
				USB_EP2_set(&lcddev, sizeof(lcddev));
				break;
			default:
				/* error :/ discard packet */
		}
		break;
	case RAW_WRITE:
		hd44780_send(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS, cake);
		input_state = NORMAL;
		break;
	case RAW_WRITE_ALL:
		hd44780_send_all(bite&CAKE_FLAG_BITS, cake);
		input_state = NORMAL;
		break;
	case NUM_READ:
		/* do cake reads */
		cake = min(cake, CAKE_INTESTINE_SIZE-intestine_cnt); // roll to our receive buffer 
		for (; cake; cake--) {
			intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS);
			intestine_cnt++;
		}
		input_state = NORMAL;
		break;
	default:
		input_state = NORMAL;
	}
}


void cake_eat_basket(unsigned char __near *basket, unsigned char cnt) // basket full of cakes !
{
	unsigned char cake;
	
	while (cnt) {
		
		cake = *basket;
		++basket;
		--cnt;
		
		cake_eat_cake(cake);
		
	}
}
