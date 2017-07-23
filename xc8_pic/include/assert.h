/*
 * assert.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef ASSERT_H_
#define ASSERT_H_ 1

extern void __assert (const char *__assertion, const char *__file, unsigned int __line);

#define assert(expr)                                                   \
    ((expr)                                                            \
     ? ((void)(0))                                                     \
     : __assert (#expr, __FILE__, __LINE__))

#ifndef static_assert
# ifdef __XC
#  pragma warning disable 350  // unused typedef
# endif
# define static_assert_2(expr) do{ typedef char static_assert[(!!(expr))*2-1]; }while(0)
# define static_assert_1(expr) static_assert_2((expr))
# define static_assert(expr)   static_assert_1((expr))
#endif

#endif /* ASSERT_H_ */
