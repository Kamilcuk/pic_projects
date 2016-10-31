;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:55:22 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
; * MPLAB/MPASM/MPASMWIN/MPLINK compatibility mode enabled
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"main.c"
	list	p=18f2550
	radix	dec
	include <p18f2550.inc>
	CONFIG	PLLDIV=4
	CONFIG	CPUDIV=OSC4_PLL6
	CONFIG	USBDIV=1
	CONFIG	FOSC=INTOSCIO_EC
	CONFIG	IESO=OFF,PWRT=OFF,BOR=OFF,BORV=2,VREGEN=OFF
	CONFIG	WDT=OFF,WDTPS=32768,MCLRE=ON
	CONFIG	LPT1OSC=OFF
	CONFIG	PBADEN=OFF,CCP2MX=OFF,STVREN=ON,LVP=OFF,XINST=OFF,DEBUG=OFF
	CONFIG	CP0=OFF,CP1=OFF,CP2=OFF,CP3=OFF,CPB=OFF,CPD=OFF,WRT0=OFF,WRT1=OFF,WRT2=OFF,WRT3=OFF,WRTB=OFF,WRTC=OFF,WRTD=OFF,EBTR0=OFF,EBTR1=OFF,EBTR2=OFF,EBTR3=OFF,EBTRB=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_sec
	global	_min
	global	_hour
	global	_init
	global	_RTCinit
	global	_info
	global	_main

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

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
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
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1

udata_main_0	udata
_min	res	4

udata_main_1	udata
_hour	res	4

udata_main_2	udata
_sec	res	4

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block
S_main__RTCisr	code
_RTCisr:
;	.line	92; main.c	static void RTCisr(void) __interrupt
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1, ACCESS
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
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
;	.line	94; main.c	if ( PORTAbits.RA6 ) {
	BTFSS	_PORTAbits, 6, ACCESS
	BRA	_00124_DS_
_00120_DS_:
;	.line	96; main.c	if ( PORTCbits.RC4 ) {
	BTFSS	_PORTCbits, 4, ACCESS
	BRA	_00118_DS_
	BANKSEL	_min
;	.line	97; main.c	min++;
	INCF	_min, F, BANKED
	BNC	_00166_DS_
	BANKSEL	(_min + 1)
	INCF	(_min + 1), F, BANKED
	BNC	_00166_DS_
	BANKSEL	(_min + 2)
	INCFSZ	(_min + 2), F, BANKED
	BRA	_10222_DS_
	BANKSEL	(_min + 3)
	INCF	(_min + 3), F, BANKED
_10222_DS_:
_00166_DS_:
;	.line	98; main.c	if ( min >= 60 )
	MOVLW	0x00
	BANKSEL	(_min + 3)
	SUBWF	(_min + 3), W, BANKED
	BNZ	_00167_DS_
	MOVLW	0x00
	BANKSEL	(_min + 2)
	SUBWF	(_min + 2), W, BANKED
	BNZ	_00167_DS_
	MOVLW	0x00
	BANKSEL	(_min + 1)
	SUBWF	(_min + 1), W, BANKED
	BNZ	_00167_DS_
	MOVLW	0x3c
	BANKSEL	_min
	SUBWF	_min, W, BANKED
_00167_DS_:
	BNC	_00107_DS_
	BANKSEL	_min
;	.line	99; main.c	min = 0;
	CLRF	_min, BANKED
	BANKSEL	(_min + 1)
	CLRF	(_min + 1), BANKED
	BANKSEL	(_min + 2)
	CLRF	(_min + 2), BANKED
	BANKSEL	(_min + 3)
	CLRF	(_min + 3), BANKED
_00107_DS_:
;	.line	100; main.c	while ( PORTCbits.RC4 ) {}
	BTFSS	_PORTCbits, 4, ACCESS
	BRA	_00119_DS_
	BRA	_00107_DS_
_00118_DS_:
;	.line	101; main.c	} else if ( PORTCbits.RC5 ) {
	BTFSS	_PORTCbits, 5, ACCESS
	BRA	_00119_DS_
	BANKSEL	_hour
;	.line	102; main.c	hour++;
	INCF	_hour, F, BANKED
	BNC	_00168_DS_
	BANKSEL	(_hour + 1)
	INCF	(_hour + 1), F, BANKED
	BNC	_00168_DS_
	BANKSEL	(_hour + 2)
	INCFSZ	(_hour + 2), F, BANKED
	BRA	_20223_DS_
	BANKSEL	(_hour + 3)
	INCF	(_hour + 3), F, BANKED
_20223_DS_:
_00168_DS_:
;	.line	103; main.c	if ( hour >= 24 )
	MOVLW	0x00
	BANKSEL	(_hour + 3)
	SUBWF	(_hour + 3), W, BANKED
	BNZ	_00169_DS_
	MOVLW	0x00
	BANKSEL	(_hour + 2)
	SUBWF	(_hour + 2), W, BANKED
	BNZ	_00169_DS_
	MOVLW	0x00
	BANKSEL	(_hour + 1)
	SUBWF	(_hour + 1), W, BANKED
	BNZ	_00169_DS_
	MOVLW	0x18
	BANKSEL	_hour
	SUBWF	_hour, W, BANKED
_00169_DS_:
	BNC	_00112_DS_
	BANKSEL	_hour
;	.line	104; main.c	hour = 0;
	CLRF	_hour, BANKED
	BANKSEL	(_hour + 1)
	CLRF	(_hour + 1), BANKED
	BANKSEL	(_hour + 2)
	CLRF	(_hour + 2), BANKED
	BANKSEL	(_hour + 3)
	CLRF	(_hour + 3), BANKED
_00112_DS_:
;	.line	105; main.c	while ( PORTCbits.RC5 ) {}
	BTFSC	_PORTCbits, 5, ACCESS
	BRA	_00112_DS_
_00119_DS_:
	BANKSEL	_sec
;	.line	107; main.c	PORTA = sec;
	MOVF	_sec, W, BANKED
	MOVWF	_PORTA, ACCESS
;	.line	108; main.c	PORTB = min | ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
	MOVLW	0x04
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	SWAPF	r0x00, W, ACCESS
	ANDLW	0xf0
	MOVWF	r0x01, ACCESS
	MOVFF	r0x01, r0x00
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	BANKSEL	_min
	MOVF	_min, W, BANKED
	IORWF	r0x00, F, ACCESS
	BANKSEL	(_min + 1)
	MOVF	(_min + 1), W, BANKED
	IORWF	r0x02, F, ACCESS
	BANKSEL	(_min + 2)
	MOVF	(_min + 2), W, BANKED
	IORWF	r0x03, F, ACCESS
	BANKSEL	(_min + 3)
	MOVF	(_min + 3), W, BANKED
	IORWF	r0x04, F, ACCESS
	MOVLW	0x02
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x01, ACCESS
	CLRF	r0x05, ACCESS
	CLRF	r0x06, ACCESS
	CLRF	r0x07, ACCESS
	RRNCF	r0x01, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xc0
	MOVWF	r0x05, ACCESS
	MOVFF	r0x05, r0x01
	CLRF	r0x06, ACCESS
	CLRF	r0x07, ACCESS
	CLRF	r0x08, ACCESS
	MOVF	r0x01, W, ACCESS
	IORWF	r0x00, F, ACCESS
	MOVF	r0x06, W, ACCESS
	IORWF	r0x02, F, ACCESS
	MOVF	r0x07, W, ACCESS
	IORWF	r0x03, F, ACCESS
	MOVF	r0x08, W, ACCESS
	IORWF	r0x04, F, ACCESS
	MOVF	r0x00, W, ACCESS
	MOVWF	_PORTB, ACCESS
;	.line	109; main.c	PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
	MOVLW	0x01
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	RLNCF	r0x00, W, ACCESS
	RLNCF	WREG, W, ACCESS
	ANDLW	0xfc
	MOVWF	r0x01, ACCESS
	MOVLW	0x18
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	SWAPF	r0x00, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xf8
	MOVWF	r0x02, ACCESS
	MOVF	r0x02, W, ACCESS
	IORWF	r0x01, W, ACCESS
	MOVWF	_PORTC, ACCESS
;	.line	110; main.c	} while ( PORTAbits.RA6 );
	BTFSC	_PORTAbits, 6, ACCESS
	BRA	_00120_DS_
_00124_DS_:
	BANKSEL	_sec
;	.line	113; main.c	sec++;
	INCF	_sec, F, BANKED
	BNC	_00177_DS_
	BANKSEL	(_sec + 1)
	INCF	(_sec + 1), F, BANKED
	BNC	_00177_DS_
	BANKSEL	(_sec + 2)
	INCFSZ	(_sec + 2), F, BANKED
	BRA	_30224_DS_
	BANKSEL	(_sec + 3)
	INCF	(_sec + 3), F, BANKED
_30224_DS_:
_00177_DS_:
;	.line	114; main.c	if ( sec >= 60 ) {
	MOVLW	0x00
	BANKSEL	(_sec + 3)
	SUBWF	(_sec + 3), W, BANKED
	BNZ	_00178_DS_
	MOVLW	0x00
	BANKSEL	(_sec + 2)
	SUBWF	(_sec + 2), W, BANKED
	BNZ	_00178_DS_
	MOVLW	0x00
	BANKSEL	(_sec + 1)
	SUBWF	(_sec + 1), W, BANKED
	BNZ	_00178_DS_
	MOVLW	0x3c
	BANKSEL	_sec
	SUBWF	_sec, W, BANKED
_00178_DS_:
	BTFSS	STATUS, 0, ACCESS
	BRA	_00130_DS_
	BANKSEL	_sec
;	.line	115; main.c	sec = 0;
	CLRF	_sec, BANKED
	BANKSEL	(_sec + 1)
	CLRF	(_sec + 1), BANKED
	BANKSEL	(_sec + 2)
	CLRF	(_sec + 2), BANKED
	BANKSEL	(_sec + 3)
	CLRF	(_sec + 3), BANKED
	BANKSEL	_min
;	.line	116; main.c	min++;
	INCF	_min, F, BANKED
	BNC	_00179_DS_
	BANKSEL	(_min + 1)
	INCF	(_min + 1), F, BANKED
	BNC	_00179_DS_
	BANKSEL	(_min + 2)
	INCFSZ	(_min + 2), F, BANKED
	BRA	_40225_DS_
	BANKSEL	(_min + 3)
	INCF	(_min + 3), F, BANKED
_40225_DS_:
_00179_DS_:
;	.line	117; main.c	if ( min >= 60 ) {
	MOVLW	0x00
	BANKSEL	(_min + 3)
	SUBWF	(_min + 3), W, BANKED
	BNZ	_00180_DS_
	MOVLW	0x00
	BANKSEL	(_min + 2)
	SUBWF	(_min + 2), W, BANKED
	BNZ	_00180_DS_
	MOVLW	0x00
	BANKSEL	(_min + 1)
	SUBWF	(_min + 1), W, BANKED
	BNZ	_00180_DS_
	MOVLW	0x3c
	BANKSEL	_min
	SUBWF	_min, W, BANKED
_00180_DS_:
	BTFSS	STATUS, 0, ACCESS
	BRA	_00128_DS_
	BANKSEL	_min
;	.line	118; main.c	min = 0;
	CLRF	_min, BANKED
	BANKSEL	(_min + 1)
	CLRF	(_min + 1), BANKED
	BANKSEL	(_min + 2)
	CLRF	(_min + 2), BANKED
	BANKSEL	(_min + 3)
	CLRF	(_min + 3), BANKED
	BANKSEL	_hour
;	.line	119; main.c	hour++;
	INCF	_hour, F, BANKED
	BNC	_00181_DS_
	BANKSEL	(_hour + 1)
	INCF	(_hour + 1), F, BANKED
	BNC	_00181_DS_
	BANKSEL	(_hour + 2)
	INCFSZ	(_hour + 2), F, BANKED
	BRA	_50226_DS_
	BANKSEL	(_hour + 3)
	INCF	(_hour + 3), F, BANKED
_50226_DS_:
_00181_DS_:
;	.line	120; main.c	if ( hour >= 24 ) {
	MOVLW	0x00
	BANKSEL	(_hour + 3)
	SUBWF	(_hour + 3), W, BANKED
	BNZ	_00182_DS_
	MOVLW	0x00
	BANKSEL	(_hour + 2)
	SUBWF	(_hour + 2), W, BANKED
	BNZ	_00182_DS_
	MOVLW	0x00
	BANKSEL	(_hour + 1)
	SUBWF	(_hour + 1), W, BANKED
	BNZ	_00182_DS_
	MOVLW	0x18
	BANKSEL	_hour
	SUBWF	_hour, W, BANKED
_00182_DS_:
	BNC	_00126_DS_
	BANKSEL	_hour
;	.line	121; main.c	hour = 0;
	CLRF	_hour, BANKED
	BANKSEL	(_hour + 1)
	CLRF	(_hour + 1), BANKED
	BANKSEL	(_hour + 2)
	CLRF	(_hour + 2), BANKED
	BANKSEL	(_hour + 3)
	CLRF	(_hour + 3), BANKED
_00126_DS_:
;	.line	123; main.c	PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
	MOVLW	0x01
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	RLNCF	r0x00, W, ACCESS
	RLNCF	WREG, W, ACCESS
	ANDLW	0xfc
	MOVWF	r0x01, ACCESS
	MOVLW	0x18
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	SWAPF	r0x00, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xf8
	MOVWF	r0x02, ACCESS
	MOVF	r0x02, W, ACCESS
	IORWF	r0x01, W, ACCESS
	MOVWF	_PORTC, ACCESS
;	.line	124; main.c	PORTB = ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
	MOVLW	0x04
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	SWAPF	r0x00, W, ACCESS
	ANDLW	0xf0
	MOVWF	r0x01, ACCESS
	MOVLW	0x02
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	RRNCF	r0x00, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xc0
	MOVWF	r0x02, ACCESS
	MOVF	r0x02, W, ACCESS
	IORWF	r0x01, W, ACCESS
	MOVWF	_PORTB, ACCESS
_00128_DS_:
;	.line	132; main.c	PORTB = min | ( PORTB&0b11000000 );
	MOVLW	0xc0
	ANDWF	_PORTB, W, ACCESS
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	BANKSEL	_min
	MOVF	_min, W, BANKED
	IORWF	r0x00, F, ACCESS
	BANKSEL	(_min + 1)
	MOVF	(_min + 1), W, BANKED
	IORWF	r0x01, F, ACCESS
	BANKSEL	(_min + 2)
	MOVF	(_min + 2), W, BANKED
	IORWF	r0x02, F, ACCESS
	BANKSEL	(_min + 3)
	MOVF	(_min + 3), W, BANKED
	IORWF	r0x03, F, ACCESS
	MOVF	r0x00, W, ACCESS
	MOVWF	_PORTB, ACCESS
_00130_DS_:
	BANKSEL	_sec
;	.line	134; main.c	PORTA = sec;
	MOVF	_sec, W, BANKED
	MOVWF	_PORTA, ACCESS
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
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W, ACCESS
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	

; ; Starting pCode block
S_main__low_interrupt	code	0X000018
_low_interrupt:
	BSF TMR1H, 7 ; Preload for 1 sec overflow
	BCF PIR1, TMR1IF ; Clear interrupt flag
	GOTO _RTCisr
; I code from now on!
; ; Starting pCode block
S_main__main	code
_main:
;	.line	275; main.c	OSCTUNEbits.INTSRC = 0;
	BCF	_OSCTUNEbits, 7, ACCESS
;	.line	276; main.c	OSCTUNEbits.TUN = 0b10000;
	MOVF	_OSCTUNEbits, W, ACCESS
	ANDLW	0xe0
	IORLW	0x10
	MOVWF	_OSCTUNEbits, ACCESS
;	.line	278; main.c	init();
	CALL	_init
;	.line	280; main.c	RTCinit();
	CALL	_RTCinit
;	.line	282; main.c	OSCCONbits.SCS1 = 0; /* SEC_RUN , cpu clock from timer1 oscilator :D*/
	BCF	_OSCCONbits, 1, ACCESS
;	.line	283; main.c	OSCCONbits.SCS0 = 1;
	BSF	_OSCCONbits, 0, ACCESS
;	.line	284; main.c	OSCCONbits.IDLEN = 1; /* SEC_IDLE when sleep */
	BSF	_OSCCONbits, 7, ACCESS
;	.line	286; main.c	info();
	CALL	_info
;	.line	288; main.c	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	BSF	_RCONbits, 7, ACCESS
;	.line	289; main.c	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	BSF	_INTCONbits, 7, ACCESS
;	.line	290; main.c	INTCONbits.GIEL = 1; /* Enables all low priority interrupts */
	BSF	_INTCONbits, 6, ACCESS
_00223_DS_:
	sleep 
	BRA	_00223_DS_
	RETURN	

; ; Starting pCode block
S_main__info	code
_info:
;	.line	252; main.c	void info()
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
;	.line	255; main.c	PORTBbits.RB0 = 1;
	BSF	_PORTBbits, 0, ACCESS
;	.line	256; main.c	PORTBbits.RB1 = 0;
	BCF	_PORTBbits, 1, ACCESS
;	.line	257; main.c	PORTBbits.RB2 = T1CONbits.T1RUN; /* should to be set ! */
	CLRF	r0x00, ACCESS
	BTFSC	_T1CONbits, 6, ACCESS
	INCF	r0x00, F, ACCESS
	MOVF	r0x00, W, ACCESS
	ANDLW	0x01
	RLNCF	WREG, W, ACCESS
	RLNCF	WREG, W, ACCESS
	MOVWF	PRODH, ACCESS
	MOVF	_PORTBbits, W, ACCESS
	ANDLW	0xfb
	IORWF	PRODH, W, ACCESS
	MOVWF	_PORTBbits, ACCESS
;	.line	258; main.c	PORTBbits.RB3 = OSCCONbits.OSTS; /* should to be clear ! */
	CLRF	r0x00, ACCESS
	BTFSC	_OSCCONbits, 3, ACCESS
	INCF	r0x00, F, ACCESS
	MOVF	r0x00, W, ACCESS
	ANDLW	0x01
	SWAPF	WREG, W, ACCESS
	RRNCF	WREG, W, ACCESS
	MOVWF	PRODH, ACCESS
	MOVF	_PORTBbits, W, ACCESS
	ANDLW	0xf7
	IORWF	PRODH, W, ACCESS
	MOVWF	_PORTBbits, ACCESS
;	.line	259; main.c	PORTC=0xff;
	MOVLW	0xff
	MOVWF	_PORTC, ACCESS
;	.line	260; main.c	for (i=0;;++i) {
	CLRF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
_00205_DS_:
;	.line	261; main.c	if ( i == ( 32768/512 ) ) {
	MOVFF	r0x00, r0x02
	MOVFF	r0x01, r0x03
	CLRF	r0x04, ACCESS
	CLRF	r0x05, ACCESS
	MOVF	r0x02, W, ACCESS
	XORLW	0x40
	BNZ	_00217_DS_
	MOVF	r0x03, W, ACCESS
	BNZ	_00217_DS_
	MOVF	r0x04, W, ACCESS
	BNZ	_00217_DS_
	MOVF	r0x05, W, ACCESS
	BZ	_00204_DS_
_00217_DS_:
;	.line	264; main.c	PORTA = i>>4;
	SWAPF	r0x00, W, ACCESS
	ANDLW	0x0f
	MOVWF	r0x02, ACCESS
	SWAPF	r0x01, W, ACCESS
	MOVWF	r0x03, ACCESS
	ANDLW	0xf0
	XORWF	r0x03, F, ACCESS
	ADDWF	r0x02, F, ACCESS
	MOVF	r0x02, W, ACCESS
	MOVWF	_PORTA, ACCESS
;	.line	260; main.c	for (i=0;;++i) {
	INFSNZ	r0x00, F, ACCESS
	INCF	r0x01, F, ACCESS
	BRA	_00205_DS_
_00204_DS_:
	BANKSEL	_sec
;	.line	268; main.c	PORTA = sec;
	MOVF	_sec, W, BANKED
	MOVWF	_PORTA, ACCESS
;	.line	269; main.c	PORTB = min | ( (hour&0b00100 )<<4) | ( (hour&0b00010 )<<6);
	MOVLW	0x04
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	SWAPF	r0x00, W, ACCESS
	ANDLW	0xf0
	MOVWF	r0x01, ACCESS
	MOVFF	r0x01, r0x00
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	BANKSEL	_min
	MOVF	_min, W, BANKED
	IORWF	r0x00, F, ACCESS
	BANKSEL	(_min + 1)
	MOVF	(_min + 1), W, BANKED
	IORWF	r0x02, F, ACCESS
	BANKSEL	(_min + 2)
	MOVF	(_min + 2), W, BANKED
	IORWF	r0x03, F, ACCESS
	BANKSEL	(_min + 3)
	MOVF	(_min + 3), W, BANKED
	IORWF	r0x04, F, ACCESS
	MOVLW	0x02
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x01, ACCESS
	CLRF	r0x05, ACCESS
	CLRF	r0x06, ACCESS
	CLRF	r0x07, ACCESS
	RRNCF	r0x01, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xc0
	MOVWF	r0x05, ACCESS
	MOVFF	r0x05, r0x01
	CLRF	r0x06, ACCESS
	CLRF	r0x07, ACCESS
	CLRF	r0x08, ACCESS
	MOVF	r0x01, W, ACCESS
	IORWF	r0x00, F, ACCESS
	MOVF	r0x06, W, ACCESS
	IORWF	r0x02, F, ACCESS
	MOVF	r0x07, W, ACCESS
	IORWF	r0x03, F, ACCESS
	MOVF	r0x08, W, ACCESS
	IORWF	r0x04, F, ACCESS
	MOVF	r0x00, W, ACCESS
	MOVWF	_PORTB, ACCESS
;	.line	270; main.c	PORTC = ( (hour&0b00001)<<2 ) | ( (hour&0b11000) <<3 ) ;
	MOVLW	0x01
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x01, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	RLNCF	r0x00, W, ACCESS
	RLNCF	WREG, W, ACCESS
	ANDLW	0xfc
	MOVWF	r0x01, ACCESS
	MOVLW	0x18
	BANKSEL	_hour
	ANDWF	_hour, W, BANKED
	MOVWF	r0x00, ACCESS
	CLRF	r0x02, ACCESS
	CLRF	r0x03, ACCESS
	CLRF	r0x04, ACCESS
	SWAPF	r0x00, W, ACCESS
	RRNCF	WREG, W, ACCESS
	ANDLW	0xf8
	MOVWF	r0x02, ACCESS
	MOVF	r0x02, W, ACCESS
	IORWF	r0x01, W, ACCESS
	MOVWF	_PORTC, ACCESS
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
S_main__RTCinit	code
_RTCinit:
;	.line	206; main.c	void RTCinit()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	208; main.c	TMR1H = 0x80;
	MOVLW	0x80
	MOVWF	_TMR1H, ACCESS
;	.line	209; main.c	TMR1L = 0x00;
	CLRF	_TMR1L, ACCESS
;	.line	212; main.c	T1CON=0b00001111;
	MOVLW	0x0f
	MOVWF	_T1CON, ACCESS
	BANKSEL	_sec
;	.line	243; main.c	sec=0;
	CLRF	_sec, BANKED
	BANKSEL	(_sec + 1)
	CLRF	(_sec + 1), BANKED
	BANKSEL	(_sec + 2)
	CLRF	(_sec + 2), BANKED
	BANKSEL	(_sec + 3)
	CLRF	(_sec + 3), BANKED
	BANKSEL	_min
;	.line	244; main.c	min=0;
	CLRF	_min, BANKED
	BANKSEL	(_min + 1)
	CLRF	(_min + 1), BANKED
	BANKSEL	(_min + 2)
	CLRF	(_min + 2), BANKED
	BANKSEL	(_min + 3)
	CLRF	(_min + 3), BANKED
;	.line	245; main.c	hour=12;
	MOVLW	0x0c
	BANKSEL	_hour
	MOVWF	_hour, BANKED
	BANKSEL	(_hour + 1)
	CLRF	(_hour + 1), BANKED
	BANKSEL	(_hour + 2)
	CLRF	(_hour + 2), BANKED
	BANKSEL	(_hour + 3)
	CLRF	(_hour + 3), BANKED
;	.line	247; main.c	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	BCF	_PIR1bits, 0, ACCESS
;	.line	248; main.c	PIE1bits.TMR1IE = 1; /* timer0 enable interrupt */ 
	BSF	_PIE1bits, 0, ACCESS
;	.line	249; main.c	IPR1bits.TMR1IP = 0; /* timer0 interrupt high/low */
	BCF	_IPR1bits, 0, ACCESS
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__init	code
_init:
;	.line	181; main.c	void init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	183; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0, ACCESS
;	.line	184; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1, ACCESS
;	.line	185; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON, ACCESS
;	.line	186; main.c	UCFGbits.UTRDIS = 1; // turn off USB module 
	BSF	_UCFGbits, 3, ACCESS
;	.line	189; main.c	PORTA=0x00;
	CLRF	_PORTA, ACCESS
;	.line	190; main.c	LATA=0x00;
	CLRF	_LATA, ACCESS
;	.line	191; main.c	TRISA=0x00;
	CLRF	_TRISA, ACCESS
;	.line	194; main.c	PORTB=0x00;
	CLRF	_PORTB, ACCESS
;	.line	195; main.c	LATB=0x00;
	CLRF	_LATB, ACCESS
;	.line	196; main.c	TRISB=0x00;
	CLRF	_TRISB, ACCESS
;	.line	199; main.c	PORTC=0x00;
	CLRF	_PORTC, ACCESS
;	.line	200; main.c	LATC=0x00;
	CLRF	_LATC, ACCESS
;	.line	201; main.c	TRISC=0x00;
	CLRF	_TRISC, ACCESS
;	.line	203; main.c	TRISAbits.RA6 = 1;
	BSF	_TRISAbits, 6, ACCESS
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1376 (0x0560) bytes ( 1.05%)
;           	  688 (0x02b0) words
; udata size:	   12 (0x000c) bytes ( 0.67%)
; access size:	    9 (0x0009) bytes


	end
