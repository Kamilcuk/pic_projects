/*
 * seconddelay.c

 delay implementation for 48Mhz pic processor speed
 * 
 * Under BEER-WARE license 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 * 
 */

 #include "sdelay.h"

/* BUG: argument cant be 0 !!!! (thest why it is _delay_XX no chekcing */

void _sdelay_us(unsigned int __us) 
{
	// for 12Mhz instruction cycle
	// we execute 12 instruction per one loop :D
	// 12Mhz - one instruction
	// 12*12Mhz = 1Mhz = 1us
	do {
		// 12-7 = 5 instructions
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
		__endasm;
	} while(--__us); // 7 instructions with branch
}

void sdelay_us(unsigned int __us) 
{
	while(__us--); // 7 instructions with branch
	{
		// 12-7 = 5 instructions
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
		__endasm;
	} 
}

void _sdelay_ms(unsigned int ms)
{
	do {
		_sdelay_us(1000);
	} while(--ms);
}

void sdelay_ms(unsigned int ms)
{
	while(ms--) {
		sdelay_us(1000);
	} 
}
