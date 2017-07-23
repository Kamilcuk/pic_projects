/*
 * test_output.c
 *
 *  Created on: 20 lip 2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */
#include "system.h"

#if CFG_TEST == CFG_TEST_OUTPUT

#include <xc.h>
#include <stdio.h>
#include <stdint.h>

void main_test() {
	for(uint8_t i=0;;++i) {
		printf(" i=%d \n", i);
		__delay_ms(100);
	}
}

#endif
