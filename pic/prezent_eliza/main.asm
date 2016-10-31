;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:51 2015
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
	global	_state
	global	_timer_speed_H
	global	_timer_speed_L
	global	_serial_init
	global	_uart_process
	global	_process
	global	_clear
	global	_main
	global	_USB_init_in_configured_state

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__divuchar
	extern	__moduchar
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
	extern	_delay10ktcy
	extern	_usart_open
	extern	_usart_getc
	extern	_usart_putc
	extern	_USB_service

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
INDF0	equ	0xfef
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_timer_speed_H	db	0xf9
_timer_speed_L	db	0xff
_timer_interrupt_pos_1_33	db	0x00


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

udata_main_0	udata
_state	res	3

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
	.line	65; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	66; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	67; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	70; main.c	PORTA=0x00;
	CLRF	_PORTA
	.line	71; main.c	LATA=0x00;
	CLRF	_LATA
	.line	72; main.c	TRISA=0x00;
	CLRF	_TRISA
	.line	75; main.c	PORTB=0x00;
	CLRF	_PORTB
	.line	76; main.c	LATB=0x00;
	CLRF	_LATB
	.line	77; main.c	TRISB=0x00;
	CLRF	_TRISB
	.line	80; main.c	PORTC=0x00;
	CLRF	_PORTC
	.line	81; main.c	LATC=0x00;
	CLRF	_LATC
	.line	82; main.c	TRISC=0x00;
	CLRF	_TRISC
	.line	84; main.c	for(i=0; i<ROWS;i++)
	CLRF	r0x00
_00328_DS_:
	.line	85; main.c	state[i] = 0;
	MOVLW	LOW(_state)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_state)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	84; main.c	for(i=0; i<ROWS;i++)
	INCF	r0x00, F
	MOVLW	0x03
	SUBWF	r0x00, W
	BNC	_00328_DS_
	.line	245; main.c	serial_init();
	CALL	_serial_init
	.line	248; main.c	T1CON=0b10000001;
	MOVLW	0x81
	MOVWF	_T1CON
	.line	278; main.c	PIR1bits.TMR1IF = 0; /* timer0 clear interrupt flag */ 
	BCF	_PIR1bits, 0
	.line	279; main.c	PIE1bits.TMR1IE = 1; /* timer0 rnable interrupt */ 
	BSF	_PIE1bits, 0
	.line	280; main.c	IPR1bits.TMR1IP = 1; /* timer0 high interrupt */
	BSF	_IPR1bits, 0
	.line	281; main.c	TMR1H = 0xff;
	MOVLW	0xff
	MOVWF	_TMR1H
	.line	282; main.c	TMR1L = 0xf0;
	MOVLW	0xf0
	MOVWF	_TMR1L
	.line	288; main.c	PORTB = 0xff;
	MOVLW	0xff
	MOVWF	_PORTB
	.line	289; main.c	PORTC = 0xff;
	MOVLW	0xff
	MOVWF	_PORTC
	.line	290; main.c	delay10ktcy(10);
	MOVLW	0x0a
	CALL	_delay10ktcy
	.line	292; main.c	USB_init_in_configured_state();
	CALL	_USB_init_in_configured_state
	.line	293; main.c	USB_interrupt_priority_high();
	BSF	_IPR2bits, 5
	.line	294; main.c	USB_interrupt_enable();
	BSF	_PIE2bits, 5
	.line	296; main.c	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	BSF	_RCONbits, 7
	.line	297; main.c	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	BSF	_INTCONbits, 7
	.line	298; main.c	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	BSF	_OSCCONbits, 7
	.line	305; main.c	set_state_10(0x01, 0x01, 0x01);
	MOVLW	0x01
	BANKSEL	_state
	MOVWF	_state, B
	MOVLW	0x01
	BANKSEL	(_state + 1)
	MOVWF	(_state + 1), B
	MOVLW	0x01
	BANKSEL	(_state + 2)
	MOVWF	(_state + 2), B
	MOVLW	0x05
	CALL	_delay10ktcy
_00331_DS_:
	.line	306; main.c	for(i=0;;i++) {
	BRA	_00331_DS_
	RETURN	

; ; Starting pCode block
S_main__clear	code
_clear:
	.line	235; main.c	void clear() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	237; main.c	for(i=0;i<ROWS;i++)
	CLRF	r0x00
_00306_DS_:
	.line	238; main.c	state[i] = 0;
	MOVLW	LOW(_state)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_state)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	237; main.c	for(i=0;i<ROWS;i++)
	INCF	r0x00, F
	MOVLW	0x03
	SUBWF	r0x00, W
	BNC	_00306_DS_
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__process	code
_process:
	.line	222; main.c	void process(unsigned char *str)
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	225; main.c	unsigned char save = 3;
	MOVLW	0x03
	MOVWF	r0x03
	.line	226; main.c	for(i=0;str[i]!='\0';i++) {
	CLRF	r0x04
_00280_DS_:
	MOVF	r0x04, W
	ADDWF	r0x00, W
	MOVWF	r0x05
	CLRF	WREG
	ADDWFC	r0x01, W
	MOVWF	r0x06
	CLRF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x07
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, PRODL
	MOVF	r0x07, W
	CALL	__gptrget1
	MOVWF	r0x05
	MOVF	r0x05, W
	BZ	_00281_DS_
	.line	227; main.c	if ( save == 3 ) {
	MOVF	r0x03, W
	XORLW	0x03
	BNZ	_00274_DS_
	.line	228; main.c	save = str[i]-'0';
	MOVF	r0x05, W
	MOVWF	r0x06
	MOVLW	0xd0
	ADDWF	r0x06, W
	MOVWF	r0x03
	.line	229; main.c	continue;
	BRA	_00277_DS_
_00274_DS_:
	.line	231; main.c	toggle_bit(str[i]-'0', state[save]);
	MOVLW	LOW(_state)
	ADDWF	r0x03, W
	MOVWF	r0x06
	CLRF	r0x07
	MOVLW	HIGH(_state)
	ADDWFC	r0x07, F
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, FSR0H
	MOVFF	INDF0, r0x08
	MOVLW	0xd0
	ADDWF	r0x05, F
	MOVLW	0x01
	MOVWF	r0x09
	MOVF	r0x05, W
	BZ	_00297_DS_
	BN	_00300_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00298_DS_:
	RLCF	r0x09, F
	ADDLW	0x01
	BNC	_00298_DS_
	BRA	_00297_DS_
_00300_DS_:
	BCF	STATUS, 0
_00299_DS_:
	RRCF	r0x09, F
	ADDLW	0x01
	BNC	_00299_DS_
_00297_DS_:
	MOVF	r0x09, W
	MOVWF	r0x05
	MOVF	r0x05, W
	XORWF	r0x08, F
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, FSR0H
	MOVFF	r0x08, INDF0
	.line	232; main.c	save = 3;
	MOVLW	0x03
	MOVWF	r0x03
_00277_DS_:
	.line	226; main.c	for(i=0;str[i]!='\0';i++) {
	INCF	r0x04, F
	BRA	_00280_DS_
_00281_DS_:
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
S_main__low_interrupt	code
_low_interrupt:
	.line	210; main.c	static void low_interrupt(void) __interrupt(2)
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
_00264_DS_:
	.line	212; main.c	USB_interrupt_service();
	BCF	_PIR2bits, 5
	CALL	_USB_service
	BTFSC	_PIR2bits, 5
	BRA	_00264_DS_
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
	.line	201; main.c	static void high_interrupt(void) __interrupt(1)
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
	.line	203; main.c	if ( PIR1bits.TMR1IF ) {
	BTFSS	_PIR1bits, 0
	BRA	_00256_DS_
	.line	204; main.c	PIR1bits.TMR1IF = 0;
	BCF	_PIR1bits, 0
	.line	205; main.c	timer_interrupt();
	CALL	_timer_interrupt
_00256_DS_:
	.line	207; main.c	USB_interrupt_service();
	BCF	_PIR2bits, 5
	CALL	_USB_service
	BTFSC	_PIR2bits, 5
	BRA	_00256_DS_
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
S_main__timer_interrupt	code
_timer_interrupt:
	.line	161; main.c	static void timer_interrupt()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	.line	166; main.c	TMR1H = timer_speed_H;
	MOVFF	_timer_speed_H, _TMR1H
	.line	167; main.c	TMR1L = timer_speed_L;
	MOVFF	_timer_speed_L, _TMR1L
	.line	171; main.c	PORTB = 0x00;
	CLRF	_PORTB
	.line	172; main.c	PORTCbits.RC0 = 0;
	BCF	_PORTCbits, 0
	.line	173; main.c	PORTCbits.RC1 = 0;
	BCF	_PORTCbits, 1
	.line	174; main.c	PORTCbits.RC2 = 0;
	BCF	_PORTCbits, 2
	.line	175; main.c	PORTCbits.RC4 = 0;
	BCF	_PORTCbits, 4
	.line	176; main.c	PORTCbits.RC5 = 0;
	BCF	_PORTCbits, 5
	BANKSEL	_timer_interrupt_pos_1_33
	.line	179; main.c	if ( pos == 0 ) {
	MOVF	_timer_interrupt_pos_1_33, W, B
	BNZ	_00222_DS_
	.line	180; main.c	PORTCbits.RC0 = 1;
	BSF	_PORTCbits, 0
	BRA	_00223_DS_
_00222_DS_:
	BANKSEL	_timer_interrupt_pos_1_33
	.line	181; main.c	} else if ( pos == 1 ) {
	MOVF	_timer_interrupt_pos_1_33, W, B
	XORLW	0x01
	BNZ	_00219_DS_
	.line	182; main.c	PORTCbits.RC1 = 1;
	BSF	_PORTCbits, 1
	BRA	_00223_DS_
_00219_DS_:
	BANKSEL	_timer_interrupt_pos_1_33
	.line	183; main.c	} else if ( pos == 2 ) {
	MOVF	_timer_interrupt_pos_1_33, W, B
	XORLW	0x02
	BNZ	_00216_DS_
	.line	184; main.c	PORTCbits.RC2 = 1;
	BSF	_PORTCbits, 2
	BRA	_00223_DS_
_00216_DS_:
	BANKSEL	_timer_interrupt_pos_1_33
	.line	185; main.c	} else if (pos == 3) {
	MOVF	_timer_interrupt_pos_1_33, W, B
	XORLW	0x03
	BNZ	_00213_DS_
	.line	186; main.c	PORTCbits.RC4 = 1;
	BSF	_PORTCbits, 4
	BRA	_00223_DS_
_00213_DS_:
	.line	188; main.c	PORTCbits.RC5 = 1;
	BSF	_PORTCbits, 5
_00223_DS_:
	.line	192; main.c	PORTB = state[pos];
	MOVLW	LOW(_state)
	BANKSEL	_timer_interrupt_pos_1_33
	ADDWF	_timer_interrupt_pos_1_33, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVLW	HIGH(_state)
	ADDWFC	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, _PORTB
	BANKSEL	_timer_interrupt_pos_1_33
	.line	195; main.c	++pos;
	INCF	_timer_interrupt_pos_1_33, F, B
	.line	196; main.c	if ( pos >= ROWS )
	MOVLW	0x03
	BANKSEL	_timer_interrupt_pos_1_33
	SUBWF	_timer_interrupt_pos_1_33, W, B
	BNC	_00226_DS_
	BANKSEL	_timer_interrupt_pos_1_33
	.line	197; main.c	pos = 0;
	CLRF	_timer_interrupt_pos_1_33, B
_00226_DS_:
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__uart_process	code
_uart_process:
	.line	110; main.c	void uart_process()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	.line	114; main.c	byte = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
	.line	116; main.c	if ( byte == PR_CLEAR ) {
	MOVF	r0x00, W
	XORLW	0x02
	BNZ	_00145_DS_
	.line	117; main.c	for(byte2 = 0; byte2<ROWS; byte2++)
	CLRF	r0x01
_00148_DS_:
	.line	118; main.c	state[byte2] = 0;
	MOVLW	LOW(_state)
	ADDWF	r0x01, W
	MOVWF	r0x02
	CLRF	r0x03
	MOVLW	HIGH(_state)
	ADDWFC	r0x03, F
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	117; main.c	for(byte2 = 0; byte2<ROWS; byte2++)
	INCF	r0x01, F
	MOVLW	0x03
	SUBWF	r0x01, W
	BNC	_00148_DS_
	BRA	_00146_DS_
_00145_DS_:
	.line	120; main.c	byte2 = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x01
	.line	122; main.c	if ( byte2 != byte )
	MOVF	r0x01, W
	XORWF	r0x00, W
	BZ	_00190_DS_
	BRA	_00147_DS_
_00190_DS_:
	.line	126; main.c	switch(byte) {
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00192_DS_
	BRA	_00146_DS_
_00192_DS_:
	MOVF	r0x00, W
	XORLW	0x03
	BZ	_00130_DS_
	MOVF	r0x00, W
	XORLW	0x04
	BNZ	_00196_DS_
	BRA	_00136_DS_
_00196_DS_:
	MOVF	r0x00, W
	XORLW	0x05
	BNZ	_00198_DS_
	BRA	_00139_DS_
_00198_DS_:
	BRA	_00146_DS_
_00130_DS_:
	.line	128; main.c	byte = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
	.line	129; main.c	byte2 = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x01
	.line	130; main.c	if ( byte != byte2 )
	MOVF	r0x00, W
	XORWF	r0x01, W
	BZ	_00200_DS_
	BRA	_00147_DS_
_00200_DS_:
	.line	132; main.c	toggle_bit(byte%10, state[byte/10]);
	MOVLW	0x0a
	MOVWF	POSTDEC1
	MOVFF	r0x00, POSTDEC1
	CALL	__divuchar
	MOVWF	r0x02
	MOVF	PREINC1, W
	MOVF	PREINC1, W
	CLRF	r0x03
	MOVLW	LOW(_state)
	ADDWF	r0x02, F
	MOVLW	HIGH(_state)
	ADDWFC	r0x03, F
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x04
	MOVLW	0x0a
	MOVWF	POSTDEC1
	MOVFF	r0x00, POSTDEC1
	CALL	__moduchar
	MOVWF	r0x05
	MOVF	PREINC1, W
	MOVF	PREINC1, W
	MOVLW	0x01
	MOVWF	r0x06
	MOVF	r0x05, W
	BZ	_00201_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00202_DS_:
	RLCF	r0x06, F
	ADDLW	0x01
	BNC	_00202_DS_
_00201_DS_:
	MOVF	r0x06, W
	XORWF	r0x04, F
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	r0x04, INDF0
	.line	133; main.c	break;
	BRA	_00146_DS_
_00136_DS_:
	.line	135; main.c	byte = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
	.line	136; main.c	byte2 = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x01
	.line	137; main.c	if ( byte != byte2 )
	MOVF	r0x00, W
	XORWF	r0x01, W
	BNZ	_00147_DS_
	.line	139; main.c	timer_speed_H = byte;
	MOVFF	r0x00, _timer_speed_H
	.line	140; main.c	break;
	BRA	_00146_DS_
_00139_DS_:
	.line	142; main.c	byte = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
	.line	143; main.c	byte2 = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x01
	.line	144; main.c	if ( byte != byte2 )
	MOVF	r0x00, W
	XORWF	r0x01, W
	BNZ	_00147_DS_
	.line	146; main.c	timer_speed_L = byte;
	MOVFF	r0x00, _timer_speed_L
_00146_DS_:
	.line	153; main.c	usart_putc(PR_OK);
	MOVLW	0x06
	CALL	_usart_putc
	.line	154; main.c	usart_putc(PR_OK);
	MOVLW	0x06
	CALL	_usart_putc
	.line	155; main.c	return;
	BRA	_00150_DS_
_00147_DS_:
	.line	157; main.c	usart_putc(PR_ERR);
	MOVLW	0x07
	CALL	_usart_putc
	.line	158; main.c	usart_putc(PR_ERR);
	MOVLW	0x07
	CALL	_usart_putc
_00150_DS_:
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
S_main__serial_init	code
_serial_init:
	.line	87; main.c	void serial_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	97; main.c	8332
	MOVLW	0x20
	MOVWF	POSTDEC1
	MOVLW	0x8c
	MOVWF	POSTDEC1
	MOVLW	0x2c
	CALL	_usart_open
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	99; main.c	for(i=0xff;i;i--)
	MOVLW	0xff
	MOVWF	r0x00
_00120_DS_:
	NOP 
	.line	99; main.c	for(i=0xff;i;i--)
	DECFSZ	r0x00, F
	BRA	_00120_DS_
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__ports_init	code
_ports_init:
	.line	61; main.c	__once void ports_init()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	65; main.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
	.line	66; main.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
	.line	67; main.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
	.line	70; main.c	PORTA=0x00;
	CLRF	_PORTA
	.line	71; main.c	LATA=0x00;
	CLRF	_LATA
	.line	72; main.c	TRISA=0x00;
	CLRF	_TRISA
	.line	75; main.c	PORTB=0x00;
	CLRF	_PORTB
	.line	76; main.c	LATB=0x00;
	CLRF	_LATB
	.line	77; main.c	TRISB=0x00;
	CLRF	_TRISB
	.line	80; main.c	PORTC=0x00;
	CLRF	_PORTC
	.line	81; main.c	LATC=0x00;
	CLRF	_LATC
	.line	82; main.c	TRISC=0x00;
	CLRF	_TRISC
	.line	84; main.c	for(i=0; i<ROWS;i++)
	CLRF	r0x00
_00106_DS_:
	.line	85; main.c	state[i] = 0;
	MOVLW	LOW(_state)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_state)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVLW	0x00
	MOVWF	INDF0
	.line	84; main.c	for(i=0; i<ROWS;i++)
	INCF	r0x00, F
	MOVLW	0x03
	SUBWF	r0x00, W
	BNC	_00106_DS_
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1310 (0x051e) bytes ( 1.00%)
;           	  655 (0x028f) words
; udata size:	    3 (0x0003) bytes ( 0.17%)
; access size:	   10 (0x000a) bytes


	end
