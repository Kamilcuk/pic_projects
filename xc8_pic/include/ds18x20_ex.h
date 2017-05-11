/*
 *        File: ds18b20_ex.h
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef DS18X20_EX_H_
#define DS18X20_EX_H_

#include <onewire.h>
#include <ds18x20.h>
#include <stdint.h>

struct ds18x20_s {
	uint8_t romcode[OW_ROMCODE_SIZE];
};

/**
 * Finds all ds18x20 devices connected and stores theirs information inro ds18x20 struct.
 * @param sensors array of struct ds18b20_s
 * @param sensorslen length of sensors array
 * @return number of sensors found
 * example:
 *
#define MAXSENSORS 15
struct ds18x20_s gSensorIDs[MAXSENSORS];
ret = DS18X20_search_sensors(gSensorIDs, MAXSENSORS);
* * whatever *
 * */
uint8_t DS18X20_search_sensors(struct ds18x20_s *sensors, const uint8_t sensorslen);

#endif /* DS18X20_EX_H_ */
