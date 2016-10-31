#ifndef _USB_EP1_H_
#define  _USB_EP1_H_

void godpic_flush();
void godpic_putc(char src);
void godpic_puts(char *src);

extern void USB_EP1_init(void);
extern void USB_EP1_transmission(void);


#endif // _USB_EP1_H_

