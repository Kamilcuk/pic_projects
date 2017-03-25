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
#include "usb.h"
#include <adc.h>
#include <sdelay.h>

#include <hd44780/hd44780.h>
#include <ds18x20/onewire.h>
#include <ds18x20/ds18x20.h>
#include <seconddelay/seconddelay.h>

static unsigned char __pos = 0;

#include <stdio.h>
PUTCHAR(c)
{
	hd44780_write_data_all(c);
	__pos++;
	if ( __pos == 8 ) {
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | (1<<6) );
	} else if ( __pos == 16 ) {
		__pos = 0;
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS);
	}
}

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
}
static void low_interrupt(void) __interrupt(2)
{
}

/* ---------------- ENDOF interrupthandlesr --------------------- */

unsigned int get_temp(unsigned char chn)
{
	unsigned int new;
	adc_setchannel(chn);
	adc_conv();
	while(adc_busy()) {}
	
	delay100tcy(1);
	
	new = adc_read();
	
	new >>= 6;
	new &= 0x03ff;
	
	new *= 5; // convert to XXX.X stopni celcjusza
	
	return new;
}

void stop()
{
	PORTCbits.RC2 = 0;
}

void start()
{
	PORTCbits.RC2 = 1;
}

void init_text(void)
{
	char buff[] = "START";
	unsigned char k;
		
	hd44780_write_inst_all(HD44780_CLRDISP);
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS);
	
	for (k=0; k < sizeof(buff)/sizeof(char)-1; k++) {
		hd44780_write_data_all(buff[k]);
	}
	
	hd44780_write_inst(0, HD44780_DDRAM_ADDRESS | (1<<6) );
	for (k=0; k < sizeof(buff)/sizeof(char)-1; k++) {
		hd44780_write_data_all(buff[k]);
	}
	
	hd44780_write_inst_all(HD44780_CLRDISP);
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS);
}


#define clrscr() do{ __pos = 0; hd44780_write_inst_all(HD44780_CLRDISP); hd44780_write_inst_all(HD44780_DDRAM_ADDRESS); } while(0)

#define MAXSENSORS 5

uint8_t nSensors;
__near uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];


void init_sensors()
{
	uint8_t i;
	
	clrscr();
	printf_tiny("Scan    " "        ");
	
	nSensors = DS18X20_search_sensors((__near uint8_t *)gSensorIDs, MAXSENSORS);
	
	delay100ktcy(100);
	clrscr();
	printf_tiny("Sensors " "%d", nSensors);
	delay100ktcy(100);
		
	for ( i = 0; i < nSensors; i++ ) {
		
		clrscr();
		
		DS18X20_write_scratchpad( &gSensorIDs[i][0], 0, 0, DS18B20_9_BIT );
		
		printf_tiny( "#%d ", i+1 );
		
		if ( gSensorIDs[i][0] == DS18S20_FAMILY_CODE ) {
			printf_tiny( "S20/20" );
		} else if ( gSensorIDs[i][0] == DS1822_FAMILY_CODE ) {
			printf_tiny( "22    " );
		} else {
			printf_tiny( "B20   " );
		}
		if ( DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE ) {
			printf_tiny( "   p" );
		} else {
			printf_tiny( "   e" ); 
		}
		delay100ktcy(100);
	}
	
}

void print_num(unsigned int num)
{	
	unsigned char n1, n2, n3, n4;
	
	n1=num%10;
	num/=10;
	n2=num%10;
	num/=10;
	n3=num%10;
	num/=10;
	n4=num;
	
	if ( n4 == 0 ) {
		hd44780_write_data_all(' ');
	} else {
		hd44780_write_data_all(n4+'0');
	}
	if ( n3+n4 == 0 ) {
		hd44780_write_data_all(' ');
	} else {
		hd44780_write_data_all(n3+'0');
	}
	if ( n2+n3+n4 == 0 ) {
		hd44780_write_data_all(' ');
	} else {
		hd44780_write_data_all(n2+'0');
	}
	hd44780_write_data_all(n1+'0');
}

#define HISTEREZA 20

int main( void )
{
	int16_t decicelsius;
	unsigned char error;
	unsigned int temp;
	unsigned char state;
	
	state = 0;
	stop();
	
	hd44780_init();
	
	init_text();
	delay100ktcy(100);
	
	adc_open(0,
		ADC_FOSC_64 | ADC_ACQT_12,
		ADC_CFG_2A,
		ADC_FRM_LJUST | ADC_INT_OFF | ADC_VCFG_VDD_VSS
	);
	
	init_sensors();
	
	for(;;) {   // main loop
		
		error=0;
		if ( nSensors == 0 )
			error++;
		
		// only one sensor
		if ( DS18X20_start_meas( DS18X20_POWER_PARASITE, &gSensorIDs[0][0] ) != DS18X20_OK ) {
			printf_tiny("Sm.errs" );
			error++;
		}
			
		_sdelay_ms( DS18B20_TCONV_9BIT );
			
		if ( DS18X20_read_decicelsius( &gSensorIDs[0][0], &decicelsius) != DS18X20_OK ) {
			printf_tiny( "CRC" );
			error++;
		}
		
		temp = get_temp(1);
		
		clrscr();
		print_num(temp-HISTEREZA);
		print_num(temp+HISTEREZA);
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | 1<<6 );	
		print_num(decicelsius);
		printf_tiny(state ? "  ON" : " OFF");
		
		if ( state == 0 ) {
			if ( temp <= decicelsius-HISTEREZA ) {
				state=1;
				start();
			}
		} else {
			if ( temp >= decicelsius+HISTEREZA ) {
				state=0;
				stop();
			}
		}
		
		
		if ( error ) {
			
			printf_tiny( "error    " );
			delay100ktcy(100);
			clrscr();
			init_sensors();
		}
	}
}

