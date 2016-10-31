;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:53 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"usb_ep2.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_USB_EP2_init
	global	_USB_EP2_set
	global	_USB_EP2_transmission

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	_UFRMLbits
	extern	_UFRMHbits
	extern	_UIRbits
	extern	_UIEbits
	extern	_UEIRbits
	extern	_UEIEbits
	extern	_USTATbits
	extern	_UCONbits
	extern	_UADDRbits
	extern	_UCFGbits
	extern	_UEP0bits
	extern	_UEP1bits
	extern	_UEP2bits
	extern	_UEP3bits
	extern	_UEP4bits
	extern	_UEP5bits
	extern	_UEP6bits
	extern	_UEP7bits
	extern	_UEP8bits
	extern	_UEP9bits
	extern	_UEP10bits
	extern	_UEP11bits
	extern	_UEP12bits
	extern	_UEP13bits
	extern	_UEP14bits
	extern	_UEP15bits
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTEbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_OSCTUNEbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_CCP1ASbits
	extern	_ECCP1ASbits
	extern	_CCP1DELbits
	extern	_ECCP1DELbits
	extern	_BAUDCONbits
	extern	_BAUDCTLbits
	extern	_CCP2CONbits
	extern	_CCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSPCON2bits
	extern	_SSPCON1bits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_HLVDCONbits
	extern	_LVDCONbits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_usb_ustat
	extern	_usb_bd
	extern	_UFRM
	extern	_UFRML
	extern	_UFRMH
	extern	_UIR
	extern	_UIE
	extern	_UEIR
	extern	_UEIE
	extern	_USTAT
	extern	_UCON
	extern	_UADDR
	extern	_UCFG
	extern	_UEP0
	extern	_UEP1
	extern	_UEP2
	extern	_UEP3
	extern	_UEP4
	extern	_UEP5
	extern	_UEP6
	extern	_UEP7
	extern	_UEP8
	extern	_UEP9
	extern	_UEP10
	extern	_UEP11
	extern	_UEP12
	extern	_UEP13
	extern	_UEP14
	extern	_UEP15
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_OSCTUNE
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_EECON1
	extern	_EECON2
	extern	_EEDATA
	extern	_EEADR
	extern	_RCSTA
	extern	_TXSTA
	extern	_TXREG
	extern	_RCREG
	extern	_SPBRG
	extern	_SPBRGH
	extern	_T3CON
	extern	_TMR3
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_CCP1AS
	extern	_ECCP1AS
	extern	_CCP1DEL
	extern	_ECCP1DEL
	extern	_BAUDCON
	extern	_BAUDCTL
	extern	_CCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSPCON2
	extern	_SSPCON1
	extern	_SSPSTAT
	extern	_SSPADD
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_LVDCON
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC0	equ	0xfee
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb


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


usb_buff	udata
_USB_EP2_in_buffer	res	64

udata_usb_ep2_0	udata
_to_send	res	3

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_usb_ep2__USB_EP2_transmission	code
_USB_EP2_transmission:
	.line	122; usb_ep2.c	void USB_EP2_transmission(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	_to_send
	.line	126; usb_ep2.c	if (to_send.len) {
	MOVF	_to_send, W, B
	BZ	_00160_DS_
	.line	128; usb_ep2.c	fill_and_set_send(bdpnt);
	MOVLW	HIGH(_usb_bd + 20)
	MOVWF	POSTDEC1
	MOVLW	LOW(_usb_bd + 20)
	MOVWF	POSTDEC1
	CALL	_fill_and_set_send
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00160_DS_:
	.line	135; usb_ep2.c	return;
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep2__USB_EP2_set	code
_USB_EP2_set:
	.line	87; usb_ep2.c	void USB_EP2_set(const void __near *src, unsigned char len)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	BANKSEL	(_usb_bd + 20)
	.line	91; usb_ep2.c	if ( bdpnt->statbits.UOWN ) {
	BTFSS	(_usb_bd + 20), 7, B
	BRA	_00151_DS_
	.line	100; usb_ep2.c	return;
	BRA	_00153_DS_
_00151_DS_:
	.line	104; usb_ep2.c	to_send.len = len;
	MOVF	r0x02, W
	BANKSEL	_to_send
	MOVWF	_to_send, B
	.line	105; usb_ep2.c	to_send.src = src;
	MOVF	r0x00, W
	BANKSEL	(_to_send + 1)
	MOVWF	(_to_send + 1), B
	MOVF	r0x01, W
	BANKSEL	(_to_send + 2)
	MOVWF	(_to_send + 2), B
	.line	108; usb_ep2.c	fill_and_set_send(bdpnt);
	MOVLW	HIGH(_usb_bd + 20)
	MOVWF	POSTDEC1
	MOVLW	LOW(_usb_bd + 20)
	MOVWF	POSTDEC1
	CALL	_fill_and_set_send
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00153_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep2__fill_and_set_send	code
_fill_and_set_send:
	.line	58; usb_ep2.c	static void fill_and_set_send(usb_bd_t __near * const bdpnt) 
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
	.line	60; usb_ep2.c	unsigned char __near * const dst = bdpnt->adr;
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	POSTINC0, r0x02
	MOVFF	INDF0, r0x03
	.line	61; usb_ep2.c	const unsigned char __near * const src = to_send.src;
	MOVFF	(_to_send + 1), r0x04
	MOVFF	(_to_send + 2), r0x05
	.line	65; usb_ep2.c	if ( to_send.len < EP2_BUFFER_SIZE ) {
	MOVFF	_to_send, r0x06
	MOVLW	0x40
	SUBWF	r0x06, W
	BC	_00123_DS_
	.line	66; usb_ep2.c	len = to_send.len;
	MOVFF	r0x06, r0x07
	BANKSEL	_to_send
	.line	67; usb_ep2.c	to_send.len = 0x00;
	CLRF	_to_send, B
	BRA	_00124_DS_
_00123_DS_:
	.line	70; usb_ep2.c	len = EP2_BUFFER_SIZE;
	MOVLW	0x40
	MOVWF	r0x07
	.line	71; usb_ep2.c	to_send.len -= EP2_BUFFER_SIZE;
	MOVLW	0xc0
	ADDWF	r0x06, F
	MOVF	r0x06, W
	BANKSEL	_to_send
	MOVWF	_to_send, B
_00124_DS_:
	.line	74; usb_ep2.c	to_send.src += len;
	MOVF	r0x07, W
	BANKSEL	(_to_send + 1)
	ADDWF	(_to_send + 1), W, B
	MOVWF	r0x06
	CLRF	WREG
	BANKSEL	(_to_send + 2)
	ADDWFC	(_to_send + 2), W, B
	MOVWF	r0x08
	MOVF	r0x06, W
	BANKSEL	(_to_send + 1)
	MOVWF	(_to_send + 1), B
	MOVF	r0x08, W
	BANKSEL	(_to_send + 2)
	MOVWF	(_to_send + 2), B
	.line	77; usb_ep2.c	for (i=0; i<len; i++) {
	CLRF	r0x06
_00130_DS_:
	MOVF	r0x07, W
	SUBWF	r0x06, W
	BC	_00125_DS_
	.line	78; usb_ep2.c	dst[i] = src[i];
	MOVF	r0x06, W
	ADDWF	r0x02, W
	MOVWF	r0x08
	CLRF	WREG
	ADDWFC	r0x03, W
	MOVWF	r0x09
	MOVF	r0x06, W
	ADDWF	r0x04, W
	MOVWF	r0x0a
	CLRF	WREG
	ADDWFC	r0x05, W
	MOVWF	r0x0b
	MOVFF	r0x0a, FSR0L
	MOVFF	r0x0b, FSR0H
	MOVFF	INDF0, r0x0a
	MOVFF	r0x08, FSR0L
	MOVFF	r0x09, FSR0H
	MOVFF	r0x0a, INDF0
	.line	77; usb_ep2.c	for (i=0; i<len; i++) {
	INCF	r0x06, F
	BRA	_00130_DS_
_00125_DS_:
	.line	82; usb_ep2.c	bdpnt->cnt = len;
	MOVF	r0x00, W
	ADDLW	0x01
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	r0x07, INDF0
	.line	84; usb_ep2.c	USB_BD_SET_STAT(bdpnt);
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x02
	MOVLW	0x40
	ANDWF	r0x02, F
	BTG	r0x02, 6
	MOVLW	0x88
	IORWF	r0x02, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	r0x02, INDF0
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

; ; Starting pCode block
S_usb_ep2__USB_EP2_init	code
_USB_EP2_init:
	.line	36; usb_ep2.c	void USB_EP2_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	40; usb_ep2.c	for (i=0; i<sizeof(USB_EP2_in_buffer); i++)
	CLRF	r0x00
_00106_DS_:
	.line	41; usb_ep2.c	((unsigned char *)USB_EP2_in_buffer)[i] = 0;
	MOVLW	LOW(_USB_EP2_in_buffer)
	MOVWF	r0x01
	MOVLW	HIGH(_USB_EP2_in_buffer)
	MOVWF	r0x02
	MOVF	r0x00, W
	ADDWF	r0x01, F
	CLRF	WREG
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	40; usb_ep2.c	for (i=0; i<sizeof(USB_EP2_in_buffer); i++)
	INCF	r0x00, F
	MOVLW	0x40
	SUBWF	r0x00, W
	BNC	_00106_DS_
	.line	44; usb_ep2.c	bdpnt->adr = USB_EP2_in_buffer[0];
	MOVLW	LOW(_USB_EP2_in_buffer)
	BANKSEL	(_usb_bd + 22)
	MOVWF	(_usb_bd + 22), B
	MOVLW	HIGH(_USB_EP2_in_buffer)
	BANKSEL	(_usb_bd + 23)
	MOVWF	(_usb_bd + 23), B
	BANKSEL	(_usb_bd + 21)
	.line	45; usb_ep2.c	bdpnt->cnt = 0;
	CLRF	(_usb_bd + 21), B
	.line	46; usb_ep2.c	bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA0 | BD_STAT_DTSEN;
	MOVLW	0x08
	BANKSEL	(_usb_bd + 20)
	MOVWF	(_usb_bd + 20), B
	.line	55; usb_ep2.c	UEP2 = UEP_EPHSHK | UEP_EPINEN;
	MOVLW	0x12
	MOVWF	_UEP2
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  574 (0x023e) bytes ( 0.44%)
;           	  287 (0x011f) words
; udata size:	   67 (0x0043) bytes ( 3.74%)
; access size:	   12 (0x000c) bytes


	end
