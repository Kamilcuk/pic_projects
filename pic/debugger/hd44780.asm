;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:47 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"hd44780.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_hd44780_recv
	global	_hd44780_send
	global	_hd44780_send_all
	global	_hd44780_init
	global	_lcddev

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
WREG	equ	0xfe8
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
r0x02	res	1
r0x03	res	1
r0x04	res	1

udata_hd44780_0	udata
_lcddev	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_hd44780__hd44780_init	code
_hd44780_init:
	.line	306; hd44780.c	void hd44780_init(void) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	.line	114; hd44780.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	115; hd44780.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	116; hd44780.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	119; hd44780.c	PORTA=0x00;
	CLRF	_PORTA
	.line	120; hd44780.c	LATA=0x00;
	CLRF	_LATA
	.line	121; hd44780.c	TRISA=0x00;
	CLRF	_TRISA
	.line	124; hd44780.c	PORTB=0x00;
	CLRF	_PORTB
	.line	125; hd44780.c	LATB=0x00;
	CLRF	_LATB
	.line	126; hd44780.c	TRISB=0x00;
	CLRF	_TRISB
	.line	129; hd44780.c	PORTC=0x00;
	CLRF	_PORTC
	.line	130; hd44780.c	LATC=0x00;
	CLRF	_LATC
	.line	131; hd44780.c	TRISC=0x00;
	CLRF	_TRISC
	.line	133; hd44780.c	_hd44780_data_set_(0x00);
	CLRF	_PORTB
	.line	134; hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
	.line	225; hd44780.c	set_bit(FLAG_NOBFCHECK, lcddev.flags);
	MOVLW	0x02
	BANKSEL	_lcddev
	IORWF	_lcddev, W, B
	MOVWF	r0x00
	MOVF	r0x00, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
	.line	228; hd44780.c	for (i = 43; i; --i)
	MOVLW	0x2b
	MOVWF	r0x00
_00447_DS_:
	.line	229; hd44780.c	for (j=0xff; j; --j);
	MOVLW	0xff
	MOVWF	r0x01
_00424_DS_:
	DECFSZ	r0x01, F
	BRA	_00424_DS_
	.line	228; hd44780.c	for (i = 43; i; --i)
	DECFSZ	r0x00, F
	BRA	_00447_DS_
	.line	235; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	237; hd44780.c	for (i = 17; i; --i)
	MOVLW	0x11
	MOVWF	r0x00
_00451_DS_:
	.line	239; hd44780.c	do { }while(0);
	MOVLW	0xff
	MOVWF	r0x01
_00396_DS_:
	.line	238; hd44780.c	for (j = 0xff; j; --j)
	DECFSZ	r0x01, F
	BRA	_00396_DS_
	.line	237; hd44780.c	for (i = 17; i; --i)
	DECFSZ	r0x00, F
	BRA	_00451_DS_
	.line	243; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	245; hd44780.c	for (i = 2; i; --i)
	MOVLW	0x02
	MOVWF	r0x00
_00455_DS_:
	.line	246; hd44780.c	for (j = 0xff; j; --j);
	MOVLW	0xff
	MOVWF	r0x01
_00432_DS_:
	DECFSZ	r0x01, F
	BRA	_00432_DS_
	.line	245; hd44780.c	for (i = 2; i; --i)
	DECFSZ	r0x00, F
	BRA	_00455_DS_
	.line	251; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	260; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00404_DS_:
	.line	259; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00404_DS_
	.line	264; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	267; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00407_DS_:
	.line	266; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00407_DS_
	.line	271; hd44780.c	HD44780_DOOC_CURSORNOBLINK); /* display off */
	MOVLW	0x08
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	274; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00410_DS_:
	.line	273; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00410_DS_
	.line	276; hd44780.c	HD44780_CLRDISP); /* display clear */
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	279; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00413_DS_:
	.line	278; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00413_DS_
	.line	281; hd44780.c	HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	284; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00416_DS_:
	.line	283; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00416_DS_
	BANKSEL	_lcddev
	.line	287; hd44780.c	clear_bit(FLAG_NOBFCHECK, lcddev.flags);
	CLRF	_lcddev, B
	BANKSEL	_lcddev
	.line	312; hd44780.c	lcddev_init();
	CLRF	_lcddev, B
	.line	315; hd44780.c	write_inst_all( HD44780_FS_DATAWIDTH8BIT |
	MOVLW	0x38
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	318; hd44780.c	write_inst_all( HD44780_DOOC_DISPLAYON |
	MOVLW	0x0f
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	321; hd44780.c	write_inst_all( HD44780_CLRDISP);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	322; hd44780.c	write_inst_all( HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780__hd44780_initialize_by_instruction	code
_hd44780_initialize_by_instruction:
	.line	220; hd44780.c	__once void hd44780_initialize_by_instruction(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	.line	225; hd44780.c	set_bit(FLAG_NOBFCHECK, lcddev.flags);
	MOVLW	0x02
	BANKSEL	_lcddev
	IORWF	_lcddev, W, B
	MOVWF	r0x00
	MOVF	r0x00, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
	.line	228; hd44780.c	for (i = 43; i; --i)
	MOVLW	0x2b
	MOVWF	r0x00
_00370_DS_:
	.line	229; hd44780.c	for (j=0xff; j; --j);
	MOVLW	0xff
	MOVWF	r0x01
_00347_DS_:
	DECFSZ	r0x01, F
	BRA	_00347_DS_
	.line	228; hd44780.c	for (i = 43; i; --i)
	DECFSZ	r0x00, F
	BRA	_00370_DS_
	.line	235; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	237; hd44780.c	for (i = 17; i; --i)
	MOVLW	0x11
	MOVWF	r0x00
_00374_DS_:
	.line	239; hd44780.c	do { }while(0);
	MOVLW	0xff
	MOVWF	r0x01
_00320_DS_:
	.line	238; hd44780.c	for (j = 0xff; j; --j)
	DECFSZ	r0x01, F
	BRA	_00320_DS_
	.line	237; hd44780.c	for (i = 17; i; --i)
	DECFSZ	r0x00, F
	BRA	_00374_DS_
	.line	243; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	245; hd44780.c	for (i = 2; i; --i)
	MOVLW	0x02
	MOVWF	r0x00
_00378_DS_:
	.line	246; hd44780.c	for (j = 0xff; j; --j);
	MOVLW	0xff
	MOVWF	r0x01
_00355_DS_:
	DECFSZ	r0x01, F
	BRA	_00355_DS_
	.line	245; hd44780.c	for (i = 2; i; --i)
	DECFSZ	r0x00, F
	BRA	_00378_DS_
	.line	251; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	260; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00328_DS_:
	.line	259; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00328_DS_
	.line	264; hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	267; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00331_DS_:
	.line	266; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00331_DS_
	.line	271; hd44780.c	HD44780_DOOC_CURSORNOBLINK); /* display off */
	MOVLW	0x08
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	274; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00334_DS_:
	.line	273; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00334_DS_
	.line	276; hd44780.c	HD44780_CLRDISP); /* display clear */
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	279; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00337_DS_:
	.line	278; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00337_DS_
	.line	281; hd44780.c	HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	284; hd44780.c	do { }while(0);
	MOVLW	0x70
	MOVWF	r0x00
_00340_DS_:
	.line	283; hd44780.c	for (i = 112; i; --i)
	DECFSZ	r0x00, F
	BRA	_00340_DS_
	BANKSEL	_lcddev
	.line	287; hd44780.c	clear_bit(FLAG_NOBFCHECK, lcddev.flags);
	CLRF	_lcddev, B
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780__hd44780_send_all	code
_hd44780_send_all:
	.line	186; hd44780.c	void hd44780_send_all(u8 flags, u8 command)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	BANKSEL	_lcddev
	.line	190; hd44780.c	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) {
	BTFSC	_lcddev, 1, B
	BRA	_00279_DS_
	.line	192; hd44780.c	for (i=0; i<NUM_CONTROLLERS ; i++) {
	CLRF	r0x02
_00296_DS_:
	.line	193; hd44780.c	_hd44780_wait_for_ready_(i);
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	__hd44780_wait_for_ready_
	MOVF	POSTINC1, F
	.line	192; hd44780.c	for (i=0; i<NUM_CONTROLLERS ; i++) {
	INCF	r0x02, F
	MOVLW	0x05
	SUBWF	r0x02, W
	BNC	_00296_DS_
_00279_DS_:
	.line	197; hd44780.c	_hd44780_data_forward_();
	CLRF	_TRISB
	.line	198; hd44780.c	_hd44780_data_set_(command);
	MOVFF	r0x01, _PORTB
	.line	199; hd44780.c	_hd44780_capable_(flags);
	MOVFF	r0x00, _PORTC
	.line	200; hd44780.c	_hd44780_enable_all_(flags);
	MOVLW	0x3f
	MOVWF	_PORTA
	MOVLW	0xc0
	IORWF	r0x00, W
	MOVWF	_PORTC
	nop 
	nop 
	nop 
	nop 
	.line	201; hd44780.c	_hd44780_disable_(flags);
	CLRF	_PORTA
	MOVFF	r0x00, _PORTC
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780__hd44780_send	code
_hd44780_send:
	.line	164; hd44780.c	void hd44780_send(u8 ctrl_nr, u8 flags, u8 command)
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
	.line	166; hd44780.c	if ( ctrl_nr >= NUM_CONTROLLERS ) return;
	MOVLW	0x05
	SUBWF	r0x00, W
	BC	_00254_DS_
_00235_DS_:
	BANKSEL	_lcddev
	.line	170; hd44780.c	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) 
	BTFSC	_lcddev, 1, B
	BRA	_00237_DS_
	.line	171; hd44780.c	_hd44780_wait_for_ready_(ctrl_nr);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	__hd44780_wait_for_ready_
	MOVF	POSTINC1, F
_00237_DS_:
	.line	174; hd44780.c	_hd44780_data_forward_();
	CLRF	_TRISB
	.line	175; hd44780.c	_hd44780_data_set_(command);
	MOVFF	r0x02, _PORTB
	.line	176; hd44780.c	_hd44780_capable_(flags);
	MOVFF	r0x01, _PORTC
	.line	177; hd44780.c	_hd44780_enable_(flags, ctrl_nr);
	MOVF	r0x00, W
	XORLW	0x07
	BNZ	_00256_DS_
	MOVLW	0x01
	MOVWF	r0x02
	BRA	_00257_DS_
_00256_DS_:
	MOVLW	0x02
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00257_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00272_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00272_DS_
_00257_DS_:
	MOVLW	0x3f
	ANDWF	r0x02, W
	MOVWF	_PORTA
	MOVLW	0xc0
	ANDWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x02, W
	MOVWF	_PORTC
	nop 
	nop 
	nop 
	nop 
	.line	178; hd44780.c	_hd44780_disable_(flags);
	CLRF	_PORTA
	MOVFF	r0x01, _PORTC
_00254_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780__hd44780_recv	code
_hd44780_recv:
	.line	138; hd44780.c	u8 hd44780_recv(u8 ctrl_nr, u8 flags)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	142; hd44780.c	if ( ctrl_nr >= NUM_CONTROLLERS ) return 0;
	MOVLW	0x05
	SUBWF	r0x00, W
	BNC	_00188_DS_
	CLRF	WREG
	BRA	_00210_DS_
_00188_DS_:
	.line	144; hd44780.c	flags |= RW_READ;
	BSF	r0x01, 0
	BANKSEL	_lcddev
	.line	146; hd44780.c	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) 
	BTFSC	_lcddev, 1, B
	BRA	_00190_DS_
	.line	147; hd44780.c	_hd44780_wait_for_ready_(ctrl_nr);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	__hd44780_wait_for_ready_
	MOVF	POSTINC1, F
_00190_DS_:
	.line	149; hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
	.line	150; hd44780.c	_hd44780_capable_(flags);
	MOVFF	r0x01, _PORTC
	.line	151; hd44780.c	_hd44780_enable_(flags, ctrl_nr);
	MOVF	r0x00, W
	XORLW	0x07
	BNZ	_00212_DS_
	MOVLW	0x01
	MOVWF	r0x02
	BRA	_00213_DS_
_00212_DS_:
	MOVLW	0x02
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00213_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00229_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00229_DS_
_00213_DS_:
	MOVLW	0x3f
	ANDWF	r0x02, W
	MOVWF	_PORTA
	MOVLW	0xc0
	ANDWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x02, W
	MOVWF	_PORTC
	nop 
	nop 
	nop 
	nop 
	nop 
	nop 
	nop 
	nop 
	nop 
	nop 
	.line	153; hd44780.c	status = _hd44780_data_get_();
	MOVFF	_PORTB, r0x00
	.line	154; hd44780.c	_hd44780_disable_(flags);
	CLRF	_PORTA
	MOVFF	r0x01, _PORTC
	.line	161; hd44780.c	return status;
	MOVF	r0x00, W
_00210_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780__hd44780_init_port	code
_hd44780_init_port:
	.line	112; hd44780.c	__once void hd44780_init_port(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	114; hd44780.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	115; hd44780.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	116; hd44780.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	119; hd44780.c	PORTA=0x00;
	CLRF	_PORTA
	.line	120; hd44780.c	LATA=0x00;
	CLRF	_LATA
	.line	121; hd44780.c	TRISA=0x00;
	CLRF	_TRISA
	.line	124; hd44780.c	PORTB=0x00;
	CLRF	_PORTB
	.line	125; hd44780.c	LATB=0x00;
	CLRF	_LATB
	.line	126; hd44780.c	TRISB=0x00;
	CLRF	_TRISB
	.line	129; hd44780.c	PORTC=0x00;
	CLRF	_PORTC
	.line	130; hd44780.c	LATC=0x00;
	CLRF	_LATC
	.line	131; hd44780.c	TRISC=0x00;
	CLRF	_TRISC
	.line	133; hd44780.c	_hd44780_data_set_(0x00);
	CLRF	_PORTB
	.line	134; hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_hd44780___hd44780_wait_for_ready_	code
__hd44780_wait_for_ready_:
	.line	81; hd44780.c	static void _hd44780_wait_for_ready_(u8 ctrl_nr)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	86; hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
	.line	87; hd44780.c	_hd44780_capable_(RW_READ | RS_INST);
	MOVLW	0x01
	MOVWF	_PORTC
	.line	88; hd44780.c	_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	CLRF	r0x01
	MOVF	r0x00, W
	XORLW	0x07
	BNZ	_00170_DS_
	INCF	r0x01, F
_00170_DS_:
	MOVF	r0x01, W
	BZ	_00146_DS_
	MOVLW	0x01
	MOVWF	r0x02
	BRA	_00147_DS_
_00146_DS_:
	MOVLW	0x02
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00147_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00172_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00172_DS_
_00147_DS_:
	MOVLW	0x3f
	ANDWF	r0x02, W
	MOVWF	_PORTA
	MOVLW	0xc0
	ANDWF	r0x02, F
	MOVLW	0x01
	IORWF	r0x02, W
	MOVWF	_PORTC
	nop 
	nop 
	nop 
	nop 
	.line	89; hd44780.c	for ( count = BUSYFLAG_STUCK; count && _hd44780_data_get_busyflag_(); --count ) {
	MOVLW	0x02
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00176_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00177_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00177_DS_
_00176_DS_:
	MOVLW	0xff
	MOVWF	r0x00
	MOVWF	r0x03
_00142_DS_:
	MOVF	r0x00, W
	IORWF	r0x03, W
	BZ	_00132_DS_
	BTFSS	_PORTBbits, 7
	BRA	_00132_DS_
	.line	90; hd44780.c	_hd44780_disable_(RW_READ | RS_INST);
	CLRF	_PORTA
	MOVLW	0x01
	MOVWF	_PORTC
	.line	94; hd44780.c	_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	MOVF	r0x01, W
	BZ	_00148_DS_
	MOVLW	0x01
	MOVWF	r0x04
	BRA	_00149_DS_
_00148_DS_:
	MOVFF	r0x02, r0x04
_00149_DS_:
	MOVLW	0x3f
	ANDWF	r0x04, W
	MOVWF	_PORTA
	MOVLW	0xc0
	ANDWF	r0x04, F
	MOVLW	0x01
	IORWF	r0x04, W
	MOVWF	_PORTC
	nop 
	nop 
	nop 
	nop 
	.line	89; hd44780.c	for ( count = BUSYFLAG_STUCK; count && _hd44780_data_get_busyflag_(); --count ) {
	MOVLW	0xff
	ADDWF	r0x00, F
	ADDWFC	r0x03, F
	BRA	_00142_DS_
_00132_DS_:
	.line	96; hd44780.c	_hd44780_disable_(RW_READ | RS_INST);
	CLRF	_PORTA
	MOVLW	0x01
	MOVWF	_PORTC
	.line	102; hd44780.c	if ( !count ) {
	MOVF	r0x00, W
	IORWF	r0x03, W
	BNZ	_00144_DS_
	.line	105; hd44780.c	set_bit(FLAG_NOBFCHECK, lcddev.flags);
	MOVLW	0x02
	BANKSEL	_lcddev
	IORWF	_lcddev, W, B
	MOVWF	r0x00
	MOVF	r0x00, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
_00144_DS_:
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1310 (0x051e) bytes ( 1.00%)
;           	  655 (0x028f) words
; udata size:	    1 (0x0001) bytes ( 0.06%)
; access size:	    5 (0x0005) bytes


	end
