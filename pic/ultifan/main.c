/*
 * main.c
 *
 *  Created on: 09.02.2017
 *      Author: Kamil Cukrowski
 */
#include <pic18fregs.h>
#include "usbcdc/usbcdc.h"
#include <delay.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pt.h"
#define printf printf_tiny

// silence sdcc warning
#pragma config XINST = OFF

/* ----------------------- config -------------------------------------- */

static __data unsigned char fans[1] = { 0x10 };
#define FAN0_TRISBIT TRISCbits.RC6
#define FAN0_PORTBIT PORTCbits.RC6
#define FAN0_TACHBIT PORTCbits.RC7

/* ----------------------- interrupts ---------------------------------- */

static __data unsigned char timerCnt = 0;

static __data unsigned int  tachoIn = 0;

void _high_interrupt_(void) __shadowregs __interrupt(1)
{
	if ( PIR1bits.TMR2IF ) {
		if ( timerCnt == 0 ) {
			if ( fans[0] != 0 ) {
				FAN0_PORTBIT = 1;
			}
		} else {
			const unsigned char timerCntMinus1 = timerCnt-1;
			if ( timerCntMinus1 == fans[0] ) {
				FAN0_PORTBIT = 0;
			}
		}
		++timerCnt;
		PIR1bits.TMR2IF = 0; /* timer0 clear interrupt flag */
	}
	if ( PIR1bits.CCP1IF ) {
		tachoIn = CCPR2;
		PIR1bits.CCP1IF = 0; /* CCP clear interrupt flag */
	}
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

static void timer2_init()
{
	T2CON = 0x00;

	PIR1bits.TMR2IF = 0; /* timer0 clear interrupt flag */
	PIE1bits.TMR2IE = 1; /* timer0 enable interrupt */
	IPR1bits.TMR2IP = 1; /* timer0 interrupt high/low */

	PR2 = 0xff;
	TMR2 = 0x00;
	T2CONbits.TMR2ON = 1; // Timer2 On bit
}

static void CPP_start(void)
{
	// CAPTURE/COMPARE/PWM (CCP) MODULES
	// configure Timer3 with CCP

	T3CONbits.RD16 = 0;
	T3CONbits.T3CKPS = 0b00;
	T3CONbits.T3CCP1 = 1;
	T3CONbits.T3CCP2 = 0;
	T3CONbits.TMR3CS = 0;

	TMR3H = TMR3L = 0x00;
	T3CONbits.TMR3ON = 1;

	CCPR2H = CCPR2L = 0x00;
	/*
0100 = Capture mode: every falling edge
0101 = Capture mode: every rising edge
0110 = Capture mode: every 4th rising edge
0111 = Capture mode: every 16th rising edge*/
	CCP1CON = 0b00000100;


	PIR1bits.CCP1IF = 0; /* CCP clear interrupt flag */
	PIE1bits.CCP1IE = 1; /* CCP enable interrupt */
	IPR1bits.CCP1IP = 1; /* CCP interrupt high/low */
}

static void CPP_stop(void)
{
	PIE1bits.CCP1IE = 0; /* CCP enable interrupt */
	PIR1bits.CCP1IF = 0; /* CCP clear interrupt flag */
	CCP1CON = 0x00;
}

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

	timer2_init();
}


/* ----------------------- main handlers ---------------------------------- */

static __data char buff[20];
static __data unsigned char buffpos = 0;
#define ARRAYLEN(x) (sizeof((x))/sizeof(*(x)))

static unsigned char findCommaInBuff(unsigned char start) {
	for(;start<buffpos;++start) {
		if ( buff[start] == ',' ) {
			break;
		}
	}
	return start;
}

#define FOR_EVERY_COMMA_SEPARATED_VALUE_IN_BUFF(iterator, start) \
	for( (iterator) = (start); (iterator) < buffpos; (iterator) = findCommaInBuff(buff[(iterator)])+1 )

static unsigned char numberOfCommanSeparatedValuesInBuff(unsigned char start) {
	unsigned char output = 0, iterator;
	FOR_EVERY_COMMA_SEPARATED_VALUE_IN_BUFF(iterator, start) {
		++output;
	}
	return output;
}

static void handleLine(void)
{
	switch(buff[0]) {
	/// set fans f=10,20,30
	case 'f':
		switch(buff[1] ) {
		case '=':
		{
			const unsigned char start = 2;
			unsigned char f, b;
			if ( numberOfCommanSeparatedValuesInBuff(start) != sizeof(fans) ) {
				printf("ERROR - numberOfCommanSeparatedValuesInBuff(start) != sizeof(fans) \n");
				return;
			}
			f = 0;
			FOR_EVERY_COMMA_SEPARATED_VALUE_IN_BUFF(b, start) {
				if ( f >= sizeof(fans) ) {
					printf("WARN - there are less fans that values given \n");
					break;
				}
				fans[f]=atoi(&buff[b]);
				++f;
			}
			if ( f < sizeof(fans) ) {
				printf("WARN - there are more fans that values given \n");
			}
		}
			/* no break */
		case '?':
		{
			unsigned char f;
			for( f = 0; f < sizeof(fans); ++f) {
				printf("fans[%d]=%d\n", f, fans[f]);
			}
		}
			break;
		default:
			printf("f something something NOT IMPLEMENTED \n");
		}
		break;
	case 't': /// set timer
		switch(buff[1]) {
		case '=':
		{
			unsigned char tmp, b = 2;
			tmp = (unsigned char)atoi(&buff[b]);
			if ( tmp <= 10 ) {
				printf("ERROR - bad value for timer PR = %d\n", tmp);
				return;
			} else {
				PR2 = tmp;
			}
			b = findCommaInBuff(b);
			if ( b >= buffpos ) {
				printf("WARN - only timer value given\n");
			} else {
				tmp = atoi(&buff[b+1]);
				if ( tmp > 0b1111 ) {
					printf("ERROR - bad value for timer postscaler = %d\n", tmp);
					return;
				}
				T2CONbits.TOUTPS = tmp;
			}
		}
			/* no break */
		case '?':
			printf("timer PR2=%d\n", PR2);
			printf("timer postscale=%d\n", T2CONbits.TOUTPS);
			break;
		default:
			printf("Sets timer values like this:\n"
				   "t=PR,postscaler\n");
		}
		break;
	case 'm': // measure tachometer on specified fan
		printf(" NOT IMPLEMENTED \n");
		break;

	case 'i': 	// print all values
		buff[0] = 'f'; buff[1] = '?'; handleLine();
		buff[0] = 't'; buff[1] = '?'; handleLine();
		break;

	case 'R': /* reset */
		__asm__("reset");
		break;
	case 'C': /* Configuration bits */
	{
		static const __code unsigned char * const CONFIG = 0x300000;
		static const __code unsigned char * const DEVID  = 0x3ffffe;
		unsigned char i;
		for(i=0;i<7;++i) {
			printf_tiny("COFNIG%dL=%x\n", i, *(CONFIG+i*2));
			printf_tiny("COFNIG%dH=%x\n", i, *(CONFIG+i*2+1));
		}
		printf("DEVICE ID=%d,%d\n", *(DEVID), *(DEVID+1));
	}
		break;
	default:
		if ( buffpos > 0 ) {
			printf_tiny("Unrecognized command %c\n", buff[0]);
		}
		/* no break */
	case 'v': // print version
		printf_tiny(
				"\n"
				"Version information:\n"
				"ultifan pic firmware\n"
				"Type=ultifan\n"
				"Version=0.1\n"
				"Compilation time=" __DATE__" " __TIME__ "\n"
				"Author=Kamil Cukrowski\n"
				"\n"
				"Available commands: \n"
				"v                - print version info and this help\n"
				"i                - print all values\n"
				"R                - soft reset\n"
				"C                - print out configuration bits\n"
				"f=NUM[,NUM...]   - set fan speeds\n"
				"t=NUM,NUM        - set timer values\n"
				"s=BOOL[,BOOL...] - starts/stops fans (not yet implmented)\n"
				"m=NUM            - measure tachometer on specified fan\n"
				"\n"
				"BOOLs are '0' or '1'\n"
				"NUMs are 'unsigned char', in decimal form, between '0' to '255'\n"
				"ex.\n"
				"f=100,255,0 - sets fan0=100,fan1=255,fan2=0\n"
				"t=50        - sets timerH = 50\n"
				"\n"
		);
		break;
	}
}

static void thread_console(void)
{
	if ( getchar_ready() ) {
		char c = getchar();
		printf_tiny("%c",c);
		flush();

		buff[buffpos]=c;
		++buffpos;
		buffpos%=sizeof(buff);

		if ( c == '\n' || c == '\r' ) {
			printf_tiny("\r\n");

			handleLine();
			printf_tiny("\r\n");
			flush();

			buffpos = 0;
			memset(buff, 0, ARRAYLEN(buff));
		}
	}
}

static void thread_tachometer(void)
{

}

void main(void)
{
	main_start();

	usbcdc_wait_configured();
	printf_tiny("\n\nWelcome!\n\n");

	while(1) {
		thread_console();
	}
}
