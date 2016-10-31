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
	CONFIG	IESO=ON,PWRT=ON,BOR=ON,BORV=3,VREGEN=ON,WDT=OFF,WDTPS=32768,MCLRE=ON,LPT1OSC=OFF,PBADEN=OFF,CCP2MX=OFF,STVREN=ON,LVP=OFF,DEBUG=OFF,CP0=OFF,CP1=OFF,CP2=OFF,CP3=OFF,CPB=OFF,CPD=OFF,WRT0=OFF,WRT1=OFF,WRT2=OFF,WRT3=OFF,WRTB=OFF,WRTC=OFF,WRTD=OFF,EBTR0=OFF,EBTR1=OFF,EBTR2=OFF,EBTR3=OFF,EBTRB=OFF
	CONFIG	XINST=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_stack
	global	_stack_end
	global	_wait
	global	_pro_init
	global	_main
	global	_buff1
	global	_buff2
	global	_buff3
	global	_buff4
	global	_buff5

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
	extern	_hd44780_recv
	extern	_hd44780_send
	extern	_hd44780_send_all
	extern	_USB_init
	extern	_USB_wait_for_configured_state
	extern	_USB_service

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
TBLPTRL	equ	0xff6
TBLPTRH	equ	0xff7
TBLPTRU	equ	0xff8
TABLAT	equ	0xff5
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
r0x05	res	1
r0x06	res	1
r0x07	res	1


ustat_main_00	udata	0X0300
_stack         	res	254
_stack_end     	res	1

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
	.line	219; main.c	hd44780_init();
	CALL	_hd44780_init
	.line	221; main.c	pro_init();
	CALL	_pro_init
	.line	223; main.c	USB_init();
	CALL	_USB_init
	.line	224; main.c	USB_wait_for_configured_state();
	CALL	_USB_wait_for_configured_state
	.line	226; main.c	USB_interrupt_priority_high();
	BSF	_IPR2bits, 5
	.line	227; main.c	USB_interrupt_enable();
	BSF	_PIE2bits, 5
	.line	229; main.c	RCONbits.IPEN = 1; /* Enable priority levels on interrupts */
	BSF	_RCONbits, 7
	.line	230; main.c	INTCONbits.GIEH = 1; /* Enables all high priority interrupts */
	BSF	_INTCONbits, 7
	.line	231; main.c	OSCCONbits.IDLEN = 1; /* Device enters Idle mode on SLEEP instruction (PRI_IDLE mode) */
	BSF	_OSCCONbits, 7
_00370_DS_:
	.line	235; main.c	for(i=0xff;i;i--)
	MOVLW	0xff
	MOVWF	r0x00
_00364_DS_:
	nop 
	.line	235; main.c	for(i=0xff;i;i--)
	DECFSZ	r0x00, F
	BRA	_00364_DS_
	sleep 
	BRA	_00370_DS_
	RETURN	

; ; Starting pCode block
S_main__pro_init	code
_pro_init:
	.line	146; main.c	void pro_init(void)
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
	.line	150; main.c	for(k=MAX_NUM_CONTROLLERS; k; k-- ) {
	MOVLW	0x08
	MOVWF	r0x00
_00224_DS_:
	.line	151; main.c	for(l=MAX_NUM_CONTROLLERS; l>=k; l--) {
	MOVLW	0x08
	MOVWF	r0x01
_00187_DS_:
	MOVF	r0x00, W
	SUBWF	r0x01, W
	BTFSS	STATUS, 0
	BRA	_00144_DS_
	.line	152; main.c	i=l-1;
	DECF	r0x01, W
	MOVWF	r0x02
	.line	154; main.c	hd44780_write_inst(i, HD44780_CLRDISP);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	155; main.c	hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) );
	MOVLW	0x80
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	157; main.c	write_str(i, buff1);
	CLRF	r0x03
_00178_DS_:
	MOVLW	LOW(_buff1)
	ADDWF	r0x03, W
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_buff1)
	ADDWFC	r0x05, F
	CLRF	r0x06
	MOVLW	UPPER(_buff1)
	ADDWFC	r0x06, F
	MOVFF	r0x04, TBLPTRL
	MOVFF	r0x05, TBLPTRH
	MOVFF	r0x06, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	INCF	r0x03, F
	MOVLW	0x0c
	SUBWF	r0x03, W
	BNC	_00178_DS_
	.line	159; main.c	hd44780_write_data(i, l-k+'0');
	MOVF	r0x00, W
	SUBWF	r0x01, W
	MOVWF	r0x03
	MOVLW	0x30
	ADDWF	r0x03, F
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	160; main.c	write_str(i, buff2);
	CLRF	r0x03
_00180_DS_:
	MOVLW	LOW(_buff2)
	ADDWF	r0x03, W
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_buff2)
	ADDWFC	r0x05, F
	CLRF	r0x06
	MOVLW	UPPER(_buff2)
	ADDWFC	r0x06, F
	MOVFF	r0x04, TBLPTRL
	MOVFF	r0x05, TBLPTRH
	MOVFF	r0x06, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	INCF	r0x03, F
	MOVLW	0x0a
	SUBWF	r0x03, W
	BNC	_00180_DS_
	.line	162; main.c	for(j=0; j<MAX_NUM_CONTROLLERS; j++)
	CLRF	r0x03
_00182_DS_:
	.line	163; main.c	hd44780_write_data(i, test_bit(j, lcddev.disabled)?'0':'1');
	MOVLW	0x01
	MOVWF	r0x04
	MOVLW	0x00
	MOVWF	r0x05
	MOVF	r0x03, W
	BZ	_00331_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00332_DS_:
	RLCF	r0x04, F
	RLCF	r0x05, F
	ADDLW	0x01
	BNC	_00332_DS_
_00331_DS_:
	MOVFF	_lcddev, r0x06
	CLRF	r0x07
	MOVF	r0x06, W
	ANDWF	r0x04, F
	MOVF	r0x07, W
	ANDWF	r0x05, F
	MOVF	r0x04, W
	IORWF	r0x05, W
	BZ	_00210_DS_
	MOVLW	0x30
	MOVWF	r0x04
	BRA	_00211_DS_
_00210_DS_:
	MOVLW	0x31
	MOVWF	r0x04
_00211_DS_:
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	162; main.c	for(j=0; j<MAX_NUM_CONTROLLERS; j++)
	INCF	r0x03, F
	MOVLW	0x08
	SUBWF	r0x03, W
	BNC	_00182_DS_
	.line	165; main.c	hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
	MOVLW	0xc0
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	166; main.c	write_str(i, buff3);
	CLRF	r0x03
_00184_DS_:
	MOVLW	LOW(_buff3)
	ADDWF	r0x03, W
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_buff3)
	ADDWFC	r0x05, F
	CLRF	r0x06
	MOVLW	UPPER(_buff3)
	ADDWFC	r0x06, F
	MOVFF	r0x04, TBLPTRL
	MOVFF	r0x05, TBLPTRH
	MOVFF	r0x06, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	INCF	r0x03, F
	MOVLW	0x28
	SUBWF	r0x03, W
	BNC	_00184_DS_
	.line	168; main.c	wait();
	CALL	_wait
	.line	151; main.c	for(l=MAX_NUM_CONTROLLERS; l>=k; l--) {
	DECF	r0x01, F
	BRA	_00187_DS_
_00144_DS_:
	.line	170; main.c	wait();
	CALL	_wait
	.line	150; main.c	for(k=MAX_NUM_CONTROLLERS; k; k-- ) {
	DECFSZ	r0x00, F
	BRA	_00224_DS_
	.line	173; main.c	wait();
	CALL	_wait
	.line	175; main.c	hd44780_write_inst_all(HD44780_CLRDISP);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	176; main.c	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 0 << 6 ) );
	MOVLW	0x80
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	177; main.c	write_str_all(buff1);
	CLRF	r0x00
_00191_DS_:
	MOVLW	LOW(_buff1)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_buff1)
	ADDWFC	r0x02, F
	CLRF	r0x03
	MOVLW	UPPER(_buff1)
	ADDWFC	r0x03, F
	MOVFF	r0x01, TBLPTRL
	MOVFF	r0x02, TBLPTRH
	MOVFF	r0x03, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x01
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	INCF	r0x00, F
	MOVLW	0x0c
	SUBWF	r0x00, W
	BNC	_00191_DS_
	.line	179; main.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	CLRF	r0x00
_00193_DS_:
	.line	180; main.c	hd44780_write_data(i, i+'0');
	MOVF	r0x00, W
	MOVWF	r0x01
	MOVLW	0x30
	ADDWF	r0x01, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	179; main.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00193_DS_
	.line	182; main.c	write_str_all(buff2);
	CLRF	r0x00
_00195_DS_:
	MOVLW	LOW(_buff2)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_buff2)
	ADDWFC	r0x02, F
	CLRF	r0x03
	MOVLW	UPPER(_buff2)
	ADDWFC	r0x03, F
	MOVFF	r0x01, TBLPTRL
	MOVFF	r0x02, TBLPTRH
	MOVFF	r0x03, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x01
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	INCF	r0x00, F
	MOVLW	0x0a
	SUBWF	r0x00, W
	BNC	_00195_DS_
	.line	184; main.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	CLRF	r0x00
_00197_DS_:
	.line	185; main.c	hd44780_write_data_all(test_bit(i, lcddev.disabled)?'0':'1');
	MOVLW	0x01
	MOVWF	r0x01
	MOVLW	0x00
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00338_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00339_DS_:
	RLCF	r0x01, F
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00339_DS_
_00338_DS_:
	MOVFF	_lcddev, r0x03
	CLRF	r0x04
	MOVF	r0x03, W
	ANDWF	r0x01, F
	MOVF	r0x04, W
	ANDWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x02, W
	BZ	_00212_DS_
	MOVLW	0x30
	MOVWF	r0x01
	BRA	_00213_DS_
_00212_DS_:
	MOVLW	0x31
	MOVWF	r0x01
_00213_DS_:
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	184; main.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00197_DS_
	.line	187; main.c	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
	MOVLW	0xc0
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	188; main.c	write_str_all(buff3);
	CLRF	r0x00
_00199_DS_:
	MOVLW	LOW(_buff3)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_buff3)
	ADDWFC	r0x02, F
	CLRF	r0x03
	MOVLW	UPPER(_buff3)
	ADDWFC	r0x03, F
	MOVFF	r0x01, TBLPTRL
	MOVFF	r0x02, TBLPTRH
	MOVFF	r0x03, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x01
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	INCF	r0x00, F
	MOVLW	0x28
	SUBWF	r0x00, W
	BNC	_00199_DS_
	.line	190; main.c	wait();
	CALL	_wait
	.line	192; main.c	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 1 << 6 ) );
	MOVLW	0xc0
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	193; main.c	for(i=0;i<MAX_NUM_CONTROLLERS;i++) {
	CLRF	r0x00
_00207_DS_:
	.line	194; main.c	if ( test_bit(i, lcddev.disabled) )
	MOVLW	0x01
	MOVWF	r0x01
	MOVLW	0x00
	MOVWF	r0x02
	MOVF	r0x00, W
	BZ	_00342_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00343_DS_:
	RLCF	r0x01, F
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00343_DS_
_00342_DS_:
	MOVFF	_lcddev, r0x03
	CLRF	r0x04
	MOVF	r0x03, W
	ANDWF	r0x01, F
	MOVF	r0x04, W
	ANDWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x02, W
	BTFSS	STATUS, 2
	BRA	_00176_DS_
	.line	197; main.c	for(j=0;j<sizeof(buff3)/sizeof(*buff3)-1; j++) {
	CLRF	r0x01
_00201_DS_:
	.line	198; main.c	k = hd44780_recv(i, RS_DATA);
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_hd44780_recv
	MOVWF	r0x02
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	199; main.c	if ( k != buff3[j] ) {
	MOVLW	LOW(_buff3)
	ADDWF	r0x01, W
	MOVWF	r0x03
	CLRF	r0x04
	MOVLW	HIGH(_buff3)
	ADDWFC	r0x04, F
	CLRF	r0x05
	MOVLW	UPPER(_buff3)
	ADDWFC	r0x05, F
	MOVFF	r0x03, TBLPTRL
	MOVFF	r0x04, TBLPTRH
	MOVFF	r0x05, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x03
	MOVF	r0x02, W
	XORWF	r0x03, W
	BNZ	_00164_DS_
	.line	197; main.c	for(j=0;j<sizeof(buff3)/sizeof(*buff3)-1; j++) {
	INCF	r0x01, F
	MOVLW	0x28
	SUBWF	r0x01, W
	BNC	_00201_DS_
_00164_DS_:
	.line	204; main.c	hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 34 );
	MOVLW	0xa2
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	205; main.c	if ( j != sizeof(buff3)/sizeof(*buff3)-1 ) {
	MOVF	r0x01, W
	XORLW	0x28
	BZ	_00244_DS_
	.line	206; main.c	write_str(i, buff4);
	CLRF	r0x01
_00203_DS_:
	MOVLW	LOW(_buff4)
	ADDWF	r0x01, W
	MOVWF	r0x02
	CLRF	r0x03
	MOVLW	HIGH(_buff4)
	ADDWFC	r0x03, F
	CLRF	r0x04
	MOVLW	UPPER(_buff4)
	ADDWFC	r0x04, F
	MOVFF	r0x02, TBLPTRL
	MOVFF	r0x03, TBLPTRH
	MOVFF	r0x04, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	INCF	r0x01, F
	MOVLW	0x04
	SUBWF	r0x01, W
	BNC	_00203_DS_
	BRA	_00175_DS_
_00244_DS_:
	.line	208; main.c	write_str(i, buff5);
	CLRF	r0x01
_00205_DS_:
	MOVLW	LOW(_buff5)
	ADDWF	r0x01, W
	MOVWF	r0x02
	CLRF	r0x03
	MOVLW	HIGH(_buff5)
	ADDWFC	r0x03, F
	CLRF	r0x04
	MOVLW	UPPER(_buff5)
	ADDWFC	r0x04, F
	MOVFF	r0x02, TBLPTRL
	MOVFF	r0x03, TBLPTRH
	MOVFF	r0x04, TBLPTRU
	TBLRD*+	
	MOVFF	TABLAT, r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_hd44780_send
	MOVLW	0x03
	ADDWF	FSR1L, F
	INCF	r0x01, F
	MOVLW	0x02
	SUBWF	r0x01, W
	BNC	_00205_DS_
_00175_DS_:
	.line	211; main.c	wait();
	CALL	_wait
_00176_DS_:
	.line	193; main.c	for(i=0;i<MAX_NUM_CONTROLLERS;i++) {
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BTFSS	STATUS, 0
	BRA	_00207_DS_
	.line	214; main.c	hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 0 );
	MOVLW	0x80
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
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
S_main__wait	code
_wait:
	.line	142; main.c	void wait() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	.line	144; main.c	for(a=0xff;a;a--)for(b=0xff;b;b--);
	MOVLW	0xff
	MOVWF	r0x00
	CLRF	r0x01
_00126_DS_:
	MOVLW	0xff
	MOVWF	r0x02
	CLRF	r0x03
_00121_DS_:
	MOVLW	0xff
	ADDWF	r0x02, F
	ADDWFC	r0x03, F
	MOVF	r0x02, W
	IORWF	r0x03, W
	BNZ	_00121_DS_
	MOVLW	0xff
	ADDWF	r0x00, F
	ADDWFC	r0x01, F
	MOVF	r0x00, W
	IORWF	r0x01, W
	BNZ	_00126_DS_
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__low_interrupt	code
_low_interrupt:
	.line	54; main.c	static void low_interrupt(void) __interrupt(2)
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
	.line	56; main.c	}
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
	.line	49; main.c	static void high_interrupt(void) __interrupt(1)
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
_00105_DS_:
	.line	51; main.c	USB_interrupt_service();
	BCF	_PIR2bits, 5
	CALL	_USB_service
	BTFSC	_PIR2bits, 5
	BRA	_00105_DS_
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
_buff1:
	DB	0x20, 0x4c, 0x43, 0x44, 0x20, 0x4e, 0x55, 0x4d, 0x45, 0x52, 0x3a, 0x20
	DB	0x00
; ; Starting pCode block for Ival
_buff2:
	DB	0x20, 0x45, 0x4e, 0x41, 0x42, 0x4c, 0x45, 0x44, 0x3a, 0x20, 0x00
; ; Starting pCode block for Ival
_buff3:
	DB	0x51, 0x57, 0x45, 0x72, 0x74, 0x79, 0x75, 0x69, 0x6f, 0x70, 0x5b, 0x5d
	DB	0x41, 0x53, 0x44, 0x46, 0x67, 0x68, 0x3f, 0x6b, 0x6c, 0x3b, 0x27, 0x7a
	DB	0x78, 0x63, 0xff, 0xf0, 0xaa, 0xc0, 0x2c, 0x2e, 0x2f, 0x60, 0x31, 0x32
	DB	0x33, 0x34, 0x35, 0x36, 0x00
; ; Starting pCode block for Ival
_buff4:
	DB	0x46, 0x41, 0x49, 0x4c, 0x00
; ; Starting pCode block for Ival
_buff5:
	DB	0x4f, 0x4b, 0x00


; Statistics:
; code size:	 1492 (0x05d4) bytes ( 1.14%)
;           	  746 (0x02ea) words
; udata size:	  255 (0x00ff) bytes (14.23%)
; access size:	    8 (0x0008) bytes


	end
