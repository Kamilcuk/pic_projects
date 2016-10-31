;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:52 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"cake.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_cake_eat_basket

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
	extern	_hd44780_recv
	extern	_hd44780_send
	extern	_hd44780_send_all
	extern	_USB_EP2_set

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCL	equ	0xff9
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3


	idata
_intestine_cnt	db	0x00
_input_state	db	0x00


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

udata_cake_0	udata
_bite	res	1

udata_cake_1	udata
_intestine	res	64

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_cake__cake_eat_basket	code
_cake_eat_basket:
	.line	132; cake.c	void cake_eat_basket(unsigned char __near *basket, unsigned char cnt) // basket full of cakes !
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
_00226_DS_:
	.line	136; cake.c	while (cnt) {
	MOVF	r0x02, W
	BTFSC	STATUS, 2
	BRA	_00263_DS_
	.line	138; cake.c	cake = *basket;
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x03
	.line	139; cake.c	++basket;
	INFSNZ	r0x00, F
	INCF	r0x01, F
	.line	140; cake.c	--cnt;
	DECF	r0x02, F
	.line	49; cake.c	switch(input_state) {
	MOVLW	0x04
	BANKSEL	_input_state
	SUBWF	_input_state, W, B
	BTFSC	STATUS, 0
	BRA	_00255_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	BANKSEL	_input_state
	RLCF	_input_state, W, B
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00327_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00327_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00327_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00327_DS_:
	GOTO	_00250_DS_
	GOTO	_00251_DS_
	GOTO	_00252_DS_
	GOTO	_00253_DS_
_00250_DS_:
	.line	51; cake.c	switch (cake&CAKE_FILLING_BITS) {
	MOVLW	0xe0
	ANDWF	r0x03, W
	MOVWF	r0x04
	MOVF	r0x04, W
	MOVWF	r0x05
	MOVF	r0x05, W
	BZ	_00234_DS_
	MOVF	r0x04, W
	XORLW	0x20
	BNZ	_00332_DS_
	BRA	_00241_DS_
_00332_DS_:
	MOVF	r0x04, W
	XORLW	0x40
	BNZ	_00334_DS_
	BRA	_00243_DS_
_00334_DS_:
	MOVF	r0x04, W
	XORLW	0x60
	BNZ	_00336_DS_
	BRA	_00242_DS_
_00336_DS_:
	MOVF	r0x04, W
	XORLW	0x80
	BNZ	_00338_DS_
	BRA	_00246_DS_
_00338_DS_:
	MOVF	r0x04, W
	XORLW	0xa0
	BNZ	_00226_DS_
	BRA	_00247_DS_
_00340_DS_:
	BRA	_00226_DS_
_00234_DS_:
	.line	53; cake.c	if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
	BTFSS	r0x03, 0
	BRA	_00232_DS_
	.line	55; cake.c	if (intestine_cnt >= CAKE_INTESTINE_SIZE) // our recv buffer is full
	MOVLW	0x40
	BANKSEL	_intestine_cnt
	SUBWF	_intestine_cnt, W, B
	BTFSC	STATUS, 0
	BRA	_00226_DS_
	.line	57; cake.c	intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(cake), cake&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVLW	0x1c
	ANDWF	r0x03, W
	MOVWF	r0x06
	RRNCF	r0x06, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x06
	MOVLW	0x03
	ANDWF	r0x03, W
	MOVWF	r0x07
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x06
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	r0x06, INDF0
	BANKSEL	_intestine_cnt
	.line	58; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	BRA	_00226_DS_
_00232_DS_:
	.line	61; cake.c	input_state = RAW_WRITE;
	MOVLW	0x01
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	62; cake.c	bite = cake;
	MOVFF	r0x03, _bite
	.line	64; cake.c	break;
	BRA	_00226_DS_
_00241_DS_:
	.line	66; cake.c	if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
	BTFSS	r0x03, 0
	BRA	_00239_DS_
	.line	68; cake.c	if (intestine_cnt > (CAKE_INTESTINE_SIZE-MAX_NUM_CONTROLLERS) )
	MOVLW	0x39
	BANKSEL	_intestine_cnt
	SUBWF	_intestine_cnt, W, B
	BTFSC	STATUS, 0
	BRA	_00226_DS_
	BANKSEL	_bite
	.line	72; cake.c	for (bite=0; bite<MAX_NUM_CONTROLLERS; bite++) {
	CLRF	_bite, B
	MOVLW	0x03
	ANDWF	r0x03, W
	MOVWF	r0x04
_00258_DS_:
	.line	73; cake.c	intestine[intestine_cnt] = hd44780_recv(bite, cake&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x05
	CLRF	r0x06
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x06, F
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	BANKSEL	_bite
	MOVF	_bite, W, B
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x07
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x07, INDF0
	BANKSEL	_intestine_cnt
	.line	74; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	BANKSEL	_bite
	.line	72; cake.c	for (bite=0; bite<MAX_NUM_CONTROLLERS; bite++) {
	INCF	_bite, F, B
	MOVLW	0x08
	BANKSEL	_bite
	SUBWF	_bite, W, B
	BNC	_00258_DS_
	BRA	_00226_DS_
_00239_DS_:
	.line	78; cake.c	input_state = RAW_WRITE_ALL;
	MOVLW	0x02
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	79; cake.c	bite = cake;
	MOVFF	r0x03, _bite
	.line	81; cake.c	break;
	BRA	_00226_DS_
_00242_DS_:
	.line	83; cake.c	USB_EP2_set(intestine, intestine_cnt);
	MOVLW	LOW(_intestine)
	MOVWF	r0x04
	MOVLW	HIGH(_intestine)
	MOVWF	r0x05
	BANKSEL	_intestine_cnt
	MOVF	_intestine_cnt, W, B
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_USB_EP2_set
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_intestine_cnt
	.line	84; cake.c	intestine_cnt = 0;
	CLRF	_intestine_cnt, B
	.line	85; cake.c	break;
	BRA	_00226_DS_
_00243_DS_:
	.line	87; cake.c	bite = cake;
	MOVFF	r0x03, _bite
	.line	88; cake.c	input_state  = NUM_READ;
	MOVLW	0x03
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	89; cake.c	break;
	BRA	_00226_DS_
_00246_DS_:
	.line	91; cake.c	if ( intestine_cnt+8 >= CAKE_INTESTINE_SIZE )
	MOVFF	_intestine_cnt, r0x04
	CLRF	r0x05
	MOVLW	0x08
	ADDWF	r0x04, F
	BTFSC	STATUS, 0
	INCF	r0x05, F
	MOVF	r0x05, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00349_DS_
	MOVLW	0x40
	SUBWF	r0x04, W
_00349_DS_:
	BTFSC	STATUS, 0
	BRA	_00226_DS_
	.line	93; cake.c	intestine[intestine_cnt++] = DISP_COLS;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x28
	MOVWF	INDF0
	.line	94; cake.c	intestine[intestine_cnt++] = DISP_ROWS;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x10
	MOVWF	INDF0
	.line	95; cake.c	intestine[intestine_cnt++] = MAX_NUM_CONTROLLERS;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x08
	MOVWF	INDF0
	.line	96; cake.c	intestine[intestine_cnt++] = ROWS_PER_CTRL;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x02
	MOVWF	INDF0
	.line	97; cake.c	intestine[intestine_cnt++] = sizeof(lcddev);
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x81
	MOVWF	INDF0
	.line	98; cake.c	intestine[intestine_cnt++] = lcddev.disabled;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	_lcddev, r0x06
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	r0x06, INDF0
	.line	99; cake.c	intestine[intestine_cnt++] = 0;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	100; cake.c	intestine[intestine_cnt++] = 0;
	MOVFF	_intestine_cnt, r0x04
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x05
	MOVLW	LOW(_intestine)
	ADDWF	r0x04, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	101; cake.c	break;
	BRA	_00226_DS_
_00247_DS_:
	.line	103; cake.c	USB_EP2_set(&lcddev, sizeof(lcddev));
	MOVLW	LOW(_lcddev)
	MOVWF	r0x04
	MOVLW	HIGH(_lcddev)
	MOVWF	r0x05
	MOVLW	0x81
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_USB_EP2_set
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	104; cake.c	break;
	BRA	_00226_DS_
_00251_DS_:
	.line	110; cake.c	hd44780_send(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS, cake);
	MOVLW	0x1c
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x04
	RRNCF	r0x04, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x04
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x05
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_input_state
	.line	111; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	112; cake.c	break;
	BRA	_00226_DS_
_00252_DS_:
	.line	114; cake.c	hd44780_send_all(bite&CAKE_FLAG_BITS, cake);
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x04
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	_input_state
	.line	115; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	116; cake.c	break;
	BRA	_00226_DS_
_00253_DS_:
	.line	119; cake.c	cake = min(cake, CAKE_INTESTINE_SIZE-intestine_cnt); // roll to our receive buffer 
	MOVFF	_intestine_cnt, r0x04
	CLRF	r0x05
	MOVF	r0x04, W
	SUBLW	0x40
	MOVWF	r0x04
	MOVLW	0x00
	SUBFWB	r0x05, F
	MOVFF	r0x03, r0x06
	CLRF	r0x07
	MOVF	r0x05, W
	ADDLW	0x80
	MOVWF	PRODL
	MOVF	r0x07, W
	ADDLW	0x80
	SUBWF	PRODL, W
	BNZ	_00353_DS_
	MOVF	r0x06, W
	SUBWF	r0x04, W
_00353_DS_:
	BC	_00265_DS_
	BANKSEL	_intestine_cnt
	MOVF	_intestine_cnt, W, B
	SUBLW	0x40
	MOVWF	r0x04
	BRA	_00266_DS_
_00265_DS_:
	MOVFF	r0x03, r0x04
_00266_DS_:
	MOVFF	r0x04, r0x03
_00261_DS_:
	.line	120; cake.c	for (; cake; cake--) {
	MOVF	r0x03, W
	BZ	_00254_DS_
	.line	121; cake.c	intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x05, F
	MOVLW	0x1c
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x06
	RRNCF	r0x06, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x06
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x07
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x06
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	r0x06, INDF0
	BANKSEL	_intestine_cnt
	.line	122; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	.line	120; cake.c	for (; cake; cake--) {
	DECF	r0x03, F
	BRA	_00261_DS_
_00254_DS_:
	BANKSEL	_input_state
	.line	124; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	125; cake.c	break;
	BRA	_00226_DS_
_00255_DS_:
	BANKSEL	_input_state
	.line	127; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	142; cake.c	cake_eat_cake(cake);
	BRA	_00226_DS_
_00263_DS_:
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
S_cake__cake_eat_cake	code
_cake_eat_cake:
	.line	47; cake.c	extern inline void cake_eat_cake(unsigned char cake)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	49; cake.c	switch(input_state) {
	MOVLW	0x04
	BANKSEL	_input_state
	SUBWF	_input_state, W, B
	BTFSC	STATUS, 0
	BRA	_00131_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	BANKSEL	_input_state
	RLCF	_input_state, W, B
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00195_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00195_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00195_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00195_DS_:
	GOTO	_00105_DS_
	GOTO	_00127_DS_
	GOTO	_00128_DS_
	GOTO	_00129_DS_
_00105_DS_:
	.line	51; cake.c	switch (cake&CAKE_FILLING_BITS) {
	MOVLW	0xe0
	ANDWF	r0x00, W
	MOVWF	r0x01
	MOVF	r0x01, W
	MOVWF	r0x02
	MOVF	r0x02, W
	BZ	_00106_DS_
	MOVF	r0x01, W
	XORLW	0x20
	BNZ	_00200_DS_
	BRA	_00112_DS_
_00200_DS_:
	MOVF	r0x01, W
	XORLW	0x40
	BNZ	_00202_DS_
	BRA	_00120_DS_
_00202_DS_:
	MOVF	r0x01, W
	XORLW	0x60
	BNZ	_00204_DS_
	BRA	_00119_DS_
_00204_DS_:
	MOVF	r0x01, W
	XORLW	0x80
	BNZ	_00206_DS_
	BRA	_00121_DS_
_00206_DS_:
	MOVF	r0x01, W
	XORLW	0xa0
	BNZ	_00208_DS_
	BRA	_00124_DS_
_00208_DS_:
	BRA	_00138_DS_
_00106_DS_:
	.line	53; cake.c	if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
	BTFSS	r0x00, 0
	BRA	_00110_DS_
	.line	55; cake.c	if (intestine_cnt >= CAKE_INTESTINE_SIZE) // our recv buffer is full
	MOVLW	0x40
	BANKSEL	_intestine_cnt
	SUBWF	_intestine_cnt, W, B
	BNC	_00108_DS_
	.line	56; cake.c	return;
	BRA	_00138_DS_
_00108_DS_:
	.line	57; cake.c	intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(cake), cake&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVLW	0x1c
	ANDWF	r0x00, W
	MOVWF	r0x03
	RRNCF	r0x03, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x03
	MOVLW	0x03
	ANDWF	r0x00, W
	MOVWF	r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x03
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x03, INDF0
	BANKSEL	_intestine_cnt
	.line	58; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	BRA	_00138_DS_
_00110_DS_:
	.line	61; cake.c	input_state = RAW_WRITE;
	MOVLW	0x01
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	62; cake.c	bite = cake;
	MOVFF	r0x00, _bite
	.line	64; cake.c	break;
	BRA	_00138_DS_
_00112_DS_:
	.line	66; cake.c	if (cake&CAKE_RW_BIT) { // 0 is write, 1 is read
	BTFSS	r0x00, 0
	BRA	_00117_DS_
	.line	68; cake.c	if (intestine_cnt > (CAKE_INTESTINE_SIZE-MAX_NUM_CONTROLLERS) )
	MOVLW	0x39
	BANKSEL	_intestine_cnt
	SUBWF	_intestine_cnt, W, B
	BNC	_00114_DS_
	.line	69; cake.c	return;
	BRA	_00138_DS_
_00114_DS_:
	BANKSEL	_bite
	.line	72; cake.c	for (bite=0; bite<MAX_NUM_CONTROLLERS; bite++) {
	CLRF	_bite, B
	MOVLW	0x03
	ANDWF	r0x00, W
	MOVWF	r0x01
_00133_DS_:
	.line	73; cake.c	intestine[intestine_cnt] = hd44780_recv(bite, cake&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x02
	CLRF	r0x03
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x03, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	BANKSEL	_bite
	MOVF	_bite, W, B
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x04
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	r0x04, INDF0
	BANKSEL	_intestine_cnt
	.line	74; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	BANKSEL	_bite
	.line	72; cake.c	for (bite=0; bite<MAX_NUM_CONTROLLERS; bite++) {
	INCF	_bite, F, B
	MOVLW	0x08
	BANKSEL	_bite
	SUBWF	_bite, W, B
	BNC	_00133_DS_
	BRA	_00138_DS_
_00117_DS_:
	.line	78; cake.c	input_state = RAW_WRITE_ALL;
	MOVLW	0x02
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	79; cake.c	bite = cake;
	MOVFF	r0x00, _bite
	.line	81; cake.c	break;
	BRA	_00138_DS_
_00119_DS_:
	.line	83; cake.c	USB_EP2_set(intestine, intestine_cnt);
	MOVLW	LOW(_intestine)
	MOVWF	r0x01
	MOVLW	HIGH(_intestine)
	MOVWF	r0x02
	BANKSEL	_intestine_cnt
	MOVF	_intestine_cnt, W, B
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_USB_EP2_set
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_intestine_cnt
	.line	84; cake.c	intestine_cnt = 0;
	CLRF	_intestine_cnt, B
	.line	85; cake.c	break;
	BRA	_00138_DS_
_00120_DS_:
	.line	87; cake.c	bite = cake;
	MOVFF	r0x00, _bite
	.line	88; cake.c	input_state  = NUM_READ;
	MOVLW	0x03
	BANKSEL	_input_state
	MOVWF	_input_state, B
	.line	89; cake.c	break;
	BRA	_00138_DS_
_00121_DS_:
	.line	91; cake.c	if ( intestine_cnt+8 >= CAKE_INTESTINE_SIZE )
	MOVFF	_intestine_cnt, r0x01
	CLRF	r0x02
	MOVLW	0x08
	ADDWF	r0x01, F
	BTFSC	STATUS, 0
	INCF	r0x02, F
	MOVF	r0x02, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00217_DS_
	MOVLW	0x40
	SUBWF	r0x01, W
_00217_DS_:
	BNC	_00123_DS_
	.line	92; cake.c	return;
	BRA	_00138_DS_
_00123_DS_:
	.line	93; cake.c	intestine[intestine_cnt++] = DISP_COLS;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x28
	MOVWF	INDF0
	.line	94; cake.c	intestine[intestine_cnt++] = DISP_ROWS;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x10
	MOVWF	INDF0
	.line	95; cake.c	intestine[intestine_cnt++] = MAX_NUM_CONTROLLERS;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x08
	MOVWF	INDF0
	.line	96; cake.c	intestine[intestine_cnt++] = ROWS_PER_CTRL;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x02
	MOVWF	INDF0
	.line	97; cake.c	intestine[intestine_cnt++] = sizeof(lcddev);
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x81
	MOVWF	INDF0
	.line	98; cake.c	intestine[intestine_cnt++] = lcddev.disabled;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	_lcddev, r0x03
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x03, INDF0
	.line	99; cake.c	intestine[intestine_cnt++] = 0;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	100; cake.c	intestine[intestine_cnt++] = 0;
	MOVFF	_intestine_cnt, r0x01
	BANKSEL	_intestine_cnt
	INCF	_intestine_cnt, F, B
	CLRF	r0x02
	MOVLW	LOW(_intestine)
	ADDWF	r0x01, F
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	101; cake.c	break;
	BRA	_00138_DS_
_00124_DS_:
	.line	103; cake.c	USB_EP2_set(&lcddev, sizeof(lcddev));
	MOVLW	LOW(_lcddev)
	MOVWF	r0x01
	MOVLW	HIGH(_lcddev)
	MOVWF	r0x02
	MOVLW	0x81
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_USB_EP2_set
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	104; cake.c	break;
	BRA	_00138_DS_
_00127_DS_:
	.line	110; cake.c	hd44780_send(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS, cake);
	MOVLW	0x1c
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x01
	RRNCF	r0x01, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x01
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x02
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_input_state
	.line	111; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	112; cake.c	break;
	BRA	_00138_DS_
_00128_DS_:
	.line	114; cake.c	hd44780_send_all(bite&CAKE_FLAG_BITS, cake);
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x01
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	_input_state
	.line	115; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	116; cake.c	break;
	BRA	_00138_DS_
_00129_DS_:
	.line	119; cake.c	cake = min(cake, CAKE_INTESTINE_SIZE-intestine_cnt); // roll to our receive buffer 
	MOVFF	_intestine_cnt, r0x01
	CLRF	r0x02
	MOVF	r0x01, W
	SUBLW	0x40
	MOVWF	r0x01
	MOVLW	0x00
	SUBFWB	r0x02, F
	MOVFF	r0x00, r0x03
	CLRF	r0x04
	MOVF	r0x02, W
	ADDLW	0x80
	MOVWF	PRODL
	MOVF	r0x04, W
	ADDLW	0x80
	SUBWF	PRODL, W
	BNZ	_00221_DS_
	MOVF	r0x03, W
	SUBWF	r0x01, W
_00221_DS_:
	BC	_00140_DS_
	BANKSEL	_intestine_cnt
	MOVF	_intestine_cnt, W, B
	SUBLW	0x40
	MOVWF	r0x01
	BRA	_00141_DS_
_00140_DS_:
	MOVFF	r0x00, r0x01
_00141_DS_:
	MOVFF	r0x01, r0x00
_00136_DS_:
	.line	120; cake.c	for (; cake; cake--) {
	MOVF	r0x00, W
	BZ	_00130_DS_
	.line	121; cake.c	intestine[intestine_cnt] = hd44780_recv(CAKE_CTRL_NR(bite), bite&CAKE_FLAG_BITS);
	MOVLW	LOW(_intestine)
	BANKSEL	_intestine_cnt
	ADDWF	_intestine_cnt, W, B
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_intestine)
	ADDWFC	r0x02, F
	MOVLW	0x1c
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x03
	RRNCF	r0x03, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x03
	MOVLW	0x03
	BANKSEL	_bite
	ANDWF	_bite, W, B
	MOVWF	r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x03
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x03, INDF0
	BANKSEL	_intestine_cnt
	.line	122; cake.c	intestine_cnt++;
	INCF	_intestine_cnt, F, B
	.line	120; cake.c	for (; cake; cake--) {
	DECF	r0x00, F
	BRA	_00136_DS_
_00130_DS_:
	BANKSEL	_input_state
	.line	124; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
	.line	125; cake.c	break;
	BRA	_00138_DS_
_00131_DS_:
	BANKSEL	_input_state
	.line	127; cake.c	input_state = NORMAL;
	CLRF	_input_state, B
_00138_DS_:
	.line	128; cake.c	}
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1970 (0x07b2) bytes ( 1.50%)
;           	  985 (0x03d9) words
; udata size:	   65 (0x0041) bytes ( 3.63%)
; access size:	    8 (0x0008) bytes


	end
