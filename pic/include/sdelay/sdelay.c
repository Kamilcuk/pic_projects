/*
 * seconddelay.c

 delay implementation for 48Mhz pic processor speed
 * 
 * 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
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
