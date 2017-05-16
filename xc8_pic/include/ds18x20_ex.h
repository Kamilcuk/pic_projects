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

/**
 * Pullup transistor:
The 1-Wire bus must be switched to the strong pullup within
10µs (max) after a Convert T [44h] or Copy Scratchpad
[48h] command is issued, and the bus must be held high
by the pullup for the duration of the conversion (tCONV)
or data transfer (tWR = 10ms). No other activity can take
place on the 1-Wire bus while the pullup is enabled.
 *
 * After functions DS18X20_start_meas() and DS18X20_scratchpad_to_eeprom()
 * You must enable transistor pullup
 */

#endif /* DS18X20_EX_H_ */
