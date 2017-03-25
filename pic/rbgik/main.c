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

#define VERSION "0.0.1"

#pragma config PLLDIV = 5 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

struct stan_s {
	unsigned char timerH;
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
static __near struct stan_s stan;

/* ---------------------- interrupt handlesrts ------------------------------ */

static void high_interrupt(void) __interrupt(1)
{
	static __near unsigned char cnt = 0;
	static __near unsigned char tmp = 0;
	static __near unsigned char tmp2 = 0;
	static __near unsigned char R, G, B = 0;
	
	TMR1H = stan.timerH;
	
	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */
	
	if ( tmp != tmp2 ) {
		LATB = tmp;
		tmp2 = tmp;
	} else {
		__asm nop 
		nop
		nop
		nop __endasm;
	}
	
	if ( cnt == 0 ) {
		R = stan.R;
		G = stan.G;
		B = stan.B;
		
		if ( R != 0 )
			tmp |= 0b10000000;
		if ( G != 0 )
			tmp |= 0b01000000;
		if ( B != 0 )
			tmp |= 0b00100000;
	} else {
		
		if ( cnt == R )
			tmp &= 0b01111111;
		if ( cnt == G )
			tmp &= 0b10111111;
		if ( cnt == B )
			tmp &= 0b11011111;
	}
	
	cnt++;
	/* when cnt reasches 255 it automagically rewinds to 0 */
}

static void low_interrupt(void) __interrupt(2)
{
}

/* ---------------- ENDOF interrupthandlesr --------------------- */

void process(__near unsigned char *msg, unsigned char cnt)
{
	unsigned char R, G, B;
	
	switch ( msg[0] ) {
	case 'x':
		R = msg[2];
		B = msg[3];
		G = msg[4];
		
		PIE1bits.TMR2IE = 0;
		stan.R = R;
		stan.B = B;
		stan.G = G;
		PIE1bits.TMR2IE = 1;
		
		break;
	case 'H':
		stan.timerH = msg[2];
		break;
	default:
	}
}

void ports_init()
{	
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	CMCON=0x07; // turn off comparator module
	UCFGbits.UTRDIS = 1; // turn off USB module 
	
	// port a
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

void timer1_start()
{
	stan.timerH = 0xff;
	TMR1H = 0xff;
	TMR1L = 0x00;
	
	/* timer setup configure */
	T1CON=0b00001101;
/**	
bit 7   RD16: 16-Bit Read/Write Mode Enable bit
        1 = Enables register read/write of Timer1 in one 16-bit operation
        0 = Enables register read/write of Timer1 in two 8-bit operations
bit 6   T1RUN: Timer1 System Clock Status bit
        1 = Device clock is derived from Timer1 oscillator
        0 = Device clock is derived from another source
bit 5-4 T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits
        11 = 1:8 Prescale value
        10 = 1:4 Prescale value
        01 = 1:2 Prescale value
        00 = 1:1 Prescale value
bit 3   T1OSCEN: Timer1 Oscillator Enable bit
        1 = Timer1 oscillator is enabled
        0 = Timer1 oscillator is shut off
        The oscillator inverter and feedback resistor are turned off to eliminate power drain.
bit 2   T1SYNC: Timer1 External Clock Input Synchronization Select bit
        When TMR1CS = 1:
        1 = Do not synchronize external clock input
        0 = Synchronize external clock input
        When TMR1CS = 0:
        This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
bit 1   TMR1CS: Timer1 Clock Source Select bit
        1 = External clock from RC0/T1OSO/T13CKI pin (on the rising edge)
        0 = Internal clock (FOSC/4)
bit 0   TMR1ON: Timer1 On bit
        1 = Enables Timer1
        0 = Stops Timer1
* */
	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	PIE1bits.TMR1IE = 1; /* timer0 enable interrupt */ 
	IPR1bits.TMR1IP = 1; /* timer0 interrupt high/low */	
}

int main()
{
	
	ports_init();
	timer1_start();
	
	/* initialize random seed */
	srand(1234);
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	INTCONbits.GIEL = 0; /* Enables all low priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	
	// may god see the light ! 
	stan.timerH = 0xff;
	stan.B = 0x00;
	stan.R = stan.G = 0xff;
	
	TRISCbits.RC2 = 1; /* USB ? */
	
	for(;;) {
		
		if ( PORTCbits.RC2 ) {
			
			USB_init();
			
			/* fuck waiting for ending single-ended condition */
			UIE = 0x11; /* IDLEIE URSTIE */
			
			while ( PORTCbits.RC2 ) { // dopoki usb jest podlanczone
				USB_service(); //looping here with usb
			}
			
			USB_disable();
			
		} else {
			
			while ( !PORTCbits.RC2 ) {
				stan.B = 0x00;
				stan.R = stan.G = 0xff;
				_sdelay_ms( 500 );
				stan.R = 0x00;
				stan.G = stan.B = 0xff;
				_sdelay_ms( 500 );
				stan.G = 0x00;
				stan.R = stan.B = 0xff;
				_sdelay_ms( 500 );
				
				stan.B = 0xff;
				stan.R = stan.G = 0x00;
				_sdelay_ms( 500 );
				stan.R = 0xff;
				stan.G = stan.B = 0x00;
				_sdelay_ms( 500 );
				stan.G = 0xff;
				stan.R = stan.B = 0x00;
				_sdelay_ms( 500 );
			}
		}
	}
}

/* =--------------------- */
		//~ 
		//~ union {
			//~ long num;
			//~ struct {
				//~ unsigned char a;
				//~ unsigned char b;
				//~ unsigned char c;
				//~ unsigned char d;
			//~ } bajts;
		//~ } num;
		//~ 
		//~ //while ( !PORTCbits.RC2 ) {
			//~ 
			//~ /* algorytm by Paweł Wierzchowski :D */
			//~ 
			//~ num.num = rand(); 
			//~ stan.R = num.bajts.a;
			//~ stan.G = num.bajts.b;
			//~ stan.B = num.bajts.c;
			//~ if ( num.bajts.d == 0 ) {
				//~ num.bajts.d = 1;
			//~ }
			//~ //_delay_ms( num.bajts.d*2+50 );
			//~ _delay_ms( 500 );
			//~ 
			//~ num.num = rand();
			//~ stan.R = num.bajts.a/3;
			//~ stan.G = num.bajts.b/3;
			//~ stan.B = num.bajts.c/3;
			//~ if ( num.bajts.d == 0 ) {
				//~ num.bajts.d = 1;
			//~ }
			//~ //_delay_ms( num.bajts.d*2+50 );
			//~ _delay_ms( 500 );
			//~ 
			//~ num.num = rand(); 
			//~ stan.R = num.bajts.a/3;
			//~ stan.G = num.bajts.b/3;
			//~ stan.B = num.bajts.c/3;
			//~ if ( num.bajts.d == 0 ) {
				//~ num.bajts.d = 1;
			//~ }
			//~ //_delay_ms( num.bajts.d*2+50 );
			//~ _delay_ms( 500 );
			//~ 
		//~ //}
		
