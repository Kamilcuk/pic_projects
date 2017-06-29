/*
 * assert.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef ASSERT_H_
#define ASSERT_H_ 1

#include <system.h> // configuration - ASSERT_USE_*

extern void __assert (const char *__assertion, const char *__file, unsigned int __line);

# define assert(expr)                                                  \
    ((expr)                                                            \
     ? ((void)(0))                                                     \
     : __assert (#expr, __FILE__, __LINE__))

#ifndef static_assert
# ifdef __XC
#  pragma warning disable 350  // unused typedef
# endif
# define static_assert(expr) do{ typedef char static_assert[(!!(expr))*2-1]; }while(0)
#endif

#endif /* ASSERT_H_ */
