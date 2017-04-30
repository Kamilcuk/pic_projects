/*
 * File:   main.c
 * Author: kamil
 *
 * Created on 28 kwietnia 2017, 16:02
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <GenericTypeDefs.h>

void Serinit(void)
{
  TRISC = 0xFF;
  RCSTA = 0xB0;
  TXSTA = 0x24;
  SPBRG = 0x12;
}
void putch(char data)
{

  while(!TXIF);
TXREG = data;
}

#pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = INTOSC_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = OFF        // USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
#pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
#pragma config XINST    = OFF        // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CP2      = OFF
#pragma config CP3      = OFF
#pragma config CPB      = OFF
#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRT2     = OFF
#pragma config WRT3     = OFF
#pragma config WRTB     = OFF        // Boot Block Write Protection
#pragma config WRTC     = OFF
#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTR2    = OFF
#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF


#define _XTAL_FREQ 300000

static uint8_t addrstack[150];
static uint8_t *addrstack_pnt = addrstack;

#define addrstack_start addrstack
#define addrstack_len   (sizeof(addrstack)/sizeof(*addrstack))
#define addrstack_end   addrstack_start+(uint8_t*)(addrstack_len)

void ReturnAddressStack_push(void)
{
	UINT24_VAL myret;

	di();

	// store our ReturnAddress
	myret.Val = TOS;
	--STKPTRbits.STKPTR;

	// we need to save this many ReturnAdresses
	const unsigned char stkptr = STKPTRbits.STKPTR;

	while( STKPTRbits.STKPTR != 0 ) {

		// save ReturnAdresses
		*addrstack_pnt = TOSL;
		++addrstack_pnt;
		*addrstack_pnt = TOSH;
		++addrstack_pnt;
		*addrstack_pnt = TOSU;
		++addrstack_pnt;

		--STKPTRbits.STKPTR;
	}

	// remember how many ReturnAddresses we saved
	*addrstack_pnt = stkptr;
	++addrstack_pnt;

	// restore our ReturnAddress
	++STKPTRbits.STKPTR;
	WREG = myret.byte.UB;
	TOSU = WREG;
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

void ReturnAddressStack_pop(void)
{
	UINT24_VAL myret;

	di();

	/* remember where do we return */
	myret.Val = TOS;
	--STKPTRbits.STKPTR;
	
	// first char is length of ReturnAddresses we saved
	--addrstack_pnt;
	unsigned char stkptr = *addrstack_pnt;

	// restore ReturnAddresses
	while( stkptr != 0 ) {

		// STKPTR is first incremented
		++STKPTRbits.STKPTR;
		--stkptr;

		// restore ReturnAddress
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSU = WREG;
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSH = WREG;
		--addrstack_pnt;
		WREG = *addrstack_pnt;
		TOSL = WREG;
	}

	// restore my return location
	++STKPTRbits.STKPTR;
	WREG = myret.byte.UB;
	TOSU = WREG;
	WREG = myret.byte.HB;
	TOSH = WREG;
	WREG = myret.byte.LB;
	TOSL = WREG;

	ei();
}

#define declare_interrupt_reset_priotiy( FUNC ) \
asm("global	_" #FUNC ",powerup,start"); \
asm("psect	powerup,class=CODE,delta=1,reloc=2"); \
asm("powerup:"); \
asm("call _SYS_InterruptReset"); \
asm("goto start"); \
void FUNC(void)

declare_interrupt_reset_priotiy         ( SYS_InterruptReset )
{
	RCONbits.RI = RCONbits.TO = RCONbits.PD = RCONbits.POR = RCONbits.BOR = 1;
	STKPTRbits.STKFUL = STKPTRbits.STKUNF = 0;
}

void interrupt high_priority SYS_InterruptHigh(void)
{    
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

#define FUNC(i, j) \
	void f_ ## i();\
	void f_ ## j();\
	void f_ ## i(){\
		printf("-> f_" #i "() -> f_" #j "()\n" );\
		f_ ## j();\
		printf("<- f_" #i "()\n" );\
	}

#define FUNC_SAVE(i, j) \
	void f_ ## i();\
	void f_ ## j();\
	void f_ ## i(){\
		printf("-> f_" #i "() -> f_" #j "()\n" );\
		ReturnAddressStack_push(); \
		f_ ## j();\
		ReturnAddressStack_pop(); \
		printf("<- f_" #i "()\n" );\
	}

FUNC(1, 2)  FUNC(2, 3)    FUNC(3, 4)   FUNC(4, 5)   FUNC(5, 6)   FUNC(6, 7)   FUNC(7, 8)   FUNC(8, 9)   FUNC(9, 10)  FUNC_SAVE(10, 11)
FUNC(11, 12) FUNC(12, 13) FUNC(13, 14) FUNC(14, 15) FUNC(15, 16) FUNC(16, 17) FUNC(17, 18) FUNC(18, 19) FUNC(19, 20) FUNC_SAVE(20, 21)
FUNC(21, 22) FUNC(22, 23) FUNC(23, 24) FUNC(24, 25) FUNC(25, 26) FUNC(26, 27) FUNC(27, 28) FUNC(28, 29) FUNC(29, 30) FUNC_SAVE(30, 31)
FUNC(31, 32) FUNC(32, 33) FUNC(33, 34) FUNC(34, 35) FUNC(35, 36) FUNC(36, 37) FUNC(37, 38) FUNC(38, 39) FUNC(39, 40) FUNC_SAVE(40, EEEND)
FUNC(41, 42) FUNC(42, 43) FUNC(43, 44) FUNC(44, 45) FUNC(45, 46) FUNC(46, 47) FUNC(47, 48) FUNC(48, 49) FUNC(49, 50) FUNC(50, 51)
FUNC(51, 52) FUNC(52, 53) FUNC(53, 54) FUNC(54, 55) FUNC(55, 56) FUNC(56, 57) FUNC(57, 58) FUNC(58, 59) FUNC(59, 60) FUNC_SAVE(60, 61)
FUNC(61, 62) FUNC(62, 63) FUNC(63, 64) FUNC(64, 65) FUNC(65, 66) FUNC(66, 67) FUNC(67, 68) FUNC(68, 69) FUNC(69, 70) FUNC(70, 71)
FUNC(71, 72) FUNC(72, 73) FUNC(73, 74) FUNC(74, 75) FUNC(75, 76) FUNC(76, 77) FUNC(77, 78) FUNC(78, 79) FUNC(79, 80) FUNC_SAVE(80, 81)
FUNC(81, 82) FUNC(82, 83) FUNC(83, 84) FUNC(84, 85) FUNC(85, 86) FUNC(86, 87) FUNC(87, 88) FUNC(88, 89) FUNC(89, 90) FUNC(90, 91)
FUNC(91, 92) FUNC(92, 93) FUNC(93, 94) FUNC(94, 95) FUNC(95, 96) FUNC(96, 97) FUNC(97, 98) FUNC(98, 99) FUNC(99, 100) FUNC_SAVE(100, EEEND)
void f_EEEND() {
	printf("<- f_EEEND()\n" );
}
void main(void)
{
	Serinit();
	while(1) {
		f_1();
	}
	return;
}
