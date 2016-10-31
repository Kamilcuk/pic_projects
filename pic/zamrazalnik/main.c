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
 * zamrazalnik
 * 
 */
#include <pic18fregs.h>
#include <pic18f2550.h>
#include <sdelay/sdelay.h>
#include "pwm.c"
#include "pwm.h"


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

void ports_init()
{
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	CMCON=0x07; // turn off comparator module
	UCFGbits.UTRDIS = 1; // turn off USB module 
	
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
	
	TRISBbits.RB0 = 1;
	TRISBbits.RB1 = 1;
}

#define _step_ms 10
#define w_ms(x) (( (x)/_step_ms ))

void main(void)
{
	unsigned int licz;
	unsigned int licz2;
	unsigned char stan;
	
	licz = licz2 = stan = 0;
	
	ports_init();	
	InitPWM();
	PORTB = 0xff;
	_delay_ms(1000);
	
	for(;;) {
		if ( PORTBbits.RB0 == 1 ) {
			// zamknięte drzwi
			licz = 0;
			PORTB = 0x00;
		} else {
			PORTB = 0xff;
			
			// otwarte drzwi;
			// zaczekaj 30*100*10 ms = 30*1000ms = 30sec
			if ( licz <= w_ms(30*1000) ) {
				licz++;
			} else {
				
				// dosc czekania, trzeba pipac
				while ( PORTBbits.RB0 == 0 ) {
					
					// beepuj co 0,5 sec
					licz2++;
					if ( licz2 <= w_ms(250) ) {
						SetPWMDutyCycle(512);
						PORTB = 0xff;
					} else if ( licz2 <= w_ms(500) ) {
						PORTB = 0;
						SetPWMDutyCycle(0); 
					} else {
						licz2 = 0;
					}
					
					_delay_ms(_step_ms);
				}
				
				// jesli zamkniesz drzwi, przestan pipkac
				licz = 0;
				SetPWMDutyCycle(512);
				_delay_ms(50);
				SetPWMDutyCycle(0);
				_delay_ms(50);
				SetPWMDutyCycle(512);
				_delay_ms(50);
				SetPWMDutyCycle(0);
				_delay_ms(50);
				SetPWMDutyCycle(512);
				_delay_ms(50);
				SetPWMDutyCycle(0);
				_delay_ms(50);
				
			}
		}
		_delay_ms(_step_ms);
	}
}

