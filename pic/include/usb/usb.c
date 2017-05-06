/*
 * usb.c - usb implementation with defines configuration
 * 
 * 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 * 
 * 
 * 
 * Code based on and thanks to:
 * thank you Bradley A. Minch from Organization: Franklin W. Olin College of Engineering for lab1.c
 * thank you Pierre Gaufillet <pierre.gaufillet@magic.fr> for PUF (PIC USB Framework)
 * thank you Microchip for Microchip USB C18 Firmware Version 1.0 (and other versions, too!)
 * 
 * */
#define __USB__ "0.1.6"
#include <pic18fregs.h>
#include "usb_config.h"

#include "usb/usb_usb.h"
#include "usb_ch9.h"
#include "usb_ep0.h"

/* debug print */
#define USB_PDEBUG(...) //printf_tiny( __VA_ARGS__ )
#define USB_PDEBUG_EP0(...) //printf_tiny( __VA_ARGS__ )

/* declare device descriptors */
#include "usb_dt.c"

#pragma udata usb_bd usb_bd
volatile usb_bd_t __near __at(0x400) usb_bd[USB_BUFFER_DESCRIPTORS_NUMBER];

struct usb_ustat_save usb_ustat;

static struct usb_device_info usbdev; /* internal USB-DEVice info */

/* ----------------- configuration 0 endpoints init -------------- */
static void USB_configuration0_endps_init(void)
{
#ifdef USB_CONFIG_ENDPOINTS_INIT
	USB_CONFIG_ENDPOINTS_INIT();
#endif
}

/* USB_EPs_clear - clear EP1 to EP15, EP0 is not here ! */
static void USB_clear_all_EP_exept_EP0()
{ 
	UEP1 = UEP2 = UEP3 = UEP4 = UEP5 = UEP6 = UEP7 = UEP8 = UEP9 = UEP10 = UEP11 = UEP12 = UEP13 = UEP14 = UEP15 = 0; 
}

/* usb_ep0.c is used as a default endpoint dtherefore inlined here */
#include "usb_ep0.c"

void USB_init(void)
{
#if USB_BUFFER_DESCRIPTOR_MODE >= 2
	unsigned char i;
#endif
	
	UIE = 0x00; // mask all USB interrupts
	UIR = 0x00; // clear all USB interrupt flags
	
	UCFG = 0x14 | USB_BUFFER_DESCRIPTOR_MODE;
	/* UCFG = 0b00010100; 
	bit 7 UTEYE: USB Eye Pattern Test Enable bit
		1 = Eye pattern test enabled
		0 = Eye pattern test disabled
	bit 6 UOEMON: USB OE Monitor Enable bit (1)
		1 = UOE signal active; it indicates intervals during which the D+/D- lines are driving
		0 = UOE signal inactive
	bit 5 Unimplemented: Read as ‘0’
	bit 4 UPUEN: USB On-Chip Pull-up Enable bit (2,3)
		1 = On-chip pull-up enabled (pull-up on D+ with FSEN = 1 or D- with FSEN = 0)
		0 = On-chip pull-up disabled
	bit 3 UTRDIS: On-Chip Transceiver Disable bit (2)
		1 = On-chip transceiver disabled; digital transceiver interface enabled
		0 = On-chip transceiver active
	bit 2 FSEN: Full-Speed Enable bit (2)
		1 = Full-speed device: controls transceiver edge rates; requires input clock at 48 MHz
		0 = Low-speed device: controls transceiver edge rates; requires input clock at 6 MHz
	bit 1-0 PPB1:PPB0: Ping-Pong Buffers Configuration bits
		11 = Even/Odd ping-pong buffers enabled for Endpoints 1 to 15
		10 = Even/Odd ping-pong buffers enabled for all endpoints
		01 = Even/Odd ping-pong buffer enabled for OUT E
	 */
	
	
	while(UIRbits.TRNIF)       // Flush any pending transactions
		UIRbits.TRNIF = 0; // to clear out the USTAT FIFO
	
#if USB_BUFFER_DESCRIPTOR_MODE != 0
	/* 
	 * reset ping-pong buffers 
	 * */
	UCONbits.PPBRST = 1;
#if USB_BUFFER_DESCRIPTOR_MODE >= 2
	/* 
	 * clear allocated ping-pong buffer pointers 
	 * */
	for (i=0; i < USB_BD_PP_PNT_NUMBER; i++)
		usb_ustat.pp_in_pnt[i] = usb_ustat.pp_out_pnt[i] = 0;
#endif
	UCONbits.PPBRST = 0;
#endif
	
	
	UEP0 = 0; 
	USB_clear_all_EP_exept_EP0(); /* clear all enpoints */
	
	UADDR = 0x00; /* clear usb address */
	
	/* UCON = 0b00001000;
	 *               ^ USBEN - enable the USB module and its supporting circuitry 
	 * */
	UCON = 0x08;
	
	
	/* 
	 * default to ATTACHED_STATE
	 * all my devices are powered from usb
	 * */
	usbdev.state = ATTACHED_STATE;
	usbdev.config = 0;
	usbdev.status = 0;
}

/* 
 * macro for that in usb.h , no need to change usbdev.state think
void USB_disable(void)
{
	UIE = UIR = UIRbits.TRNIF = UADDR = UCON = UCFG = 0; 
	UCFGbits.UTRDIS = 1;
	
	usbdev.state = ATTACHED_STATE;
	usbdev.config = 0;
	usbdev.status = 0;
} 
*/

__once void USB_reset(void)
{
	USB_init();
	
	USB_PDEBUG("-RST");
	
	UEIR = 0x00;                       // Clear all USB error flags
	UIR  = 0x00;                        // Clears all USB interrupts
	UEIE = 0b10011111;              // Unmask all USB error interrupts
	UIE  = 0b01111011;               // Enable all interrupts except ACTVIE
	
	usbdev.state = DEFAULT_STATE;
	usbdev.config = 0;
	usbdev.status = 0;
	
	USB_EP0_init(); /* reset EP0 */
}

void USB_wait_for_powerered_state(void)
{
	if ( usbdev.state >= POWERED_STATE )
		/* device already is in that state */
		return;
	
	/*
	 * wait for the first SE0 to end
	 * NOTE: from my experince: on some devices USB module gets broken (pull-up resistors seem to be on fire)
	 * i destroyed 3 pics that way. SO if your device is not working, this is can be one of many places
	 * where your device may sleep(loop) forever 
	 * */ 
	while (UCONbits.SE0);
	usbdev.state = POWERED_STATE;
	UIE = 0x11; /* IDLEIE URSTIE */
}


/* ----------------- USB_service ------------------------- */
void USB_service(void)
{
	/*
	 *  we dont need to check if we are in POWERED_STATE, cause when we are,
	 *  we will mask ALL interrupts here, so no worries
	 * */
	UIR &= UIE; /* mask UIE only bits in UIR register */
	
	/*
	 * Task A: Service USB Activity Interrupt
	 */
	if (UIRbits.ACTVIF) {/* Activity on bus detected */
		UIEbits.ACTVIE = 0;
		UCONbits.SUSPND = 0;
		do { UIRbits.ACTVIF = 0; } while (UIRbits.ACTVIF); /* documentation page 179 */
		USB_ACTIVE_FUNCTION();
	} else
	
	/*
	 * Task B: Service USB Bus Reset Interrupt.
	 * When bus reset is received during suspend, ACTVIF will be set first,
	 * once the UCONbits.SUSPND is clear, then the URSTIF bit will be asserted.
	 * This is why URSTIF is checked after ACTVIF.
	 */
	if (UIRbits.URSTIF) {
		USB_reset();
	} else
	
	/*
	 * Task C: Service other USB interrupts
	 */
	if (UIRbits.IDLEIF) { /* Idle condition detected */
		UIRbits.IDLEIF  = 0;
		UIEbits.ACTVIE = 1;
		UCONbits.SUSPND = 1;
		USB_SUSPEND_FUNCTION();
	} else
	if (UIRbits.SOFIF) { /* START-OF-FRAME token was received */
		UIRbits.SOFIF = 0;
	} else
	if (UIRbits.STALLIF) {
		UIRbits.STALLIF = 0;
	} else 
	if (UIRbits.UERRIF) {
		UIRbits.UERRIF = 0;
		UEIR = 0x00;
	} else
	
	/*
	 * Task D: Servicing USB Transaction Complete Interrupt
	 */
	if (UIRbits.TRNIF) {
		unsigned char i = 4;
		unsigned char endp;
		
		/*
		 * Drain or deplete the USTAT FIFO entries.  If the USB FIFO ever gets full, USB bandwidth 
		 * utilization can be compromised, and the device won't be able to receive SETUP packets.
		 * */
		do { /* }  while ( i is set &&  TRNIF is set && no other usb signal was received */
			
			/* put endpoint info on stack, for faster usage */
			endp = USTATbits.ENDP;
			
			/* save ustat register to our special variable */
			usb_ustat.USTAT = USTAT;
			
			/* when servicing setup token packet processing is disabled
			 * (so nothing happens here, when setup token is received)
			 * and USTAT is saved to out special variable (see above)
			 * (so USTAT can be changed here by the SIE with no consequences)
			 * we can safely flush the transaction right now */
			UIRbits.TRNIF = 0;
			
			/* increase our in pointer in ping-pong buffers HERE[!] */
			#if USB_BUFFER_DESCRIPTOR_MODE >= 2
			if (usb_ustat.USTATbits.DIR)
				USB_BD_PP_IN_PNT_INC(endp);
			else
				USB_BD_PP_OUT_PNT_INC(endp);
			#endif
			
			/* service incoming transaction */
			switch (endp) {
				case 0:
					USB_PDEBUG_EP0("-");
					if (usb_ustat.USTATbits.DIR)
						/* DIR = 1 -> transfer in */
						USB_EP0_in_token(); 
					else
						/* DIR = 0 -> transfer out */
						USB_EP0_out_token();
					break;
			
#define USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(x) \
				case ( (x) ): \
					USB_EP ## x ## _TRANSMISSION(); \
					break;
			
				#if (1) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(1)
				#endif
				#if (2) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(2)
				#endif
				#if (3) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(3)
				#endif
				#if (4) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(4)
				#endif
				#if (5) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(5)
				#endif
				#if (6) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(6)
				#endif
				#if (7) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(7)
				#endif
				#if (8) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(8)
				#endif
				#if (9) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(9)
				#endif
				#if (10) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(10)
				#endif
				#if (11) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(11)
				#endif
				#if (12) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(12)
				#endif
				#if (13) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(13)
				#endif
				#if (14) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(14)
				#endif
				#if (15) <= USB_CONFIG_NUM_ENDPOINTS
				USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE(15)
				#endif
		
#undef USB_CONFIG_NUM_ENDPOINTS_TRANSMISSION_ADD_CASE
			} /* switch (endp) */
		
		--i;
		} while (i && UIRbits.TRNIF && !(UIR&0xf7) );
	}
}

void USB_wait_for_configured_state(void) 
{
	USB_wait_for_powerered_state();
	while ( usbdev.state < CONFIGURED_STATE )
		/* btw, what happens if we get disconnected ? (loop forever!) */
		USB_service();
}
