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
 * To use SwSpiWrite define in system.h:
 * SW_SPI_SCK_PORT
 * SW_SPI_SCK_PIN
 * SW_SPI_OUT_PORT
 * SW_SPI_OUT_PIN
 */
#if defined(SW_SPI_SCK_PORT) && defined(SW_SPI_SCK_PIN) && defined(SW_SPI_OUT_PORT) && defined(SW_SPI_OUT_PIN)

/**
 * Write blockingly SPI in MODE0
 */
void SwSpiWrite(char input);

#endif

#endif /* SWSPIWRITE_H_ */
