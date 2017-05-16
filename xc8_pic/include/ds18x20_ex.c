/*
 *        File: ds18b20_ex.c
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <ds18x20_ex.h>

#include <onewire.h>

uint8_t DS18X20_search_sensors(struct ds18x20_s *sensors, const uint8_t sensorslen)
{
	uint8_t diff = OW_SEARCH_FIRST;
	uint8_t nSensors = 0;

	while(nSensors < sensorslen) {
		if ( DS18X20_find_sensor( &diff, &sensors->romcode[0] ) == DS18X20_ERROR ){
			break;
		}
		++sensors;
		++nSensors;
	}
	if ( diff == OW_LAST_DEVICE ) {
		++nSensors;
	}

	return nSensors;
}
