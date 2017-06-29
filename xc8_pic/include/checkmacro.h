/*
 *        File: checkmacro.h
 *  Created on: 21.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef CHECKMACRO_H_
#define CHECKMACRO_H_

// CHECKMACRO_STR_NEXT is compilator dependend
// generated with: for i in $(seq 1 16); do echo "#define CHECKMACRO_STR${i}($(for j in $(seq 1 $i);do echo -ne "S${j},"; done | sed 's/,$//')) \\"; echo -e "\tCHECKMACRO_STR$((i-1))($(for j in $(seq 1 $((i-1)));do echo -ne "S${j},"; done | sed 's/,$//'))CHECKMACRO_STR_NEXT(S$i)"; done

#define CHECKMACRO_STR0(S1) \
	S1

#define CHECKMACRO_STR2(S1,S2) \
	CHECKMACRO_STR1(S1)CHECKMACRO_STR_NEXT(S2)
#define CHECKMACRO_STR3(S1,S2,S3) \
	CHECKMACRO_STR2(S1,S2)CHECKMACRO_STR_NEXT(S3)
#define CHECKMACRO_STR4(S1,S2,S3,S4) \
	CHECKMACRO_STR3(S1,S2,S3)CHECKMACRO_STR_NEXT(S4)
#define CHECKMACRO_STR5(S1,S2,S3,S4,S5) \
	CHECKMACRO_STR4(S1,S2,S3,S4)CHECKMACRO_STR_NEXT(S5)
#define CHECKMACRO_STR6(S1,S2,S3,S4,S5,S6) \
	CHECKMACRO_STR5(S1,S2,S3,S4,S5)CHECKMACRO_STR_NEXT(S6)
#define CHECKMACRO_STR7(S1,S2,S3,S4,S5,S6,S7) \
	CHECKMACRO_STR6(S1,S2,S3,S4,S5,S6)CHECKMACRO_STR_NEXT(S7)
#define CHECKMACRO_STR8(S1,S2,S3,S4,S5,S6,S7,S8) \
	CHECKMACRO_STR7(S1,S2,S3,S4,S5,S6,S7)CHECKMACRO_STR_NEXT(S8)
#define CHECKMACRO_STR9(S1,S2,S3,S4,S5,S6,S7,S8,S9) \
	CHECKMACRO_STR8(S1,S2,S3,S4,S5,S6,S7,S8)CHECKMACRO_STR_NEXT(S9)
#define CHECKMACRO_STR10(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10) \
	CHECKMACRO_STR9(S1,S2,S3,S4,S5,S6,S7,S8,S9)CHECKMACRO_STR_NEXT(S10)
#define CHECKMACRO_STR11(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11) \
	CHECKMACRO_STR10(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10)CHECKMACRO_STR_NEXT(S11)
#define CHECKMACRO_STR12(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12) \
	CHECKMACRO_STR11(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11)CHECKMACRO_STR_NEXT(S12)
#define CHECKMACRO_STR13(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13) \
	CHECKMACRO_STR12(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12)CHECKMACRO_STR_NEXT(S13)
#define CHECKMACRO_STR14(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14) \
	CHECKMACRO_STR13(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13)CHECKMACRO_STR_NEXT(S14)
#define CHECKMACRO_STR15(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15) \
	CHECKMACRO_STR14(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14)CHECKMACRO_STR_NEXT(S15)
#define CHECKMACRO_STR16(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15,S16) \
	CHECKMACRO_STR15(S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15)CHECKMACRO_STR_NEXT(S16)


#if defined( __XC8 )

#define CHECKMACRO_STR1(S1)             CHECKMACRO_STR0(S1)
#define CHECKMARO_COMMA                 -
#define CHECKMACRO_STR_NEXT__P(S1)      S1 /* this is really strange on XC8 preprocessor */
#define CHECKMACRO_STR_NEXT(S1)         CHECKMACRO_STR_NEXT__P(CHECKMARO_COMMA) ## CHECKMACRO_STR1(S1)
#define CHECKMACRO(N,VAR)               warning (COMPILECHECK--#VAR=CHECKMACRO_STR ## N(VAR))

/**
 * Usage example for __XC8 compiler:
#define VAL 123
#pragma CHECKMACRO(1, VAL)
#define VAL9 {1,2,3,4,5,6,7,8,9}
#pragma CHECKMACRO(9, VAL9)
#define VAL16 {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
#pragma CHECKMACRO(16, VAL16)
 * This will produce following warnings:
 * include/checkmacro.h:72: warning: (335) unknown pragma "COMPILECHECK--"VAL"="123""
 * include/checkmacro.h:74: warning: (335) unknown pragma "COMPILECHECK--"VAL9"="{1"-"2"-"3"-"4"-"5"-"6"-"7"-"8"-"9}""
 * include/checkmacro.h:76: warning: (335) unknown pragma "COMPILECHECK--"VAL16"="{1"-"2"-"3"-"4"-"5"-"6"-"7"-"8"-"9"-"10"-"11"-"12"-"13"-"14"-"15"-"16}""
 */

#elif defined(__GNUC__)

#define CHECKMACRO_STR1(S1)             CHECKMACRO_STR0(#S1)
#define CHECKMARO_COMMA                 ","
#define CHECKMACRO_STR_NEXT(S1)         CHECKMARO_COMMA CHECKMACRO_STR1(S1)
#define CHECKMACRO(N,VAR)               ("COMPILECHECK \""#VAR"\"=\""CHECKMACRO_STR ## N(VAR)"\"")

/**
 * Usage example for gcc compiler:
#define VAL 123
#pragma message CHECKMACRO(CHECKMACRO_STR, VAL)
 * This will produce following warnings:
checkmacro.h:85:9: note: #pragma message: COMPILECHECK--VAL=123
#pragma message CHECKMACRO(CHECKMACRO_STR, VAL)
 */

#else // defined( __XC8 )
#define CHECKMACRO(STRINGIFY, VAR)
#endif // defined( __XC8 )

#endif /* CHECKMACRO_H_ */
