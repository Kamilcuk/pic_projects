;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:48 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"main.c"
	list	p=18f2550
	radix	dec
	CONFIG	PLLDIV=4
	CONFIG	CPUDIV=OSC1_PLL2
	CONFIG	USBDIV=2
	CONFIG	FOSC=HSPLL_HS
	CONFIG	IESO=ON,PWRT=ON,BOR=ON,BORV=3,VREGEN=ON,WDT=OFF,WDTPS=32768,MCLRE=ON,LPT1OSC=OFF,PBADEN=OFF,CCP2MX=OFF,STVREN=ON,LVP=OFF,XINST=OFF,DEBUG=OFF,CP0=OFF,CP1=OFF,CP2=OFF,CP3=OFF,CPB=OFF,CPD=OFF,WRT0=OFF,WRT1=OFF,WRT2=OFF,WRT3=OFF,WRTB=OFF,WRTC=OFF,WRTD=OFF,EBTR0=OFF,EBTR1=OFF,EBTR2=OFF,EBTR3=OFF,EBTRB=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_serial_init
	global	_myprint
	global	_main
	global	_charmap

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
	extern	_lcddev
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
	extern	_hd44780_init
	extern	_hd44780_send
	extern	_usart_open
	extern	_usart_drdy
	extern	_usart_getc

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
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_myprint_ctrl_1_20	db	0x00
_myprint_pos_1_20	db	0x00


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1


databank7	udata

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
	.line	98; main.c	hd44780_init();
	CALL	_hd44780_init
	.line	99; main.c	serial_init();
	CALL	_serial_init
_00161_DS_:
	.line	102; main.c	while ( !usart_drdy() ) {}
	CALL	_usart_drdy
	MOVWF	r0x00
	MOVF	r0x00, W
	BZ	_00161_DS_
	.line	103; main.c	myprint( usart_getc() );
	CALL	_usart_getc
	MOVWF	r0x00
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_myprint
	MOVF	POSTINC1, F
	BRA	_00161_DS_
	RETURN	

; ; Starting pCode block
S_main__myprint	code
_myprint:
	.line	67; main.c	void myprint(unsigned char buf)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	72; main.c	if ( buf == '\n' ) {
	MOVF	r0x00, W
	XORLW	0x0a
	BNZ	_00129_DS_
	.line	73; main.c	if ( pos < 40 ) {
	MOVLW	0x28
	BANKSEL	_myprint_pos_1_20
	SUBWF	_myprint_pos_1_20, W, B
	BC	_00126_DS_
	.line	74; main.c	pos = 40;
	MOVLW	0x28
	BANKSEL	_myprint_pos_1_20
	MOVWF	_myprint_pos_1_20, B
	.line	75; main.c	write_inst(ctrl, HD44780_DDRAM_ADDRESS | pos );
	MOVLW	0xa8
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	BANKSEL	_myprint_ctrl_1_20
	MOVF	_myprint_ctrl_1_20, W, B
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00127_DS_
_00126_DS_:
	BANKSEL	_myprint_pos_1_20
	.line	77; main.c	pos = 0;
	CLRF	_myprint_pos_1_20, B
	.line	78; main.c	write_inst(ctrl, HD44780_DDRAM_ADDRESS); /* cursor to [0,0] on current ctrl */
	MOVLW	0x80
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	BANKSEL	_myprint_ctrl_1_20
	MOVF	_myprint_ctrl_1_20, W, B
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_myprint_ctrl_1_20
	.line	79; main.c	ctrl++;
	INCF	_myprint_ctrl_1_20, F, B
	.line	80; main.c	if ( ctrl >= NUM_CONTROLLERS ) 
	MOVLW	0x05
	BANKSEL	_myprint_ctrl_1_20
	SUBWF	_myprint_ctrl_1_20, W, B
	BNC	_00127_DS_
	BANKSEL	_myprint_ctrl_1_20
	.line	81; main.c	ctrl = 0;
	CLRF	_myprint_ctrl_1_20, B
_00127_DS_:
	.line	83; main.c	return;
	BRA	_00134_DS_
_00129_DS_:
	.line	86; main.c	write_data(ctrl, buf);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	BANKSEL	_myprint_ctrl_1_20
	MOVF	_myprint_ctrl_1_20, W, B
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_myprint_pos_1_20
	.line	87; main.c	pos++;
	INCF	_myprint_pos_1_20, F, B
	.line	88; main.c	if ( pos >= DISP_COLS*ROWS_PER_CTRL ) { 
	MOVLW	0x50
	BANKSEL	_myprint_pos_1_20
	SUBWF	_myprint_pos_1_20, W, B
	BNC	_00134_DS_
	BANKSEL	_myprint_pos_1_20
	.line	89; main.c	pos = 0;
	CLRF	_myprint_pos_1_20, B
	BANKSEL	_myprint_ctrl_1_20
	.line	90; main.c	ctrl++;
	INCF	_myprint_ctrl_1_20, F, B
	.line	91; main.c	if ( ctrl >= NUM_CONTROLLERS ) 
	MOVLW	0x05
	BANKSEL	_myprint_ctrl_1_20
	SUBWF	_myprint_ctrl_1_20, W, B
	BNC	_00134_DS_
	BANKSEL	_myprint_ctrl_1_20
	.line	92; main.c	ctrl = 0;
	CLRF	_myprint_ctrl_1_20, B
_00134_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__serial_init	code
_serial_init:
	.line	51; main.c	void serial_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	61; main.c	8332
	MOVLW	0x20
	MOVWF	POSTDEC1
	MOVLW	0x8c
	MOVWF	POSTDEC1
	MOVLW	0x2c
	CALL	_usart_open
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	63; main.c	for(i=0xff;i;i--)
	MOVLW	0xff
	MOVWF	r0x00
_00116_DS_:
	NOP 
	.line	63; main.c	for(i=0xff;i;i--)
	DECFSZ	r0x00, F
	BRA	_00116_DS_
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__low_interrupt	code
_low_interrupt:
	.line	45; main.c	static void low_interrupt(void) __interrupt(2)
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
	.line	47; main.c	}
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
	.line	41; main.c	static void high_interrupt(void) __interrupt(1)
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
	.line	43; main.c	}
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

; ; Starting pCode block for Ival
	code
_charmap:
	DB	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b
	DB	0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
	DB	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23
	DB	0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
	DB	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b
	DB	0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47
	DB	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53
	DB	0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x2f, 0x5d, 0x5e, 0x5f
	DB	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b
	DB	0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77
	DB	0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83
	DB	0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f
	DB	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b
	DB	0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0x21, 0xec, 0xed, 0xa4, 0x5c, 0x7c, 0xa7
	DB	0x22, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xdf, 0xb1, 0xb2, 0xb3
	DB	0x27, 0xf9, 0xf7, 0xa5, 0x2c, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0x3f
	DB	0x41, 0x41, 0x41, 0x41, 0xe1, 0x41, 0x41, 0x43, 0x45, 0x45, 0x45, 0x45
	DB	0x49, 0x49, 0x49, 0x49, 0x44, 0x4e, 0x4f, 0x4f, 0x4f, 0x4f, 0xef, 0x78
	DB	0x30, 0x55, 0x55, 0x55, 0xf5, 0x59, 0xf0, 0xe2, 0x61, 0x61, 0x61, 0x61
	DB	0xe1, 0x61, 0x61, 0x63, 0x65, 0x65, 0x65, 0x65, 0x69, 0x69, 0x69, 0x69
	DB	0x6f, 0x6e, 0x6f, 0x6f, 0x6f, 0x6f, 0xef, 0xfd, 0x30, 0x75, 0x75, 0x75
	DB	0xf5, 0x79, 0xf0, 0xff


; Statistics:
; code size:	  472 (0x01d8) bytes ( 0.36%)
;           	  236 (0x00ec) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    1 (0x0001) bytes


	end
