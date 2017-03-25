/*
 * main.c
 *
 *  Created on: 09.02.2017
 *      Author: Kamil Cukrowski
 */
#include <pic18fregs.h>
#include "usbcdc/usbcdc.h"
#include <stdio.h>
#include <ctype.h>
#include <sdelay.h>
#include <stdlib.h>
#include <string.h>
#include "pt.h"
#define printf printf_tiny

// silence sdcc warning
#pragma config XINST = OFF


/* ----------------------- interrupts ---------------------------------- */

void _high_interrupt_(void) __shadowregs __interrupt(1)
{
}

void _low__interrupt_(void) __shadowregs __interrupt(2)
{
	if ( PIR2bits.USBIF ) {
		usbcdc_handler();
		PIR2bits.USBIF = 0;
	}
}

/* ----------------- putchar getchar functions ------------------ */

PUTCHAR(c)
{
	if ( c == '\n' ) {
		usbcdc_putchar('\r');
	}
	usbcdc_putchar(c);
	if ( c == '\n' ) {
		usbcdc_flush();
	}
}
char getchar(void) {
	usbcdc_flush();
	return usbcdc_getchar();
}
void flush(void) {
	usbcdc_flush();
}
#define getchar_ready() usbcdc_getchar_ready()

/* ----------------------- startup --------------------------- */

static void main_start(void)
{
	OSCCON = 0x70;

	/* port A */
	PORTA=LATA=TRISA=0x00;
	/* port B */
	PORTB=LATB=TRISB=0x00;
	/* port C */
	PORTC=LATC=TRISC=0x00;

	usbcdc_init();
	USB_interrupt_priority_low();
	USB_interrupt_enable();

	RCONbits.IPEN = 1; // Enable priority levels on interrupts
	INTCONbits.GIEH = 1;  // Enables all high priority interrupt
	INTCONbits.GIEL = 1; // Enables all low priority interrupts
	
	usbcdc_wait_configured();
	printf_tiny("\n\nWelcome!\n\n");
}


/* ----------------------- main handlers ---------------------------------- */

void main(void)
{
	unsigned int a = 0;
	unsigned int i=0;

	main_start();
	
	while(1) {
		printf("CZESC! \n");
		if ( getchar_ready() ) {
			char znak = getchar();
			printf(" WPISALES %c , a to szesnastkowo to jest tyle: %x \n", znak, znak);
		}
	
		PORTCbits.RC7 = 1;
		PORTCbits.RC6 = 1;
		for(i=0;i<11;++i) for(a=0;a<65535;++a);
		PORTCbits.RC7 = 0;
		PORTCbits.RC6 = 0;
		for(i=0;i<11;++i) for(a=0;a<65535;++a);
	}
}
