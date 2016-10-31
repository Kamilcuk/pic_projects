;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:53 2015
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
	global	_InitPWM
	global	_SetPWMDutyCycle
	global	_ports_init
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
	extern	__delay_ms

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
	.line	83; main.c	licz = licz2 = stan = 0;
	CLRF	r0x00
	CLRF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	.line	85; main.c	ports_init();	
	CALL	_ports_init
	.line	86; main.c	InitPWM();
	CALL	_InitPWM
	.line	87; main.c	PORTB = 0xff;
	MOVLW	0xff
	MOVWF	_PORTB
	.line	88; main.c	_delay_ms(1000);
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVLW	0xe8
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00146_DS_:
	.line	91; main.c	if ( PORTBbits.RB0 == 1 ) {
	CLRF	r0x04
	BTFSC	_PORTBbits, 0
	INCF	r0x04, F
	MOVF	r0x04, W
	XORLW	0x01
	BNZ	_00143_DS_
	.line	93; main.c	licz = 0;
	CLRF	r0x02
	CLRF	r0x03
	.line	94; main.c	PORTB = 0x00;
	CLRF	_PORTB
	BRA	_00144_DS_
_00143_DS_:
	.line	96; main.c	PORTB = 0xff;
	MOVLW	0xff
	MOVWF	_PORTB
	.line	100; main.c	if ( licz <= w_ms(30*1000) ) {
	MOVLW	0x0b
	SUBWF	r0x03, W
	BNZ	_00173_DS_
	MOVLW	0xb9
	SUBWF	r0x02, W
_00173_DS_:
	BC	_00136_DS_
	.line	101; main.c	licz++;
	INFSNZ	r0x02, F
	INCF	r0x03, F
	BRA	_00144_DS_
_00136_DS_:
	.line	105; main.c	while ( PORTBbits.RB0 == 0 ) {
	BTFSC	_PORTBbits, 0
	BRA	_00138_DS_
	.line	108; main.c	licz2++;
	INFSNZ	r0x00, F
	INCF	r0x01, F
	.line	109; main.c	if ( licz2 <= w_ms(250) ) {
	MOVLW	0x00
	SUBWF	r0x01, W
	BNZ	_00174_DS_
	MOVLW	0x1a
	SUBWF	r0x00, W
_00174_DS_:
	BC	_00134_DS_
	.line	110; main.c	SetPWMDutyCycle(512);
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	111; main.c	PORTB = 0xff;
	MOVLW	0xff
	MOVWF	_PORTB
	BRA	_00135_DS_
_00134_DS_:
	.line	112; main.c	} else if ( licz2 <= w_ms(500) ) {
	MOVLW	0x00
	SUBWF	r0x01, W
	BNZ	_00175_DS_
	MOVLW	0x33
	SUBWF	r0x00, W
_00175_DS_:
	BC	_00131_DS_
	.line	113; main.c	PORTB = 0;
	CLRF	_PORTB
	.line	114; main.c	SetPWMDutyCycle(0); 
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00135_DS_
_00131_DS_:
	.line	116; main.c	licz2 = 0;
	CLRF	r0x00
	CLRF	r0x01
_00135_DS_:
	.line	119; main.c	_delay_ms(_step_ms);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00136_DS_
_00138_DS_:
	.line	123; main.c	licz = 0;
	CLRF	r0x02
	CLRF	r0x03
	.line	124; main.c	SetPWMDutyCycle(512);
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	125; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	126; main.c	SetPWMDutyCycle(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	127; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	128; main.c	SetPWMDutyCycle(512);
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	129; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	130; main.c	SetPWMDutyCycle(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	131; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	132; main.c	SetPWMDutyCycle(512);
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	133; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	134; main.c	SetPWMDutyCycle(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	135; main.c	_delay_ms(50);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x32
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00144_DS_:
	.line	139; main.c	_delay_ms(_step_ms);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	CALL	__delay_ms
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00146_DS_
	RETURN	

; ; Starting pCode block
S_main__ports_init	code
_ports_init:
	.line	48; main.c	void ports_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	50; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	51; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	52; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	53; main.c	UCFGbits.UTRDIS = 1; // turn off USB module 
	BSF	_UCFGbits, 3
	.line	56; main.c	PORTA=0x00;
	CLRF	_PORTA
	.line	57; main.c	LATA=0x00;
	CLRF	_LATA
	.line	58; main.c	TRISA=0x00;
	CLRF	_TRISA
	.line	61; main.c	PORTB=0x00;
	CLRF	_PORTB
	.line	62; main.c	LATB=0x00;
	CLRF	_LATB
	.line	63; main.c	TRISB=0x00;
	CLRF	_TRISB
	.line	66; main.c	PORTC=0x00;
	CLRF	_PORTC
	.line	67; main.c	LATC=0x00;
	CLRF	_LATC
	.line	68; main.c	TRISC=0x00;
	CLRF	_TRISC
	.line	70; main.c	TRISBbits.RB0 = 1;
	BSF	_TRISBbits, 0
	.line	71; main.c	TRISBbits.RB1 = 1;
	BSF	_TRISBbits, 1
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__low_interrupt	code
_low_interrupt:
	.line	44; main.c	static void low_interrupt(void) __interrupt(2)
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
	.line	46; main.c	}
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
	.line	40; main.c	static void high_interrupt(void) __interrupt(1)
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
	.line	42; main.c	}
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
S_main__SetPWMDutyCycle	code
_SetPWMDutyCycle:
	.line	26; ../include/pwm.c	void SetPWMDutyCycle(unsigned int DutyCycle)      // Give a value in between 0 and 1024 for DutyCycle
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	28; ../include/pwm.c	CCPR1L   = DutyCycle>>2;        	// Put MSB 8 bits in CCPR1L
	BCF	STATUS, 0
	RRCF	r0x01, W
	MOVWF	r0x03
	RRCF	r0x00, W
	MOVWF	r0x02
	BCF	STATUS, 0
	RRCF	r0x03, F
	RRCF	r0x02, F
	MOVF	r0x02, W
	MOVWF	_CCPR1L
	.line	29; ../include/pwm.c	CCP1CON &= 0xCF;                	// Make bit4 and 5 zero
	MOVLW	0xcf
	ANDWF	_CCP1CON, F
	.line	30; ../include/pwm.c	CCP1CON |= (0x30&(DutyCycle<<4));   // Assign Last 2 LSBs to CCP1CON
	SWAPF	r0x00, W
	ANDLW	0xf0
	MOVWF	r0x01
	MOVLW	0x30
	ANDWF	r0x01, W
	MOVWF	r0x00
	MOVF	r0x00, W
	IORWF	_CCP1CON, F
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__InitPWM	code
_InitPWM:
	.line	10; ../include/pwm.c	void InitPWM(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	12; ../include/pwm.c	TRISC  = 0;              // Make CCP1 pin as output
	CLRF	_TRISC
	.line	13; ../include/pwm.c	CCP1CON = 0x0C;           // Configure CCP1 module in PWM mode
	MOVLW	0x0c
	MOVWF	_CCP1CON
	.line	15; ../include/pwm.c	PR2   = 0xFF;             // Configure the Timer2 period
	MOVLW	0xff
	MOVWF	_PR2
	.line	16; ../include/pwm.c	T2CON = 0x03;            
	MOVLW	0x03
	MOVWF	_T2CON
	.line	19; ../include/pwm.c	SetPWMDutyCycle(0);       // Intialize the PWM to 0 duty cycle
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_SetPWMDutyCycle
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	21; ../include/pwm.c	T2CON |= 0x04;            // Enable the Timer2, hence enable the PWM.
	BSF	_T2CON, 2
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  750 (0x02ee) bytes ( 0.57%)
;           	  375 (0x0177) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    5 (0x0005) bytes


	end
