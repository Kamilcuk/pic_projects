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
 * 
 */
#include <pic18fregs.h>
#include <usb/usb.h>
#include <ds18x20/onewire.h>
#include <ds18x20/ds18x20.h>
#include <stdio.h>
#include <sdelay/sdelay.h>
#include "usb_ep1.h"

#define VERSION "0.0.3"

#pragma config PLLDIV = 4 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
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

PUTCHAR(c)
{
	godpic_putc(c);
}

void port_init()
{	
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	CMCON=0x07; // turn off comparator module
	
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

void usb_init(void)
{
	USB_init_in_configured_state();
	USB_interrupt_priority_high();
	USB_interrupt_enable();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
}


#define MAXSENSORS 10
unsigned char nSensors = 0;
__near unsigned char gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];

void init_sensors()
{
	unsigned char i, j;
	
	printf_tiny("Scanning \n");
	godpic_flush();
	
	nSensors = DS18X20_search_sensors((__near uint8_t *)gSensorIDs, MAXSENSORS);
	
	printf_tiny("Sensors %d \n", nSensors);
	godpic_flush();
		
	for ( i = 0; i < nSensors; i++ ) {
		
		DS18X20_write_scratchpad( &gSensorIDs[i][0], 0, 0, DS18B20_12_BIT );
		
		printf_tiny( "#%d DS18", i+1 );
		
		if ( gSensorIDs[i][0] == DS18S20_FAMILY_CODE ) {
			printf_tiny( "S20/20" );
		} else if ( gSensorIDs[i][0] == DS1822_FAMILY_CODE ) {
			printf_tiny( "22" );
		} else {
			printf_tiny( "B20" );
		}
		if ( DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE ) {
			printf_tiny( " parasite" );
		} else {
			printf_tiny( " external" ); 
		}
		
		printf_tiny(" ID:");
		for(j=0;j<8;j++) {
			printf_tiny("%x", gSensorIDs[i][j] );
		}
		
		printf_tiny("\n");
	}
	godpic_flush();
}

#define delay() do { unsigned char i, j; for(i=0xff;i;--i) for(j=0xff;j;--j) __asm NOP __endasm; } while(0)
void main(void)
{
	unsigned int temp;
	unsigned char error;
	unsigned char timer = 20;
	unsigned char i;
	
	port_init();
	
	usb_init();
	
	// some delay for godpic to initialize
	delay();
	godpic_puts("START \n");
	
	init_sensors();
	
	error = 0;
	for(;;) {
		
		timer--;
		if ( error || nSensors == 0 || !timer ) {
			error=0;
			timer = 20;
			init_sensors();
			delay();
			continue;
		}
		
		// send all to start conversion
		if ( DS18X20_start_meas( DS18X20_POWER_PARASITE, NULL ) != DS18X20_OK ) {
			printf_tiny("Sm.errs \n");
			error++;
		}
		
		_sdelay_ms( DS18B20_TCONV_12BIT );
		
		printf_tiny("Temperatury: ");
		
		for ( i = 0; i < nSensors; i++ ) {
				
			if ( DS18X20_read_decicelsius( &gSensorIDs[i][0], &temp) != DS18X20_OK ) {
				printf_tiny( "[%d] CRC rescanning", i);
				error++;
				break;
			}
			
			printf_tiny(" %d ", temp);
		}
		printf_tiny("\n");
		godpic_flush();
	}
}


