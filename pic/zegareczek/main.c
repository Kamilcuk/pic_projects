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

#define VERSION "0.0.1"


#pragma config PLLDIV = 4 // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz // 5 for 20Mhz 
#pragma config CPUDIV = OSC4_PLL6
#pragma config USBDIV = 1 // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb	
#pragma config FOSC = INTOSCIO_EC
#pragma config IESO = OFF, PWRT = OFF, BOR = OFF, BORV = 2, VREGEN = OFF
#pragma config WDT = OFF, WDTPS = 32768, MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF, CCP2MX = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF, WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF, EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
#pragma config FCMEM = OFF, ICPRT = OFF 
#endif

__near unsigned char sec, min, hour;


/*** code from pdf :
 *
RTCinit
        MOVLW  80h          ; Preload TMR1 register pair
        MOVWF  TMR1H        ; for 1 second overflow
        CLRF   TMR1L
        MOVLW  b'00001111'  ; Configure for external clock,
        MOVWF  T1CON        ; Asynchronous operation, external oscillator
        CLRF   secs         ; Initialize timekeeping registers
        CLRF   mins         ;
        MOVLW  .12
        MOVWF  hours
        BSF    PIE1, TMR1IE ; Enable Timer1 interrupt
        RETURN
RTCisr
                            ; Insert the next 4 lines of code when TMR1
                            ; can not be reliably updated before clock pulse goes low
        BTFSC  TMR1L,0      ; wait for TMR1L to become clear
        BRA    $-2          ; (may already be clear)
        BTFSS  TMR1L,0      ; wait for TMR1L to become set
        BRA    $-2          ; TMR1 has just incremented
                            ; If TMR1 update can be completed before clock pulse goes low
                            ; Start ISR here
        BSF    TMR1H, 7     ; Preload for 1 sec overflow
        BCF    PIR1, TMR1IF ; Clear interrupt flag
        INCF   secs, F      ; Increment seconds
        MOVLW  .59          ; 60 seconds elapsed?
        CPFSGT secs
        RETURN              ; No, done
        CLRF   secs         ; Clear seconds
        INCF   mins, F      ; Increment minutes
        MOVLW  .59          ; 60 minutes elapsed?
        CPFSGT mins
        RETURN              ; No, done
        CLRF   mins         ; clear minutes
        INCF   hours, F     ; Increment hours
        MOVLW  .23          ; 24 hours elapsed?
        CPFSGT hours
        RETURN              ; No, done
        CLRF   hours        ; Reset hours
        RETURN              ; Done


 * */		

/* ---------------- START interrupthandlesr --------------------- */

static void RTCisr(void) __interrupt
{
	if ( PORTAbits.RA6 ) {
		do { 
			if ( PORTCbits.RC4 ) {
				min++;
				if ( min >= 60 )
					min = 0;
				while ( PORTCbits.RC4 ) {}
			} else if ( PORTCbits.RC5 ) {
				hour++;
				if ( hour >= 24 )
					hour = 0;
				while ( PORTCbits.RC5 ) {}
			}
			PORTA = sec;
			PORTB = min | ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
			PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
		} while ( PORTAbits.RA6 );
	}
	
	sec++;
	if ( sec >= 60 ) {
		sec = 0;
		min++;
		if ( min >= 60 ) {
			min = 0;
			hour++;
			if ( hour >= 24 ) {
				hour = 0;
			}
			PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
			PORTB = ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
			// PORTB =  min | ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
			//PORTCbits.RC2 = hour&0b00001;
			//PORTBbits.RB7 = hour&0b00010;
			//PORTBbits.RB6 = hour&0b00100;
			//PORTCbits.RC6 = hour&0b01000;
			//PORTCbits.RC7 = hour&0b10000;
		}
		PORTB = min | ( PORTB&0b11000000 );
	}
	PORTA = sec;
/*
 * 
__asm
        INCF   _sec, F      ; Increment seconds
        MOVLW  .59          ; 60 seconds elapsed?
        CPFSGT _sec         ; Skip next command if sec > 59
	GOTO SecUpdate      ; Update display of seconds
        CLRF   _sec         ; Clear seconds
        INCF   _min, F      ; Increment minutes
        MOVLW  .59          ; 60 minutes elapsed?
        CPFSGT _min         ; Skip next command if min > 59
	GOTO MinUpdate      ; Update display of minutes
        CLRF   _min         ; clear minutes
        INCF   _hour, F     ; Increment hours
        MOVLW  .23          ; 24 hours elapsed?
        CPFSGT _hour        ; Skip next command if hour > 23
	GOTO HourUpdate     ; Update display of hours
        CLRF   _hour        ; Reset hours
HourUpdate:
__endasm;
	PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
	PORTB = ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
__asm
MinUpdate:
__endasm;
	PORTB = min | ( PORTB&0b11000000 );
__asm
SecUpdate:
__endasm;
	PORTA = sec;
*
* */

}

static void low_interrupt(void) __interrupt(2) __naked
{
__asm
        BSF    TMR1H, 7     ; Preload for 1 sec overflow
        BCF    PIR1, TMR1IF ; Clear interrupt flag
        GOTO _RTCisr
__endasm;
}

/* ---------------- ENDOF interrupthandlesr --------------------- */

void init()
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
	
	TRISAbits.RA6 = 1;
}

void RTCinit()
{
	TMR1H = 0x80;
	TMR1L = 0x00;
	
	/* timer setup configure */
	T1CON=0b00001111;
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

	sec=0;
	min=0;
	hour=12;
	
	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	PIE1bits.TMR1IE = 1; /* timer0 enable interrupt */ 
	IPR1bits.TMR1IP = 0; /* timer0 interrupt high/low */
}

void info()
{
	unsigned int i;
	PORTBbits.RB0 = 1;
	PORTBbits.RB1 = 0;
	PORTBbits.RB2 = T1CONbits.T1RUN; /* should to be set ! */
	PORTBbits.RB3 = OSCCONbits.OSTS; /* should to be clear ! */
	PORTC=0xff;
	for (i=0;;++i) {
		if ( i == ( 32768/512 ) ) {
			break;
		}
		PORTA = i>>4;
	}
	
	/* for the first time */
	PORTA = sec;
	PORTB = min | ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
	PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
}

int main()
{
	OSCTUNEbits.INTSRC = 0;
	OSCTUNEbits.TUN = 0b10000;
	
	init();
	
	RTCinit();
	
	OSCCONbits.SCS1 = 0; /* SEC_RUN , cpu clock from timer1 oscilator :D*/
	OSCCONbits.SCS0 = 1;
	OSCCONbits.IDLEN = 1; /* SEC_IDLE when sleep */
	
	info();
	
	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	INTCONbits.GIEL = 1; /* Enables all low priority interrupts */
	
	for(;;)
		__asm sleep __endasm; /* entering SEC_IDLE mode  - 57uA consumption */
}
