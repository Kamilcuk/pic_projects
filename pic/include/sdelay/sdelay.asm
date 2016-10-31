;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:51 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"../include/sdelay/sdelay.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	__delay_us
	global	__delay_ms

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_sdelay___delay_ms	code
__delay_ms:
	.line	45; ../include/sdelay/sdelay.c	void _delay_ms(unsigned int ms)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
_00113_DS_:
	.line	48; ../include/sdelay/sdelay.c	_delay_us(1000);
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVLW	0xe8
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	49; ../include/sdelay/sdelay.c	} while(--ms);
	MOVLW	0xff
	ADDWF	r0x00, F
	ADDWFC	r0x01, F
	MOVF	r0x00, W
	IORWF	r0x01, W
	BNZ	_00113_DS_
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_sdelay___delay_us	code
__delay_us:
	.line	31; ../include/sdelay/sdelay.c	void _delay_us(unsigned int __us) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
_00105_DS_:
	NOP
	NOP
	NOP
	NOP
	NOP
	
	.line	42; ../include/sdelay/sdelay.c	} while(--__us); // 7 instructions with branch
	MOVLW	0xff
	ADDWF	r0x00, F
	ADDWFC	r0x01, F
	MOVF	r0x00, W
	IORWF	r0x01, W
	BNZ	_00105_DS_
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  136 (0x0088) bytes ( 0.10%)
;           	   68 (0x0044) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    2 (0x0002) bytes


	end
