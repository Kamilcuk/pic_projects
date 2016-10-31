/*
 * main.c
 * 
 * Copyright 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
 * rbg
 * 
 */
#include <pic18fregs.h>
#include <pic18f2550.h>
#include <stdint.h>
#include <stdlib.h>
#include <sdelay/sdelay.h>
#include <usb/usb.h>
#include "usb_ep.h"

typedef unsigned char u8;

#define VERSION "0.0.1"

#pragma config PLLDIV = 4 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

u8 time;

/* ----------------------interrupt handlesrts ------------------------------ */

static void high_interrupt(void) __interrupt(1)
{
	PORTBbits.RB6 = 1;
	USB_interrupt_service();
	PORTBbits.RB6 = 0;
}

static void low_interrupt(void) __interrupt(2)
{
}

/* ---------------- ENDOF interrupthandlesr --------------------- */

void process(__near unsigned char *msg, unsigned char cnt)
{
	if ( cnt != 2 ) return;
	for(;cnt;cnt--) {
		switch(*msg) {
			case 'T':
				if ( *(msg+1) )
					PORTBbits.RB7 = 1;
				else
					PORTBbits.RB7 = 0;
			case 'A':
				PORTA = *(msg+1);
				cnt--;
				break;
			case 'B':
				PORTB = *(msg+1);
				cnt--;
				break;
			case 'C':
				PORTC = *(msg+1);
				cnt--;
				break;
			case 't':
				time = *(msg+1);
				cnt--;
				break;
		}
	}
}

void ports_init()
{	
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	CMCON=0x07; // turn off comparator module
	// UCFGbits.UTRDIS = 1; // turn off USB module 
	
	/* port A */
	PORTA=0x00;
	LATA=0x00;
	TRISA=0x00;
	
	// port b
	PORTB=0x00;
	LATB=0x00;
	TRISB=0x00;
	
	// port c
	PORTC=0x00;
	LATC=0x00;
	TRISC=0x00;
}

int main()
{
	
	ports_init();
	
	TRISAbits.RA0 = 1;
	PORTBbits.RB6 = 0;
	
	USB_init();
	USB_wait_for_configured_state();
	
	USB_interrupt_priority_high();
	USB_interrupt_enable();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	
	USB_EP2_transmission();
	
	for(;;) {
		__asm nop __endasm;
		__asm nop __endasm;
		__asm nop __endasm;
		__asm nop __endasm;
		__asm nop __endasm;
		__asm nop __endasm;
		__asm sleep __endasm;
	}
}
