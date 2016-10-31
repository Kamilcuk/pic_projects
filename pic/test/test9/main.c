
#include <pic18fregs.h>
#include <pic18f2550.h>


#pragma udata databank2 R
#pragma udata databank2 B
#pragma udata databank2 G
#pragma udata databank2 R2
#pragma udata databank2 B2
#pragma udata databank2 G2
#pragma udata databank2 timerH
#pragma udata databank2 cnt
#pragma udata databank2 tmp
__near unsigned char R, B, G, R2, B2, G2, timerH;
struct stan_s {
	unsigned char timerH;
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
static __near struct stan_s stan;
static void high_interrupt(void) __interrupt(1)
{
	static __near unsigned char cnt = 0;
	static __near unsigned char tmp = 0;
	
	TMR1H = timerH;
	
	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */
	
	if ( cnt == 0 ) {
		R2 = stan.R;
		G2 = stan.G;
		B2 = stan.B;
		
		if ( R2 != 0 )
			tmp |= 0b10000000;
		if ( G2 != 0 )
			tmp |= 0b01000000;
		if ( B2 != 0 )
			tmp |= 0b00100000;
	} else {
		if ( cnt == R2 )
			tmp &= 0b01111111;
		if ( cnt == G2 )
			tmp &= 0b10111111;
		if ( cnt == B2 )
			tmp &= 0b11011111;
	}
	
	PORTB = tmp;
	cnt++;
	/* when cnt reasches 255 it automagically rewinds to 0 */
}

int main() 
{
	return 0;
}
