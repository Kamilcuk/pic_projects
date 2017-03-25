/*
 * seconddelay.c

 delay implementation for 48Mhz pic processor speed
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
