/*
 *        File: ds18b20_ex.h
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
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
