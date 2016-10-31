;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:46:42 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"main.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_serial_init
	global	_port_init
	global	_main
	global	_buff

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
	extern	_usart_open
	extern	_usart_busy
	extern	_usart_putc

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PRODL	equ	0xff3
PRODH	equ	0xff4


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_main_ivec_0x1_high_interrupt	code	0X000008
ivec_0x1_high_interrupt:
	GOTO	_high_interrupt

; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_main_ivec_0x2_low_interrupt	code	0X000018
ivec_0x2_low_interrupt:
	GOTO	_low_interrupt

; I code from now on!
; ; Starting pCode block
S_main__main	code
_main:
	.line	151; main.c	u8 d = 0;
	CLRF	r0x00
	.line	153; main.c	port_init();
	CALL	_port_init
	.line	154; main.c	serial_init();
	CALL	_serial_init
	.line	155; main.c	PORTA=0xff;
	MOVLW	0xff
	MOVWF	_PORTA
	.line	159; main.c	while ( usart_busy() ) {}
	CLRF	r0x01
_00133_DS_:
	CALL	_usart_busy
	MOVWF	r0x02
	MOVF	r0x02, W
	BNZ	_00133_DS_
	.line	160; main.c	usart_putc(i);
	MOVF	r0x01, W
	CALL	_usart_putc
	.line	162; main.c	if ( d++ == 1 ) { 
	MOVFF	r0x00, r0x02
	INCF	r0x00, F
	MOVF	r0x02, W
	XORLW	0x01
	BNZ	_00165_DS_
	.line	163; main.c	PORTA = PORTA ? 0 : 0xff;
	MOVF	_PORTA, W
	BZ	_00155_DS_
	CLRF	r0x02
	BRA	_00156_DS_
_00155_DS_:
	MOVLW	0xff
	MOVWF	r0x02
_00156_DS_:
	MOVFF	r0x02, _PORTA
	.line	164; main.c	d = 0;
	CLRF	r0x00
_00165_DS_:
	.line	169; main.c	for(i=0xff;i;--i)
	MOVLW	0xff
	MOVWF	r0x02
_00163_DS_:
	.line	170; main.c	for(j=0xff;j;--j)
	MOVLW	0xff
	MOVWF	r0x03
_00161_DS_:
	.line	171; main.c	for(k=1;k;--k)
	MOVLW	0x01
	MOVWF	r0x04
_00146_DS_:
	DECFSZ	r0x04, F
	BRA	_00146_DS_
	.line	170; main.c	for(j=0xff;j;--j)
	DECFSZ	r0x03, F
	BRA	_00161_DS_
	.line	169; main.c	for(i=0xff;i;--i)
	DECFSZ	r0x02, F
	BRA	_00163_DS_
	.line	158; main.c	for (i=0;;i++) {
	INCF	r0x01, F
	BRA	_00133_DS_
	RETURN	

; ; Starting pCode block
S_main__port_init	code
_port_init:
	.line	124; main.c	void port_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	126; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	127; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	128; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	131; main.c	PORTA=0x00;
	CLRF	_PORTA
	.line	132; main.c	LATA=0x00;
	CLRF	_LATA
	.line	133; main.c	TRISA=0x00;
	CLRF	_TRISA
	.line	136; main.c	PORTB=0x00;
	CLRF	_PORTB
	.line	137; main.c	LATB=0x00;
	CLRF	_LATB
	.line	138; main.c	TRISB=0x00;
	CLRF	_TRISB
	.line	141; main.c	PORTC=0x00;
	CLRF	_PORTC
	.line	142; main.c	LATC=0x00;
	CLRF	_LATC
	.line	143; main.c	TRISC=0x00;
	CLRF	_TRISC
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__serial_init	code
_serial_init:
	.line	88; main.c	void serial_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	98; main.c	8332
	MOVLW	0x20
	MOVWF	POSTDEC1
	MOVLW	0x8c
	MOVWF	POSTDEC1
	MOVLW	0x2c
	CALL	_usart_open
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	100; main.c	for(i=0xff;i;i--)
	MOVLW	0xff
	MOVWF	r0x00
_00121_DS_:
	NOP 
	.line	100; main.c	for(i=0xff;i;i--)
	DECFSZ	r0x00, F
	BRA	_00121_DS_
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__low_interrupt	code
_low_interrupt:
	.line	84; main.c	static void low_interrupt(void) __interrupt(2)
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	86; main.c	}
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	

; ; Starting pCode block
S_main__high_interrupt	code
_high_interrupt:
	.line	80; main.c	static void high_interrupt(void) __interrupt(1)
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	82; main.c	}
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	

; ; Starting pCode block
S_main____config__lines__	code
___config__lines__:
	config PLLDIV = 5 
	config CPUDIV = OSC1_PLL2 
	config USBDIV = 2 
	config FOSC = HSPLL_HS 
	config IESO = ON
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
	config WRTB = OFF
	config WRTC = OFF
	config WRTD = OFF
	config EBTR0 = OFF
	config EBTR1 = OFF
	config EBTR2 = OFF
	config EBTR3 = OFF
	config EBTRB = OFF
; ; Starting pCode block for Ival
	code
_buff:
	DB	0x20, 0x20, 0x20, 0x50, 0x49, 0x43, 0x20, 0x49, 0x4e, 0x49, 0x54, 0x49
	DB	0x41, 0x4c, 0x49, 0x5a, 0x45, 0x44, 0x20, 0x21, 0x20, 0x00, 0x00, 0x00
	DB	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	DB	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x28, 0x28, 0x60
	DB	0x27, 0x2d, 0x22, 0x60, 0x60, 0x22, 0x22, 0x2d, 0x27, 0x60, 0x29, 0x29
	DB	0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x29, 0x20, 0x20, 0x20, 0x2d
	DB	0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x20, 0x28, 0x00, 0x00, 0x00, 0x00
	DB	0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x20, 0x28, 0x6f, 0x20, 0x5f, 0x20
	DB	0x6f, 0x29, 0x20, 0x20, 0x20, 0x01, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20
	DB	0x01, 0x20, 0x20, 0x20, 0x20, 0x28, 0x20, 0x30, 0x20, 0x29, 0x20, 0x20
	DB	0x20, 0x20, 0x2f, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x5f, 0x27, 0x2d
	DB	0x2e, 0x2e, 0x5f, 0x27, 0x3d, 0x27, 0x5f, 0x2e, 0x2e, 0x2d, 0x27, 0x5f
	DB	0x00, 0x00, 0x00, 0x20, 0x2f, 0x60, 0x3b, 0x23, 0x27, 0x23, 0x27, 0x23
	DB	0x2e, 0x2d, 0x2e, 0x23, 0x27, 0x23, 0x27, 0x23, 0x3b, 0x60, 0x01, 0x00
	DB	0x20, 0x01, 0x5f, 0x29, 0x29, 0x20, 0x20, 0x20, 0x20, 0x27, 0x23, 0x27
	DB	0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x5f, 0x2f, 0x00, 0x20, 0x20, 0x20
	DB	0x23, 0x2e, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
	DB	0x20, 0x2e, 0x23, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x27, 0x23, 0x2e
	DB	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x23, 0x27
	DB	0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x27, 0x23, 0x2e, 0x20
	DB	0x20, 0x20, 0x20, 0x20, 0x2e, 0x23, 0x27, 0x20, 0x00, 0x00, 0x00, 0x00
	DB	0x20, 0x20, 0x5f, 0x01, 0x20, 0x20, 0x01, 0x27, 0x23, 0x2e, 0x20, 0x2e
	DB	0x23, 0x27, 0x2f, 0x20, 0x20, 0x2f, 0x5f, 0x00, 0x00, 0x20, 0x28, 0x28
	DB	0x28, 0x5f, 0x5f, 0x5f, 0x29, 0x20, 0x27, 0x23, 0x27, 0x20, 0x28, 0x5f
	DB	0x5f, 0x5f, 0x29, 0x29, 0x29, 0x00


; Statistics:
; code size:	  478 (0x01de) bytes ( 0.36%)
;           	  239 (0x00ef) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    5 (0x0005) bytes


	end
