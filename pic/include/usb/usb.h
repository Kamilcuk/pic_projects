/*
 * usb.h - function declaration for use in main loop/thread/interrupt
 * 
 * Under BEER-WARE license 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 */
#ifndef _USBLIB_H_
#define _USBLIB_H_

#include <pic18fregs.h>

/* interrupts *SHOULD* be disabled in here */
#define USB_interrupt_service() do { PIR2bits.USBIF = 0; USB_service(); }while( PIR2bits.USBIF )

#define USB_interrupt_priority_high() do{ IPR2bits.USBIP = 1; }while(0)

#define USB_interrupt_priority_low() do{ IPR2bits.USBIP = 0; }while(0)

#define USB_interrupt_enable() do{ PIE2bits.USBIE = 1; }while(0)

#define USB_interrupt_disable() do{ PIE2bits.USBIE = 0; }while(0)

#define USB_interrupt() ((PIR2bits.USBIF))
#define USB_interrupt_clear() do{ PIR2bits.USBIF = 0; } while(0)
#define USB_interrupt_set() do{ PIR2bits.USBIF = 1; } while(0)

extern void USB_init(void);
#define USB_disable() do { UIE = UIR = UIRbits.TRNIF = UADDR = UCON = UCFG = 0; UCFGbits.UTRDIS = 1; }while(0)
//extern void USB_disable(void);
extern void USB_wait_for_powerered_state(void);
extern void USB_wait_for_configured_state(void);
extern void USB_reset(void);
extern void USB_service(void); 

#endif // _USBLIB_H_
