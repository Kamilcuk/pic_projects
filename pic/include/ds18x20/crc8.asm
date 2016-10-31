;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:51 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"../include/ds18x20/crc8.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_crc8

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1
r0x0a	res	1
r0x0b	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_crc8__crc8	code
_crc8:
	.line	8; ../include/ds18x20/crc8.c	uint8_t crc8(uint8_t *data, uint16_t number_of_bytes_in_data )
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x0a, POSTDEC1
	MOVFF	r0x0b, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	MOVLW	0x06
	MOVFF	PLUSW2, r0x04
	.line	16; ../include/ds18x20/crc8.c	crc = CRC8INIT;
	CLRF	r0x05
	.line	18; ../include/ds18x20/crc8.c	for (loop_count = 0; loop_count != number_of_bytes_in_data; loop_count++)
	CLRF	r0x06
	CLRF	r0x07
_00114_DS_:
	MOVF	r0x06, W
	XORWF	r0x03, W
	BNZ	_00139_DS_
	MOVF	r0x07, W
	XORWF	r0x04, W
	BZ	_00112_DS_
_00139_DS_:
	.line	20; ../include/ds18x20/crc8.c	b = data[loop_count];
	MOVF	r0x06, W
	ADDWF	r0x00, W
	MOVWF	r0x08
	MOVF	r0x07, W
	ADDWFC	r0x01, W
	MOVWF	r0x09
	CLRF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x0a
	MOVFF	r0x08, FSR0L
	MOVFF	r0x09, PRODL
	MOVF	r0x0a, W
	CALL	__gptrget1
	MOVWF	r0x08
	.line	23; ../include/ds18x20/crc8.c	do {
	MOVLW	0x08
	MOVWF	r0x09
_00109_DS_:
	.line	24; ../include/ds18x20/crc8.c	feedback_bit = (crc ^ b) & 0x01;
	MOVF	r0x08, W
	XORWF	r0x05, W
	MOVWF	r0x0a
	MOVLW	0x01
	ANDWF	r0x0a, F
	.line	26; ../include/ds18x20/crc8.c	if ( feedback_bit == 0x01 ) {
	MOVF	r0x0a, W
	XORLW	0x01
	BNZ	_00106_DS_
	.line	27; ../include/ds18x20/crc8.c	crc = crc ^ CRC8POLY;
	MOVLW	0x18
	XORWF	r0x05, F
_00106_DS_:
	.line	29; ../include/ds18x20/crc8.c	crc = (crc >> 1) & 0x7F;
	RRNCF	r0x05, W
	ANDLW	0x7f
	MOVWF	r0x0b
	MOVLW	0x7f
	ANDWF	r0x0b, W
	MOVWF	r0x05
	.line	30; ../include/ds18x20/crc8.c	if ( feedback_bit == 0x01 ) {
	MOVF	r0x0a, W
	XORLW	0x01
	BNZ	_00108_DS_
	.line	31; ../include/ds18x20/crc8.c	crc = crc | 0x80;
	BSF	r0x05, 7
_00108_DS_:
	.line	34; ../include/ds18x20/crc8.c	b = b >> 1;
	BCF	STATUS, 0
	RRCF	r0x08, F
	.line	35; ../include/ds18x20/crc8.c	bit_counter--;
	DECFSZ	r0x09, F
	BRA	_00109_DS_
	.line	18; ../include/ds18x20/crc8.c	for (loop_count = 0; loop_count != number_of_bytes_in_data; loop_count++)
	INFSNZ	r0x06, F
	INCF	r0x07, F
	BRA	_00114_DS_
_00112_DS_:
	.line	40; ../include/ds18x20/crc8.c	return crc;
	MOVF	r0x05, W
	MOVFF	PREINC1, r0x0b
	MOVFF	PREINC1, r0x0a
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  252 (0x00fc) bytes ( 0.19%)
;           	  126 (0x007e) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	   12 (0x000c) bytes


	end
