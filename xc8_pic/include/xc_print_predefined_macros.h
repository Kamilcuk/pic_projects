/*
 *        File: xc_print_predefined_macros.h
 *  Created on: 29.06.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef XC_PRINT_PREDEFINED_MACROS_H_
#define XC_PRINT_PREDEFINED_MACROS_H_

#include <xc.h>

#include "checkmacro.h" // CHECKMACRO

#ifndef CHECKMACRO
#define CHECKMACRO_STR1(VAR) #VAR
#define CHECKMACRO(_,VAR) warning (COMPILECHECK--#VAR=CHECKMACRO_STR ## 1(VAR))
#endif

// 5.14.3 Predefined Macros
#pragma CHECKMACRO(1, __DATABANK)
#pragma CHECKMACRO(1, __DATE__)
#pragma CHECKMACRO(1, __EXTMEM)
#pragma CHECKMACRO(1, __FILE__)
#pragma CHECKMACRO(1, __FLASHTYPE)
#pragma CHECKMACRO(1, __LINE__)
#pragma CHECKMACRO(1, __J_PART)
#pragma CHECKMACRO(1, __MPLAB_ICDX__)
#pragma CHECKMACRO(1, __MPLAB_PICKITX__)
#pragma CHECKMACRO(1, __MPLAB_REALICE__)
#pragma CHECKMACRO(1, __OPTIMIZE_SPEED__)
#pragma CHECKMACRO(1, __OPTIMIZE_SPACE__)
#pragma CHECKMACRO(1, __OPTIMIZE_NONE__)
#pragma CHECKMACRO(1, __PICCPRO__)
#pragma CHECKMACRO(1, __PICC__)
#pragma CHECKMACRO(1, __PICC18__)
#pragma CHECKMACRO(1, __RESETBITS_ADDR)
#pragma CHECKMACRO(1, __STACK)
#pragma CHECKMACRO(1, __STACK_COMPILED)
#pragma CHECKMACRO(1, __STACK_HYBRID)
#pragma CHECKMACRO(1, __STACK_REENTRANT)
#pragma CHECKMACRO(1, __STRICT)
#pragma CHECKMACRO(1, __TIME__)
#pragma CHECKMACRO(1, __TRADITIONAL18__)
#pragma CHECKMACRO(1, __XC)
#pragma CHECKMACRO(1, __XC8)
#pragma CHECKMACRO(1, __XC8_VERSION)
#pragma CHECKMACRO(1, _CHIPNAME)
#pragma CHECKMACRO(1, _18F2550)
#pragma CHECKMACRO(1, _BANKBITS_)
#pragma CHECKMACRO(1, _BANKCOUNT_)
#pragma CHECKMACRO(1, _COMMON_)
#pragma CHECKMACRO(1, _EEPROMSIZE)
#pragma CHECKMACRO(1, _ERRATA_TYPES)
#pragma CHECKMACRO(1, _FLASH_ERASE_SIZE)
#pragma CHECKMACRO(1, _FLASH_WRITE_SIZE)
#pragma CHECKMACRO(1, _GPRBITS_)
#pragma CHECKMACRO(1, _GPRCOUNT_)
#pragma CHECKMACRO(1, _HAS_OSCVAL_)
#pragma CHECKMACRO(1, _HTC_EDITION_)
#pragma CHECKMACRO(1, _HTC_VER_MAJOR_)
#pragma CHECKMACRO(1, _HTC_VER_MINOR_)
#pragma CHECKMACRO(1, _HTC_VER_PATCH_)
#pragma CHECKMACRO(1, _HTC_VER_PLVL_)
#pragma CHECKMACRO(1, _MPC_)
#pragma CHECKMACRO(1, _OMNI_CODE_)
#pragma CHECKMACRO(1, _PIC12)
#pragma CHECKMACRO(1, _PIC12E)
#pragma CHECKMACRO(1, _PIC14)
#pragma CHECKMACRO(1, _PIC14E)
#pragma CHECKMACRO(1, _PIC18)
#pragma CHECKMACRO(1, _PROGMEM_)
#pragma CHECKMACRO(1, _RAMSIZE)
#pragma CHECKMACRO(1, _ROMSIZE)
#pragma CHECKMACRO(1, ERRATA_4000_BOUNDARY)
#pragma CHECKMACRO(1, HI_TECH_C)
#pragma CHECKMACRO(1, MPLAB_ICD)

#endif /* XC_PRINT_PREDEFINED_MACROS_H_ */
