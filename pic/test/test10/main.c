/* Author: Kamil Cukrowski
 * hd44780 pic2550 driver
 * licensed under gplv2
 */
/* OK! so..
 * (hd44780 documentation page 24 table 6 Instructions)
 * this driver needs to support hd44780 operations that is:
 * -clear display
 * -return home
 * -entry mode set
 * -display on/off control
 * -cursor or display shift
 * -function set
 * -set CGRAM address
 * -set DDRAM address
 * -read busy flag & address
 * -write data to CGRAM or DDRAM
 * -read data from CGRAM or DDRAM
 * 
 * to do that we have in 18f2550
 * we have 8+8+7 -2 (for usb) -2(for osc) = 19 I/O ports, so we can develop up to 9 controllers with all controlers (R/W control)
 * up to 16 endpoints in USB module in 18f2550
 * 
 * so lets get to work
 * 
 * but my driver will be simpler
 *  - - - - first implemetation idea - - - -
 * the driver will work on 1 endpoint IN/OUT
 * for every instruction exected on dispaply i need to tranfer
 * 2 bits - user choose the wait after operation - ( 37 us , 1.52ms , 0 us )
 * 4 bits - choose the controller (1 to 9)
 * 1 bit  - for RS state
 * 1 bit  - for R/W state
 * 8 bits - DB7 to DB0 sended to display
 * - - -end of idea :D -- -- -- 
 * */

#include <pic18f2550.h>
#include "types.h"
#include "usb_config.h"
#include "usb/usb.h"

#pragma stack 0x300 0xff

static void __config__lines__(void) __naked {  
/* founded that #pragma config sucks:
 * 1. gives me errors, couse in *.asm file i get 
 * #pragma config blabla=lalal
 * transforms into
 ; ; pcode starts here
 ; *more sdcc output*
 config somth=somth
 code
 * the "code" thing on the end sucks, when having tons of #pragma config
 * cause asm needs to have all configs together, in one place, line by line :D
 * 2. char __at __CONFIGXY conf=smthconf;
 *  gives me:
 * _config is deprecated! 
 * */
	__asm config PLLDIV = 5  __endasm; // 20MHz / 5 =  4Mhz -> for PLL to get 96Mhz
	
	__asm config FOSC = HSPLL_HS __endasm; // High Speed Crystal / Resonator with PLL enabled
	__asm config USBDIV = 2 __endasm; // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb
	
	/* CPUDIV = OSC1_PLL2
	 *               ^^^^ this means that, when PLL is used, it will be divided by 2 -> 96Mhz / 2 = 48Mhz
	 *          ^^^^ this means that when external oscilator is used, it will be divided by 1.
	 * ^^^^^^ this is our microcontroller speed, it is primary clock
	 * */
	__asm config CPUDIV = OSC1_PLL2 __endasm;
	
__asm
	config IESO = OFF 
	config PWRT = OFF 
	config BOR = OFF
	config VREGEN = ON 
	config WDT = OFF 
	config WDTPS = 32768 
	config MCLRE = ON 
	config LPT1OSC = OFF 
	config PBADEN = OFF 
	config CCP2MX = OFF
	config STVREN = ON 
	config LVP = OFF 
	config XINST = OFF 
	config DEBUG = OFF 
	config CP0 = OFF 
	config CP1 = OFF 
	config CP2 = OFF 
	config CP3 = OFF 
	config CPB = OFF 
	config CPD = OFF 
	config WRT0 = OFF 
	config WRT1 = OFF 
	config WRT2 = OFF 
	config WRT3 = OFF 
	config WRTB = OFF 
	config WRTC = OFF 
	config WRTD = OFF 
	config EBTR0 = OFF 
	config EBTR1 = OFF 
	config EBTR2 = OFF 
	config EBTR3 = OFF 
	config EBTRB = OFF 
#ifdef __18f4550 // for pic18f4550 and (i guess!) also for pic18f4455
	config BORV = 21 
	config FCMEM = OFF 
	config ICPRT = OFF 
#endif
__endasm;  
}

/* ---------------- START interrupts handlers  -------------- */

/* note: reset interrupt in crt file */

//#pragma code __reset_interrupt__ 0x0800
/*void __reset_interrupt__(void) __interrupt(0)
{
	__asm
	goto    __startup
	__endasm;
}*/
#pragma code __high_interrupt__ 0x0808
void __high_interrupt__(void)
{
}
#pragma code __low_interrupt__ 0x0818
void __low_interrupt__(void)
{
}


/* ---------------- ENDOF interrupthandlesr --------------------- */

void main(void) 
{
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as (normal) digital inputs
	CMCON=0x07; // turn off comparator module
	
	/* port A */
	LATA=0x00;
	TRISA=0x00;
	
	// port b
	LATB=0x00;
	TRISB=0x00;
	
	// port c
	LATC=0x00;
	TRISC=0x00;
	

	PORTA = PORTB = PORTC = 0xff;
	
	USB_init();
	do {
		USB_service();

	} while (1);
}


