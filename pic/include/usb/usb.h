/*
 * usb.h - function declaration for use in main loop/thread/interrupt
 * 
 * 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
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
