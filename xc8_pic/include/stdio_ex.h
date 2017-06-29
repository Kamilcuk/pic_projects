/*
 * stdio_ex.h
 *
 *  Created on: 31.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef STDIO_EX_H_
#define STDIO_EX_H_

#include <stdio.h> // putchar() getchar() printf()
#include <stdbool.h>

/**
 * Check if calling getchar() will block.
 * Corresponds with ( !feof(stdin) ) on a POSIX system.
 * This is only predeclaration, implementation is program specific.
 */
extern bool getchar_ready();

/**
 * Flush putchar() buffers.
 * Corresponds with fflush(stdout) on POSIX system.
 * This is only predeclaration, implementation is program specific.
 */
extern void flush();

#endif /* STDIO_EX_H_ */
