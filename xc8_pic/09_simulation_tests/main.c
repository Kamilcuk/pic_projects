/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <system.h>

#include <mdb.h>
#include <common.h>

void main_test();

MDB_UART_PUTCH_DECLARE()

void main()
{
	COMMON_MAIN_PREINIT();
	MDB_UART_INIT();
	main_test();
}

