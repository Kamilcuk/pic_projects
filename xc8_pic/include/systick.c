/*
 * systick.c
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "systick.h"

#include <stdbool.h>
#include <interrupt.h> // ATOMIC_CODE

volatile systick_t systick_counter = 0;

systick_t systickGet(void)
{
	systick_t systick_buff;
	ATOMIC_CODE(
		systick_buff = systick_counter;
	);
	return systick_buff;
}

bool systickElapsed(systick_t Tickstop, systick_t MaxMargin)
{
	systick_t systick_buff;
	ATOMIC_CODE(
		systick_buff = systick_counter;
	);
	return
			( Tickstop < systick_buff ) ||
			(
					(
							Tickstop < MaxMargin ?
							((systick_t)(SYSTICK_MAX_VALUE - MaxMargin + Tickstop)) :
							((systick_t)(Tickstop - MaxMargin))
					) > systick_buff
			);
}

bool systickElapsed_unsafe(systick_t Tickstop)
{
	systick_t systick_buff;
	ATOMIC_CODE(
		systick_buff = systick_counter;
	);
	return Tickstop < systick_buff;
}
