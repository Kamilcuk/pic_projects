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
#include <usart.h>
#include <pic18fregs.h>
#include <usb/usb.h>
#include <sdelay.h>
#include <usart.h>
#include <types.h>
#include "usb_ep1.h"

#include <signal.h>
#include <bitops.h>
#include <interrupt.h>


/* ********************* config ************************** */

#pragma config PLLDIV = 5 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = HSPLL_HS // High Speed Crystal / Resonator with PLL enabled
#pragma config IESO = ON, PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768, MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF, CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

/* ********************* EOF config ************************** */



#define ROWS 3
__near unsigned char state[ROWS];
unsigned char timer_speed_H = (( 0xff - 0x06 ));
unsigned char timer_speed_L = (( 0xff - 0x00 ));

/* ********************** main body ************************* */

__once void ports_init()
{
	unsigned char i;
	
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

	for(i=0; i<ROWS;i++)
		state[i] = 0;
}
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

#define PR_PRESENCE 0x01
#define PR_CLEAR 0x02
#define PR_TOGGLE 0x03
#define PR_SETSLEEP_HIGH 0x04
#define PR_SETSLEEP_LOW 0x05
#define PR_OK 0x06
#define PR_ERR 0x07
void uart_process()
{
	unsigned char byte, byte2;
	
	byte = usart_getc();
	
	if ( byte == PR_CLEAR ) {
		for(byte2 = 0; byte2<ROWS; byte2++)
			state[byte2] = 0;
	} else {	
		byte2 = usart_getc();
		
		if ( byte2 != byte )
			goto ERR;
		
		
		switch(byte) {
		case PR_TOGGLE:
			byte = usart_getc();
			byte2 = usart_getc();
			if ( byte != byte2 )
				goto ERR;
			toggle_bit(byte%10, state[byte/10]);
			break;
		case PR_SETSLEEP_HIGH:
			byte = usart_getc();
			byte2 = usart_getc();
			if ( byte != byte2 )
				goto ERR;
			timer_speed_H = byte;
			break;
		case PR_SETSLEEP_LOW:
			byte = usart_getc();
			byte2 = usart_getc();
			if ( byte != byte2 )
				goto ERR;
			timer_speed_L = byte;
			break;
		case PR_PRESENCE:
			break;
		}
	}
	
	usart_putc(PR_OK);
	usart_putc(PR_OK);
	return;
ERR:
	usart_putc(PR_ERR);
	usart_putc(PR_ERR);
}

static void timer_interrupt()
{
	static unsigned char pos = 0;
	
	// set timer value
	TMR1H = timer_speed_H;
	TMR1L = timer_speed_L;
	
	// set_diodes
	// claer all
	PORTB = 0x00;
	PORTCbits.RC0 = 0;
	PORTCbits.RC1 = 0;
	PORTCbits.RC2 = 0;
	PORTCbits.RC4 = 0;
	PORTCbits.RC5 = 0;
	
	// ROW
	if ( pos == 0 ) {
		PORTCbits.RC0 = 1;
	} else if ( pos == 1 ) {
		PORTCbits.RC1 = 1;
	} else if ( pos == 2 ) {
		PORTCbits.RC2 = 1;
	} else if (pos == 3) {
		PORTCbits.RC4 = 1;
	} else {
		PORTCbits.RC5 = 1;
	}
	
	// SET COL
	PORTB = state[pos];
	
	// pos increment
	++pos;
	if ( pos >= ROWS )
		pos = 0;
	
}

static void high_interrupt(void) __interrupt(1)
{			
	if ( PIR1bits.TMR1IF ) {
		PIR1bits.TMR1IF = 0;
		timer_interrupt();
	}
	USB_interrupt_service();
}

static void low_interrupt(void) __interrupt(2)
{
	USB_interrupt_service();
/*	if ( PIR1bits.RCIF ) {
		PIR1bits.RCIF = 0;
		for(;;) {
			PORTCbits.RC1 = 1;
			PORTB=0xff;
		}
	}*/
}

void process(unsigned char *str)
{
	unsigned char i;
	unsigned char save = 3;
	for(i=0;str[i]!='\0';i++) {
		if ( save == 3 ) {
			save = str[i]-'0';
			continue;
		}
		toggle_bit(str[i]-'0', state[save]);
		save = 3;
	}
}
void clear() {
	unsigned char i;
	for(i=0;i<ROWS;i++)
		state[i] = 0;
}

void main(void)
{
unsigned char i;
	ports_init();
	serial_init();
	
	/* timer setup configure */
	T1CON=0b10000001;
/* 
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
*/
	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	PIE1bits.TMR1IE = 1; /* timer0 rnable interrupt */ 
	IPR1bits.TMR1IP = 1; /* timer0 high interrupt */
	TMR1H = 0xff;
	TMR1L = 0xf0;
	
	//PIR1bits.RCIF = 0; /* EUSART Receive Interrupt Flag bit */
	//PIE1bits.RCIE = 0; /*  EUSART Receive Interrupt Enable bit */
	//IPR1bits.RCIP = 0; /* EUSART Receive Interrupt Priority bit */
	
	PORTB = 0xff;
	PORTC = 0xff;
	delay10ktcy(10);
	
	USB_init_in_configured_state();
	USB_interrupt_priority_high();
	USB_interrupt_enable();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	

#define set_state(x, y, z) state[0]=x;state[1]=y;state[2]=z;
#define set_state_10(x, y, z) set_state(x,y,z);delay10ktcy(5);
#define process_delay(str) process(str);delay10ktcy(1);clear();

	set_state_10(0x01, 0x01, 0x01);
	for(i=0;;i++) {
	}
}
