/*
 * swSpiWrite.h
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#ifndef SWSPIWRITE_H_
#define SWSPIWRITE_H_

#include <system.h> // SW_SPI_PORT , SW_SPI_PIN

/**
 * Example:
 * To use SwSpiWrite define in system.h:
#define SW_SPI_SCK_PORT A
#define SW_SPI_SCK_PIN  2
#define SW_SPI_OUT_PORT A
#define SW_SPI_OUT_PIN  3
 * or define:
#define SW_SPI_SCK_PORTPIN A, 2
#define SW_SPI_OUT_PORTPIN A, 3
 */

/**
 * Write blocking SPI. Mode is MODE0
 */
void SwSpiWrite(char input);

#endif /* SWSPIWRITE_H_ */
