/*
 * main.c
 * 
 * Copyright 2013 Kamil Cukrowski <kamil@dyzio.pl>
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
 * 
 */
#include <pic18fregs.h>
#include "usb/usb.h"
#include <adc.h>

#define VERSION "0.0.3"

#pragma config PLLDIV = 5 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

/* ---------------- START interrupthandlesr --------------------- */

static void high_interrupt(void) __interrupt(1)
{
	USB_interrupt_service();
}
static void low_interrupt(void) __interrupt(2)
{
}

/* ---------------- ENDOF interrupthandlesr --------------------- */

void main(void) 
{
	adc_open(0, 
		ADC_FOSC_64 | ADC_ACQT_12,
		ADC_CFG_16A, 
		ADC_FRM_LJUST | ADC_INT_OFF | ADC_VCFG_AN3_VSS
	);
	
	USB_init_in_configured_state();
	USB_interrupt_priority_high();
	USB_interrupt_enable();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */

	for(;;) {
		__asm sleep __endasm; /* we get woken up by an USB interrupt */
	}
}


