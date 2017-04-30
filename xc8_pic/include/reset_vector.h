/*
 * reset_vector.h
 *
 *  Created on: 28.04.2017
 *      Author: kamil
 */

#ifndef RESET_VECTOR_H_
#define RESET_VECTOR_H_


/**
 * Use to declare reset vector using powerup routing in XC8 compiler.
 */
#define RESET_VECTOR_DECLARE( FUNC ) \
		asm("   global _" #FUNC ",powerup,start"); \
		asm("   psect  powerup,class=CODE,delta=1,reloc=2"); \
		asm("powerup:"); \
		asm("   call   _SYS_InterruptReset"); \
		asm("   goto   start"); \
		\
		void FUNC (void)


#define RESET_VEC_clear_flags() do{ \
	RCONbits.RI = RCONbits.POR = RCONbits.BOR = 1; \
	STKPTRbits.STKFUL = STKPTRbits.STKUNF = 0; \
}while(0)

#if 0

#define RESET_VEC_RCON_FLAGS   ( RCON   & 0b00011111 )
#define RESET_VEC_STKPTR_FLAGS ( STKPTR & 0b11000000 )

#define RESET_VEC_Power_on_Reset() \
	( RESET_VEC_RCON_FLAGS == 0b00011100 )
#define RESET_VEC_RESET_VEC_Instruction() \
	( RESET_VEC_RCON_FLAGS == 0b00001111 )
#define RESET_VEC_Brown_out() \
	( RESET_VEC_RCON_FLAGS == 0b00011110 )
#define RESET_VEC_MCLR_during_Power_Managed_Run_modes() \
	( RESET_VEC_RCON_FLAGS == 0b00011111 && RESET_VEC_STKPTR_FLAGS == 0b00000000 )
#define RESET_VEC_MCLR_during_Power_Managed_Idle_modes_and_Sleep_mode() \
	( RESET_VEC_RCON_FLAGS == 0b00011011 )
#define RESET_VEC_WDT_Time_out_during_Full_Power_or_Power-Managed_Run_modes() \
	( RESET_VEC_RCON_FLAGS == 0b00010011 )
#define RESET_VEC_MCLR_during_Full_Power_Execution() \
	( RESET_VEC_RCON_FLAGS == 0b00011111 && RESET_VEC_STKPTR_FLAGS == 0b00000000 )
#define RESET_VEC_Stack_Full_Reset() \
	(                                       RESET_VEC_STKPTR_FLAGS == 0b00000010 )
#define RESET_VEC_Stack_Underflow_Reset () \
	(                                       RESET_VEC_STKPTR_FLAGS == 0b00000001 )
#define RESET_VEC_MCLR_during_Full_Power_Execution() \
	(                                       RESET_VEC_STKPTR_FLAGS == 0b00000010 )
#define RESET_VEC_WDT_Time_out_during_Power_Managed_Idle_or_Sleep_modes() \
	( RESET_VEC_RCON_FLAGS == 0b00010011 )
#define RESET_VEC_Interrupt_Exit_from_Power_Managed_modes() \
	( RESET_VEC_RCON_FLAGS == 0b00011011 )

#endif


/********************  documentation  *******************************
 *
 * **************** MPLAB® XC8 C COMPILER USER’S GUIDE
 * __at http://ww1.microchip.com/downloads/en/DeviceDoc/50002053G.pdf
 *
 * 5.10.2 The Powerup Routine
Some hardware configurations require special initialization, often within the first few
instruction cycles after Reset. To achieve this there is a hook to the Reset vector provided
via the powerup routine.
This routine can be supplied in a user-defined assembler module that will be executed
immediately after Reset.

[...]

[..] No special linker options or other code is required. The compiler
will detect if you have defined a powerup routine and will automatically use it, provided
the code in this routine is contained in a psect called powerup.
For correct operation (when using the default compiler-generated runtime startup
code), the code must end with a GOTO instruction to the label called start.
 *
 *
 * **************** PIC18F2455/2550/4455/4550
 * __at http://ww1.microchip.com/downloads/en/devicedoc/39632c.pdf
 *
 * 4.0 RESET
The PIC18F2455/2550/4455/4550 devices differentiate
between various kinds of Reset:
a) Power-on Reset (POR)
b) MCLR Reset during normal operation
c) MCLR Reset during power-managed modes
d) Watchdog Timer (WDT) Reset (during execution)
e) Programmable Brown-out Reset (BOR)
f) RESET Instruction
g) Stack Full Reset
h) Stack Underflow Reset
 *
 */


#endif /* RESET_VECTOR_H_ */
