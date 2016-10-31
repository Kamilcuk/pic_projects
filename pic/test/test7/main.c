
#include <pic18f2550.h>


typedef unsigned char u8;
typedef unsigned char u16;


static void __config__lines__(void) __naked 
{  
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
	//__asm config PLLDIV = 4  __endasm; // 16MHz / 4 =  4Mhz -> for PLL to get 96Mhz
	__asm config PLLDIV = 5  __endasm; // 20Mhz
	__asm config CPUDIV = OSC1_PLL2 __endasm;
	/* CPUDIV = OSC1_PLL2
	 *               ^^^^ this means that, when PLL is used, it will be divided by 2 -> 96Mhz / 2 = 48Mhz
	 *          ^^^^ this means that when external oscilator is used, it will be divided by 1.
	 * ^^^^^^ this is our microcontroller speed, it is primary clock
	 * */
	__asm config USBDIV = 2 __endasm; // from PLL -> 96Mhz / 2 = 48Mhz -> full speed usb
	
	__asm config FOSC = HSPLL_HS __endasm; // High Speed Crystal / Resonator with PLL enabled
	
__asm
	config IESO = ON
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
#define delayl() do { delay();delay();delay();delay();delay();delay();delay(); } while(0)
#define delayll() do { delayl();delayl();delayl(); } while(0)
void port_init()
{
	/* port A */
        PORTA=0xff;
        LATA=0x00;
        TRISA=0x00;

        // port b
        PORTB=0xff;
        LATB=0x00;
        TRISB=0x00;

        // port c
        PORTC=0xff;
        LATC=0x00;
        TRISC=0x00;
}

const char zamien[10] = {
	0b11111100,
	0b01100000,
	0b11011010,
	0b11110010,
	0b01100110,
	0b10110110,
	0b10111110,
	0b11100000,
	0b11111110,
	0b11110110,
};

void light_set(u8 what, u8 __near  *pnt, u8 bit, u8 __near *clk_pnt, u8 clk_bit)
{
	u8 i = 1;

	do {
		if ( what&i )
			*pnt |= 1 << bit;
		else
			*pnt &= ~(1 << bit);
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		// 100 ns minimum data set up time
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		 // 30 ns pulse width;
		*clk_pnt |= 1 << clk_bit;
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
		*clk_pnt &= ~(1 << clk_bit);
		__asm NOP __endasm;
		__asm NOP __endasm;
		__asm NOP __endasm;
			
		i <<= 1;
	} while( i );
}

void __bcd_write(u8 what, u8 where)
{
	if ( what > 10 ) {
		light_set(1, &PORTB, 0, &PORTB, 1);
		return;
	}
	
	switch(where) {
	case 0:
		light_set(zamien[what], &PORTB, 0, &PORTB, 1);
		break;
	case 1:
		light_set(zamien[what], &PORTB, 0, &PORTB, 2);
		break;
	case 2:
		light_set(zamien[what], &PORTB, 0, &PORTB, 3);
		break;
	}
}

void bcd_write(u8 num)
{
	u8 tmp;
	if ( num >= 100 )
		return;
		
	tmp = num%10;
	__bcd_write(tmp, 0);
	__bcd_write(num/10, 1);
}

void bcd_init()
{
	bcd_write(0);
}



int main(void)
{
	unsigned char i;
	
	bcd_init();
	
	port_init();
	
	for(;;) {
		for(i=0;i<100;i++) {
			delayll();
			bcd_write(i);
			PORTA=PORTA?0:0xff;
		}
	}
	
	
	return 0;
}

