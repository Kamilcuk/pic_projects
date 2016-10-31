;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:42:50 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"main.c"
	list	p=18f2550
	radix	dec
	CONFIG	PLLDIV=5
	CONFIG	CPUDIV=OSC1_PLL2
	CONFIG	USBDIV=2
	CONFIG	FOSC=HSPLL_HS
	CONFIG	IESO=ON,PWRT=ON,BOR=ON,BORV=3,VREGEN=ON,WDT=OFF,WDTPS=32768,MCLRE=ON,LPT1OSC=OFF,PBADEN=OFF,CCP2MX=OFF,STVREN=ON,LVP=OFF,XINST=OFF,DEBUG=OFF,CP0=OFF,CP1=OFF,CP2=OFF,CP3=OFF,CPB=OFF,CPD=OFF,WRT0=OFF,WRT1=OFF,WRT2=OFF,WRT3=OFF,WRTB=OFF,WRTC=OFF,WRTD=OFF,EBTR0=OFF,EBTR1=OFF,EBTR2=OFF,EBTR3=OFF,EBTRB=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_process
	global	_ports_init
	global	_timer1_start
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
	extern	_srand
	extern	__delay_ms
	extern	_USB_init
	extern	_USB_service

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
INDF0	equ	0xfef
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_high_interrupt_cnt_1_29	db	0x00
_high_interrupt_tmp_1_29	db	0x00
_high_interrupt_tmp2_1_29	db	0x00
_high_interrupt_B_1_29	db	0x00


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1

udata_main_0	udata
_stan	res	4

udata_main_1	udata
_high_interrupt_R_1_29	res	1

udata_main_2	udata
_high_interrupt_G_1_29	res	1

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
	.line	197; main.c	ports_init();
	CALL	_ports_init
	.line	198; main.c	timer1_start();
	CALL	_timer1_start
	.line	201; main.c	srand(1234);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x04
	MOVWF	POSTDEC1
	MOVLW	0xd2
	MOVWF	POSTDEC1
	CALL	_srand
	MOVLW	0x04
	ADDWF	FSR1L, F
	.line	203; main.c	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	BSF	_RCONbits, 7
	.line	204; main.c	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	BSF	_INTCONbits, 7
	.line	205; main.c	INTCONbits.GIEL = 0; /* Enables all low priority interrupts */
	BCF	_INTCONbits, 6
	.line	206; main.c	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	BSF	_OSCCONbits, 7
	BANKSEL	_stan
	.line	209; main.c	stan.timerH = 0xff;
	SETF	_stan, B
	BANKSEL	(_stan + 3)
	.line	210; main.c	stan.B = 0x00;
	CLRF	(_stan + 3), B
	BANKSEL	(_stan + 2)
	.line	211; main.c	stan.R = stan.G = 0xff;
	SETF	(_stan + 2), B
	BANKSEL	(_stan + 1)
	SETF	(_stan + 1), B
	.line	213; main.c	TRISCbits.RC2 = 1; /* USB ? */
	BSF	_TRISCbits, 2
_00214_DS_:
	.line	217; main.c	if ( PORTCbits.RC2 ) {
	BTFSS	_PORTCbits, 2
	BRA	_00207_DS_
	.line	219; main.c	USB_init();
	CALL	_USB_init
	.line	222; main.c	UIE = 0x11; /* IDLEIE URSTIE */
	MOVLW	0x11
	MOVWF	_UIE
_00201_DS_:
	.line	224; main.c	while ( PORTCbits.RC2 ) { // dopoki usb jest podlanczone
	BTFSS	_PORTCbits, 2
	BRA	_00204_DS_
	.line	225; main.c	USB_service(); //looping here with usb
	CALL	_USB_service
	BRA	_00201_DS_
_00204_DS_:
	.line	228; main.c	USB_disable();
	CLRF	_UCFG
	CLRF	_UCON
	CLRF	_UADDR
	BCF	_UIRbits, 3
	CLRF	r0x00
	BTFSC	_UIRbits, 3
	INCF	r0x00, F
	MOVFF	r0x00, _UIR
	MOVFF	r0x00, _UIE
	BSF	_UCFGbits, 3
	BRA	_00214_DS_
_00207_DS_:
	.line	232; main.c	while ( !PORTCbits.RC2 ) {
	BTFSC	_PORTCbits, 2
	BRA	_00214_DS_
	BANKSEL	(_stan + 3)
	.line	233; main.c	stan.B = 0x00;
	CLRF	(_stan + 3), B
	BANKSEL	(_stan + 2)
	.line	234; main.c	stan.R = stan.G = 0xff;
	SETF	(_stan + 2), B
	BANKSEL	(_stan + 1)
	SETF	(_stan + 1), B
	.line	235; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	(_stan + 1)
	.line	236; main.c	stan.R = 0x00;
	CLRF	(_stan + 1), B
	BANKSEL	(_stan + 3)
	.line	237; main.c	stan.G = stan.B = 0xff;
	SETF	(_stan + 3), B
	BANKSEL	(_stan + 2)
	SETF	(_stan + 2), B
	.line	238; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	(_stan + 2)
	.line	239; main.c	stan.G = 0x00;
	CLRF	(_stan + 2), B
	BANKSEL	(_stan + 3)
	.line	240; main.c	stan.R = stan.B = 0xff;
	SETF	(_stan + 3), B
	BANKSEL	(_stan + 1)
	SETF	(_stan + 1), B
	.line	241; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	(_stan + 3)
	.line	243; main.c	stan.B = 0xff;
	SETF	(_stan + 3), B
	BANKSEL	(_stan + 2)
	.line	244; main.c	stan.R = stan.G = 0x00;
	CLRF	(_stan + 2), B
	BANKSEL	(_stan + 1)
	CLRF	(_stan + 1), B
	.line	245; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	(_stan + 1)
	.line	246; main.c	stan.R = 0xff;
	SETF	(_stan + 1), B
	BANKSEL	(_stan + 3)
	.line	247; main.c	stan.G = stan.B = 0x00;
	CLRF	(_stan + 3), B
	BANKSEL	(_stan + 2)
	CLRF	(_stan + 2), B
	.line	248; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BANKSEL	(_stan + 2)
	.line	249; main.c	stan.G = 0xff;
	SETF	(_stan + 2), B
	BANKSEL	(_stan + 3)
	.line	250; main.c	stan.R = stan.B = 0x00;
	CLRF	(_stan + 3), B
	BANKSEL	(_stan + 1)
	CLRF	(_stan + 1), B
	.line	251; main.c	_delay_ms( 500 );
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00207_DS_
	RETURN	

; ; Starting pCode block
S_main__timer1_start	code
_timer1_start:
	.line	152; main.c	void timer1_start()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	_stan
	.line	154; main.c	stan.timerH = 0xff;
	SETF	_stan, B
	.line	155; main.c	TMR1H = 0xff;
	MOVLW	0xff
	MOVWF	_TMR1H
	.line	156; main.c	TMR1L = 0x00;
	CLRF	_TMR1L
	.line	159; main.c	T1CON=0b00001101;
	MOVLW	0x0d
	MOVWF	_T1CON
	.line	189; main.c	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	BCF	_PIR1bits, 0
	.line	190; main.c	PIE1bits.TMR1IE = 1; /* timer0 enable interrupt */ 
	BSF	_PIE1bits, 0
	.line	191; main.c	IPR1bits.TMR1IP = 1; /* timer0 interrupt high/low */	
	BSF	_IPR1bits, 0
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__ports_init	code
_ports_init:
	.line	129; main.c	void ports_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	131; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	132; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	133; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	134; main.c	UCFGbits.UTRDIS = 1; // turn off USB module 
	BSF	_UCFGbits, 3
	.line	137; main.c	PORTA=0x00;
	CLRF	_PORTA
	.line	138; main.c	LATA=0x00;
	CLRF	_LATA
	.line	139; main.c	TRISA=0x00;
	CLRF	_TRISA
	.line	142; main.c	PORTB=0x00;
	CLRF	_PORTB
	.line	143; main.c	LATB=0x00;
	CLRF	_LATB
	.line	144; main.c	TRISB=0x00;
	CLRF	_TRISB
	.line	147; main.c	PORTC=0x00;
	CLRF	_PORTC
	.line	148; main.c	LATC=0x00;
	CLRF	_LATC
	.line	149; main.c	TRISC=0x00;
	CLRF	_TRISC
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__process	code
_process:
	.line	105; main.c	void process(__near unsigned char *msg, unsigned char cnt)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	109; main.c	switch ( msg[0] ) {
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	XORLW	0x48
	BZ	_00172_DS_
	MOVF	r0x02, W
	XORLW	0x78
	BZ	_00186_DS_
	BRA	_00175_DS_
_00186_DS_:
	.line	111; main.c	R = msg[2];
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	.line	112; main.c	B = msg[3];
	MOVF	r0x00, W
	ADDLW	0x03
	MOVWF	r0x03
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x04
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, FSR0H
	MOVFF	INDF0, r0x03
	.line	113; main.c	G = msg[4];
	MOVF	r0x00, W
	ADDLW	0x04
	MOVWF	r0x04
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x05
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	INDF0, r0x04
	.line	115; main.c	PIE1bits.TMR2IE = 0;
	BCF	_PIE1bits, 1
	.line	116; main.c	stan.R = R;
	MOVF	r0x02, W
	BANKSEL	(_stan + 1)
	MOVWF	(_stan + 1), B
	.line	117; main.c	stan.B = B;
	MOVF	r0x03, W
	BANKSEL	(_stan + 3)
	MOVWF	(_stan + 3), B
	.line	118; main.c	stan.G = G;
	MOVF	r0x04, W
	BANKSEL	(_stan + 2)
	MOVWF	(_stan + 2), B
	.line	119; main.c	PIE1bits.TMR2IE = 1;
	BSF	_PIE1bits, 1
	.line	121; main.c	break;
	BRA	_00175_DS_
_00172_DS_:
	.line	123; main.c	stan.timerH = msg[2];
	MOVLW	0x02
	ADDWF	r0x00, F
	BTFSC	STATUS, 0
	INCF	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x00
	MOVF	r0x00, W
	BANKSEL	_stan
	MOVWF	_stan, B
_00175_DS_:
	.line	126; main.c	}
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__low_interrupt	code
_low_interrupt:
	.line	99; main.c	static void low_interrupt(void) __interrupt(2)
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
	.line	101; main.c	}
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
	.line	53; main.c	static void high_interrupt(void) __interrupt(1)
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
	.line	60; main.c	TMR1H = stan.timerH;
	MOVFF	_stan, _TMR1H
	.line	62; main.c	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */
	BCF	_PIR1bits, 0
	BANKSEL	_high_interrupt_tmp_1_29
	.line	64; main.c	if ( tmp != tmp2 ) {
	MOVF	_high_interrupt_tmp_1_29, W, B
	BANKSEL	_high_interrupt_tmp2_1_29
	XORWF	_high_interrupt_tmp2_1_29, W, B
	BZ	_00106_DS_
	.line	65; main.c	LATB = tmp;
	MOVFF	_high_interrupt_tmp_1_29, _LATB
	.line	66; main.c	tmp2 = tmp;
	MOVFF	_high_interrupt_tmp_1_29, _high_interrupt_tmp2_1_29
	BRA	_00107_DS_
_00106_DS_:
	nop
	nop
	nop
	nop 
_00107_DS_:
	BANKSEL	_high_interrupt_cnt_1_29
	.line	74; main.c	if ( cnt == 0 ) {
	MOVF	_high_interrupt_cnt_1_29, W, B
	BNZ	_00121_DS_
	.line	75; main.c	R = stan.R;
	MOVFF	(_stan + 1), _high_interrupt_R_1_29
	.line	76; main.c	G = stan.G;
	MOVFF	(_stan + 2), _high_interrupt_G_1_29
	.line	77; main.c	B = stan.B;
	MOVFF	(_stan + 3), _high_interrupt_B_1_29
	BANKSEL	_high_interrupt_R_1_29
	.line	79; main.c	if ( R != 0 )
	MOVF	_high_interrupt_R_1_29, W, B
	BZ	_00109_DS_
	BANKSEL	_high_interrupt_tmp_1_29
	.line	80; main.c	tmp |= 0b10000000;
	BSF	_high_interrupt_tmp_1_29, 7, B
_00109_DS_:
	BANKSEL	_high_interrupt_G_1_29
	.line	81; main.c	if ( G != 0 )
	MOVF	_high_interrupt_G_1_29, W, B
	BZ	_00111_DS_
	BANKSEL	_high_interrupt_tmp_1_29
	.line	82; main.c	tmp |= 0b01000000;
	BSF	_high_interrupt_tmp_1_29, 6, B
_00111_DS_:
	BANKSEL	_high_interrupt_B_1_29
	.line	83; main.c	if ( B != 0 )
	MOVF	_high_interrupt_B_1_29, W, B
	BZ	_00122_DS_
	BANKSEL	_high_interrupt_tmp_1_29
	.line	84; main.c	tmp |= 0b00100000;
	BSF	_high_interrupt_tmp_1_29, 5, B
	BRA	_00122_DS_
_00121_DS_:
	BANKSEL	_high_interrupt_cnt_1_29
	.line	87; main.c	if ( cnt == R )
	MOVF	_high_interrupt_cnt_1_29, W, B
	BANKSEL	_high_interrupt_R_1_29
	XORWF	_high_interrupt_R_1_29, W, B
	BNZ	_00115_DS_
_00155_DS_:
	BANKSEL	_high_interrupt_tmp_1_29
	.line	88; main.c	tmp &= 0b01111111;
	BCF	_high_interrupt_tmp_1_29, 7, B
_00115_DS_:
	BANKSEL	_high_interrupt_cnt_1_29
	.line	89; main.c	if ( cnt == G )
	MOVF	_high_interrupt_cnt_1_29, W, B
	BANKSEL	_high_interrupt_G_1_29
	XORWF	_high_interrupt_G_1_29, W, B
	BNZ	_00117_DS_
_00158_DS_:
	BANKSEL	_high_interrupt_tmp_1_29
	.line	90; main.c	tmp &= 0b10111111;
	BCF	_high_interrupt_tmp_1_29, 6, B
_00117_DS_:
	BANKSEL	_high_interrupt_cnt_1_29
	.line	91; main.c	if ( cnt == B )
	MOVF	_high_interrupt_cnt_1_29, W, B
	BANKSEL	_high_interrupt_B_1_29
	XORWF	_high_interrupt_B_1_29, W, B
	BNZ	_00122_DS_
_00161_DS_:
	BANKSEL	_high_interrupt_tmp_1_29
	.line	92; main.c	tmp &= 0b11011111;
	BCF	_high_interrupt_tmp_1_29, 5, B
_00122_DS_:
	BANKSEL	_high_interrupt_cnt_1_29
	.line	95; main.c	cnt++;
	INCF	_high_interrupt_cnt_1_29, F, B
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



; Statistics:
; code size:	  880 (0x0370) bytes ( 0.67%)
;           	  440 (0x01b8) words
; udata size:	    6 (0x0006) bytes ( 0.33%)
; access size:	    6 (0x0006) bytes


	end
