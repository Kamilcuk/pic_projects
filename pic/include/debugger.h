#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <usart.h>

void debugger_init()
{
	unsigned char i;
	usart_open(
		USART_TX_INT_OFF &
		USART_RX_INT_OFF &
		USART_BRGH_LOW &
		USART_EIGHT_BIT &
		USART_CONT_RX &
		USART_ASYNCH_MODE,
		77
	);
	for(i=0xff;i;i--)
		__asm NOP __endasm;
}

#endif /* DEBUGGER_H */
