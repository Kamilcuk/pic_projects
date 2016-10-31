;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:51 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"usb_ep1.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_USB_EP1_init
	global	_godpic_flush
	global	_godpic_puts
	global	_godpic_putc
	global	_USB_EP1_transmission

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1
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
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3


	idata
_buffer_fill	db	0x00


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


databank6	udata
_USB_EP1_in_buffer	res	64

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_usb_ep1__USB_EP1_transmission	code
_USB_EP1_transmission:
	.line	109; usb_ep1.c	void USB_EP1_transmission(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	114; usb_ep1.c	}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep1__godpic_putc	code
_godpic_putc:
	.line	94; usb_ep1.c	void godpic_putc(char src)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	97; usb_ep1.c	unsigned char __near *dst = bdpnt->adr;
	MOVFF	(_usb_bd + 14), r0x01
	MOVFF	(_usb_bd + 15), r0x02
	BANKSEL	_buffer_fill
	.line	99; usb_ep1.c	if ( buffer_fill == EP1_BUFFER_SIZE ) {
	MOVF	_buffer_fill, W, B
	XORLW	0x40
	BNZ	_00174_DS_
	.line	100; usb_ep1.c	godpic_flush();
	CALL	_godpic_flush
_00170_DS_:
	BANKSEL	(_usb_bd + 12)
	.line	101; usb_ep1.c	while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	BTFSC	(_usb_bd + 12), 7, B
	BRA	_00170_DS_
_00174_DS_:
	BANKSEL	_buffer_fill
	.line	105; usb_ep1.c	dst[buffer_fill] = src;
	MOVF	_buffer_fill, W, B
	ADDWF	r0x01, F
	CLRF	WREG
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x00, INDF0
	BANKSEL	_buffer_fill
	.line	106; usb_ep1.c	buffer_fill++;
	INCF	_buffer_fill, F, B
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep1__godpic_puts	code
_godpic_puts:
	.line	68; usb_ep1.c	void godpic_puts(char *src)
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
	.line	71; usb_ep1.c	unsigned char __near *dst = bdpnt->adr;
	MOVFF	(_usb_bd + 14), r0x03
	MOVFF	(_usb_bd + 15), r0x04
	.line	74; usb_ep1.c	godpic_flush();
	CALL	_godpic_flush
_00141_DS_:
	.line	76; usb_ep1.c	while( *src != '\0' ) {
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x05
	MOVF	r0x05, W
	BTFSC	STATUS, 2
	BRA	_00146_DS_
_00135_DS_:
	BANKSEL	(_usb_bd + 12)
	.line	77; usb_ep1.c	while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	BTFSC	(_usb_bd + 12), 7, B
	BRA	_00135_DS_
	.line	80; usb_ep1.c	for (i=0; i<EP1_BUFFER_SIZE; i++) {
	MOVFF	r0x03, r0x05
	MOVFF	r0x04, r0x06
	MOVFF	r0x00, r0x07
	MOVFF	r0x01, r0x08
	MOVFF	r0x02, r0x09
	CLRF	r0x0a
_00144_DS_:
	.line	81; usb_ep1.c	*dst = *src;
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, PRODL
	MOVF	r0x09, W
	CALL	__gptrget1
	MOVWF	r0x0b
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x0b, INDF0
	.line	82; usb_ep1.c	if ( *src == '\0' ) {
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, PRODL
	MOVF	r0x09, W
	CALL	__gptrget1
	MOVWF	r0x0b
	MOVF	r0x0b, W
	BZ	_00153_DS_
	.line	85; usb_ep1.c	dst++;
	INFSNZ	r0x05, F
	INCF	r0x06, F
	.line	86; usb_ep1.c	src++;
	INCF	r0x07, F
	BNC	_00164_DS_
	INFSNZ	r0x08, F
	INCF	r0x09, F
_00164_DS_:
	.line	80; usb_ep1.c	for (i=0; i<EP1_BUFFER_SIZE; i++) {
	INCF	r0x0a, F
	MOVLW	0x40
	SUBWF	r0x0a, W
	BNC	_00144_DS_
_00153_DS_:
	MOVFF	r0x05, r0x03
	MOVFF	r0x06, r0x04
	MOVFF	r0x07, r0x00
	MOVFF	r0x08, r0x01
	MOVFF	r0x09, r0x02
	.line	89; usb_ep1.c	buffer_fill = i;
	MOVFF	r0x0a, _buffer_fill
	.line	90; usb_ep1.c	godpic_flush();
	CALL	_godpic_flush
	BRA	_00141_DS_
_00146_DS_:
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
S_usb_ep1__godpic_flush	code
_godpic_flush:
	.line	56; usb_ep1.c	void godpic_flush()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	BANKSEL	_buffer_fill
	.line	59; usb_ep1.c	if ( buffer_fill != 0 ) {
	MOVF	_buffer_fill, W, B
	BZ	_00126_DS_
	BANKSEL	_buffer_fill
	.line	60; usb_ep1.c	bdpnt->cnt = buffer_fill;
	MOVF	_buffer_fill, W, B
	BANKSEL	(_usb_bd + 13)
	MOVWF	(_usb_bd + 13), B
	.line	61; usb_ep1.c	USB_BD_SET_STAT(bdpnt);
	MOVLW	0x40
	BANKSEL	(_usb_bd + 12)
	ANDWF	(_usb_bd + 12), W, B
	MOVWF	r0x00
	BTG	r0x00, 6
	MOVLW	0x88
	IORWF	r0x00, F
	MOVF	r0x00, W
	BANKSEL	(_usb_bd + 12)
	MOVWF	(_usb_bd + 12), B
_00126_DS_:
	BANKSEL	_buffer_fill
	.line	63; usb_ep1.c	buffer_fill = 0;
	CLRF	_buffer_fill, B
_00127_DS_:
	BANKSEL	(_usb_bd + 12)
	.line	65; usb_ep1.c	while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	BTFSC	(_usb_bd + 12), 7, B
	BRA	_00127_DS_
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep1__USB_EP1_init	code
_USB_EP1_init:
	.line	32; usb_ep1.c	void USB_EP1_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	36; usb_ep1.c	for (i=0; i<sizeof(USB_EP1_in_buffer); i++)
	CLRF	r0x00
_00106_DS_:
	.line	37; usb_ep1.c	((unsigned char *)USB_EP1_in_buffer)[i] = 0;
	MOVLW	LOW(_USB_EP1_in_buffer)
	MOVWF	r0x01
	MOVLW	HIGH(_USB_EP1_in_buffer)
	MOVWF	r0x02
	MOVF	r0x00, W
	ADDWF	r0x01, F
	CLRF	WREG
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	36; usb_ep1.c	for (i=0; i<sizeof(USB_EP1_in_buffer); i++)
	INCF	r0x00, F
	MOVLW	0x40
	SUBWF	r0x00, W
	BNC	_00106_DS_
	.line	40; usb_ep1.c	bdpnt->adr = USB_EP1_in_buffer[0];
	MOVLW	LOW(_USB_EP1_in_buffer)
	BANKSEL	(_usb_bd + 14)
	MOVWF	(_usb_bd + 14), B
	MOVLW	HIGH(_USB_EP1_in_buffer)
	BANKSEL	(_usb_bd + 15)
	MOVWF	(_usb_bd + 15), B
	.line	41; usb_ep1.c	bdpnt->cnt = EP1_BUFFER_SIZE;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 13)
	MOVWF	(_usb_bd + 13), B
	.line	42; usb_ep1.c	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	MOVLW	0xc8
	BANKSEL	(_usb_bd + 12)
	MOVWF	(_usb_bd + 12), B
	.line	51; usb_ep1.c	UEP1 = UEP_EPHSHK | UEP_EPINEN;
	MOVLW	0x12
	MOVWF	_UEP1
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  568 (0x0238) bytes ( 0.43%)
;           	  284 (0x011c) words
; udata size:	   64 (0x0040) bytes ( 3.57%)
; access size:	   12 (0x000c) bytes


	end
