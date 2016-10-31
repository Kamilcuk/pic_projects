;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:51 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"../include/ds18x20/onewire.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_ow_reset
	global	_ow_bit_io
	global	_ow_byte_wr
	global	_ow_byte_rd
	global	_ow_rom_search
	global	_ow_command_intern
	global	_ow_byte_wr_with_parasite_enable

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
	extern	__delay_us

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
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

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_onewire__ow_command_intern	code
_ow_command_intern:
	.line	229; ../include/ds18x20/onewire.c	void ow_command_intern( uint8_t command, __near uint8_t *id, uint8_t with_parasite_enable )
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
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	.line	233; ../include/ds18x20/onewire.c	ow_reset();
	CALL	_ow_reset
	.line	235; ../include/ds18x20/onewire.c	if( id ) {
	MOVF	r0x01, W
	IORWF	r0x02, W
	BZ	_00258_DS_
	.line	236; ../include/ds18x20/onewire.c	ow_byte_wr( OW_MATCH_ROM );     // to a single device
	MOVLW	0x55
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVF	POSTINC1, F
	.line	238; ../include/ds18x20/onewire.c	do {
	MOVLW	0x08
	MOVWF	r0x04
_00254_DS_:
	.line	239; ../include/ds18x20/onewire.c	ow_byte_wr( *id );
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	INDF0, r0x05
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVF	POSTINC1, F
	.line	240; ../include/ds18x20/onewire.c	id++;
	INFSNZ	r0x01, F
	INCF	r0x02, F
	.line	241; ../include/ds18x20/onewire.c	} while( --i );
	DECFSZ	r0x04, F
	BRA	_00254_DS_
	BRA	_00259_DS_
_00258_DS_:
	.line	244; ../include/ds18x20/onewire.c	ow_byte_wr( OW_SKIP_ROM );      // to all devices
	MOVLW	0xcc
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVF	POSTINC1, F
_00259_DS_:
	.line	247; ../include/ds18x20/onewire.c	if ( with_parasite_enable  ) {
	MOVF	r0x03, W
	BZ	_00261_DS_
	.line	248; ../include/ds18x20/onewire.c	ow_byte_wr_with_parasite_enable( command );
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr_with_parasite_enable
	MOVF	POSTINC1, F
	BRA	_00263_DS_
_00261_DS_:
	.line	250; ../include/ds18x20/onewire.c	ow_byte_wr( command );
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVF	POSTINC1, F
_00263_DS_:
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_rom_search	code
_ow_rom_search:
	.line	180; ../include/ds18x20/onewire.c	uint8_t ow_rom_search( uint8_t diff, __near uint8_t *id )
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	185; ../include/ds18x20/onewire.c	if( ow_reset() ) {
	CALL	_ow_reset
	MOVWF	r0x03
	MOVF	r0x03, W
	BZ	_00191_DS_
	.line	186; ../include/ds18x20/onewire.c	return OW_PRESENCE_ERR;         // error, no device found <--- early exit!
	SETF	WREG
	BRA	_00211_DS_
_00191_DS_:
	.line	189; ../include/ds18x20/onewire.c	ow_byte_wr( OW_SEARCH_ROM );        // ROM search command
	MOVLW	0xf0
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVF	POSTINC1, F
	.line	190; ../include/ds18x20/onewire.c	next_diff = OW_LAST_DEVICE;         // unchanged on last device
	CLRF	r0x03
	.line	192; ../include/ds18x20/onewire.c	i = OW_ROMCODE_SIZE * 8;            // 8 bytes
	MOVLW	0x40
	MOVWF	r0x04
_00220_DS_:
	.line	196; ../include/ds18x20/onewire.c	do {
	MOVFF	r0x04, r0x05
	MOVLW	0x08
	MOVWF	r0x06
_00205_DS_:
	.line	197; ../include/ds18x20/onewire.c	b = ow_bit_io( 1 );         // read bit
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_ow_bit_io
	MOVWF	r0x07
	MOVF	POSTINC1, F
	.line	198; ../include/ds18x20/onewire.c	if( ow_bit_io( 1 ) ) {      // read complement bit
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_ow_bit_io
	MOVWF	r0x08
	MOVF	POSTINC1, F
	MOVF	r0x08, W
	BZ	_00201_DS_
	.line	199; ../include/ds18x20/onewire.c	if( b ) {               // 0b11
	MOVF	r0x07, W
	BZ	_00202_DS_
	.line	200; ../include/ds18x20/onewire.c	return OW_DATA_ERR; // data error <--- early exit!
	MOVLW	0xfe
	BRA	_00211_DS_
_00201_DS_:
	.line	204; ../include/ds18x20/onewire.c	if( !b ) {              // 0b00 = 2 devices
	MOVF	r0x07, W
	BNZ	_00202_DS_
	.line	205; ../include/ds18x20/onewire.c	if( diff > i || ((*id & 1) && diff != i) ) {
	MOVF	r0x00, W
	SUBWF	r0x05, W
	BNC	_00194_DS_
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	INDF0, r0x08
	BTFSS	r0x08, 0
	BRA	_00202_DS_
	MOVF	r0x00, W
	XORWF	r0x05, W
	BZ	_00202_DS_
_00194_DS_:
	.line	206; ../include/ds18x20/onewire.c	b = 1;          // now 1
	MOVLW	0x01
	MOVWF	r0x07
	.line	207; ../include/ds18x20/onewire.c	next_diff = i;  // next pass 0
	MOVFF	r0x05, r0x03
_00202_DS_:
	.line	211; ../include/ds18x20/onewire.c	ow_bit_io( b );             // write bit
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	CALL	_ow_bit_io
	MOVF	POSTINC1, F
	.line	212; ../include/ds18x20/onewire.c	*id >>= 1;
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	INDF0, r0x08
	RRNCF	r0x08, W
	ANDLW	0x7f
	MOVWF	r0x08
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x08, INDF0
	.line	213; ../include/ds18x20/onewire.c	if( b ) {
	MOVF	r0x07, W
	BZ	_00204_DS_
	.line	214; ../include/ds18x20/onewire.c	*id |= 0x80;            // store bit
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	INDF0, r0x07
	BSF	r0x07, 7
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x07, INDF0
_00204_DS_:
	.line	217; ../include/ds18x20/onewire.c	i--;
	DECF	r0x05, F
	MOVFF	r0x05, r0x04
	.line	219; ../include/ds18x20/onewire.c	} while( --j );
	DECFSZ	r0x06, F
	BRA	_00205_DS_
	.line	221; ../include/ds18x20/onewire.c	id++;                           // next byte
	INFSNZ	r0x01, F
	INCF	r0x02, F
	.line	223; ../include/ds18x20/onewire.c	} while( i );
	MOVF	r0x05, W
	BTFSS	STATUS, 2
	BRA	_00220_DS_
	.line	225; ../include/ds18x20/onewire.c	return next_diff;                   // to continue search
	MOVF	r0x03, W
_00211_DS_:
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
S_onewire__ow_byte_rd	code
_ow_byte_rd:
	.line	172; ../include/ds18x20/onewire.c	uint8_t ow_byte_rd( void )
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	176; ../include/ds18x20/onewire.c	return ow_byte_wr( 0xFF ); 
	MOVLW	0xff
	MOVWF	POSTDEC1
	CALL	_ow_byte_wr
	MOVWF	r0x00
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_byte_wr_with_parasite_enable	code
_ow_byte_wr_with_parasite_enable:
	.line	152; ../include/ds18x20/onewire.c	uint8_t ow_byte_wr_with_parasite_enable( uint8_t b )
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	156; ../include/ds18x20/onewire.c	do {
	MOVLW	0x08
	MOVWF	r0x01
_00161_DS_:
	.line	157; ../include/ds18x20/onewire.c	if ( i != 1 ) {
	MOVF	r0x01, W
	XORLW	0x01
	BZ	_00157_DS_
	.line	158; ../include/ds18x20/onewire.c	j = ow_bit_io_intern( b & 1, 0 );
	MOVLW	0x01
	ANDWF	r0x00, W
	MOVWF	r0x02
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_ow_bit_io_intern
	MOVWF	r0x02
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00158_DS_
_00157_DS_:
	.line	160; ../include/ds18x20/onewire.c	j = ow_bit_io_intern( b & 1, 1 );
	MOVLW	0x01
	ANDWF	r0x00, W
	MOVWF	r0x03
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_ow_bit_io_intern
	MOVWF	r0x02
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00158_DS_:
	.line	162; ../include/ds18x20/onewire.c	b >>= 1;
	BCF	STATUS, 0
	RRCF	r0x00, F
	.line	163; ../include/ds18x20/onewire.c	if( j ) {
	MOVF	r0x02, W
	BZ	_00162_DS_
	.line	164; ../include/ds18x20/onewire.c	b |= 0x80;
	BSF	r0x00, 7
_00162_DS_:
	.line	166; ../include/ds18x20/onewire.c	} while( --i );
	DECFSZ	r0x01, F
	BRA	_00161_DS_
	.line	168; ../include/ds18x20/onewire.c	return b;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_byte_wr	code
_ow_byte_wr:
	.line	137; ../include/ds18x20/onewire.c	uint8_t ow_byte_wr( uint8_t b )
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	141; ../include/ds18x20/onewire.c	do {
	MOVLW	0x08
	MOVWF	r0x01
_00148_DS_:
	.line	142; ../include/ds18x20/onewire.c	j = ow_bit_io( b & 1 );
	MOVLW	0x01
	ANDWF	r0x00, W
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_ow_bit_io
	MOVWF	r0x02
	MOVF	POSTINC1, F
	.line	143; ../include/ds18x20/onewire.c	b >>= 1;
	BCF	STATUS, 0
	RRCF	r0x00, F
	.line	144; ../include/ds18x20/onewire.c	if( j ) {
	MOVF	r0x02, W
	BZ	_00149_DS_
	.line	145; ../include/ds18x20/onewire.c	b |= 0x80;
	BSF	r0x00, 7
_00149_DS_:
	.line	147; ../include/ds18x20/onewire.c	} while( --i );
	DECFSZ	r0x01, F
	BRA	_00148_DS_
	.line	149; ../include/ds18x20/onewire.c	return b;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_bit_io	code
_ow_bit_io:
	.line	132; ../include/ds18x20/onewire.c	uint8_t ow_bit_io( uint8_t b )
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	134; ../include/ds18x20/onewire.c	return ow_bit_io_intern( b & 1, 0 );
	MOVLW	0x01
	ANDWF	r0x00, F
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_ow_bit_io_intern
	MOVWF	r0x00
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_bit_io_intern	code
_ow_bit_io_intern:
	.line	90; ../include/ds18x20/onewire.c	static uint8_t ow_bit_io_intern( uint8_t b, uint8_t with_parasite_enable )
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
	.line	92; ../include/ds18x20/onewire.c	ATOMIC_BLOCK (
	MOVFF	_INTCON, r0x02
	MOVF	_INTCON, W
	MOVWF	r0x03
	MOVLW	0x3f
	ANDWF	r0x03, W
	MOVWF	_INTCON
	BCF	_TRISBbits, 6
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x07
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BZ	_00122_DS_
	BSF	_TRISBbits, 6
_00122_DS_:
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x08
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BTFSC	_PORTBbits, 6
	BRA	_00124_DS_
	CLRF	r0x00
_00124_DS_:
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x26
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BSF	_TRISBbits, 6
	MOVF	r0x01, W
	BZ	_00131_DS_
	BCF	_TRISBbits, 6
	BSF	_PORTBbits, 6
	BSF	_PORTBbits, 7
_00131_DS_:
	MOVFF	r0x02, _INTCON
	.line	127; ../include/ds18x20/onewire.c	_delay_us(OW_RECOVERY_TIME); // may be increased for longer wires
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	129; ../include/ds18x20/onewire.c	return b;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_onewire__ow_reset	code
_ow_reset:
	.line	49; ../include/ds18x20/onewire.c	uint8_t ow_reset(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	.line	53; ../include/ds18x20/onewire.c	ow_parasite_disable();
	BSF	_TRISBbits, 6
	BCF	_PORTBbits, 7
	.line	55; ../include/ds18x20/onewire.c	ATOMIC_BLOCK (
	MOVFF	_INTCON, r0x00
	MOVF	_INTCON, W
	MOVWF	r0x01
	MOVLW	0x3f
	ANDWF	r0x01, W
	MOVWF	_INTCON
	BCF	_PORTBbits, 6
	BCF	_TRISBbits, 6
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xe0
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BSF	_TRISBbits, 6
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x40
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	CLRF	r0x01
	BTFSC	_PORTBbits, 6
	INCF	r0x01, F
	MOVFF	r0x00, _INTCON
	.line	74; ../include/ds18x20/onewire.c	_delay_us(480 - 64);       // was 480-66
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xa0
	MOVWF	POSTDEC1
	CALL	__delay_us
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	75; ../include/ds18x20/onewire.c	if( OW_GET_IN() == 0 ) {
	BTFSC	_PORTBbits, 6
	BRA	_00115_DS_
	.line	76; ../include/ds18x20/onewire.c	err = 1;             // short circuit, expected low but got high
	MOVLW	0x01
	MOVWF	r0x01
_00115_DS_:
	.line	79; ../include/ds18x20/onewire.c	return err;
	MOVF	r0x01, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1076 (0x0434) bytes ( 0.82%)
;           	  538 (0x021a) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    9 (0x0009) bytes


	end
