/*
 * main.c
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
#define UHCPIC_VERSION "0.0.5"
#include <pic18f2550.h>
#include "hd44780.h"
#include "hd44780-config.h"
#include "hd44780-inst-def.h"
#include "charmap.h"
#include <usart.h>

/* ********************* config and interrupts ************************** */

#pragma config PLLDIV = 4 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

static void high_interrupt(void) __interrupt(1)
{
}

static void low_interrupt(void) __interrupt(2)
{
}

/* ********************** main body ************************* */

void serial_init()
{
	unsigned char i;
	usart_open(
		USART_TX_INT_OFF &
		USART_RX_INT_OFF &
		USART_BRGH_LOW &
		USART_EIGHT_BIT &
		USART_CONT_RX &
		USART_ASYNCH_MODE,
		8332
	);
	for(i=0xff;i;i--)
		__asm NOP __endasm;
}

void myprint(unsigned char buf)
{
	static unsigned char ctrl = 0;
	static unsigned char pos = 0;
	
	if ( buf == '\n' ) {
		if ( pos < 40 ) {
			pos = 40;
			write_inst(ctrl, HD44780_DDRAM_ADDRESS | pos );
		} else {
			pos = 0;
			write_inst(ctrl, HD44780_DDRAM_ADDRESS); /* cursor to [0,0] on current ctrl */
			ctrl++;
			if ( ctrl >= NUM_CONTROLLERS ) 
				ctrl = 0;
		}
		return;
	}
	
	write_data(ctrl, buf);
	pos++;
	if ( pos >= DISP_COLS*ROWS_PER_CTRL ) { 
		pos = 0;
		ctrl++;
		if ( ctrl >= NUM_CONTROLLERS ) 
			ctrl = 0;
	}
}

void main(void) 
{
	hd44780_init();
	serial_init();
	
	for (;;) {		
		while ( !usart_drdy() ) {}
		myprint( usart_getc() );
	}
}
