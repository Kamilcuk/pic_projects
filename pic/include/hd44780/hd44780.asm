;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:49 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"../include/hd44780/hd44780.c"
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
	extern	_delay100tcy
	extern	_delay10ktcy

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

udata_hd44780_0	udata
_lcddev	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
; ;ic:1:  _entry($19) :
; ;ic:2: 	proc _hd44780_init [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
S_hd44780__hd44780_init	code
_hd44780_init:
	.line	404; ../include/hd44780/hd44780.c	void hd44780_init(void) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
; ;ic:3: 	_ADCON0 [k2 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	200; ../include/hd44780/hd44780.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
; ;ic:4: 	_ADCON1 [k3 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0xf {const-unsigned-char literal}
	.line	201; ../include/hd44780/hd44780.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
; ;ic:5: 	_CMCON [k4 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x7 {const-unsigned-char literal}
	.line	202; ../include/hd44780/hd44780.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
; ;ic:6: 	_PORTA [k5 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	205; ../include/hd44780/hd44780.c	PORTA=0x00;
	CLRF	_PORTA
; ;ic:7: 	_LATA [k6 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	206; ../include/hd44780/hd44780.c	LATA=0x00;
	CLRF	_LATA
; ;ic:8: 	_TRISA [k7 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	207; ../include/hd44780/hd44780.c	TRISA=0x00;
	CLRF	_TRISA
; ;ic:9: 	_PORTB [k8 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	210; ../include/hd44780/hd44780.c	PORTB=0x00;
	CLRF	_PORTB
; ;ic:10: 	_LATB [k9 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	211; ../include/hd44780/hd44780.c	LATB=0x00;
	CLRF	_LATB
; ;ic:11: 	_TRISB [k10 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	212; ../include/hd44780/hd44780.c	TRISB=0x00;
	CLRF	_TRISB
; ;ic:12: 	_PORTC [k11 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	215; ../include/hd44780/hd44780.c	PORTC=0x00;
	CLRF	_PORTC
; ;ic:13: 	_LATC [k12 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	216; ../include/hd44780/hd44780.c	LATC=0x00;
	CLRF	_LATC
; ;ic:14: 	_TRISC [k13 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	217; ../include/hd44780/hd44780.c	TRISC=0x00;
	CLRF	_TRISC
; ;ic:15: 	_PORTB [k8 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	219; ../include/hd44780/hd44780.c	_hd44780_data_set_(0x00);
	CLRF	_PORTB
; ;ic:16: 	_TRISB [k10 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0xff {const-unsigned-char literal}
	.line	220; ../include/hd44780/hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
; ;ic:17: 	iTemp0 [k15 lr17:77 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] = &[_lcddev [k14 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{struct pic_device fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:18: 	*(iTemp0 [k15 lr17:77 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := 0x0 {const-unsigned-char literal}
	BANKSEL	_lcddev
	.line	407; ../include/hd44780/hd44780.c	lcddev_init();
	CLRF	_lcddev, B
; ;ic:19: 	iTemp11 [k30 lr19:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] := 0x0 {const-unsigned-char literal}
	.line	337; ../include/hd44780/hd44780.c	set_bit(i, lcddev.disabled);
	CLRF	r0x00
; ;ic:21:  _dobody_24_1($5) :
; ;ic:22: 	iTemp7 [k26 lr22:24 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp0 [k15 lr17:77 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:23: 	iTemp8 [k27 lr23:24 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = 0x1 {const-unsigned-char literal} << iTemp11 [k30 lr19:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ]
_00298_DS_:
	MOVLW	0x01
	MOVWF	r0x01
	MOVF	r0x00, W
	BZ	_00327_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00328_DS_:
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00328_DS_
; ;ic:24: 	iTemp9 [k28 lr24:25 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = iTemp7 [k26 lr22:24 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} | iTemp8 [k27 lr23:24 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
_00327_DS_:
	BANKSEL	_lcddev
	MOVF	_lcddev, W, B
	IORWF	r0x01, F
; ;ic:25: 	*(iTemp0 [k15 lr17:77 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := iTemp9 [k28 lr24:25 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
	MOVF	r0x01, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
; ;ic:26: 	iTemp11 [k30 lr19:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] = iTemp11 [k30 lr19:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] + 0x1 {const-unsigned-char literal}
	.line	336; ../include/hd44780/hd44780.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
; ;ic:27: 	iTemp12 [k31 lr27:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp11 [k30 lr19:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] < 0x8 {const-unsigned-char literal}
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00298_DS_
; ;ic:28: 	if iTemp12 [k31 lr27:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} != 0 goto _dobody_24_1($5)
; ;ic:29: 	send 0x32 {const-unsigned-char literal}{argreg = 1}
; ;ic:30: 	iTemp13 [k34 lr30:30 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k32 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	341; ../include/hd44780/hd44780.c	delay10ktcy(50);
	MOVLW	0x32
	CALL	_delay10ktcy
; ;ic:31: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:32: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:33: 	iTemp14 [k38 lr33:33 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	345; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:34: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:35: 	iTemp15 [k39 lr35:35 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k32 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	347; ../include/hd44780/hd44780.c	delay10ktcy(5);
	MOVLW	0x05
	CALL	_delay10ktcy
; ;ic:36: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:37: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:38: 	iTemp16 [k40 lr38:38 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	351; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:39: 	send 0x1 {const-unsigned-char literal}{argreg = 1}
; ;ic:40: 	iTemp17 [k41 lr40:40 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k32 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	353; ../include/hd44780/hd44780.c	delay10ktcy(1);
	MOVLW	0x01
	CALL	_delay10ktcy
; ;ic:41: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:42: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:43: 	iTemp18 [k42 lr43:43 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	357; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:44: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:45: 	iTemp19 [k45 lr45:45 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k43 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	364; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:46: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:47: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:48: 	iTemp20 [k46 lr48:48 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	368; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:49: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:50: 	iTemp21 [k47 lr50:50 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k43 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	369; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:51: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:52: 	send 0x8 {unsigned-char literal}{argreg = 2}
; ;ic:53: 	iTemp22 [k48 lr53:53 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	373; ../include/hd44780/hd44780.c	HD44780_DOOC_CURSORNOBLINK); /* display off */
	MOVLW	0x08
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:54: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:55: 	iTemp23 [k49 lr55:55 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k43 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	374; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:56: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:57: 	send 0x1 {const-unsigned-char literal}{argreg = 2}
; ;ic:58: 	iTemp24 [k50 lr58:58 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	376; ../include/hd44780/hd44780.c	HD44780_CLRDISP); /* display clear */
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:59: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:60: 	iTemp25 [k51 lr60:60 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k43 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	377; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:61: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:62: 	send 0x6 {unsigned-char literal}{argreg = 2}
; ;ic:63: 	iTemp26 [k52 lr63:63 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	379; ../include/hd44780/hd44780.c	HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:64: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:65: 	iTemp27 [k53 lr65:65 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k43 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	380; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:66: 	iTemp38 [k66 lr66:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] := 0x0 {const-unsigned-char literal}
	.line	384; ../include/hd44780/hd44780.c	clear_bit(i, lcddev.disabled);
	CLRF	r0x00
; ;ic:68:  _dobody_25_1($9) :
; ;ic:69: 	iTemp32 [k60 lr69:72 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp0 [k15 lr17:77 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:70: 	iTemp33 [k61 lr70:71 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = 0x1 {const-unsigned-char literal} << iTemp38 [k66 lr66:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ]
_00302_DS_:
	MOVLW	0x01
	MOVWF	r0x01
	MOVF	r0x00, W
	BZ	_00331_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00332_DS_:
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00332_DS_
; ;ic:71: 	iTemp34 [k62 lr71:73 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ] = not iTemp33 [k61 lr70:71 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
_00331_DS_:
	MOVF	r0x01, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x01
	RLCF	r0x01, F
; ;ic:72: 	iTemp35 [k63 lr72:73 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x02 ] = (char fixed)iTemp32 [k60 lr69:72 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev}
	BANKSEL	_lcddev
	MOVF	_lcddev, W, B
	MOVWF	r0x02
; ;ic:73: 	iTemp36 [k64 lr73:74 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ] = iTemp35 [k63 lr72:73 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x02 ] & iTemp34 [k62 lr71:73 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ]
	MOVF	r0x02, W
	ANDWF	r0x01, F
; ;ic:74: 	*(iTemp0 [k15 lr17:77 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := iTemp36 [k64 lr73:74 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ]
	MOVF	r0x01, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
; ;ic:75: 	iTemp38 [k66 lr66:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] = iTemp38 [k66 lr66:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] + 0x1 {const-unsigned-char literal}
	.line	383; ../include/hd44780/hd44780.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
; ;ic:76: 	iTemp39 [k67 lr76:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp38 [k66 lr66:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_init_i_4_60}[r0x00 ] < 0x8 {const-unsigned-char literal}
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00302_DS_
; ;ic:77: 	if iTemp39 [k67 lr76:77 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} != 0 goto _dobody_25_1($9)
; ;ic:78: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:79: 	send 0x38 {unsigned-char literal}{argreg = 2}
; ;ic:80: 	iTemp40 [k68 lr80:80 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	422; ../include/hd44780/hd44780.c	hd44780_write_inst_all( HD44780_FS_DATAWIDTH8BIT |
	MOVLW	0x38
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:81: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:82: 	send 0xe {unsigned-char literal}{argreg = 2}
; ;ic:83: 	iTemp41 [k69 lr83:83 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	425; ../include/hd44780/hd44780.c	hd44780_write_inst_all( HD44780_DOOC_DISPLAYON |
	MOVLW	0x0e
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:84: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:85: 	send 0x1 {const-unsigned-char literal}{argreg = 2}
; ;ic:86: 	iTemp42 [k70 lr86:86 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	428; ../include/hd44780/hd44780.c	hd44780_write_inst_all( HD44780_CLRDISP);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:87: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:88: 	send 0x6 {unsigned-char literal}{argreg = 2}
; ;ic:89: 	iTemp43 [k71 lr89:89 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k35 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	429; ../include/hd44780/hd44780.c	hd44780_write_inst_all( HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:90:  _return($18) :
; ;ic:91: 	eproc _hd44780_init [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
; ;ic:1:  _entry($14) :
; ;ic:2: 	proc _hd44780_initialize_by_instruction [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
S_hd44780__hd44780_initialize_by_instruction	code
_hd44780_initialize_by_instruction:
	.line	331; ../include/hd44780/hd44780.c	__once void hd44780_initialize_by_instruction(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
; ;ic:3: 	iTemp9 [k15 lr3:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] := 0x0 {const-unsigned-char literal}
	.line	337; ../include/hd44780/hd44780.c	set_bit(i, lcddev.disabled);
	CLRF	r0x00
; ;ic:5:  _dobody_24($1) :
; ;ic:6: 	iTemp1 [k5 lr6:62 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] = &[_lcddev [k4 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{struct pic_device fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:7: 	iTemp5 [k11 lr7:9 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp1 [k5 lr6:62 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:8: 	iTemp6 [k12 lr8:9 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = 0x1 {const-unsigned-char literal} << iTemp9 [k15 lr3:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ]
_00257_DS_:
	MOVLW	0x01
	MOVWF	r0x01
	MOVF	r0x00, W
	BZ	_00282_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00283_DS_:
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00283_DS_
; ;ic:9: 	iTemp7 [k13 lr9:10 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = iTemp5 [k11 lr7:9 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} | iTemp6 [k12 lr8:9 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
_00282_DS_:
	BANKSEL	_lcddev
	MOVF	_lcddev, W, B
	IORWF	r0x01, F
; ;ic:10: 	*(iTemp1 [k5 lr6:62 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := iTemp7 [k13 lr9:10 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
	MOVF	r0x01, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
; ;ic:11: 	iTemp9 [k15 lr3:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] = iTemp9 [k15 lr3:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] + 0x1 {const-unsigned-char literal}
	.line	336; ../include/hd44780/hd44780.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
; ;ic:12: 	iTemp10 [k16 lr12:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp9 [k15 lr3:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] < 0x8 {const-unsigned-char literal}
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00257_DS_
; ;ic:13: 	if iTemp10 [k16 lr12:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} != 0 goto _dobody_24($1)
; ;ic:14: 	send 0x32 {const-unsigned-char literal}{argreg = 1}
; ;ic:15: 	iTemp11 [k19 lr15:15 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k17 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	341; ../include/hd44780/hd44780.c	delay10ktcy(50);
	MOVLW	0x32
	CALL	_delay10ktcy
; ;ic:16: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:17: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:18: 	iTemp12 [k23 lr18:18 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	345; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:19: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:20: 	iTemp13 [k24 lr20:20 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k17 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	347; ../include/hd44780/hd44780.c	delay10ktcy(5);
	MOVLW	0x05
	CALL	_delay10ktcy
; ;ic:21: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:22: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:23: 	iTemp14 [k25 lr23:23 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	351; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:24: 	send 0x1 {const-unsigned-char literal}{argreg = 1}
; ;ic:25: 	iTemp15 [k26 lr25:25 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay10ktcy [k17 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	353; ../include/hd44780/hd44780.c	delay10ktcy(1);
	MOVLW	0x01
	CALL	_delay10ktcy
; ;ic:26: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:27: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:28: 	iTemp16 [k27 lr28:28 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	357; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:29: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:30: 	iTemp17 [k30 lr30:30 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k28 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	364; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:31: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:32: 	send 0x30 {unsigned-char literal}{argreg = 2}
; ;ic:33: 	iTemp18 [k31 lr33:33 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	368; ../include/hd44780/hd44780.c	HD44780_FS_5x8DOTS);
	MOVLW	0x30
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:34: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:35: 	iTemp19 [k32 lr35:35 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k28 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	369; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:36: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:37: 	send 0x8 {unsigned-char literal}{argreg = 2}
; ;ic:38: 	iTemp20 [k33 lr38:38 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	373; ../include/hd44780/hd44780.c	HD44780_DOOC_CURSORNOBLINK); /* display off */
	MOVLW	0x08
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:39: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:40: 	iTemp21 [k34 lr40:40 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k28 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	374; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:41: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:42: 	send 0x1 {const-unsigned-char literal}{argreg = 2}
; ;ic:43: 	iTemp22 [k35 lr43:43 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	376; ../include/hd44780/hd44780.c	HD44780_CLRDISP); /* display clear */
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:44: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:45: 	iTemp23 [k36 lr45:45 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k28 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	377; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:46: 	send 0x0 {const-unsigned-char literal}{argreg = 1}
; ;ic:47: 	send 0x6 {unsigned-char literal}{argreg = 2}
; ;ic:48: 	iTemp24 [k37 lr48:48 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _hd44780_send_all [k20 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	.line	379; ../include/hd44780/hd44780.c	HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_hd44780_send_all
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
; ;ic:49: 	send 0x5 {const-unsigned-char literal}{argreg = 1}
; ;ic:50: 	iTemp25 [k38 lr50:50 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call _delay100tcy [k28 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	380; ../include/hd44780/hd44780.c	NORMAL_DELAY();
	MOVLW	0x05
	CALL	_delay100tcy
; ;ic:51: 	iTemp36 [k51 lr51:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] := 0x0 {const-unsigned-char literal}
	.line	384; ../include/hd44780/hd44780.c	clear_bit(i, lcddev.disabled);
	CLRF	r0x00
; ;ic:53:  _dobody_25($5) :
; ;ic:54: 	iTemp30 [k45 lr54:57 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp1 [k5 lr6:62 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:55: 	iTemp31 [k46 lr55:56 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = 0x1 {const-unsigned-char literal} << iTemp36 [k51 lr51:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ]
_00261_DS_:
	MOVLW	0x01
	MOVWF	r0x01
	MOVF	r0x00, W
	BZ	_00286_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00287_DS_:
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00287_DS_
; ;ic:56: 	iTemp32 [k47 lr56:58 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ] = not iTemp31 [k46 lr55:56 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
_00286_DS_:
	MOVF	r0x01, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x01
	RLCF	r0x01, F
; ;ic:57: 	iTemp33 [k48 lr57:58 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x02 ] = (char fixed)iTemp30 [k45 lr54:57 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev}
	BANKSEL	_lcddev
	MOVF	_lcddev, W, B
	MOVWF	r0x02
; ;ic:58: 	iTemp34 [k49 lr58:59 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ] = iTemp33 [k48 lr57:58 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x02 ] & iTemp32 [k47 lr56:58 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ]
	MOVF	r0x02, W
	ANDWF	r0x01, F
; ;ic:59: 	*(iTemp1 [k5 lr6:62 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := iTemp34 [k49 lr58:59 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed}[r0x01 ]
	MOVF	r0x01, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
; ;ic:60: 	iTemp36 [k51 lr51:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] = iTemp36 [k51 lr51:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] + 0x1 {const-unsigned-char literal}
	.line	383; ../include/hd44780/hd44780.c	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
	INCF	r0x00, F
; ;ic:61: 	iTemp37 [k52 lr61:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp36 [k51 lr51:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_initialize_by_instruction_i_1_49}[r0x00 ] < 0x8 {const-unsigned-char literal}
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00261_DS_
; ;ic:62: 	if iTemp37 [k52 lr61:62 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} != 0 goto _dobody_25($5)
; ;ic:63:  _return($13) :
; ;ic:64: 	eproc _hd44780_initialize_by_instruction [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
; ;ic:1:  _entry($25) :
; ;ic:2: 	proc _hd44780_send_all [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
S_hd44780__hd44780_send_all	code
_hd44780_send_all:
	.line	289; ../include/hd44780/hd44780.c	void hd44780_send_all(u8 flags, u8 command)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
; ;ic:3: iTemp0 [k2 lr3:24 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_flags_1_39}[r0x00 ] = recv _hd44780_send_all [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
; ;ic:4: iTemp1 [k4 lr4:21 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_command_1_39}[r0x01 ] = recv _hd44780_send_all [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
; ;ic:5: 	iTemp3 [k9 lr5:19 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] = &[_lcddev [k8 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{struct pic_device fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:6: 	iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ] := 0x0 {const-unsigned-char literal}
	.line	296; ../include/hd44780/hd44780.c	for (i=0; i<MAX_NUM_CONTROLLERS ; i++) {
	CLRF	r0x02
; ;ic:8:  _forbody_1($22) :
; ;ic:9: 	iTemp5 [k12 lr9:11 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp3 [k9 lr5:19 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:10: 	iTemp7 [k14 lr10:12 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] = 0x1 {int literal} << iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ]
_00236_DS_:
	.line	297; ../include/hd44780/hd44780.c	if ( !test_bit(i, lcddev.disabled) )
	MOVLW	0x01
	MOVWF	r0x03
	MOVLW	0x00
	MOVWF	r0x04
	MOVF	r0x02, W
	BZ	_00250_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00251_DS_:
	RLCF	r0x03, F
	RLCF	r0x04, F
	ADDLW	0x01
	BNC	_00251_DS_
; ;ic:11: 	iTemp8 [k15 lr11:12 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x05 r0x06 ] = (int register)iTemp5 [k12 lr9:11 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev}
_00250_DS_:
	MOVFF	_lcddev, r0x05
	CLRF	r0x06
; ;ic:12: 	iTemp9 [k16 lr12:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] = iTemp8 [k15 lr11:12 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x05 r0x06 ] & iTemp7 [k14 lr10:12 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ]
	MOVF	r0x05, W
	ANDWF	r0x03, F
	MOVF	r0x06, W
	ANDWF	r0x04, F
; ;ic:13: 	if iTemp9 [k16 lr12:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] != 0 goto _forcontinue_1($23)
	MOVF	r0x03, W
	IORWF	r0x04, W
	BNZ	_00237_DS_
; ;ic:14: 	send iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ]{argreg = 1}
; ;ic:15: 	iTemp10 [k19 lr15:15 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call __hd44780_wait_for_ready_ [k17 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	.line	298; ../include/hd44780/hd44780.c	_hd44780_wait_for_ready_(i);
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	__hd44780_wait_for_ready_
	MOVF	POSTINC1, F
; ;ic:16:  _forcontinue_1($23) :
; ;ic:17: 	iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ] = iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ] + 0x1 {const-unsigned-char literal}
_00237_DS_:
	.line	296; ../include/hd44780/hd44780.c	for (i=0; i<MAX_NUM_CONTROLLERS ; i++) {
	INCF	r0x02, F
; ;ic:18: 	iTemp13 [k22 lr18:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp12 [k21 lr6:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_i_1_40}[r0x02 ] < 0x8 {const-unsigned-char literal}
	MOVLW	0x08
	SUBWF	r0x02, W
	BNC	_00236_DS_
; ;ic:19: 	if iTemp13 [k22 lr18:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} != 0 goto _forbody_1($22)
; ;ic:20: 	_TRISB [k24 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	303; ../include/hd44780/hd44780.c	_hd44780_data_forward_();
	CLRF	_TRISB
; ;ic:21: 	_PORTB [k25 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := iTemp1 [k4 lr4:21 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_command_1_39}[r0x01 ]
	.line	304; ../include/hd44780/hd44780.c	_hd44780_data_set_(command);
	MOVFF	r0x01, _PORTB
; ;ic:22: 	iTemp15 [k27 lr22:23 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] = &[_PORTCbits [k26 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:23: 	iTemp16 [k29 lr23:24 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] := iTemp15 [k27 lr22:23 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]
; ;ic:24: 	*(iTemp16 [k29 lr23:24 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]) := iTemp0 [k2 lr3:24 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_all_flags_1_39}[r0x00 ]
	.line	305; ../include/hd44780/hd44780.c	_hd44780_capable_(flags);
	MOVF	r0x00, W
	ANDLW	0x01
	RRNCF	WREG, W
	MOVWF	PRODH
	MOVF	_PORTCbits, W
	ANDLW	0x7f
	IORWF	PRODH, W
	MOVWF	_PORTCbits
; ;ic:25: inline
	nop 
; ;ic:26: inline
	nop 
; ;ic:27: inline
	nop 
; ;ic:28: inline
	nop 
; ;ic:29: 	iTemp17 [k30 lr29:30 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k26 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:30: 	iTemp18 [k32 lr30:31 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp17 [k30 lr29:30 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:31: 	*(iTemp18 [k32 lr30:31 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x1 {const-unsigned-char literal}
	.line	306; ../include/hd44780/hd44780.c	_hd44780_enable_all_(flags);
	BSF	_PORTCbits, 6
; ;ic:32: inline
	nop 
; ;ic:33: inline
	nop 
; ;ic:34: inline
	nop 
; ;ic:35: inline
	nop 
; ;ic:36: inline
	nop 
; ;ic:37: inline
	nop 
; ;ic:38: inline
	nop 
; ;ic:39: inline
	nop 
; ;ic:40: inline
	nop 
; ;ic:41: inline
	nop 
; ;ic:42: inline
	nop 
; ;ic:43: inline
	nop 
; ;ic:44: inline
	nop 
; ;ic:45: inline
	nop 
; ;ic:46: inline
	nop 
; ;ic:47: inline
	nop 
; ;ic:48: inline
	nop 
; ;ic:49: inline
	nop 
; ;ic:50: inline
	nop 
; ;ic:51: inline
	nop 
; ;ic:52: inline
	nop 
; ;ic:53: inline
	nop 
; ;ic:54: inline
	nop 
; ;ic:55: inline
	nop 
; ;ic:56: inline
	nop 
; ;ic:57: inline
	nop 
; ;ic:58: inline
	nop 
; ;ic:59: inline
	nop 
; ;ic:60: inline
	nop 
; ;ic:61: inline
	nop 
; ;ic:62: 	iTemp19 [k33 lr62:63 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k26 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:63: 	iTemp20 [k35 lr63:64 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp19 [k33 lr62:63 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:64: 	*(iTemp20 [k35 lr63:64 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x0 {const-unsigned-char literal}
	.line	307; ../include/hd44780/hd44780.c	_hd44780_disable_(flags);
	BCF	_PORTCbits, 6
; ;ic:65: inline
	nop 
; ;ic:66: inline
	nop 
; ;ic:67: inline
	nop 
; ;ic:68: inline
	nop 
; ;ic:69: inline
	nop 
; ;ic:70: inline
	nop 
; ;ic:71: inline
	nop 
; ;ic:72: inline
	nop 
; ;ic:73: inline
	nop 
; ;ic:74: inline
	nop 
; ;ic:75: inline
	nop 
; ;ic:76: inline
	nop 
; ;ic:77: inline
	nop 
; ;ic:78: inline
	nop 
; ;ic:79: inline
	nop 
; ;ic:80: inline
	nop 
; ;ic:81: inline
	nop 
; ;ic:82: inline
	nop 
; ;ic:83: inline
	nop 
; ;ic:84: inline
	nop 
; ;ic:85: inline
	nop 
; ;ic:86: inline
	nop 
; ;ic:87: inline
	nop 
; ;ic:88: inline
	nop 
; ;ic:89: inline
	nop 
; ;ic:90: inline
	nop 
; ;ic:91: inline
	nop 
; ;ic:92: inline
	nop 
; ;ic:93: inline
	nop 
; ;ic:94: inline
	nop 
; ;ic:95:  _return($24) :
; ;ic:96: 	eproc _hd44780_send_all [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed) fixed}
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
; ;ic:1:  _entry($24) :
; ;ic:2: 	proc _hd44780_send [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed, unsigned-char fixed) fixed}
S_hd44780__hd44780_send	code
_hd44780_send:
	.line	262; ../include/hd44780/hd44780.c	void hd44780_send(unsigned char ctrl_nr, unsigned char flags, unsigned char command)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
; ;ic:3: iTemp0 [k2 lr3:18 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_ctrl_nr_1_31}[r0x00 ] = recv _hd44780_send [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed, unsigned-char fixed) fixed}
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
; ;ic:4: iTemp1 [k4 lr4:24 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_flags_1_31}[r0x01 ] = recv _hd44780_send [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed, unsigned-char fixed) fixed}
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
; ;ic:5: iTemp2 [k6 lr5:21 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_command_1_31}[r0x02 ] = recv _hd44780_send [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed, unsigned-char fixed) fixed}
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
; ;ic:6: 	iTemp3 [k8 lr6:7 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} = iTemp0 [k2 lr3:18 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_ctrl_nr_1_31}[r0x00 ] > 0x8 {const-unsigned-char literal}
	.line	264; ../include/hd44780/hd44780.c	if ( ctrl_nr > MAX_NUM_CONTROLLERS ) return;
	MOVLW	0x09
	SUBWF	r0x00, W
	BNC	_00179_DS_
; ;ic:7: 	if iTemp3 [k8 lr6:7 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{char fixed} == 0 goto __iffalse_1($2)
; ;ic:8: 	ret
	BRA	_00200_DS_
; ;ic:9:  __iffalse_1($2) :
; ;ic:10: 	iTemp4 [k10 lr10:11 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] = &[_lcddev [k9 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{struct pic_device fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:11: 	iTemp6 [k13 lr11:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp4 [k10 lr10:11 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:12: 	iTemp8 [k15 lr12:14 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] = 0x1 {int literal} << iTemp0 [k2 lr3:18 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_ctrl_nr_1_31}[r0x00 ]
_00179_DS_:
	.line	265; ../include/hd44780/hd44780.c	if ( test_bit(ctrl_nr, lcddev.disabled) ) return;
	MOVLW	0x01
	MOVWF	r0x03
	MOVLW	0x00
	MOVWF	r0x04
	MOVF	r0x00, W
	BZ	_00209_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00210_DS_:
	RLCF	r0x03, F
	RLCF	r0x04, F
	ADDLW	0x01
	BNC	_00210_DS_
; ;ic:13: 	iTemp9 [k16 lr13:14 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x05 r0x06 ] = (int register)iTemp6 [k13 lr11:13 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev}
_00209_DS_:
	MOVFF	_lcddev, r0x05
	CLRF	r0x06
; ;ic:14: 	iTemp10 [k17 lr14:15 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] = iTemp9 [k16 lr13:14 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x05 r0x06 ] & iTemp8 [k15 lr12:14 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ]
	MOVF	r0x05, W
	ANDWF	r0x03, F
	MOVF	r0x06, W
	ANDWF	r0x04, F
; ;ic:15: 	if iTemp10 [k17 lr14:15 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{int fixed}[r0x03 r0x04 ] == 0 goto __iffalse_2($4)
	MOVF	r0x03, W
	IORWF	r0x04, W
	BZ	_00181_DS_
; ;ic:16: 	ret
	BRA	_00200_DS_
; ;ic:17:  __iffalse_2($4) :
; ;ic:18: 	send iTemp0 [k2 lr3:18 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_ctrl_nr_1_31}[r0x00 ]{argreg = 1}
; ;ic:19: 	iTemp11 [k20 lr19:19 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void fixed} = call __hd44780_wait_for_ready_ [k18 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
_00181_DS_:
	.line	267; ../include/hd44780/hd44780.c	_hd44780_wait_for_ready_(ctrl_nr);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	__hd44780_wait_for_ready_
	MOVF	POSTINC1, F
; ;ic:20: 	_TRISB [k22 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	271; ../include/hd44780/hd44780.c	_hd44780_data_forward_();
	CLRF	_TRISB
; ;ic:21: 	_PORTB [k23 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := iTemp2 [k6 lr5:21 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_command_1_31}[r0x02 ]
	.line	272; ../include/hd44780/hd44780.c	_hd44780_data_set_(command);
	MOVFF	r0x02, _PORTB
; ;ic:22: 	iTemp13 [k25 lr22:23 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] = &[_PORTCbits [k24 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:23: 	iTemp14 [k27 lr23:24 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] := iTemp13 [k25 lr22:23 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]
; ;ic:24: 	*(iTemp14 [k27 lr23:24 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]) := iTemp1 [k4 lr4:24 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _hd44780_send_flags_1_31}[r0x01 ]
	.line	273; ../include/hd44780/hd44780.c	_hd44780_capable_(flags);
	MOVF	r0x01, W
	ANDLW	0x01
	RRNCF	WREG, W
	MOVWF	PRODH
	MOVF	_PORTCbits, W
	ANDLW	0x7f
	IORWF	PRODH, W
	MOVWF	_PORTCbits
; ;ic:25: inline
	nop 
; ;ic:26: inline
	nop 
; ;ic:27: inline
	nop 
; ;ic:28: inline
	nop 
; ;ic:29: 	iTemp15 [k28 lr29:30 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k24 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:30: 	iTemp16 [k30 lr30:31 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp15 [k28 lr29:30 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:31: 	*(iTemp16 [k30 lr30:31 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x1 {const-unsigned-char literal}
	.line	274; ../include/hd44780/hd44780.c	_hd44780_enable_(flags, ctrl_nr);
	BSF	_PORTCbits, 6
; ;ic:32: inline
	nop 
; ;ic:33: inline
	nop 
; ;ic:34: inline
	nop 
; ;ic:35: inline
	nop 
; ;ic:36: inline
	nop 
; ;ic:37: inline
	nop 
; ;ic:38: inline
	nop 
; ;ic:39: inline
	nop 
; ;ic:40: inline
	nop 
; ;ic:41: inline
	nop 
; ;ic:42: inline
	nop 
; ;ic:43: inline
	nop 
; ;ic:44: inline
	nop 
; ;ic:45: inline
	nop 
; ;ic:46: inline
	nop 
; ;ic:47: inline
	nop 
; ;ic:48: inline
	nop 
; ;ic:49: inline
	nop 
; ;ic:50: inline
	nop 
; ;ic:51: inline
	nop 
; ;ic:52: inline
	nop 
; ;ic:53: inline
	nop 
; ;ic:54: inline
	nop 
; ;ic:55: inline
	nop 
; ;ic:56: inline
	nop 
; ;ic:57: inline
	nop 
; ;ic:58: inline
	nop 
; ;ic:59: inline
	nop 
; ;ic:60: inline
	nop 
; ;ic:61: inline
	nop 
; ;ic:62: 	iTemp17 [k31 lr62:63 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k24 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:63: 	iTemp18 [k33 lr63:64 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp17 [k31 lr62:63 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:64: 	*(iTemp18 [k33 lr63:64 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x0 {const-unsigned-char literal}
	.line	275; ../include/hd44780/hd44780.c	_hd44780_disable_(flags);
	BCF	_PORTCbits, 6
; ;ic:65: inline
	nop 
; ;ic:66: inline
	nop 
; ;ic:67: inline
	nop 
; ;ic:68: inline
	nop 
; ;ic:69: inline
	nop 
; ;ic:70: inline
	nop 
; ;ic:71: inline
	nop 
; ;ic:72: inline
	nop 
; ;ic:73: inline
	nop 
; ;ic:74: inline
	nop 
; ;ic:75: inline
	nop 
; ;ic:76: inline
	nop 
; ;ic:77: inline
	nop 
; ;ic:78: inline
	nop 
; ;ic:79: inline
	nop 
; ;ic:80: inline
	nop 
; ;ic:81: inline
	nop 
; ;ic:82: inline
	nop 
; ;ic:83: inline
	nop 
; ;ic:84: inline
	nop 
; ;ic:85: inline
	nop 
; ;ic:86: inline
	nop 
; ;ic:87: inline
	nop 
; ;ic:88: inline
	nop 
; ;ic:89: inline
	nop 
; ;ic:90: inline
	nop 
; ;ic:91: inline
	nop 
; ;ic:92: inline
	nop 
; ;ic:93: inline
	nop 
; ;ic:94: inline
	nop 
; ;ic:95:  _return($23) :
; ;ic:96: 	eproc _hd44780_send [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed, unsigned-char fixed, unsigned-char fixed) fixed}
_00200_DS_:
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
; ;ic:1:  _entry($2) :
; ;ic:2: 	proc _hd44780_recv [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char function ( unsigned-char fixed, unsigned-char fixed) fixed}
S_hd44780__hd44780_recv	code
_hd44780_recv:
	.line	254; ../include/hd44780/hd44780.c	unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
; ;ic:3: 	ret 0x1 {const-unsigned-char literal}
	.line	258; ../include/hd44780/hd44780.c	return 1;
	MOVLW	0x01
; ;ic:4:  _return($1) :
; ;ic:5: 	eproc _hd44780_recv [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char function ( unsigned-char fixed, unsigned-char fixed) fixed}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
; ;ic:1:  _entry($2) :
; ;ic:2: 	proc _hd44780_init_port [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
S_hd44780__hd44780_init_port	code
_hd44780_init_port:
	.line	198; ../include/hd44780/hd44780.c	__once void hd44780_init_port(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
; ;ic:3: 	_ADCON0 [k2 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	200; ../include/hd44780/hd44780.c	ADCON0=0x00; // turn off analog to digital conversion module
	CLRF	_ADCON0
; ;ic:4: 	_ADCON1 [k3 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0xf {const-unsigned-char literal}
	.line	201; ../include/hd44780/hd44780.c	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	MOVLW	0x0f
	MOVWF	_ADCON1
; ;ic:5: 	_CMCON [k4 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x7 {const-unsigned-char literal}
	.line	202; ../include/hd44780/hd44780.c	CMCON=0x07; // turn off comparator module
	MOVLW	0x07
	MOVWF	_CMCON
; ;ic:6: 	_PORTA [k5 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	205; ../include/hd44780/hd44780.c	PORTA=0x00;
	CLRF	_PORTA
; ;ic:7: 	_LATA [k6 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	206; ../include/hd44780/hd44780.c	LATA=0x00;
	CLRF	_LATA
; ;ic:8: 	_TRISA [k7 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	207; ../include/hd44780/hd44780.c	TRISA=0x00;
	CLRF	_TRISA
; ;ic:9: 	_PORTB [k8 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	210; ../include/hd44780/hd44780.c	PORTB=0x00;
	CLRF	_PORTB
; ;ic:10: 	_LATB [k9 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	211; ../include/hd44780/hd44780.c	LATB=0x00;
	CLRF	_LATB
; ;ic:11: 	_TRISB [k10 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	212; ../include/hd44780/hd44780.c	TRISB=0x00;
	CLRF	_TRISB
; ;ic:12: 	_PORTC [k11 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	215; ../include/hd44780/hd44780.c	PORTC=0x00;
	CLRF	_PORTC
; ;ic:13: 	_LATC [k12 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	216; ../include/hd44780/hd44780.c	LATC=0x00;
	CLRF	_LATC
; ;ic:14: 	_TRISC [k13 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	217; ../include/hd44780/hd44780.c	TRISC=0x00;
	CLRF	_TRISC
; ;ic:15: 	_PORTB [k8 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0x0 {const-unsigned-char literal}
	.line	219; ../include/hd44780/hd44780.c	_hd44780_data_set_(0x00);
	CLRF	_PORTB
; ;ic:16: 	_TRISB [k10 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0xff {const-unsigned-char literal}
	.line	220; ../include/hd44780/hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
; ;ic:17:  _return($1) :
; ;ic:18: 	eproc _hd44780_init_port [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( ) fixed}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
; ;ic:1:  _entry($44) :
; ;ic:2: 	proc __hd44780_wait_for_ready_ [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
S_hd44780___hd44780_wait_for_ready_	code
__hd44780_wait_for_ready_:
	.line	167; ../include/hd44780/hd44780.c	static void _hd44780_wait_for_ready_(unsigned char ctrl_nr)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
; ;ic:3: iTemp0 [k2 lr3:158 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ __hd44780_wait_for_ready__ctrl_nr_1_11}[r0x00 ] = recv __hd44780_wait_for_ready_ [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
; ;ic:4: 	_TRISB [k4 lr0:0 so:0]{ ia1 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-char sfr} := 0xff {const-unsigned-char literal}
	.line	172; ../include/hd44780/hd44780.c	_hd44780_data_reverse_();
	MOVLW	0xff
	MOVWF	_TRISB
; ;ic:5: 	iTemp1 [k6 lr5:6 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] = &[_PORTCbits [k5 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:6: 	iTemp2 [k8 lr6:7 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] := iTemp1 [k6 lr5:6 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]
; ;ic:7: 	*(iTemp2 [k8 lr6:7 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]) := 0x0 {unsigned-char literal}
	.line	173; ../include/hd44780/hd44780.c	_hd44780_capable_(RW_READ | RS_INST);
	BCF	_PORTCbits, 7
; ;ic:8: inline
	nop 
; ;ic:9: inline
	nop 
; ;ic:10: inline
	nop 
; ;ic:11: inline
	nop 
; ;ic:12: 	iTemp3 [k9 lr12:13 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k5 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:13: 	iTemp4 [k11 lr13:14 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp3 [k9 lr12:13 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:14: 	*(iTemp4 [k11 lr13:14 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x1 {const-unsigned-char literal}
	.line	174; ../include/hd44780/hd44780.c	_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	BSF	_PORTCbits, 6
; ;ic:15: inline
	nop 
; ;ic:16: inline
	nop 
; ;ic:17: inline
	nop 
; ;ic:18: inline
	nop 
; ;ic:19: inline
	nop 
; ;ic:20: inline
	nop 
; ;ic:21: inline
	nop 
; ;ic:22: inline
	nop 
; ;ic:23: inline
	nop 
; ;ic:24: inline
	nop 
; ;ic:25: inline
	nop 
; ;ic:26: inline
	nop 
; ;ic:27: inline
	nop 
; ;ic:28: inline
	nop 
; ;ic:29: inline
	nop 
; ;ic:30: inline
	nop 
; ;ic:31: inline
	nop 
; ;ic:32: inline
	nop 
; ;ic:33: inline
	nop 
; ;ic:34: inline
	nop 
; ;ic:35: inline
	nop 
; ;ic:36: inline
	nop 
; ;ic:37: inline
	nop 
; ;ic:38: inline
	nop 
; ;ic:39: inline
	nop 
; ;ic:40: inline
	nop 
; ;ic:41: inline
	nop 
; ;ic:42: inline
	nop 
; ;ic:43: inline
	nop 
; ;ic:44: inline
	nop 
; ;ic:45: 	iTemp13 [k25 lr45:155 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-int fixed}{ sir@ __hd44780_wait_for_ready__count_1_12}[r0x01 r0x02 ] := 0xffff {const-unsigned-int literal}
	.line	175; ../include/hd44780/hd44780.c	for ( count = BUSYFLAG_STUCK; count && _hd44780_data_get_busyflag_(); --count ) {
	MOVLW	0xff
	MOVWF	r0x01
	MOVWF	r0x02
; ;ic:47:  _forcond_0($41) :
; ;ic:48: 	if iTemp13 [k25 lr45:155 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-int fixed}{ sir@ __hd44780_wait_for_ready__count_1_12}[r0x01 r0x02 ] == 0 goto _dobody_9($31)
_00145_DS_:
	MOVF	r0x01, W
	IORWF	r0x02, W
	BTFSC	STATUS, 2
	BRA	_00135_DS_
; ;ic:49: 	iTemp6 [k15 lr49:50 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] = &[_PORTBbits [k14 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000122 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:50: 	iTemp7 [k17 lr50:51 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] := iTemp6 [k15 lr49:50 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat]
; ;ic:51: 	iTemp8 [k18 lr51:52 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} fixed}[bad ] = @[iTemp7 [k17 lr50:51 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
	BTFSS	_PORTBbits, 7
	BRA	_00135_DS_
; ;ic:52: 	if iTemp8 [k18 lr51:52 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-unsigned-bitfield {7,1} fixed}[bad ] == 0 goto _dobody_9($31)
; ;ic:53: 	iTemp9 [k19 lr53:54 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k5 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:54: 	iTemp10 [k21 lr54:55 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp9 [k19 lr53:54 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:55: 	*(iTemp10 [k21 lr54:55 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x0 {const-unsigned-char literal}
	.line	176; ../include/hd44780/hd44780.c	_hd44780_disable_(RW_READ | RS_INST);
	BCF	_PORTCbits, 6
; ;ic:56: inline
	nop 
; ;ic:57: inline
	nop 
; ;ic:58: inline
	nop 
; ;ic:59: inline
	nop 
; ;ic:60: inline
	nop 
; ;ic:61: inline
	nop 
; ;ic:62: inline
	nop 
; ;ic:63: inline
	nop 
; ;ic:64: inline
	nop 
; ;ic:65: inline
	nop 
; ;ic:66: inline
	nop 
; ;ic:67: inline
	nop 
; ;ic:68: inline
	nop 
; ;ic:69: inline
	nop 
; ;ic:70: inline
	nop 
; ;ic:71: inline
	nop 
; ;ic:72: inline
	nop 
; ;ic:73: inline
	nop 
; ;ic:74: inline
	nop 
; ;ic:75: inline
	nop 
; ;ic:76: inline
	nop 
; ;ic:77: inline
	nop 
; ;ic:78: inline
	nop 
; ;ic:79: inline
	nop 
; ;ic:80: inline
	nop 
; ;ic:81: inline
	nop 
; ;ic:82: inline
	nop 
; ;ic:83: inline
	nop 
; ;ic:84: inline
	nop 
; ;ic:85: inline
	nop 
; ;ic:86: 	iTemp11 [k22 lr86:87 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k5 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:87: 	iTemp12 [k24 lr87:88 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp11 [k22 lr86:87 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:88: 	*(iTemp12 [k24 lr87:88 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x1 {const-unsigned-char literal}
	.line	180; ../include/hd44780/hd44780.c	_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	BSF	_PORTCbits, 6
; ;ic:89: inline
	nop 
; ;ic:90: inline
	nop 
; ;ic:91: inline
	nop 
; ;ic:92: inline
	nop 
; ;ic:93: inline
	nop 
; ;ic:94: inline
	nop 
; ;ic:95: inline
	nop 
; ;ic:96: inline
	nop 
; ;ic:97: inline
	nop 
; ;ic:98: inline
	nop 
; ;ic:99: inline
	nop 
; ;ic:100: inline
	nop 
; ;ic:101: inline
	nop 
; ;ic:102: inline
	nop 
; ;ic:103: inline
	nop 
; ;ic:104: inline
	nop 
; ;ic:105: inline
	nop 
; ;ic:106: inline
	nop 
; ;ic:107: inline
	nop 
; ;ic:108: inline
	nop 
; ;ic:109: inline
	nop 
; ;ic:110: inline
	nop 
; ;ic:111: inline
	nop 
; ;ic:112: inline
	nop 
; ;ic:113: inline
	nop 
; ;ic:114: inline
	nop 
; ;ic:115: inline
	nop 
; ;ic:116: inline
	nop 
; ;ic:117: inline
	nop 
; ;ic:118: inline
	nop 
; ;ic:119: 	iTemp13 [k25 lr45:155 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-int fixed}{ sir@ __hd44780_wait_for_ready__count_1_12}[r0x01 r0x02 ] = iTemp13 [k25 lr45:155 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-int fixed}{ sir@ __hd44780_wait_for_ready__count_1_12}[r0x01 r0x02 ] - 0x1 {const-unsigned-char literal}
	.line	175; ../include/hd44780/hd44780.c	for ( count = BUSYFLAG_STUCK; count && _hd44780_data_get_busyflag_(); --count ) {
	MOVLW	0xff
	ADDWF	r0x01, F
	ADDWFC	r0x02, F
; ;ic:120: 	 goto _forcond_0($41)
	BRA	_00145_DS_
; ;ic:121:  _dobody_9($31) :
; ;ic:122: 	iTemp14 [k26 lr122:123 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] = &[_PORTCbits [k5 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{volatile-struct __00000129 fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:123: 	iTemp15 [k28 lr123:124 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat] := iTemp14 [k26 lr122:123 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]
; ;ic:124: 	*(iTemp15 [k28 lr123:124 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{volatile-unsigned-bitfield {6,1} near* fixed}[remat]) := 0x0 {const-unsigned-char literal}
_00135_DS_:
	.line	182; ../include/hd44780/hd44780.c	_hd44780_disable_(RW_READ | RS_INST);
	BCF	_PORTCbits, 6
; ;ic:125: inline
	nop 
; ;ic:126: inline
	nop 
; ;ic:127: inline
	nop 
; ;ic:128: inline
	nop 
; ;ic:129: inline
	nop 
; ;ic:130: inline
	nop 
; ;ic:131: inline
	nop 
; ;ic:132: inline
	nop 
; ;ic:133: inline
	nop 
; ;ic:134: inline
	nop 
; ;ic:135: inline
	nop 
; ;ic:136: inline
	nop 
; ;ic:137: inline
	nop 
; ;ic:138: inline
	nop 
; ;ic:139: inline
	nop 
; ;ic:140: inline
	nop 
; ;ic:141: inline
	nop 
; ;ic:142: inline
	nop 
; ;ic:143: inline
	nop 
; ;ic:144: inline
	nop 
; ;ic:145: inline
	nop 
; ;ic:146: inline
	nop 
; ;ic:147: inline
	nop 
; ;ic:148: inline
	nop 
; ;ic:149: inline
	nop 
; ;ic:150: inline
	nop 
; ;ic:151: inline
	nop 
; ;ic:152: inline
	nop 
; ;ic:153: inline
	nop 
; ;ic:154: inline
	nop 
; ;ic:155: 	if iTemp13 [k25 lr45:155 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-int fixed}{ sir@ __hd44780_wait_for_ready__count_1_12}[r0x01 r0x02 ] != 0 goto _return($43)
	.line	188; ../include/hd44780/hd44780.c	if ( !count ) {
	MOVF	r0x01, W
	IORWF	r0x02, W
	BNZ	_00147_DS_
; ;ic:156: 	iTemp16 [k30 lr156:160 so:0]{ ia0 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] = &[_lcddev [k29 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{struct pic_device fixed} , 0x0 {const-unsigned-char literal}]
; ;ic:157: 	iTemp20 [k36 lr157:159 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} = @[iTemp16 [k30 lr156:160 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat] + 0x0 {const-unsigned-char literal}]
; ;ic:158: 	iTemp21 [k37 lr158:159 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ] = 0x1 {const-unsigned-char literal} << iTemp0 [k2 lr3:158 so:0]{ ia0 a2p0 re1 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ __hd44780_wait_for_ready__ctrl_nr_1_11}[r0x00 ]
	.line	191; ../include/hd44780/hd44780.c	set_bit(ctrl_nr, lcddev.disabled);
	MOVLW	0x01
	MOVWF	r0x01
	MOVF	r0x00, W
	BZ	_00162_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00163_DS_:
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00163_DS_
; ;ic:159: 	iTemp22 [k38 lr159:160 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x00 ] = iTemp20 [k36 lr157:159 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}{ sir@ _lcddev} | iTemp21 [k37 lr158:159 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x01 ]
_00162_DS_:
	MOVF	r0x01, W
	BANKSEL	_lcddev
	IORWF	_lcddev, W, B
	MOVWF	r0x00
; ;ic:160: 	*(iTemp16 [k30 lr156:160 so:0]{ ia1 a2p0 re0 rm1 nos0 ru0 dp0}{unsigned-char near* fixed}[remat]) := iTemp22 [k38 lr159:160 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{unsigned-char fixed}[r0x00 ]
	MOVF	r0x00, W
	BANKSEL	_lcddev
	MOVWF	_lcddev, B
; ;ic:161:  _return($43) :
; ;ic:162: 	eproc __hd44780_wait_for_ready_ [k1 lr0:0 so:0]{ ia0 a2p0 re0 rm0 nos0 ru0 dp0}{void function ( unsigned-char fixed) fixed}
_00147_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1730 (0x06c2) bytes ( 1.32%)
;           	  865 (0x0361) words
; udata size:	    1 (0x0001) bytes ( 0.06%)
; access size:	    7 (0x0007) bytes


	end
