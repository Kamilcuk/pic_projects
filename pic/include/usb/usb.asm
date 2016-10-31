;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Tue Apr 21 23:49:50 2015
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"../include/usb/usb.c"
	list	p=18f2550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_usb_bd
	global	_usb_ustat
	global	_USB_init
	global	_USB_wait_for_powerered_state
	global	_USB_service
	global	_USB_wait_for_configured_state
	global	_device_descriptor
	global	_configuration0_descriptor
	global	_string0_descriptor
	global	_string1_descriptor
	global	_string2_descriptor
	global	_string3_descriptor

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1
	extern	__gptrput1
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
	extern	_USB_EP1_init
	extern	_USB_EP1_transmission
	extern	_USB_EP2_init
	extern	_USB_EP2_transmission

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
POSTINC0	equ	0xfee
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
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1
r0x0a	res	1


usb_bd	udata
_usb_bd	res	128


usb_buff	udata
_USB_EP0_out_buffer	res	64
_USB_EP0_in_buffer	res	64

udata_usb_0	udata
_usbdev	res	2

udata_usb_1	udata
_USB_EP0_to_send	res	4

udata_usb_2	udata
_usb_ustat	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_usb__USB_wait_for_configured_state	code
_USB_wait_for_configured_state:
	.line	343; ../include/usb/usb.c	void USB_wait_for_configured_state(void) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	345; ../include/usb/usb.c	USB_wait_for_powerered_state();
	CALL	_USB_wait_for_powerered_state
_00703_DS_:
	BANKSEL	_usbdev
	.line	346; ../include/usb/usb.c	while ( usbdev.state < CONFIGURED_STATE )
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x00
	MOVF	r0x00, W
	ADDLW	0x80
	ADDLW	0x79
	BC	_00706_DS_
	.line	348; ../include/usb/usb.c	USB_service();
	CALL	_USB_service
	BRA	_00703_DS_
_00706_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_service	code
_USB_service:
	.line	190; ../include/usb/usb.c	void USB_service(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	.line	196; ../include/usb/usb.c	UIR &= UIE; /* mask UIE only bits in UIR register */
	MOVF	_UIE, W
	ANDWF	_UIR, F
	.line	201; ../include/usb/usb.c	if (UIRbits.ACTVIF) {/* Activity on bus detected */
	BTFSS	_UIRbits, 2
	BRA	_00594_DS_
	.line	202; ../include/usb/usb.c	UIEbits.ACTVIE = 0;
	BCF	_UIEbits, 2
	.line	203; ../include/usb/usb.c	UCONbits.SUSPND = 0;
	BCF	_UCONbits, 1
_00561_DS_:
	.line	204; ../include/usb/usb.c	do { UIRbits.ACTVIF = 0; } while (UIRbits.ACTVIF); /* documentation page 179 */
	BCF	_UIRbits, 2
	BTFSC	_UIRbits, 2
	BRA	_00561_DS_
	BRA	_00615_DS_
_00594_DS_:
	.line	214; ../include/usb/usb.c	if (UIRbits.URSTIF) {
	BTFSS	_UIRbits, 0
	BRA	_00591_DS_
	.line	155; ../include/usb/usb.c	USB_init();
	CALL	_USB_init
	.line	159; ../include/usb/usb.c	UEIR = 0x00;                       // Clear all USB error flags
	CLRF	_UEIR
	.line	160; ../include/usb/usb.c	UIR  = 0x00;                        // Clears all USB interrupts
	CLRF	_UIR
	.line	161; ../include/usb/usb.c	UEIE = 0b10011111;              // Unmask all USB error interrupts
	MOVLW	0x9f
	MOVWF	_UEIE
	.line	162; ../include/usb/usb.c	UIE  = 0b01111011;               // Enable all interrupts except ACTVIE
	MOVLW	0x7b
	MOVWF	_UIE
	BANKSEL	_usbdev
	.line	164; ../include/usb/usb.c	usbdev.state = DEFAULT_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x0c
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	BANKSEL	(_usbdev + 1)
	.line	165; ../include/usb/usb.c	usbdev.config = 0;
	CLRF	(_usbdev + 1), B
	BANKSEL	_usbdev
	.line	166; ../include/usb/usb.c	usbdev.status = 0;
	MOVF	_usbdev, W, B
	ANDLW	0xfc
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	168; ../include/usb/usb.c	USB_EP0_init(); /* reset EP0 */
	CALL	_USB_EP0_init
	.line	215; ../include/usb/usb.c	USB_reset();
	BRA	_00615_DS_
_00591_DS_:
	.line	221; ../include/usb/usb.c	if (UIRbits.IDLEIF) { /* Idle condition detected */
	BTFSS	_UIRbits, 4
	BRA	_00588_DS_
	.line	222; ../include/usb/usb.c	UIRbits.IDLEIF  = 0;
	BCF	_UIRbits, 4
	.line	223; ../include/usb/usb.c	UIEbits.ACTVIE = 1;
	BSF	_UIEbits, 2
	.line	224; ../include/usb/usb.c	UCONbits.SUSPND = 1;
	BSF	_UCONbits, 1
	BRA	_00615_DS_
_00588_DS_:
	.line	227; ../include/usb/usb.c	if (UIRbits.SOFIF) { /* START-OF-FRAME token was received */
	BTFSS	_UIRbits, 6
	BRA	_00585_DS_
	.line	228; ../include/usb/usb.c	UIRbits.SOFIF = 0;
	BCF	_UIRbits, 6
	BRA	_00615_DS_
_00585_DS_:
	.line	230; ../include/usb/usb.c	if (UIRbits.STALLIF) {
	BTFSS	_UIRbits, 5
	BRA	_00582_DS_
	.line	231; ../include/usb/usb.c	UIRbits.STALLIF = 0;
	BCF	_UIRbits, 5
	BRA	_00615_DS_
_00582_DS_:
	.line	233; ../include/usb/usb.c	if (UIRbits.UERRIF) {
	BTFSS	_UIRbits, 1
	BRA	_00579_DS_
	.line	234; ../include/usb/usb.c	UIRbits.UERRIF = 0;
	BCF	_UIRbits, 1
	.line	235; ../include/usb/usb.c	UEIR = 0x00;
	CLRF	_UEIR
	BRA	_00615_DS_
_00579_DS_:
	.line	241; ../include/usb/usb.c	if (UIRbits.TRNIF) {
	BTFSS	_UIRbits, 3
	BRA	_00615_DS_
	.line	249; ../include/usb/usb.c	do { /* }  while ( i is set &&  TRNIF is set && no other usb signal was received */
	MOVLW	0x04
	MOVWF	r0x00
_00573_DS_:
	.line	252; ../include/usb/usb.c	endp = USTATbits.ENDP;
	MOVF	_USTATbits, W
	SWAPF	WREG, W
	RLNCF	WREG, W
	ANDLW	0x0f
	MOVWF	r0x01
	.line	255; ../include/usb/usb.c	usb_ustat.USTAT = USTAT;
	MOVF	_USTAT, W
	BANKSEL	_usb_ustat
	MOVWF	_usb_ustat, B
	.line	262; ../include/usb/usb.c	UIRbits.TRNIF = 0;
	BCF	_UIRbits, 3
	.line	273; ../include/usb/usb.c	switch (endp) {
	MOVLW	0x03
	SUBWF	r0x01, W
	BTFSC	STATUS, 0
	BRA	_00570_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	RLCF	r0x01, W
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00683_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00683_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00683_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00683_DS_:
	GOTO	_00564_DS_
	GOTO	_00568_DS_
	GOTO	_00569_DS_
_00564_DS_:
	BANKSEL	_usb_ustat
	.line	276; ../include/usb/usb.c	if (usb_ustat.USTATbits.DIR)
	BTFSS	_usb_ustat, 2, B
	BRA	_00566_DS_
	BANKSEL	_usbdev
	.line	488; ../include/usb/usb_ep0.c	if ( usbdev.state == ADDRESS_PENDING_STATE ) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x01
	MOVF	r0x01, W
	XORLW	0x04
	BNZ	_00601_DS_
	.line	492; ../include/usb/usb_ep0.c	UADDR = USB_EP0_to_send.len;
	MOVFF	_USB_EP0_to_send, _UADDR
	.line	493; ../include/usb/usb_ep0.c	if ( UADDR ) {
	MOVF	_UADDR, W
	BZ	_00598_DS_
	BANKSEL	_usbdev
	.line	494; ../include/usb/usb_ep0.c	usbdev.state = ADDRESS_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x14
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	BRA	_00570_DS_
_00598_DS_:
	BANKSEL	_usbdev
	.line	496; ../include/usb/usb_ep0.c	usbdev.state = DEFAULT_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x0c
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	499; ../include/usb/usb.c	ERROR: no line number 499 in file ../include/usb/usb.c
	BRA	_00570_DS_
_00601_DS_:
	BANKSEL	_USB_EP0_to_send
	.line	502; ../include/usb/usb_ep0.c	if ( USB_EP0_to_send.len ) {
	MOVF	_USB_EP0_to_send, W, B
	BZ	_00603_DS_
	BANKSEL	(_usb_bd + 7)
	.line	505; ../include/usb/usb_ep0.c	bd_in->cnt = USB_EP0_fill_adr(bd_in->adr);
	MOVF	(_usb_bd + 7), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_usb_bd + 6)
	MOVF	(_usb_bd + 6), W, B
	MOVWF	POSTDEC1
	CALL	_USB_EP0_fill_adr
	MOVWF	r0x01
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x01, W
	BANKSEL	(_usb_bd + 5)
	MOVWF	(_usb_bd + 5), B
	.line	509; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | ((bd_in->stat&BD_STAT_MASK_DTS)^BD_STAT_MASK_DTS) | BD_STAT_DTSEN;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 4)
	ANDWF	(_usb_bd + 4), W, B
	MOVWF	r0x01
	BTG	r0x01, 6
	MOVLW	0x88
	IORWF	r0x01, F
	MOVF	r0x01, W
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
	BRA	_00570_DS_
_00603_DS_:
	.line	520; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | BD_STAT_BSTALL;
	MOVLW	0x84
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
	.line	278; ../include/usb/usb.c	USB_EP0_in_token(); 
	BRA	_00570_DS_
_00566_DS_:
	BANKSEL	_usb_bd
	.line	530; ../include/usb/usb_ep0.c	if ( bd_out->statbits.PID == USB_PID_SETUP ) {
	MOVF	_usb_bd, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x0f
	MOVWF	r0x01
	MOVF	r0x01, W
	XORLW	0x0d
	BNZ	_00612_DS_
_00690_DS_:
	BANKSEL	(_usb_bd + 2)
	.line	532; ../include/usb/usb_ep0.c	const struct usb_controlrequest __near * const USB_buffer = (struct usb_controlrequest __near *)bd_out->adr;
	MOVF	(_usb_bd + 2), W, B
	MOVWF	r0x01
	BANKSEL	(_usb_bd + 3)
	MOVF	(_usb_bd + 3), W, B
	MOVWF	r0x02
	.line	537; ../include/usb/usb_ep0.c	switch ( ( USB_buffer->bmRequestType )&0x60 ) {
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	INDF0, r0x03
	MOVLW	0x60
	ANDWF	r0x03, F
	MOVF	r0x03, W
	MOVWF	r0x04
	MOVF	r0x04, W
	BZ	_00606_DS_
	MOVF	r0x03, W
	XORLW	0x20
	BZ	_00607_DS_
	MOVF	r0x03, W
	XORLW	0x40
	BZ	_00608_DS_
	BRA	_00609_DS_
_00606_DS_:
	.line	539; ../include/usb/usb_ep0.c	USB_standard_request(USB_buffer); /* USB_buffer is passed for reducing stack allocation */
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_USB_standard_request
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	540; ../include/usb/usb_ep0.c	break;
	BRA	_00610_DS_
_00607_DS_:
	.line	542; ../include/usb/usb_ep0.c	USB_CLASS_REQUEST();
	CALL	_USB_request_error
	.line	543; ../include/usb/usb_ep0.c	break;
	BRA	_00610_DS_
_00608_DS_:
	.line	545; ../include/usb/usb_ep0.c	USB_VENDOR_REQUEST();
	CALL	_USB_request_error
	.line	546; ../include/usb/usb_ep0.c	break;
	BRA	_00610_DS_
_00609_DS_:
	.line	548; ../include/usb/usb_ep0.c	USB_request_error();
	CALL	_USB_request_error
_00610_DS_:
	.line	555; ../include/usb/usb_ep0.c	UCONbits.PKTDIS = 0;
	BCF	_UCONbits, 4
	BRA	_00570_DS_
_00612_DS_:
	.line	571; ../include/usb/usb_ep0.c	USB_EP0_init();
	CALL	_USB_EP0_init
	.line	282; ../include/usb/usb.c	break;
	BRA	_00570_DS_
_00568_DS_:
	.line	290; ../include/usb/usb.c	USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(1)
	CALL	_USB_EP1_transmission
	BRA	_00570_DS_
_00569_DS_:
	.line	293; ../include/usb/usb.c	USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(2)
	CALL	_USB_EP2_transmission
_00570_DS_:
	.line	338; ../include/usb/usb.c	--i;
	DECF	r0x00, F
	.line	339; ../include/usb/usb.c	} while (i && UIRbits.TRNIF && !(UIR&0xf7) );
	MOVF	r0x00, W
	BZ	_00615_DS_
	BTFSS	_UIRbits, 3
	BRA	_00615_DS_
	MOVF	_UIR, W
	ANDLW	0xf7
	BTFSC	STATUS, 2
	BRA	_00573_DS_
_00615_DS_:
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_wait_for_powerered_state	code
_USB_wait_for_powerered_state:
	.line	171; ../include/usb/usb.c	void USB_wait_for_powerered_state(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	BANKSEL	_usbdev
	.line	173; ../include/usb/usb.c	if ( usbdev.state >= POWERED_STATE )
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x00
	MOVF	r0x00, W
	ADDLW	0x80
	ADDLW	0x7e
	.line	175; ../include/usb/usb.c	return;
	BC	_00545_DS_
_00542_DS_:
	.line	183; ../include/usb/usb.c	while (UCONbits.SE0);
	BTFSC	_UCONbits, 5
	BRA	_00542_DS_
	BANKSEL	_usbdev
	.line	184; ../include/usb/usb.c	usbdev.state = POWERED_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x08
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	185; ../include/usb/usb.c	UIE = 0x11; /* IDLEIE URSTIE */
	MOVLW	0x11
	MOVWF	_UIE
_00545_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_reset	code
_USB_reset:
	.line	153; ../include/usb/usb.c	__once void USB_reset(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	155; ../include/usb/usb.c	USB_init();
	CALL	_USB_init
	.line	159; ../include/usb/usb.c	UEIR = 0x00;                       // Clear all USB error flags
	CLRF	_UEIR
	.line	160; ../include/usb/usb.c	UIR  = 0x00;                        // Clears all USB interrupts
	CLRF	_UIR
	.line	161; ../include/usb/usb.c	UEIE = 0b10011111;              // Unmask all USB error interrupts
	MOVLW	0x9f
	MOVWF	_UEIE
	.line	162; ../include/usb/usb.c	UIE  = 0b01111011;               // Enable all interrupts except ACTVIE
	MOVLW	0x7b
	MOVWF	_UIE
	BANKSEL	_usbdev
	.line	164; ../include/usb/usb.c	usbdev.state = DEFAULT_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x0c
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	BANKSEL	(_usbdev + 1)
	.line	165; ../include/usb/usb.c	usbdev.config = 0;
	CLRF	(_usbdev + 1), B
	BANKSEL	_usbdev
	.line	166; ../include/usb/usb.c	usbdev.status = 0;
	MOVF	_usbdev, W, B
	ANDLW	0xfc
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	168; ../include/usb/usb.c	USB_EP0_init(); /* reset EP0 */
	CALL	_USB_EP0_init
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_init	code
_USB_init:
	.line	67; ../include/usb/usb.c	void USB_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	73; ../include/usb/usb.c	UIE = 0x00; // mask all USB interrupts
	CLRF	_UIE
	.line	74; ../include/usb/usb.c	UIR = 0x00; // clear all USB interrupt flags
	CLRF	_UIR
	.line	76; ../include/usb/usb.c	UCFG = 0x14 | USB_BUFFER_DESCRIPTOR_MODE;
	MOVLW	0x14
	MOVWF	_UCFG
_00527_DS_:
	.line	101; ../include/usb/usb.c	while(UIRbits.TRNIF)       // Flush any pending transactions
	BTFSS	_UIRbits, 3
	BRA	_00529_DS_
	.line	102; ../include/usb/usb.c	UIRbits.TRNIF = 0; // to clear out the USTAT FIFO
	BCF	_UIRbits, 3
	BRA	_00527_DS_
_00529_DS_:
	.line	120; ../include/usb/usb.c	UEP0 = 0; 
	CLRF	_UEP0
	.line	121; ../include/usb/usb.c	USB_clear_all_EP_exept_EP0(); /* clear all enpoints */
	CALL	_USB_clear_all_EP_exept_EP0
	.line	123; ../include/usb/usb.c	UADDR = 0x00; /* clear usb address */
	CLRF	_UADDR
	.line	128; ../include/usb/usb.c	UCON = 0x08;
	MOVLW	0x08
	MOVWF	_UCON
	BANKSEL	_usbdev
	.line	135; ../include/usb/usb.c	usbdev.state = ATTACHED_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x04
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	BANKSEL	(_usbdev + 1)
	.line	136; ../include/usb/usb.c	usbdev.config = 0;
	CLRF	(_usbdev + 1), B
	BANKSEL	_usbdev
	.line	137; ../include/usb/usb.c	usbdev.status = 0;
	MOVF	_usbdev, W, B
	ANDLW	0xfc
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_EP0_out_token	code
_USB_EP0_out_token:
	.line	525; ../include/usb/usb_ep0.c	__once void USB_EP0_out_token(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	BANKSEL	_usb_bd
	.line	530; ../include/usb/usb_ep0.c	if ( bd_out->statbits.PID == USB_PID_SETUP ) {
	MOVF	_usb_bd, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x0f
	MOVWF	r0x00
	MOVF	r0x00, W
	XORLW	0x0d
	BNZ	_00498_DS_
_00515_DS_:
	BANKSEL	(_usb_bd + 2)
	.line	532; ../include/usb/usb_ep0.c	const struct usb_controlrequest __near * const USB_buffer = (struct usb_controlrequest __near *)bd_out->adr;
	MOVF	(_usb_bd + 2), W, B
	MOVWF	r0x00
	BANKSEL	(_usb_bd + 3)
	MOVF	(_usb_bd + 3), W, B
	MOVWF	r0x01
	.line	537; ../include/usb/usb_ep0.c	switch ( ( USB_buffer->bmRequestType )&0x60 ) {
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x02
	MOVLW	0x60
	ANDWF	r0x02, F
	MOVF	r0x02, W
	MOVWF	r0x03
	MOVF	r0x03, W
	BZ	_00492_DS_
	MOVF	r0x02, W
	XORLW	0x20
	BZ	_00493_DS_
	MOVF	r0x02, W
	XORLW	0x40
	BZ	_00494_DS_
	BRA	_00495_DS_
_00492_DS_:
	.line	539; ../include/usb/usb_ep0.c	USB_standard_request(USB_buffer); /* USB_buffer is passed for reducing stack allocation */
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_USB_standard_request
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	540; ../include/usb/usb_ep0.c	break;
	BRA	_00496_DS_
_00493_DS_:
	.line	542; ../include/usb/usb_ep0.c	USB_CLASS_REQUEST();
	CALL	_USB_request_error
	.line	543; ../include/usb/usb_ep0.c	break;
	BRA	_00496_DS_
_00494_DS_:
	.line	545; ../include/usb/usb_ep0.c	USB_VENDOR_REQUEST();
	CALL	_USB_request_error
	.line	546; ../include/usb/usb_ep0.c	break;
	BRA	_00496_DS_
_00495_DS_:
	.line	548; ../include/usb/usb_ep0.c	USB_request_error();
	CALL	_USB_request_error
_00496_DS_:
	.line	555; ../include/usb/usb_ep0.c	UCONbits.PKTDIS = 0;
	BCF	_UCONbits, 4
	BRA	_00500_DS_
_00498_DS_:
	.line	571; ../include/usb/usb_ep0.c	USB_EP0_init();
	CALL	_USB_EP0_init
_00500_DS_:
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_EP0_in_token	code
_USB_EP0_in_token:
	.line	476; ../include/usb/usb_ep0.c	__once void USB_EP0_in_token(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	BANKSEL	_usbdev
	.line	488; ../include/usb/usb_ep0.c	if ( usbdev.state == ADDRESS_PENDING_STATE ) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x00
	MOVF	r0x00, W
	XORLW	0x04
	BNZ	_00471_DS_
	.line	492; ../include/usb/usb_ep0.c	UADDR = USB_EP0_to_send.len;
	MOVFF	_USB_EP0_to_send, _UADDR
	.line	493; ../include/usb/usb_ep0.c	if ( UADDR ) {
	MOVF	_UADDR, W
	BZ	_00468_DS_
	BANKSEL	_usbdev
	.line	494; ../include/usb/usb_ep0.c	usbdev.state = ADDRESS_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x14
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	BRA	_00469_DS_
_00468_DS_:
	BANKSEL	_usbdev
	.line	496; ../include/usb/usb_ep0.c	usbdev.state = DEFAULT_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x0c
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
_00469_DS_:
	.line	499; ../include/usb/usb_ep0.c	return;
	BRA	_00475_DS_
_00471_DS_:
	BANKSEL	_USB_EP0_to_send
	.line	502; ../include/usb/usb_ep0.c	if ( USB_EP0_to_send.len ) {
	MOVF	_USB_EP0_to_send, W, B
	BZ	_00473_DS_
	BANKSEL	(_usb_bd + 7)
	.line	505; ../include/usb/usb_ep0.c	bd_in->cnt = USB_EP0_fill_adr(bd_in->adr);
	MOVF	(_usb_bd + 7), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_usb_bd + 6)
	MOVF	(_usb_bd + 6), W, B
	MOVWF	POSTDEC1
	CALL	_USB_EP0_fill_adr
	MOVWF	r0x00
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	(_usb_bd + 5)
	MOVWF	(_usb_bd + 5), B
	.line	509; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | ((bd_in->stat&BD_STAT_MASK_DTS)^BD_STAT_MASK_DTS) | BD_STAT_DTSEN;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 4)
	ANDWF	(_usb_bd + 4), W, B
	MOVWF	r0x00
	BTG	r0x00, 6
	MOVLW	0x88
	IORWF	r0x00, F
	MOVF	r0x00, W
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
	BRA	_00475_DS_
_00473_DS_:
	.line	520; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | BD_STAT_BSTALL;
	MOVLW	0x84
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
_00475_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_EP0_init	code
_USB_EP0_init:
	.line	445; ../include/usb/usb_ep0.c	static void USB_EP0_init(void)
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
	.line	450; ../include/usb/usb_ep0.c	bdpnt = usb_bd; /* ep0 buffer descriptors start the beginning of usb_bd */
	MOVLW	LOW(_usb_bd)
	MOVWF	r0x00
	MOVLW	HIGH(_usb_bd)
	MOVWF	r0x01
	.line	452; ../include/usb/usb_ep0.c	for (i = 0; i < ((sizeof(USB_EP0_out_buffer)/EP0_BUFFER_SIZE)); ++i) {
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x04
_00441_DS_:
	.line	453; ../include/usb/usb_ep0.c	bdpnt->cnt = EP0_BUFFER_SIZE;
	MOVF	r0x00, W
	ADDLW	0x01
	MOVWF	r0x05
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x06
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVLW	0x40
	MOVWF	INDF0
	.line	454; ../include/usb/usb_ep0.c	bdpnt->adr = USB_EP0_out_buffer[i];     // EP0 OUT gets a buffer
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x05
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x06
	MOVLW	LOW(_USB_EP0_out_buffer)
	ADDWF	r0x03, W
	MOVWF	r0x07
	MOVLW	HIGH(_USB_EP0_out_buffer)
	ADDWFC	r0x04, W
	MOVWF	r0x08
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x07, POSTINC0
	MOVFF	r0x08, INDF0
	.line	455; ../include/usb/usb_ep0.c	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;          // set UOWN bit (SIE MODE)
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVLW	0xc8
	MOVWF	INDF0
	.line	457; ../include/usb/usb_ep0.c	bdpnt++; /* switch to the next buffer descriptor pointer */
	MOVLW	0x04
	ADDWF	r0x00, F
	BTFSC	STATUS, 0
	INCF	r0x01, F
	.line	452; ../include/usb/usb_ep0.c	for (i = 0; i < ((sizeof(USB_EP0_out_buffer)/EP0_BUFFER_SIZE)); ++i) {
	MOVLW	0x40
	ADDWF	r0x03, F
	BTFSC	STATUS, 0
	INCF	r0x04, F
	INCF	r0x02, F
	MOVLW	0x01
	SUBWF	r0x02, W
	BNC	_00441_DS_
	.line	460; ../include/usb/usb_ep0.c	for (i = 0; i < ((sizeof(USB_EP0_in_buffer)/EP0_BUFFER_SIZE)); ++i) {
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x04
_00443_DS_:
	.line	461; ../include/usb/usb_ep0.c	bdpnt->adr = USB_EP0_in_buffer[i]; // EP0 IN gets a buffer
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x05
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x06
	MOVLW	LOW(_USB_EP0_in_buffer)
	ADDWF	r0x03, W
	MOVWF	r0x07
	MOVLW	HIGH(_USB_EP0_in_buffer)
	ADDWFC	r0x04, W
	MOVWF	r0x08
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x07, POSTINC0
	MOVFF	r0x08, INDF0
	.line	462; ../include/usb/usb_ep0.c	bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA1 | BD_STAT_DTSEN;  // clear UOWN bit (CPU MODE)
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVLW	0x48
	MOVWF	INDF0
	.line	464; ../include/usb/usb_ep0.c	bdpnt++; /* switch to the next buffer descriptor pointer */
	MOVLW	0x04
	ADDWF	r0x00, F
	BTFSC	STATUS, 0
	INCF	r0x01, F
	.line	460; ../include/usb/usb_ep0.c	for (i = 0; i < ((sizeof(USB_EP0_in_buffer)/EP0_BUFFER_SIZE)); ++i) {
	MOVLW	0x40
	ADDWF	r0x03, F
	BTFSC	STATUS, 0
	INCF	r0x04, F
	INCF	r0x02, F
	MOVLW	0x01
	SUBWF	r0x02, W
	BNC	_00443_DS_
	BANKSEL	_USB_EP0_to_send
	.line	468; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = 0;
	CLRF	_USB_EP0_to_send, B
	BANKSEL	(_USB_EP0_to_send + 1)
	.line	469; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)0;
	CLRF	(_USB_EP0_to_send + 1), B
	BANKSEL	(_USB_EP0_to_send + 2)
	CLRF	(_USB_EP0_to_send + 2), B
	BANKSEL	(_USB_EP0_to_send + 3)
	CLRF	(_USB_EP0_to_send + 3), B
	.line	471; ../include/usb/usb_ep0.c	UEP0 = UEP_EPHSHK | UEP_EPOUTEN | UEP_EPINEN; // EP0 is a control pipe and requires an ACK
	MOVLW	0x16
	MOVWF	_UEP0
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
S_usb__USB_standard_request	code
_USB_standard_request:
	.line	104; ../include/usb/usb_ep0.c	static void USB_standard_request(const struct usb_controlrequest __near * const USB_buffer)
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
	MOVFF	r0x0a, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	BANKSEL	(_usb_bd + 7)
	.line	147; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = bd_in->adr;
	MOVF	(_usb_bd + 7), W, B
	MOVWF	r0x03
	BANKSEL	(_usb_bd + 6)
	MOVF	(_usb_bd + 6), W, B
	MOVWF	r0x02
	MOVLW	0x80
	MOVWF	r0x04
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	BANKSEL	_USB_EP0_to_send
	.line	148; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = 0;
	CLRF	_USB_EP0_to_send, B
	.line	150; ../include/usb/usb_ep0.c	switch (USB_buffer->bRequest) {
	MOVF	r0x00, W
	ADDLW	0x01
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVLW	0x0d
	SUBWF	r0x02, W
	BTFSC	STATUS, 0
	GOTO	_00242_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	RLCF	r0x02, W
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00373_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00373_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00373_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00373_DS_:
	GOTO	_00148_DS_
	GOTO	_00170_DS_
	GOTO	_00231_DS_
	GOTO	_00170_DS_
	GOTO	_00231_DS_
	GOTO	_00194_DS_
	GOTO	_00197_DS_
	GOTO	_00231_DS_
	GOTO	_00211_DS_
	GOTO	_00212_DS_
	GOTO	_00217_DS_
	GOTO	_00223_DS_
	GOTO	_00231_DS_
_00148_DS_:
	.line	152; ../include/usb/usb_ep0.c	switch (USB_buffer->bmRequestType&0x1F) {	// extract request recipient bits
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x03
	MOVLW	0x1f
	ANDWF	r0x03, F
	MOVLW	0x03
	SUBWF	r0x03, W
	BTFSC	STATUS, 0
	GOTO	_00242_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	RLCF	r0x03, W
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00376_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00376_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00376_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00376_DS_:
	GOTO	_00149_DS_
	GOTO	_00150_DS_
	GOTO	_00156_DS_
_00149_DS_:
	.line	154; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[0] = usbdev.status;
	MOVFF	(_USB_EP0_to_send + 1), r0x03
	MOVFF	(_USB_EP0_to_send + 2), r0x04
	MOVFF	(_USB_EP0_to_send + 3), r0x05
	BANKSEL	_usbdev
	MOVF	_usbdev, W, B
	ANDLW	0x03
	MOVWF	r0x06
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, PRODL
	MOVF	r0x05, W
	CALL	__gptrput1
	.line	155; ../include/usb/usb_ep0.c	break;
	BRA	_00168_DS_
_00150_DS_:
	BANKSEL	_usbdev
	.line	157; ../include/usb/usb_ep0.c	switch (usbdev.state) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x03
	MOVF	r0x03, W
	XORLW	0x05
	BNZ	_00378_DS_
	GOTO	_00242_DS_
_00378_DS_:
	MOVF	r0x03, W
	XORLW	0x07
	BZ	_00380_DS_
	BRA	_00168_DS_
_00380_DS_:
	.line	161; ../include/usb/usb_ep0.c	if (USB_buffer->wIndexLow >= NUM_INTERFACES) {
	MOVF	r0x00, W
	ADDLW	0x04
	MOVWF	r0x03
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x04
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, FSR0H
	MOVFF	INDF0, r0x03
	MOVLW	0x01
	SUBWF	r0x03, W
	BTFSC	STATUS, 0
	GOTO	_00242_DS_
	.line	164; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[0] = 0x00;
	MOVFF	(_USB_EP0_to_send + 1), r0x03
	MOVFF	(_USB_EP0_to_send + 2), r0x04
	MOVFF	(_USB_EP0_to_send + 3), r0x05
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, PRODL
	MOVF	r0x05, W
	CALL	__gptrput1
	.line	166; ../include/usb/usb_ep0.c	break;
	BRA	_00168_DS_
_00156_DS_:
	.line	169; ../include/usb/usb_ep0.c	n = USB_buffer->wIndexLow&0x0F;
	MOVF	r0x00, W
	ADDLW	0x04
	MOVWF	r0x03
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x04
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, FSR0H
	MOVFF	INDF0, r0x03
	MOVLW	0x0f
	ANDWF	r0x03, F
	BANKSEL	_usbdev
	.line	170; ../include/usb/usb_ep0.c	switch (usbdev.state) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x04
	MOVF	r0x04, W
	XORLW	0x05
	BZ	_00157_DS_
	MOVF	r0x04, W
	XORLW	0x07
	BZ	_00160_DS_
	GOTO	_00242_DS_
_00157_DS_:
	.line	173; ../include/usb/usb_ep0.c	if ( n ) {
	MOVF	r0x03, W
	BTFSS	STATUS, 2
	GOTO	_00242_DS_
	.line	177; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[0] = (((USB_buffer->data_transfer_direction) ? USB_BD_IN_EP0()->stat : USB_BD_OUT_EP0()->stat)&0x04)>>2;
	MOVFF	(_USB_EP0_to_send + 1), r0x04
	MOVFF	(_USB_EP0_to_send + 2), r0x05
	MOVFF	(_USB_EP0_to_send + 3), r0x06
	MOVFF	r0x00, r0x07
	MOVFF	r0x01, r0x08
	CLRF	WREG
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, FSR0H
	BTFSC	INDF0, 7
	INCF	WREG, F
	MOVWF	r0x07
	MOVF	r0x07, W
	BZ	_00245_DS_
	MOVFF	(_usb_bd + 4), r0x07
	BRA	_00246_DS_
_00245_DS_:
	MOVFF	_usb_bd, r0x07
_00246_DS_:
	MOVLW	0x04
	ANDWF	r0x07, F
	RRNCF	r0x07, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x07
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, PRODL
	MOVF	r0x06, W
	CALL	__gptrput1
	.line	178; ../include/usb/usb_ep0.c	break;
	BRA	_00168_DS_
_00160_DS_:
	.line	181; ../include/usb/usb_ep0.c	if ( n > USB_CONFIG_NUM_ENDPOINTS ) {
	MOVLW	0x03
	SUBWF	r0x03, W
	BTFSC	STATUS, 0
	GOTO	_00242_DS_
	.line	185; ../include/usb/usb_ep0.c	if ( ! (UEP[n] & ((USB_buffer->data_transfer_direction) ? 0x02:0x04)) )  {
	MOVLW	LOW(_UEP0)
	ADDWF	r0x03, W
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_UEP0)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	INDF0, r0x04
	BTFSS	r0x04, 2
	GOTO	_00242_DS_
	.line	190; ../include/usb/usb_ep0.c	buf_desc_ptr = (USB_buffer->data_transfer_direction) ? USB_BD_IN_EP(n) : USB_BD_OUT_EP(n);
	MOVFF	r0x00, r0x04
	MOVFF	r0x01, r0x05
	CLRF	WREG
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	BTFSC	INDF0, 7
	INCF	WREG, F
	MOVWF	r0x04
	MOVF	r0x04, W
	BZ	_00247_DS_
	RLNCF	r0x03, W
	ANDLW	0xfe
	MOVWF	r0x04
	INCF	r0x04, F
; ;multiply lit val:0x04 by variable r0x04 and store in r0x04
	MOVF	r0x04, W
	MULLW	0x04
	MOVF	PRODH, W
	MOVWF	r0x05
	MOVFF	PRODL, r0x04
	MOVLW	LOW(_usb_bd)
	ADDWF	r0x04, F
	MOVLW	HIGH(_usb_bd)
	ADDWFC	r0x05, F
	BRA	_00248_DS_
_00247_DS_:
	RLNCF	r0x03, W
	ANDLW	0xfe
	MOVWF	r0x06
; ;multiply lit val:0x04 by variable r0x06 and store in r0x06
	MOVF	r0x06, W
	MULLW	0x04
	MOVF	PRODH, W
	MOVWF	r0x07
	MOVFF	PRODL, r0x06
	MOVLW	LOW(_usb_bd)
	ADDWF	r0x06, W
	MOVWF	r0x04
	MOVLW	HIGH(_usb_bd)
	ADDWFC	r0x07, W
	MOVWF	r0x05
_00248_DS_:
	.line	192; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[0] = ( (buf_desc_ptr->stat) & 0x04) >> 2;
	MOVFF	(_USB_EP0_to_send + 1), r0x06
	MOVFF	(_USB_EP0_to_send + 2), r0x07
	MOVFF	(_USB_EP0_to_send + 3), r0x08
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	INDF0, r0x09
	MOVLW	0x04
	ANDWF	r0x09, F
	RRNCF	r0x09, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x09
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrput1
_00168_DS_:
	BANKSEL	(_USB_EP0_to_send + 1)
	.line	201; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[1] = 0x00;
	MOVF	(_USB_EP0_to_send + 1), W, B
	ADDLW	0x01
	MOVWF	r0x06
	MOVLW	0x00
	BANKSEL	(_USB_EP0_to_send + 2)
	ADDWFC	(_USB_EP0_to_send + 2), W, B
	MOVWF	r0x07
	MOVLW	0x00
	BANKSEL	(_USB_EP0_to_send + 3)
	ADDWFC	(_USB_EP0_to_send + 3), W, B
	MOVWF	r0x08
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrput1
	.line	202; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = 2;
	MOVLW	0x02
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	203; ../include/usb/usb_ep0.c	break;
	GOTO	_00232_DS_
_00170_DS_:
	.line	206; ../include/usb/usb_ep0.c	switch (USB_buffer->bmRequestType&0x1F) {	// extract request recipient bits
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x06
	MOVLW	0x1f
	ANDWF	r0x06, F
	MOVF	r0x06, W
	BZ	_00171_DS_
	MOVF	r0x06, W
	XORLW	0x02
	BNZ	_00395_DS_
	BRA	_00178_DS_
_00395_DS_:
	GOTO	_00242_DS_
_00171_DS_:
	.line	208; ../include/usb/usb_ep0.c	switch (USB_buffer->wValueLow) {
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x06
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x07
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, FSR0H
	MOVFF	INDF0, r0x06
	MOVF	r0x06, W
	XORLW	0x02
	BZ	_00397_DS_
	GOTO	_00242_DS_
_00397_DS_:
	.line	210; ../include/usb/usb_ep0.c	if (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE)
	MOVF	r0x02, W
	XORLW	0x01
	BNZ	_00174_DS_
_00399_DS_:
	BANKSEL	_usbdev
	.line	211; ../include/usb/usb_ep0.c	usbdev.status &= ~USB_DEVICE_REMOTE_WAKEUP;
	MOVF	_usbdev, W, B
	ANDLW	0x03
	MOVWF	r0x06
	BCF	r0x06, 1
	MOVF	r0x06, W
	ANDLW	0x03
	MOVWF	PRODH
	BANKSEL	_usbdev
	MOVF	_usbdev, W, B
	ANDLW	0xfc
	IORWF	PRODH, W
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	GOTO	_00232_DS_
_00174_DS_:
	BANKSEL	_usbdev
	.line	213; ../include/usb/usb_ep0.c	usbdev.status |= USB_DEVICE_REMOTE_WAKEUP;
	MOVF	_usbdev, W, B
	ANDLW	0x03
	MOVWF	r0x06
	BSF	r0x06, 1
	MOVF	r0x06, W
	ANDLW	0x03
	MOVWF	PRODH
	BANKSEL	_usbdev
	MOVF	_usbdev, W, B
	ANDLW	0xfc
	IORWF	PRODH, W
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	214; ../include/usb/usb_ep0.c	break;
	GOTO	_00232_DS_
_00178_DS_:
	.line	221; ../include/usb/usb_ep0.c	n = USB_buffer->wIndexLow&0x0F;
	MOVF	r0x00, W
	ADDLW	0x04
	MOVWF	r0x06
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x07
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, FSR0H
	MOVFF	INDF0, r0x06
	MOVLW	0x0f
	ANDWF	r0x06, W
	MOVWF	r0x03
	BANKSEL	_usbdev
	.line	222; ../include/usb/usb_ep0.c	switch (usbdev.state) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x07
	MOVF	r0x07, W
	XORLW	0x05
	BZ	_00179_DS_
	MOVF	r0x07, W
	XORLW	0x07
	BZ	_00182_DS_
	GOTO	_00242_DS_
_00179_DS_:
	.line	225; ../include/usb/usb_ep0.c	if ( n ) {
	MOVF	r0x03, W
	BTFSC	STATUS, 2
	BRA	_00232_DS_
	.line	226; ../include/usb/usb_ep0.c	goto USB_REQUEST_ERROR;
	GOTO	_00242_DS_
_00182_DS_:
	.line	230; ../include/usb/usb_ep0.c	buf_desc_ptr =  (USB_buffer->wIndexLow&0x80) ? USB_BD_IN_EP(n) : USB_BD_OUT_EP(n); // compute pointer to the buffer descriptor for the specified EP
	MOVLW	0x80
	ANDWF	r0x06, F
	MOVF	r0x06, W
	BZ	_00249_DS_
	RLNCF	r0x03, W
	ANDLW	0xfe
	MOVWF	r0x07
	INCF	r0x07, F
; ;multiply lit val:0x04 by variable r0x07 and store in r0x07
	MOVF	r0x07, W
	MULLW	0x04
	MOVF	PRODH, W
	MOVWF	r0x08
	MOVFF	PRODL, r0x07
	MOVLW	LOW(_usb_bd)
	ADDWF	r0x07, F
	MOVLW	HIGH(_usb_bd)
	ADDWFC	r0x08, F
	BRA	_00250_DS_
_00249_DS_:
	RLNCF	r0x03, W
	ANDLW	0xfe
	MOVWF	r0x09
; ;multiply lit val:0x04 by variable r0x09 and store in r0x09
	MOVF	r0x09, W
	MULLW	0x04
	MOVF	PRODH, W
	MOVWF	r0x0a
	MOVFF	PRODL, r0x09
	MOVLW	LOW(_usb_bd)
	ADDWF	r0x09, W
	MOVWF	r0x07
	MOVLW	HIGH(_usb_bd)
	ADDWFC	r0x0a, W
	MOVWF	r0x08
_00250_DS_:
	MOVFF	r0x07, r0x04
	MOVFF	r0x08, r0x05
	.line	232; ../include/usb/usb_ep0.c	if (USB_buffer->wIndexLow&0x80) {// if the specified EP direction is IN...
	MOVF	r0x06, W
	BZ	_00188_DS_
	.line	234; ../include/usb/usb_ep0.c	if ( !(UEP[n]&0x02) ) {
	MOVLW	LOW(_UEP0)
	ADDWF	r0x03, W
	MOVWF	r0x06
	CLRF	r0x07
	MOVLW	HIGH(_UEP0)
	ADDWFC	r0x07, F
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, FSR0H
	MOVFF	INDF0, r0x06
	BTFSS	r0x06, 1
	GOTO	_00242_DS_
	.line	237; ../include/usb/usb_ep0.c	buf_desc_ptr->stat = (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE) ? 0x00:0x84; 
	MOVF	r0x02, W
	XORLW	0x01
	BNZ	_00251_DS_
	CLRF	r0x06
	BRA	_00252_DS_
_00251_DS_:
	MOVLW	0x84
	MOVWF	r0x06
_00252_DS_:
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	r0x06, INDF0
	BRA	_00232_DS_
_00188_DS_:
	.line	241; ../include/usb/usb_ep0.c	if ( !(UEP[n]&0x04) ) {
	CLRF	r0x06
	MOVLW	LOW(_UEP0)
	ADDWF	r0x03, F
	MOVLW	HIGH(_UEP0)
	ADDWFC	r0x06, F
	MOVFF	r0x03, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	INDF0, r0x03
	BTFSS	r0x03, 2
	GOTO	_00242_DS_
	.line	244; ../include/usb/usb_ep0.c	buf_desc_ptr->stat = (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE) ? 0x88:0x84;
	MOVF	r0x02, W
	XORLW	0x01
	BNZ	_00253_DS_
	MOVLW	0x88
	MOVWF	r0x02
	BRA	_00254_DS_
_00253_DS_:
	MOVLW	0x84
	MOVWF	r0x02
_00254_DS_:
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	r0x02, INDF0
	.line	246; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00194_DS_:
	.line	257; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = USB_buffer->wValueLow;
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	259; ../include/usb/usb_ep0.c	if (USB_EP0_to_send.len > 0x7F)
	MOVLW	0x80
	SUBWF	r0x02, W
	BTFSC	STATUS, 0
	BRA	_00242_DS_
	BANKSEL	_usbdev
	.line	262; ../include/usb/usb_ep0.c	usbdev.state = ADDRESS_PENDING_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x10
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	263; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00197_DS_:
	.line	265; ../include/usb/usb_ep0.c	switch ( USB_buffer->wValueHigh ) {
	MOVF	r0x00, W
	ADDLW	0x03
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVLW	0x01
	SUBWF	r0x02, W
	BTFSS	STATUS, 0
	BRA	_00242_DS_
	MOVLW	0x04
	SUBWF	r0x02, W
	BTFSC	STATUS, 0
	BRA	_00242_DS_
	DECF	r0x02, F
	CLRF	PCLATH
	CLRF	PCLATU
	RLCF	r0x02, W
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00417_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00417_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00417_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00417_DS_:
	GOTO	_00198_DS_
	GOTO	_00200_DS_
	GOTO	_00202_DS_
_00198_DS_:
	.line	270; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)&device_descriptor;
	MOVLW	UPPER(_device_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_device_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_device_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	271; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(device_descriptor);
	MOVLW	0x12
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	272; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00200_DS_:
	.line	277; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)&configuration0_descriptor;
	MOVLW	UPPER(_configuration0_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_configuration0_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_configuration0_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	278; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(configuration0_descriptor);
	MOVLW	0x20
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	279; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00202_DS_:
	.line	281; ../include/usb/usb_ep0.c	switch (USB_buffer->wValueLow) {
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVLW	0x04
	SUBWF	r0x02, W
	BTFSC	STATUS, 0
	BRA	_00242_DS_
	CLRF	PCLATH
	CLRF	PCLATU
	RLCF	r0x02, W
	RLCF	PCLATH, F
	RLCF	WREG, W
	RLCF	PCLATH, F
	ANDLW	0xfc
	ADDLW	LOW(_00419_DS_)
	MOVWF	POSTDEC1
	MOVLW	HIGH(_00419_DS_)
	ADDWFC	PCLATH, F
	MOVLW	UPPER(_00419_DS_)
	ADDWFC	PCLATU, F
	MOVF	PREINC1, W
	MOVWF	PCL
_00419_DS_:
	GOTO	_00203_DS_
	GOTO	_00204_DS_
	GOTO	_00205_DS_
	GOTO	_00206_DS_
_00203_DS_:
	.line	283; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)string0_descriptor;
	MOVLW	UPPER(_string0_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_string0_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_string0_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	284; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(string0_descriptor);
	MOVLW	0x04
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	285; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00204_DS_:
	.line	287; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)string1_descriptor;
	MOVLW	UPPER(_string1_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_string1_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_string1_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	288; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(string1_descriptor);
	MOVLW	0x14
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	289; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00205_DS_:
	.line	291; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)string2_descriptor;
	MOVLW	UPPER(_string2_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_string2_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_string2_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	292; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(string2_descriptor);
	MOVLW	0x10
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	293; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00206_DS_:
	.line	295; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)string3_descriptor;
	MOVLW	UPPER(_string3_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_string3_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_string3_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	296; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(string3_descriptor);
	MOVLW	0x08
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	305; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00211_DS_:
	.line	307; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff = (unsigned char *)&configuration0_descriptor;
	MOVLW	UPPER(_configuration0_descriptor)
	MOVWF	r0x04
	MOVLW	HIGH(_configuration0_descriptor)
	MOVWF	r0x03
	MOVLW	LOW(_configuration0_descriptor)
	MOVWF	r0x02
	MOVF	r0x02, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x04, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	308; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = sizeof(configuration0_descriptor);
	MOVLW	0x20
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	309; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00212_DS_:
	.line	311; ../include/usb/usb_ep0.c	switch (USB_buffer->wValueLow) {
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	BZ	_00213_DS_
	MOVF	r0x02, W
	XORLW	0x01
	BZ	_00214_DS_
	BRA	_00242_DS_
_00213_DS_:
	BANKSEL	_usbdev
	.line	313; ../include/usb/usb_ep0.c	usbdev.state = ADDRESS_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x14
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	314; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00214_DS_:
	.line	316; ../include/usb/usb_ep0.c	USB_clear_all_EP_exept_EP0();
	CALL	_USB_clear_all_EP_exept_EP0
	.line	317; ../include/usb/usb_ep0.c	USB_configuration0_endps_init();
	CALL	_USB_configuration0_endps_init
	BANKSEL	_usbdev
	.line	318; ../include/usb/usb_ep0.c	usbdev.state = CONFIGURED_STATE;
	MOVF	_usbdev, W, B
	ANDLW	0xe3
	IORLW	0x1c
	BANKSEL	_usbdev
	MOVWF	_usbdev, B
	.line	319; ../include/usb/usb_ep0.c	usbdev.config = CONFIGURATION0_BCONFIGURATIONVALUE;
	MOVLW	0x01
	BANKSEL	(_usbdev + 1)
	MOVWF	(_usbdev + 1), B
	.line	320; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00217_DS_:
	BANKSEL	_usbdev
	.line	327; ../include/usb/usb_ep0.c	if ( usbdev.state != CONFIGURED_STATE ) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x02
	MOVF	r0x02, W
	XORLW	0x07
	BZ	_00425_DS_
	BRA	_00242_DS_
_00425_DS_:
	.line	330; ../include/usb/usb_ep0.c	switch (USB_buffer->wIndexLow) {
	MOVF	r0x00, W
	ADDLW	0x04
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	BZ	_00427_DS_
	BRA	_00242_DS_
_00427_DS_:
	.line	333; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff[0] = 0x00;
	MOVFF	(_USB_EP0_to_send + 1), r0x02
	MOVFF	(_USB_EP0_to_send + 2), r0x03
	MOVFF	(_USB_EP0_to_send + 3), r0x04
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, PRODL
	MOVF	r0x04, W
	CALL	__gptrput1
	.line	338; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = 1;
	MOVLW	0x01
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
	.line	339; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00223_DS_:
	BANKSEL	_usbdev
	.line	341; ../include/usb/usb_ep0.c	if ( usbdev.state != CONFIGURED_STATE ) {
	MOVF	_usbdev, W, B
	RRNCF	WREG, W
	RRNCF	WREG, W
	ANDLW	0x07
	MOVWF	r0x02
	MOVF	r0x02, W
	XORLW	0x07
	BZ	_00429_DS_
	BRA	_00242_DS_
_00429_DS_:
	.line	344; ../include/usb/usb_ep0.c	switch (USB_buffer->wValueLow) {
	MOVF	r0x00, W
	ADDLW	0x02
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	BZ	_00431_DS_
	BRA	_00242_DS_
_00431_DS_:
	.line	346; ../include/usb/usb_ep0.c	break;
	BRA	_00232_DS_
_00231_DS_:
	.line	356; ../include/usb/usb_ep0.c	goto USB_REQUEST_ERROR;
	BRA	_00242_DS_
_00232_DS_:
	.line	363; ../include/usb/usb_ep0.c	if (USB_buffer->data_transfer_direction) { // DIRECTION IN -> DEVICE_TO_HOST
	MOVFF	r0x00, r0x02
	MOVFF	r0x01, r0x03
	CLRF	WREG
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	BTFSC	INDF0, 7
	INCF	WREG, F
	MOVWF	r0x02
	MOVF	r0x02, W
	BTFSC	STATUS, 2
	BRA	_00240_DS_
	.line	374; ../include/usb/usb_ep0.c	if ( (USB_buffer->wLengthHigh == 0x00) && (USB_buffer->wLengthLow < USB_EP0_to_send.len) ) {
	MOVF	r0x00, W
	ADDLW	0x07
	MOVWF	r0x02
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x03
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	INDF0, r0x02
	MOVF	r0x02, W
	BNZ	_00234_DS_
	MOVLW	0x06
	ADDWF	r0x00, F
	BTFSC	STATUS, 0
	INCF	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x00
	BANKSEL	_USB_EP0_to_send
	MOVF	_USB_EP0_to_send, W, B
	SUBWF	r0x00, W
	BC	_00234_DS_
	.line	375; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = USB_buffer->wLengthLow;
	MOVF	r0x00, W
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
_00234_DS_:
	.line	378; ../include/usb/usb_ep0.c	if ( USB_EP0_to_send.buff == bd_in->adr ) {
	MOVFF	(_usb_bd + 6), r0x00
	MOVFF	(_usb_bd + 7), r0x01
	MOVF	r0x01, W
	MOVWF	r0x03
	MOVF	r0x00, W
	MOVWF	r0x02
	MOVLW	0x80
	MOVWF	r0x04
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVF	(_USB_EP0_to_send + 1), W, B
	XORWF	r0x02, W
	BNZ	_00433_DS_
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVF	(_USB_EP0_to_send + 2), W, B
	XORWF	r0x03, W
	BNZ	_00433_DS_
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVF	(_USB_EP0_to_send + 3), W, B
	XORWF	r0x04, W
	BZ	_00434_DS_
_00433_DS_:
	BRA	_00237_DS_
_00434_DS_:
	BANKSEL	_USB_EP0_to_send
	.line	380; ../include/usb/usb_ep0.c	bd_in->cnt = USB_EP0_to_send.len;
	MOVF	_USB_EP0_to_send, W, B
	BANKSEL	(_usb_bd + 5)
	MOVWF	(_usb_bd + 5), B
	BRA	_00241_DS_
_00237_DS_:
	.line	387; ../include/usb/usb_ep0.c	bd_in->cnt = USB_EP0_fill_adr(bd_in->adr);
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_USB_EP0_fill_adr
	MOVWF	r0x00
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	(_usb_bd + 5)
	MOVWF	(_usb_bd + 5), B
	BRA	_00241_DS_
_00240_DS_:
	BANKSEL	(_usb_bd + 5)
	.line	417; ../include/usb/usb_ep0.c	bd_in->cnt = 0;
	CLRF	(_usb_bd + 5), B
_00241_DS_:
	.line	427; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	MOVLW	0xc8
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
	.line	431; ../include/usb/usb_ep0.c	bd_out->cnt = EP0_BUFFER_SIZE;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 1)
	MOVWF	(_usb_bd + 1), B
	.line	432; ../include/usb/usb_ep0.c	bd_out->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	MOVLW	0xc8
	BANKSEL	_usb_bd
	MOVWF	_usb_bd, B
	.line	434; ../include/usb/usb_ep0.c	return; /* succes */
	BRA	_00243_DS_
_00242_DS_:
	.line	437; ../include/usb/usb_ep0.c	USB_request_error();
	CALL	_USB_request_error
_00243_DS_:
	.line	438; ../include/usb/usb_ep0.c	return;
	MOVFF	PREINC1, r0x0a
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
S_usb__USB_request_error	code
_USB_request_error:
	.line	82; ../include/usb/usb_ep0.c	static void USB_request_error(void) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	92; ../include/usb/usb_ep0.c	bd_out->cnt  = EP0_BUFFER_SIZE;
	MOVLW	0x40
	BANKSEL	(_usb_bd + 1)
	MOVWF	(_usb_bd + 1), B
	.line	93; ../include/usb/usb_ep0.c	bd_out->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN | BD_STAT_BSTALL;
	MOVLW	0x8c
	BANKSEL	_usb_bd
	MOVWF	_usb_bd, B
	.line	94; ../include/usb/usb_ep0.c	bd_in->stat = BD_STAT_USIE | BD_STAT_BSTALL;
	MOVLW	0x84
	BANKSEL	(_usb_bd + 4)
	MOVWF	(_usb_bd + 4), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_EP0_fill_adr	code
_USB_EP0_fill_adr:
	.line	51; ../include/usb/usb_ep0.c	static unsigned char USB_EP0_fill_adr(unsigned char __near *adr) 
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	56; ../include/usb/usb_ep0.c	if ( USB_EP0_to_send.len < EP0_BUFFER_SIZE ) {
	MOVFF	_USB_EP0_to_send, r0x02
	MOVLW	0x40
	SUBWF	r0x02, W
	BC	_00119_DS_
	.line	57; ../include/usb/usb_ep0.c	i = USB_packet_length = USB_EP0_to_send.len;
	MOVFF	r0x02, r0x03
	MOVFF	r0x03, r0x04
	BANKSEL	_USB_EP0_to_send
	.line	58; ../include/usb/usb_ep0.c	USB_EP0_to_send.len = 0x00;
	CLRF	_USB_EP0_to_send, B
	BRA	_00129_DS_
_00119_DS_:
	.line	60; ../include/usb/usb_ep0.c	i = USB_packet_length = EP0_BUFFER_SIZE;
	MOVLW	0x40
	MOVWF	r0x04
	MOVLW	0x40
	MOVWF	r0x03
	.line	61; ../include/usb/usb_ep0.c	USB_EP0_to_send.len -= EP0_BUFFER_SIZE;
	MOVLW	0xc0
	ADDWF	r0x02, F
	MOVF	r0x02, W
	BANKSEL	_USB_EP0_to_send
	MOVWF	_USB_EP0_to_send, B
_00129_DS_:
	MOVFF	r0x03, r0x02
_00123_DS_:
	.line	64; ../include/usb/usb_ep0.c	for (; i; i--) {
	MOVF	r0x02, W
	BZ	_00121_DS_
	.line	65; ../include/usb/usb_ep0.c	*adr = *USB_EP0_to_send.buff;
	MOVFF	(_USB_EP0_to_send + 1), FSR0L
	MOVFF	(_USB_EP0_to_send + 2), PRODL
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVF	(_USB_EP0_to_send + 3), W, B
	CALL	__gptrget1
	MOVWF	r0x03
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	r0x03, INDF0
	.line	66; ../include/usb/usb_ep0.c	USB_EP0_to_send.buff++;
	MOVFF	(_USB_EP0_to_send + 1), r0x03
	MOVFF	(_USB_EP0_to_send + 2), r0x05
	MOVFF	(_USB_EP0_to_send + 3), r0x06
	INCF	r0x03, F
	BNC	_00138_DS_
	INFSNZ	r0x05, F
	INCF	r0x06, F
_00138_DS_:
	MOVF	r0x03, W
	BANKSEL	(_USB_EP0_to_send + 1)
	MOVWF	(_USB_EP0_to_send + 1), B
	MOVF	r0x05, W
	BANKSEL	(_USB_EP0_to_send + 2)
	MOVWF	(_USB_EP0_to_send + 2), B
	MOVF	r0x06, W
	BANKSEL	(_USB_EP0_to_send + 3)
	MOVWF	(_USB_EP0_to_send + 3), B
	.line	67; ../include/usb/usb_ep0.c	adr++;
	INFSNZ	r0x00, F
	INCF	r0x01, F
	.line	64; ../include/usb/usb_ep0.c	for (; i; i--) {
	DECF	r0x02, F
	BRA	_00123_DS_
_00121_DS_:
	.line	70; ../include/usb/usb_ep0.c	return USB_packet_length;
	MOVF	r0x04, W
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
S_usb__USB_clear_all_EP_exept_EP0	code
_USB_clear_all_EP_exept_EP0:
	.line	59; ../include/usb/usb.c	static void USB_clear_all_EP_exept_EP0()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	61; ../include/usb/usb.c	UEP1 = UEP2 = UEP3 = UEP4 = UEP5 = UEP6 = UEP7 = UEP8 = UEP9 = UEP10 = UEP11 = UEP12 = UEP13 = UEP14 = UEP15 = 0; 
	CLRF	_UEP15
	CLRF	_UEP14
	CLRF	_UEP13
	CLRF	_UEP12
	CLRF	_UEP11
	CLRF	_UEP10
	CLRF	_UEP9
	CLRF	_UEP8
	CLRF	_UEP7
	CLRF	_UEP6
	CLRF	_UEP5
	CLRF	_UEP4
	CLRF	_UEP3
	CLRF	_UEP2
	CLRF	_UEP1
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__USB_configuration0_endps_init	code
_USB_configuration0_endps_init:
	.line	51; ../include/usb/usb.c	static void USB_configuration0_endps_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	54; ../include/usb/usb.c	USB_CONFIG_ENDPOINTS_INIT();
	CALL	_USB_EP1_init
	CALL	_USB_EP2_init
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block for Ival
	code
_device_descriptor:
	DB	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0xff, 0xff, 0x10, 0x00
	DB	0x03, 0x00, 0x01, 0x02, 0x03, 0x01
; ; Starting pCode block for Ival
_configuration0_descriptor:
	DB	0x09, 0x02, 0x20, 0x00, 0x01, 0x01, 0x00, 0x80, 0xfa, 0x09, 0x04, 0x00
	DB	0x00, 0x02, 0xff, 0xff, 0xff, 0x00, 0x07, 0x05, 0x01, 0x02, 0x40, 0x00
	DB	0x00, 0x07, 0x05, 0x82, 0x03, 0x40, 0x00, 0xff
; ; Starting pCode block for Ival
_string0_descriptor:
	DB	0x04, 0x03, 0x09, 0x04
; ; Starting pCode block for Ival
_string1_descriptor:
	DB	0x14, 0x03, 0x4b, 0x00, 0x6f, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x54, 0x00
	DB	0x65, 0x00, 0x63, 0x00, 0x68, 0x00, 0x20, 0x00
; ; Starting pCode block for Ival
_string2_descriptor:
	DB	0x10, 0x03, 0x67, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x70, 0x00, 0x69, 0x00
	DB	0x63, 0x00, 0x20, 0x00
; ; Starting pCode block for Ival
_string3_descriptor:
	DB	0x08, 0x03, 0x34, 0x00, 0x37, 0x00, 0x31, 0x00


; Statistics:
; code size:	 3828 (0x0ef4) bytes ( 2.92%)
;           	 1914 (0x077a) words
; udata size:	  263 (0x0107) bytes (14.68%)
; access size:	   11 (0x000b) bytes


	end
