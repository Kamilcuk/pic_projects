/*
 * usb_ep0.c
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 * Code based on and thanks to:
 * thank you Bradley A. Minch from Organization: Franklin W. Olin College of Engineering for lab1.c
 * thank you Pierre Gaufillet <pierre.gaufillet@magic.fr> for PUF (PIC USB Framework)
 * thank you Microchip for Microchip USB C18 Firmware Version 1.0 (and other versions, too!)
 */
 /* 
  * TODO: standart requests: SYNCH_FARME. 
  * TODO: in_buffer can be allocated on stack (IMAGINE THAT !) 
  * 	but (HELL!) it would need to allocate memory at 0x500 to 0x7ff
  * 	so we would need (teoretically) to make out own malloc implementation
  * 	with many memory blocks (now, IMAGINE THAT!)
  */


#include "usb/usb_usb.h"
#include "types.h"

#pragma udata usb_buff USB_EP0_in_buffer
#pragma udata usb_buff USB_EP0_out_buffer
static volatile unsigned char USB_EP0_out_buffer[ USB_EP0_BUFFERING_NUMBER ? 2 : 1 ][EP0_BUFFER_SIZE];
static volatile unsigned char USB_EP0_in_buffer [ (USB_EP0_BUFFERING_NUMBER/2) + 1 ][EP0_BUFFER_SIZE];

struct {
	unsigned char len; // bytes to send
	unsigned char *buff; // code pointer to buff to be sended
} static USB_EP0_to_send;

/** name: USB_EP0_send_packet_desc(void)
 * =>note: this is used to send descriptor strings
 */
static unsigned char USB_EP0_fill_adr(unsigned char __near *adr) 
{
	unsigned char USB_packet_length;
	unsigned char i;
	
	if ( USB_EP0_to_send.len < EP0_BUFFER_SIZE ) {
		i = USB_packet_length = USB_EP0_to_send.len;
		USB_EP0_to_send.len = 0x00;
	} else {
		i = USB_packet_length = EP0_BUFFER_SIZE;
		USB_EP0_to_send.len -= EP0_BUFFER_SIZE;
	}
	
	for (; i; i--) {
		*adr = *USB_EP0_to_send.buff;
		USB_EP0_to_send.buff++;
		adr++;
	}
	
	return USB_packet_length;
}

/* name: USB_request_error
 * usb documentation:
 * 9.2.7 Request Error
   When a request is received by a device that is not defined for the device, is inappropriate for the current
   setting of the device, or has values that are not compatible with the request, then a Request Error exists.
   The device deals with the Request Error by returning a STALL PID in response to the next Data stage
   transaction or in the Status stage of the message. It is preferred that the STALL PID be returned at the next
   Data stage transaction, as this avoids unnecessary bus activity.
 */
static void USB_request_error(void) 
{
	usb_bd_t __near  * const bd_out = USB_BD_OUT_EP0();
	usb_bd_t __near  * const bd_in = USB_BD_IN_EP0();
	#ifdef USB_EP0_BUFFERING_PING_PONG_IN
	usb_bd_t __near  * const bd_in_next = USB_BD_IN_EP0_NEXT();
	#endif
	
	USB_PDEBUG_EP0("E");
	
	bd_out->cnt  = EP0_BUFFER_SIZE;
	bd_out->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN | BD_STAT_BSTALL;
	bd_in->stat = BD_STAT_USIE | BD_STAT_BSTALL;
	#ifdef USB_EP0_BUFFERING_PING_PONG_IN
	bd_in_next->stat = BD_STAT_USIE | BD_STAT_BSTALL;
	#endif
}

/* name: USB_standart_request
 * arguments: USB_buffer - buffer with controlrequest unformations 
 * process and evaluate any standart request 
 * */
static void USB_standard_request(const struct usb_controlrequest __near * const USB_buffer)
{
	/* ** buffer descriptors to be filled in by this functions */
	
	/* the next IN and OUT buffer descriptors */
	usb_bd_t __near * const bd_out = USB_BD_OUT_EP0();
	usb_bd_t __near * const bd_in = USB_BD_IN_EP0();
#ifdef USB_EP0_BUFFERING_PING_PONG_IN
	// the next after the next IN buffer descriptors
	usb_bd_t __near * const bd_in_next = USB_BD_IN_EP0_NEXT();
#endif
	
	/* ** help variables */
	unsigned char __near * const UEP = (unsigned char __near *)&UEP0;
	usb_bd_t __near  *buf_desc_ptr;
	unsigned char n;
	
	
	/** ################### process standart request ##################### */
	/* fill USB_EP0_to_send struct with data to send
	 *  do requested features and so on
	* bd_in and bd_out are readed from */
	 
	/*
	USB_PDEBUG_EP0("[%x,%x,%x,%x,%x,%x,%x,%x]", 
	USB_buffer->bmRequestType,
	USB_buffer->bRequest,
	USB_buffer->wValueLow,
	USB_buffer->wValueHigh,
	USB_buffer->wIndexLow,
	USB_buffer->wIndexHigh,
	USB_buffer->wLengthLow,
	USB_buffer->wLengthHigh);
	* */
	
	USB_PDEBUG_EP0("[%x,%x,%x,%x]", 
	USB_buffer->bmRequestType,
	USB_buffer->bRequest,
	USB_buffer->wValueLow,
	USB_buffer->wValueHigh);
	
	 
	/* this gets filled/setted when processing standart request */
	USB_EP0_to_send.buff = bd_in->adr;
	USB_EP0_to_send.len = 0;
	
	switch (USB_buffer->bRequest) {
		case USB_REQ_GET_STATUS:
			switch (USB_buffer->bmRequestType&0x1F) {	// extract request recipient bits
				case USB_RECIP_DEVICE:
					USB_EP0_to_send.buff[0] = usbdev.status;
					break;
				case USB_RECIP_INTERFACE:
					switch (usbdev.state) {
						case ADDRESS_STATE:
							goto USB_REQUEST_ERROR;
						case CONFIGURED_STATE:
							if (USB_buffer->wIndexLow >= NUM_INTERFACES) {
								goto USB_REQUEST_ERROR;
							}
							USB_EP0_to_send.buff[0] = 0x00;
					}
					break;
				case USB_RECIP_ENDPOINT:
					/* strip other bytes - get endpoint number */
					n = USB_buffer->wIndexLow&0x0F;
					switch (usbdev.state) {
						case ADDRESS_STATE:
							// get EP, strip off direction bit and see if it is EP0
							if ( n ) {
								goto USB_REQUEST_ERROR;
							}
							// return the BSTALL bit of EP0 IN or OUT, whichever was requested
							USB_EP0_to_send.buff[0] = (((USB_buffer->data_transfer_direction) ? USB_BD_IN_EP0()->stat : USB_BD_OUT_EP0()->stat)&0x04)>>2;
							break;
						case CONFIGURED_STATE:
							// if then ep number is bigger then number of endpoints we have
							if ( n > USB_CONFIG_NUM_ENDPOINTS ) {
								goto USB_REQUEST_ERROR;
							}
							// if the specified EP is disabled for transfers in the specified direction...
							if ( ! (UEP[n] & ((USB_buffer->data_transfer_direction) ? 0x02:0x04)) )  {
								/* set request error - endp is not enabled */
								goto USB_REQUEST_ERROR;
							}
							// compute pointer to the buffer descriptor for the specified EP
							buf_desc_ptr = (USB_buffer->data_transfer_direction) ? USB_BD_IN_EP(n) : USB_BD_OUT_EP(n);
							// return the BSTALL bit of the specified EP
							USB_EP0_to_send.buff[0] = ( (buf_desc_ptr->stat) & 0x04) >> 2;
							break;
						default:
							goto USB_REQUEST_ERROR;
					}
					break;
				default:
					goto USB_REQUEST_ERROR;
			}
			USB_EP0_to_send.buff[1] = 0x00;
			USB_EP0_to_send.len = 2;
			break;
		case USB_REQ_CLEAR_FEATURE:
		case USB_REQ_SET_FEATURE:
			switch (USB_buffer->bmRequestType&0x1F) {	// extract request recipient bits
				case USB_RECIP_DEVICE:
					switch (USB_buffer->wValueLow) {
						case USB_DEVICE_REMOTE_WAKEUP:
							if (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE)
								usbdev.status &= ~USB_DEVICE_REMOTE_WAKEUP;
							else
								usbdev.status |= USB_DEVICE_REMOTE_WAKEUP;
							break;
						default:
							goto USB_REQUEST_ERROR;
					}
					break;
				case USB_RECIP_ENDPOINT:
					// get EP, strip off direction bit, and see if its EP0
					n = USB_buffer->wIndexLow&0x0F;
					switch (usbdev.state) {
						case ADDRESS_STATE:
							/* request error if its not EP0 */
							if ( n ) {
								goto USB_REQUEST_ERROR;
							}
							break;
						case CONFIGURED_STATE:
							buf_desc_ptr =  (USB_buffer->wIndexLow&0x80) ? USB_BD_IN_EP(n) : USB_BD_OUT_EP(n); // compute pointer to the buffer descriptor for the specified EP
							// if the specified EP is disabled for transfers in the specified direction...{
							if (USB_buffer->wIndexLow&0x80) {// if the specified EP direction is IN...
								// if EPn is disabled for IN transfers...
								if ( !(UEP[n]&0x02) ) {
									goto USB_REQUEST_ERROR;
								}
								buf_desc_ptr->stat = (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE) ? 0x00:0x84; 
							} else {
								// ...otherwise the specified EP direction is OUT, so...
								// if EPn is disabled for OUT transfers...
								if ( !(UEP[n]&0x04) ) {
									goto USB_REQUEST_ERROR;
								}
								buf_desc_ptr->stat = (USB_buffer->bRequest == USB_REQ_CLEAR_FEATURE) ? 0x88:0x84;
							}
							break;
						default:
							goto USB_REQUEST_ERROR;
					}
					break;
				default:
					goto USB_REQUEST_ERROR;
			}
			break;
		case USB_REQ_SET_ADDRESS:
			// save address value
			USB_EP0_to_send.len = USB_buffer->wValueLow;
			// if new device address is illegal, send Request Error
			if (USB_EP0_to_send.len > 0x7F)
				goto USB_REQUEST_ERROR;
			// pending a SET_ADDRESS request
			usbdev.state = ADDRESS_PENDING_STATE;
			break;
		case USB_REQ_GET_DESCRIPTOR:
			switch ( USB_buffer->wValueHigh ) {
				case USB_DT_DEVICE:
					switch (USB_buffer->wValueLow != 0) {
						goto USB_REQUEST_ERROR;
					}
					USB_EP0_to_send.buff = (unsigned char *)&device_descriptor;
					USB_EP0_to_send.len = sizeof(device_descriptor);
					break;
				case USB_DT_CONFIG:
					switch (USB_buffer->wValueLow != 0) {
						goto USB_REQUEST_ERROR;
					}
					USB_EP0_to_send.buff = (unsigned char *)&configuration0_descriptor;
					USB_EP0_to_send.len = sizeof(configuration0_descriptor);
					break;
				case USB_DT_STRING:
					switch (USB_buffer->wValueLow) {
						case 0:
							USB_EP0_to_send.buff = (unsigned char *)string0_descriptor;
							USB_EP0_to_send.len = sizeof(string0_descriptor);
							break;
						case 1:
							USB_EP0_to_send.buff = (unsigned char *)string1_descriptor;
							USB_EP0_to_send.len = sizeof(string1_descriptor);
							break;
						case 2:
							USB_EP0_to_send.buff = (unsigned char *)string2_descriptor;
							USB_EP0_to_send.len = sizeof(string2_descriptor);
							break;
						case 3:
							USB_EP0_to_send.buff = (unsigned char *)string3_descriptor;
							USB_EP0_to_send.len = sizeof(string3_descriptor);
							break;
						default:
							goto USB_REQUEST_ERROR;
					}
					break;
				default:
					goto USB_REQUEST_ERROR;
			}
			break;
		case USB_REQ_GET_CONFIGURATION:
			USB_EP0_to_send.buff = (unsigned char *)&configuration0_descriptor;
			USB_EP0_to_send.len = sizeof(configuration0_descriptor);
			break;
		case USB_REQ_SET_CONFIGURATION:
			switch (USB_buffer->wValueLow) {
				case 0:
					usbdev.state = ADDRESS_STATE;
					break;
				case CONFIGURATION0_BCONFIGURATIONVALUE:
					USB_clear_all_EP_exept_EP0();
					USB_configuration0_endps_init();
					usbdev.state = CONFIGURED_STATE;
					usbdev.config = CONFIGURATION0_BCONFIGURATIONVALUE;
					break;
				/* place for other configurations cases */
				default:
					goto USB_REQUEST_ERROR;
			}
			break;
		case USB_REQ_GET_INTERFACE:
			if ( usbdev.state != CONFIGURED_STATE ) {
				goto USB_REQUEST_ERROR;
			}
			switch (USB_buffer->wIndexLow) {
				case 0:
					// send back 0 for bAlternateSetting, we have only one configuration
					USB_EP0_to_send.buff[0] = 0x00;
					break;
				default:
					goto USB_REQUEST_ERROR;
			}
			USB_EP0_to_send.len = 1;
			break;
		case USB_REQ_SET_INTERFACE:
			if ( usbdev.state != CONFIGURED_STATE ) {
				goto USB_REQUEST_ERROR;
			}
			switch (USB_buffer->wValueLow) {
				case 0:		// currently support only bAlternateSetting of 0
					break;
				default:
					goto USB_REQUEST_ERROR;
			}
			break;
		case USB_REQ_SYNCH_FRAME:
			/* not yet implemented */
		case USB_REQ_SET_DESCRIPTOR:
			/* not supported */
		default:
			goto USB_REQUEST_ERROR;
	}
	
	
	/** ###############  set up buffer descriptors  ############## */
	/* bd_in and bd_out are setted here */
	
	if (USB_buffer->data_transfer_direction) { // DIRECTION IN -> DEVICE_TO_HOST
		/*
		 * Control Read:
		 * <SETUP[0]><IN[1]><IN[0]>...<OUT[1]> | <SETUP[0]>
		 */
		USB_PDEBUG_EP0("R%x", USB_EP0_to_send.len);
		
		/* ** Prepare IN EP to transfer data to the host. */
		
		//Error check the data stage byte count.  Make sure the user specified
		//value was no greater than the number of bytes the host requested.
		if ( (USB_buffer->wLengthHigh == 0x00) && (USB_buffer->wLengthLow < USB_EP0_to_send.len) ) {
			USB_EP0_to_send.len = USB_buffer->wLengthLow;
		}
		
		if ( USB_EP0_to_send.buff == bd_in->adr ) {
			/* if we get here, it means that data were copied manually */
			bd_in->cnt = USB_EP0_to_send.len;
			/* bd_in->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN; is below */
			#ifdef USB_EP0_BUFFERING_PING_PONG_IN
			bd_in_next->stat = BD_STAT_USIE | BD_STAT_BSTALL;
			#endif
		} else {
			/* copy data */
			bd_in->cnt = USB_EP0_fill_adr(bd_in->adr);
			/* bd_in->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN; is below */
			
			#ifdef USB_EP0_BUFFERING_PING_PONG_IN
			if ( USB_EP0_to_send.len ) {
				/* more to send? copy data to the next bd_in */
				bd_in_next->cnt = USB_EP0_fill_adr(bd_in_next->adr);
				bd_in_next->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN;
			} else {
				/* no more to send, set STALL on next bd_in */
				bd_in_next->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_BSTALL;
			}
			#endif
		}
		
		
	} else { // DIRECTION OUT - HOST_TO_DEVICE
		/* 
		 * Control write:
		 * <SETUP[0]><OUT[1]><OUT[0]>...<IN[1]> | <SETUP[0]>
		 * is not support, any data gets discarted when we receive OUT token
		 * 
		 *  ** AND **
		 * 
		 * No-data Control: 
		 * <SETUP[0]><IN[1]> | <SETUP[0]>
		 */
		USB_PDEBUG_EP0("W");
		
		/* ** Prepare for IN status stage of the control transfer */
		bd_in->cnt = 0;
		/* bd_in->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN; is below */
		
		#ifdef USB_EP0_BUFFERING_PING_PONG_IN
		/* next bd_in should be kept unarmed */
		bd_in_next->stat = BD_STAT_UCPU;
		#endif
		
	}
	/* this is done in any case */
	bd_in->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	
	/* ** Prepare this BD to receive the next SETUP or OUT packet. */
	
	bd_out->cnt = EP0_BUFFER_SIZE;
	bd_out->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	
	return; /* succes */
	
USB_REQUEST_ERROR:
	USB_request_error();
	return;
}

/* -------------  functions used in usb.c -------------- */

/* ------------------ init ----------------- */

static void USB_EP0_init(void)
{
	usb_bd_t __near  *bdpnt;
	unsigned char i = 0;
	
	bdpnt = usb_bd; /* ep0 buffer descriptors start the beginning of usb_bd */
	
	for (i = 0; i < ((sizeof(USB_EP0_out_buffer)/EP0_BUFFER_SIZE)); ++i) {
		bdpnt->cnt = EP0_BUFFER_SIZE;
		bdpnt->adr = USB_EP0_out_buffer[i];     // EP0 OUT gets a buffer
		bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;          // set UOWN bit (SIE MODE)
		
		bdpnt++; /* switch to the next buffer descriptor pointer */
	}
	
	for (i = 0; i < ((sizeof(USB_EP0_in_buffer)/EP0_BUFFER_SIZE)); ++i) {
		bdpnt->adr = USB_EP0_in_buffer[i]; // EP0 IN gets a buffer
		bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA1 | BD_STAT_DTSEN;  // clear UOWN bit (CPU MODE)
		
		bdpnt++; /* switch to the next buffer descriptor pointer */
	}
	
	/* clear USB_EP0_to_send struct */
	USB_EP0_to_send.len = 0;
	USB_EP0_to_send.buff = (unsigned char *)0;
	
	UEP0 = UEP_EPHSHK | UEP_EPOUTEN | UEP_EPINEN; // EP0 is a control pipe and requires an ACK
}

/* ----------- tokens -------- */

__once void USB_EP0_in_token(void)
{
	/* normal buffering:  bd_in = bd_in = usb_bd[number_here];
	 * ping-pong buffering:
	 * ^ current transaction occured on bd_in
	 * ^ next transaction will occur on bd_in
	 * ^ second next transaction will occur on bd_in */
	usb_bd_t __near * const bd_in = USB_BD_IN_EP0_NEXT();
	
	USB_PDEBUG_EP0("I%x", USB_EP0_to_send.len);

	// pending a SET_ADDRESS request ?
	if ( usbdev.state == ADDRESS_PENDING_STATE ) {
		USB_PDEBUG_EP0("A");
		
		/* save new UADDR address */
		UADDR = USB_EP0_to_send.len;
		if ( UADDR ) {
			usbdev.state = ADDRESS_STATE;
		} else {
			usbdev.state = DEFAULT_STATE;
		}
		/* done everything needed */
		return;
	}
	
	if ( USB_EP0_to_send.len ) {
		
		/* fill buffer to send */
		bd_in->cnt = USB_EP0_fill_adr(bd_in->adr);
		
		#ifndef USB_EP0_BUFFERING_PING_PONG_IN
		// toggle the DATA01 bit, clear the PIDs bits, and set the UOWN and DTS bits
		bd_in->stat = BD_STAT_USIE | ((bd_in->stat&BD_STAT_MASK_DTS)^BD_STAT_MASK_DTS) | BD_STAT_DTSEN;
		#else
		// dont toggle the DATA01 bit, clear the PIDs bits, and set the UOWN and DTS bits
		bd_in->stat = BD_STAT_USIE | (bd_in->stat&BD_STAT_MASK_DTS) | BD_STAT_DTSEN;
		#endif
		
	} else {
		
		/* OUT endpoint is armed while processing standart request */
		
		/* no more data - issue stall on in endpoint */
		bd_in->stat = BD_STAT_USIE | BD_STAT_BSTALL;
		
	}
}

__once void USB_EP0_out_token(void)
{
	const usb_bd_t __near * const bd_out = USB_BD_OUT_EP0_PREV();
	USB_PDEBUG_EP0("O%x", bd_out->statbits.PID);
	
	if ( bd_out->statbits.PID == USB_PID_SETUP ) {
		/* input - USB_buffer containint control request information */
		const struct usb_controlrequest __near * const USB_buffer = (struct usb_controlrequest __near *)bd_out->adr;
		
		USB_PDEBUG_EP0("S");
		
		/* strip out request type bits, and check what kind of request this is */
		switch ( ( USB_buffer->bmRequestType )&0x60 ) {
			case USB_TYPE_STANDARD:
				USB_standard_request(USB_buffer); /* USB_buffer is passed for reducing stack allocation */
				break;
			case USB_TYPE_CLASS:
				USB_CLASS_REQUEST();
				break;
			case USB_TYPE_VENDOR:
				USB_VENDOR_REQUEST();
				break;
			default:
				USB_request_error();
		}
		
		/* 
		 * packet processing is diabled, when setup token is receviced
		 * it gets enabled here 
		 * */
		UCONbits.PKTDIS = 0;
		
		
	} else { /* any other token */
		/* 
		 * normal OUT token received or ACK token received or any token different then PID_SETUP
		 * we can get here in two cases:
		 * control write - but we dont support it, 
		 * 	it does not happen anywhere, cause SET_DESCRIPTORS from standart requests
		 * 	returns STALL, so this wouldnt happen
		 * last token of control read: - we need to set up to get the next incoming setup token
		 * 	for safe i set up both tokens. As far as we get here in the last token of control read
		 * 	we return in-token to cpu (it should get stalled when processing the last in_token
		 * */
		USB_PDEBUG_EP0("U");
		/* discard any data when an OUT token */
		USB_EP0_init();
	}
}

