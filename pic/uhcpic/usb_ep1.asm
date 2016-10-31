;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:52 2015
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
	global	_USB_EP1_transmission

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
	extern	_cake_eat_basket

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


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1


usb_buff	udata
_USB_EP1_out_buffer	res	64

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_usb_ep1__USB_EP1_transmission	code
_USB_EP1_transmission:
	.line	56; usb_ep1.c	void USB_EP1_transmission(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	BANKSEL	(_usb_bd + 9)
	.line	60; usb_ep1.c	cake_eat_basket(bdpnt->adr, bdpnt->cnt);
	MOVF	(_usb_bd + 9), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_usb_bd + 11)
	MOVF	(_usb_bd + 11), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_usb_bd + 10)
	MOVF	(_usb_bd + 10), W, B
	MOVWF	POSTDEC1
	CALL	_cake_eat_basket
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	62; usb_ep1.c	bdpnt->cnt = EP1_BUFFER_SIZE;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 9)
	MOVWF	(_usb_bd + 9), B
	.line	64; usb_ep1.c	USB_BD_SET_STAT(bdpnt);
	MOVLW	0x40
	BANKSEL	(_usb_bd + 8)
	ANDWF	(_usb_bd + 8), W, B
	MOVWF	r0x00
	BTG	r0x00, 6
	MOVLW	0x88
	IORWF	r0x00, F
	MOVF	r0x00, W
	BANKSEL	(_usb_bd + 8)
	MOVWF	(_usb_bd + 8), B
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb_ep1__USB_EP1_init	code
_USB_EP1_init:
	.line	34; usb_ep1.c	void USB_EP1_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	38; usb_ep1.c	for (i=0; i<sizeof(USB_EP1_out_buffer); i++)
	CLRF	r0x00
_00106_DS_:
	.line	39; usb_ep1.c	((unsigned char *)USB_EP1_out_buffer)[i] = 0;
	MOVLW	LOW(_USB_EP1_out_buffer)
	MOVWF	r0x01
	MOVLW	HIGH(_USB_EP1_out_buffer)
	MOVWF	r0x02
	MOVF	r0x00, W
	ADDWF	r0x01, F
	CLRF	WREG
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	38; usb_ep1.c	for (i=0; i<sizeof(USB_EP1_out_buffer); i++)
	INCF	r0x00, F
	MOVLW	0x40
	SUBWF	r0x00, W
	BNC	_00106_DS_
	.line	42; usb_ep1.c	bdpnt->cnt = EP1_BUFFER_SIZE;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 9)
	MOVWF	(_usb_bd + 9), B
	.line	43; usb_ep1.c	bdpnt->adr = USB_EP1_out_buffer[0];
	MOVLW	LOW(_USB_EP1_out_buffer)
	BANKSEL	(_usb_bd + 10)
	MOVWF	(_usb_bd + 10), B
	MOVLW	HIGH(_USB_EP1_out_buffer)
	BANKSEL	(_usb_bd + 11)
	MOVWF	(_usb_bd + 11), B
	.line	44; usb_ep1.c	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN;
	MOVLW	0x88
	BANKSEL	(_usb_bd + 8)
	MOVWF	(_usb_bd + 8), B
	.line	53; usb_ep1.c	UEP1 = UEP_EPHSHK | UEP_EPOUTEN;
	MOVLW	0x14
	MOVWF	_UEP1
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  178 (0x00b2) bytes ( 0.14%)
;           	   89 (0x0059) words
; udata size:	   64 (0x0040) bytes ( 3.57%)
; access size:	    3 (0x0003) bytes


	end
