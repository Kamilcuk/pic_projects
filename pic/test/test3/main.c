
#include <pic18f2550.h>


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
	__asm config PLLDIV = 5 __endasm; // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz
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
	config PWRT = ON
	config BOR = ON 
	config BORV = 3
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


static void high_interrupt(void) __interrupt(1)
{
}

static void low_interrupt(void) __interrupt(2)
{
}

#define delay() do { unsigned char a, b; for(a=0xff;a;a--)for(b=0xff;b;b--); } while(0)
void main(void)
{
	unsigned char i;
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
	
	
	PORTA = 0xff;
	PORTB = 0xff;
	PORTC = 0xff;
	i=0;
	
	for(i=0xff;;--i) {
		delay();
		
		PORTA = i;
		PORTB = i;
		PORTC = i;
	}
	
	
}

