/*
 * cmdline.h
 *
 *  Created on: 31.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef CMDLINE_H_
#define CMDLINE_H_

#define CMDLINE_BACKSPACE_ENABLED 1 // takes ~41 lines of assembly code

/**
 *
 */
struct cmdline_s {
	char buff[20];
	unsigned char buffpos;
};

/**
 * state struct
 */
extern struct cmdline_s cmdline;

/**
 * user callback function
 */
void cmdlineService_callback(void);

/**
 * Services my standart requests
 */
void cmdlineService_standard(void);

/**
 * Service command line in a blocking fashion.
 */
void cmdlineService(void);

/**
 * Service command line in a non-blocking fashion.
 */
void cmdlineServiceThread(void);

#endif /* CMDLINE_H_ */
