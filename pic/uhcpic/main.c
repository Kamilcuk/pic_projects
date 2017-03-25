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
#include <types.h>
#include <sdelay.h>
#include <bitops.h>

#include <hd44780/hd44780.h>
#include <hd44780-config.h>
#include <hd44780/hd44780-inst-def.h>

#include <usb/usb.h>
#include <interrupt.h>

#pragma stack 0x300 0xff

/* ********************* config and interrupts ************************** */

#pragma config PLLDIV = 4 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#pragma config XINST=OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

static void high_interrupt(void) __interrupt(1)
{
	USB_interrupt_service();
}

static void low_interrupt(void) __interrupt(2)
{
}

/* ********************** main body ************************* */

/*
struct {
	const unsigned char b[22];
} const buff[15] = { 
	{"   PIC INITIALIZED ! "},
	{""},
	{"   ((`'-\"``\"\"-'`))"},
	{"    )   -    -  ("},
	{"   /   (o _ o)   \1"},
	{"   \1    ( 0 )    /"},
	{"   _'-.._'='_..-'_"},
	{" /`;#'#'#.-.#'#'#;`\1"},
	{" \1_))    '#'    ((_/"},
	{"   #.           .#"},
	{"   '#.         .#'"},
	{"   / '#.     .#' \0"},
	{"  _\1  \1'#. .#'/  /_"},
	{" (((___) '#' (___)))"},
};
const unsigned char const slash[] = {	
	0b00000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001,
	0b00000000,
	0b00000000,
};

static void init_text(void)
{
	unsigned char i, j, k, a, b;
	unsigned char row, ctrl;
	unsigned char const *pnt;
		
	hd44780_write_inst_all(HD44780_CLRDISP);
	// write missing backslash to CGRAM second character
	hd44780_write_inst_all(HD44780_CGRAM_ADDRESS | 8*1);
	for(i=0;i<sizeof(slash);i++)
		hd44780_write_data_all(slash[i]);
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS);
	hd44780_write_inst_all(HD44780_CLRDISP);
	
	
	for(a=0xff;a;a--)for(b=0xff;b;b--); 
		
	// from every line from below 
	for(i=17;i;i--)  {
		hd44780_write_inst_all(HD44780_CLRDISP);
		
		// write as many lines to the last one 
		for(j=i-1; j<16 && j+1-i < (sizeof(buff)/sizeof((*buff).b)); j++) {
			row = j%2;
			ctrl = j/2;
			
			// set cursor position 
			hd44780_write_inst(ctrl, HD44780_DDRAM_ADDRESS | ( row << 6 ) );
			
			// write buff[]
			pnt = buff[j+1-i].b;
			for (k=0; k<sizeof((*buff).b) && pnt[k] != '\0'; k++) {
				hd44780_write_data(ctrl, pnt[k]);
			}
			
		}
		
		for(a=0xff;a;a--)for(b=0xff;b;b--); 
	}
	for(a=0xff;a;a--)for(b=0xff;b;b--); 
}
*/

const unsigned char buff1[]=" LCD NUMER: ";
const unsigned char buff2[]=" ENABLED: ";
const unsigned char buff3[41]="QWErtyuiop[]ASDFgh?kl;'zxc\xff\xf0\xaa\xc0,./`123456";
const unsigned char buff4[] = "FAIL";
const unsigned char buff5[] = "OK";
extern struct pic_device lcddev;
#define write_str(ctrl_nr, _buff) do{unsigned char _x; for(_x=0;_x<sizeof(_buff)/sizeof(*_buff)-1;_x++) hd44780_write_data(ctrl_nr, _buff[_x]);}while(0)
#define write_str_all(_buff)      do{unsigned char _x; for(_x=0;_x<sizeof(_buff)/sizeof(*_buff)-1;_x++) hd44780_write_data_all(_buff[_x]);}while(0)
void wait() {
	int a, b;
	for(a=0xff;a;a--)for(b=0xff;b;b--);
}
void pro_init(void)
{
	unsigned char i, j, k, l;
		
	for(k=MAX_NUM_CONTROLLERS; k; k-- ) {
		for(l=MAX_NUM_CONTROLLERS; l>=k; l--) {
			i=l-1;
			
			hd44780_write_inst(i, HD44780_CLRDISP);
			hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) );
			
			write_str(i, buff1);
				
			hd44780_write_data(i, l-k+'0');
			write_str(i, buff2);
				
			for(j=0; j<MAX_NUM_CONTROLLERS; j++)
				hd44780_write_data(i, test_bit(j, lcddev.disabled)?'0':'1');
			
			hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
			write_str(i, buff3);
			
			wait();
		}
		wait();
	}
	
	wait();
	
	hd44780_write_inst_all(HD44780_CLRDISP);
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 0 << 6 ) );
	write_str_all(buff1);
		
	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
			hd44780_write_data(i, i+'0');
	
	write_str_all(buff2);
		
	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
		hd44780_write_data_all(test_bit(i, lcddev.disabled)?'0':'1');
	
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
	write_str_all(buff3);
	
	wait();
	
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
	for(i=0;i<MAX_NUM_CONTROLLERS;i++) {
		if ( test_bit(i, lcddev.disabled) )
			continue;
		
		for(j=0;j<sizeof(buff3)/sizeof(*buff3)-1; j++) {
			k = hd44780_recv(i, RS_DATA);
			if ( k != buff3[j] ) {
				break;
			}
		}
		
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 34 );
		if ( j != sizeof(buff3)/sizeof(*buff3)-1 ) {
			write_str(i, buff4);
		} else {
			write_str(i, buff5);
		}
		
		wait();
	}
	
	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 0 );
}

void main(void) 
{	
	hd44780_init();
	
	pro_init();
	
	USB_init();
	USB_wait_for_configured_state();
	
	USB_interrupt_priority_high();
	USB_interrupt_enable();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	
	for (;;) {
		u8 i;
		for(i=0xff;i;i--)
			__asm nop __endasm; /* wait some time to process usb requests, dunno why, but it works hell better */
		
		__asm sleep __endasm;/* entering PRI_IDLE mode, we get woken up by an USB interrupt */
		
	}
	
}
