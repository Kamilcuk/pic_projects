; TEST01b.ASM
;
;                 Programme de test du PIC18F2550 N° 1
;				 (Modification du test 1 du PIC18F4550)
;
;                        (C) CHAMOUARD 2009
;              (Libre de droits pour utilisation non 
;               commerciale et à vos propres risques)

; Clignotement des LEDs sur le port RB
;
; Le circuit correspond au montage le plus simple pour le 18F2550 :
;	- quartz 20 MHz avec ses deux capacités de 10 pF
;	- _MCLR tirée au +5V
;	- Alimentation et découplage de 100 nF et 47µF
;	- 470 nF sur Vusb
; Le port B correspond à un compteur binaire le LSB (RB0 broche 21) commutant
; 	tous les 3*256*256 cycles (environ) soit 0,04 s 
;	et le MSB (RB7 broche 28) tous les 3*256*256*128 cycles (environ) soit 5 s
;	donc une période de 10 s.

	LIST P=18F2550, F=INHX32

	extern	_SPPDATA
	extern	_SPPCFG
	extern	_SPPEPS
	extern	_SPPCON
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
	extern	_PORTD
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_TRISA
	extern	_TRISB
	extern	_TRISC
	extern	_TRISD
	extern	_TRISE
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
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_ECCP1AS
	extern	_ECCP1DEL
	extern	_BAUDCON
	extern	_CCP2CON
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
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
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_OSCCON
	extern	_T0CON
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
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU
	
	
	
	CONFIG PLLDIV = 4, CPUDIV=OSC1_PLL2, USBDIV = 2
	CONFIG FOSC = HSPLL_HS, IESO=OFF
	CONFIG PWRT=OFF, BOR=ON, BORV=3, VREGEN=ON
	CONFIG WDT=OFF, WDTPS=32768
	CONFIG MCLRE=ON, LPT1OSC=OFF, PBADEN=OFF, CCP2MX=OFF
	CONFIG STVREN=ON, LVP=OFF, XINST=OFF, DEBUG=OFF
	CONFIG CP0=OFF, CP1=OFF, CP2=OFF, CPB=OFF, CPD=OFF 
	CONFIG WRT0=OFF, WRT1=OFF, WRT2=OFF
	CONFIG WRTB=OFF, WRTC=OFF, WRTD=OFF
	CONFIG EBTR0=OFF, EBTR1=OFF, EBTR2=OFF
	CONFIG EBTRB=OFF
	CONFIG WRT3=OFF, EBTR3=OFF, CP3=OFF

	constant	RFAST=H'0008'
	constant	RSLOW=H'0009'
	constant	MYRR=H'0010'

	org		0
	goto	Debut

	org		20
Debut
	movlw	0x0f
	movwf	_ADCON1 ;  set all analog to digital conversion module inputs as (normal) digital inputs
	movlw	0x07
	movwf	_CMCON ; turn off comparator module
	movlw	0x00
	movwf	_ADCON0 ; turn off analog to digital conversion module
	movwf	_LATB
	movwf	_TRISB
	movwf	_LATA
	movwf	_TRISA 
	movwf	_LATC
	movwf	_TRISC
	movwf	RFAST
	movwf	RSLOW
	movwf	MYRR

Boucle
	incfsz	RFAST, 1				; Increment du premier registre
	goto	Boucle
	incfsz	RSLOW, 1				; Increment du second registre
	goto	Boucle
	incf	MYRR, 1
	movff	MYRR, _LATB
	movff	MYRR, _LATA
	movff	MYRR, _LATC
	goto	Boucle

	end

