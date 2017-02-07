/*
File: pic-config.h

Copyright (c) 2009,2013 Kustaa Nyholm / SpareTimeLabs

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
Version 1.1     Compatible with SDCC 3.x

*/


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
	config WRTB = ON
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
