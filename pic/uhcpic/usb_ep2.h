/*
 * usb_ep2.h
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 * 
 */
#ifndef  _USB_EP2_H_
#define  _USB_EP2_H_

extern void USB_EP2_init(void);
extern void USB_EP2_set(const void __near *buffer, unsigned char len);
extern void USB_EP2_transmission(void);

#endif // _USB_EP2_H_

