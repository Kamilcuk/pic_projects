/*
 * swSpiWrite.h
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#ifndef SWSPI_H_
#define SWSPI_H_

#include <system.h> // SW_SPI_PORT , SW_SPI_PIN

/**
 * Example:
 * To use SwSpi* define in system.h:
#define SW_SPI_SCK_PORTPIN A,2
#define SW_SPI_OUT_PORTPIN A,3
#define SW_SPI_IN_PORTPIN  A,4
 */

void SwSpiTransmit(char input);
char SwSpiReceive(void);
char SwSpiTransmitReceive(char input);

#endif /* SWSPI_H_ */
