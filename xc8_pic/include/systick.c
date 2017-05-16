/*
 * systick.c
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "systick.h"

#include <xc.h> // di ei
#include <stdbool.h>
#include <interrupt.h>

volatile systick_t systick_counter = 0;

bool systickTimeoutElapsed(systick_t tick, systick_t timeout)
{
	bool ret;
	systick_t systick_buff;
	ATOMIC_CODE(
			systick_buff = systick_counter;
	);
	ret = ( tick < systick_buff ) || ( ((systick_t)( tick -systick_buff )) > timeout );
	return ret;
}
