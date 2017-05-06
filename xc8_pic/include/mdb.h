/*
 * mdb.h
 *
 *  Created on: 01.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#ifndef MDB_H_
#define MDB_H_

#include <system.h>

#define MDB_UART_INIT() do{ \
	TRISC = 0xFF; \
	RCSTA = 0xB0; \
	TXSTA = 0x24; \
	SPBRG = 0x12; \
} while(0)

#define MDB_UART_PUTCH_DECLARE() void putch(char data) { \
	while(!TXIF); \
	TXREG = data; \
}

#endif // MDB_H_
