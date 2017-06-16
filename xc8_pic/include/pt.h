/**MIT License

Copyright (c) 2016 Serge Zaitsev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.**/
/* ----------------------------------------------------------------------------------------- */
/** from https://github.com/zserge/pt/blob/master/pt.h */
/*
 *  Created on: 30.01.2017
 *  Changes by: Kamil Cukrowski
 *
 */

#ifndef PT_H_
#define PT_H_

#include <stddef.h>
#include <stdint.h>

#define PT_USE_BOOST_PP_COUNTER

/* Protothread status values */
#define PT_STATUS_STARTED    0x00
#define PT_STATUS_BLOCKED    0x01
#define PT_STATUS_FINISHED   0x02
#define PT_STATUS_YIELDED    0x04
#define PT_STATUS_TIMER_WAIT 0x08

#if defined(PT_USE_SETJMP)

/*
 * Local continuation that uses setjmp()/longjmp() to keep thread state.
 *
 * Pros: local variables are preserved, works with all control structures.
 * Cons: slow, may erase global register variables.
 */
#include <setjmp.h>
#include <stdbool.h>
struct pt_s {
  jmp_buf env;
  bool isset;
  uint8_t status;
};
#define pt_init()                                                              \
  { .isset = 0, .status = PT_STATUS_STARTED }
#define pt_begin(pt)                                                           \
  do {                                                                         \
    if ((pt)->isset) {                                                         \
      longjmp((pt)->env, 0);                                                   \
    }                                                                          \
  } while (0)
#define pt_label(pt, stat)                                                     \
  do {                                                                         \
    (pt)->status = (stat);                                                     \
    (pt)->isset = 1;                                                           \
    setjmp((pt)->env);                                                         \
  } while (0)
#define pt_end(pt) pt_label(pt, PT_STATUS_FINISHED)

#elif defined(PT_USE_GOTO) || defined(__GNUC__) || defined(__clang__)

/*
 * Local continuation based on labels as values compiler extension.
 *
 * Pros: works with all control structures.
 * Cons: requires GCC or Clang, doesn't preserve local variables.
 */

/* Helper macros to generate unique labels */
#define _pt_line3(name, line) _pt_##name##line
#define _pt_line2(name, line) _pt_line3(name, line)
#define _pt_line(name) _pt_line2(name, __LINE__)

struct pt_s {
  void *label;
  uint8_t status;
};
#define pt_init()                                                              \
  { .label = NULL, .status = PT_STATUS_STARTED }
#define pt_begin(pt)                                                           \
  do {                                                                         \
    if ((pt)->label != NULL) {                                                 \
      goto *(pt)->label;                                                       \
    }                                                                          \
  } while (0)

#define pt_label(pt, stat)                                                     \
  do {                                                                         \
    (pt)->status = (stat);                                                     \
    (pt)->label = &&_pt_line(label);                                           \
  _pt_line(label) :;                                                           \
  } while (0)
#define pt_end(pt) pt_label(pt, PT_STATUS_FINISHED)

#else
/*
 * Local continuation based on switch/case and line numbers.
 *
 * Pros: works with any C99 compiler, most simple implementation.
 * Cons: doesn't allow more than one label per line, doesn't preserve local
 * variables.
 *
 */
#if !defined(PT_USE_BOOST_PP_COUNTER)
/**
 * This is the same as implementation above, but
 * - we have shorten label to uint8_t.
 * - label name is derived from BOOST_PP_COUNTER
 * Usage example:
	pt_begin(&pt);
	// YOUR CODE HERE
	pt_yield(&pt);
#include BOOST_PP_UPDATE_COUNTER()
	// YOUR CODE HERE
	pt_yield(&pt);
#include BOOST_PP_UPDATE_COUNTER()
	// YOUR CODE HERE
	pt_end(&pt);
 *
 */
#define PT_LABEL_TYPE          uint8_t
#define PT_LABEL_LABELVAL_END  0xff
#define PT_LABEL_LABELVAL      BOOST_PP_COUNTER
#else // defined (PT_USE_GOTO)
#define PT_LABEL_TYPE          uint16_t
#define PT_LABEL_LABELVAL_END  1
#define PT_LABEL_LABELVAL     __LINE__
#endif

struct pt_s {
	PT_LABEL_TYPE    label;
	uint8_t          status;
};

#define pt_init()           { 0, PT_STATUS_STARTED }

#define pt_init_ended()     { PT_LABEL_LABELVAL_END, PT_STATUS_STARTED }

#define pt_begin(pt)                                                           \
  switch ((pt)->label) {                                                       \
  case 0:

#define pt_label_label(pt, stat, labelval)                                     \
    do {                                                                       \
      (pt)->status = (stat);                                                   \
      (pt)->label = (labelval);                                                \
  case (labelval):;                                                            \
    } while (0)

#define pt_label(pt, stat)  pt_label_label(pt, stat, PT_LABEL_LABELVAL)

#define pt_end(pt)                                                             \
    pt_label_label(pt, PT_STATUS_FINISHED, PT_LABEL_LABELVAL_END);             \
  }

#endif

/* ------------------------------------------------------------------------------------- */

/*
 * Core protothreads API
 */
#define pt_status(pt) (pt)->status

#define pt_wait_until(pt, cond)                                                \
  do {                                                                         \
    pt_label(pt, PT_STATUS_BLOCKED);                                           \
    if (!(cond)) {                                                             \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define pt_wait_while(pt, cond)                                                \
  do {                                                                         \
    pt_label(pt, PT_STATUS_BLOCKED);                                           \
    if ((cond)) {                                                              \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define pt_label_wait_while(pt, label, stat)                                   \
  do {                                                                         \
    pt_label(pt, label);                                                       \
    if ((cond)) {                                                              \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define pt_yield(pt)                                                           \
  do {                                                                         \
    pt_label(pt, PT_STATUS_YIELDED);                                           \
    if (pt_status(pt) == PT_STATUS_YIELDED) {                                  \
      (pt)->status = PT_STATUS_BLOCKED;                                        \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define pt_exit(pt, stat)                                                      \
  do {                                                                         \
    pt_label(pt, stat);                                                        \
    return;                                                                    \
  } while (0)

#define pt_loop(pt, cond)                                                      \
  for (int _intr = 0; _intr == 0;)                                             \
    if (1) {                                                                   \
      pt_label(pt, PT_STATUS_BLOCKED);                                         \
      if (!(cond)) {                                                           \
        break;                                                                 \
      }                                                                        \
      goto _pt_line(body);                                                     \
    } else                                                                     \
      while (1)                                                                \
        if (1) {                                                               \
          _intr = 1;                                                           \
          break;                                                               \
        } else                                                                 \
          while (1)                                                            \
            if (1) {                                                           \
              return;                                                          \
            } else                                                             \
  _pt_line(body) :

/*
 * Queues
 */
#define pt_queue(T, size)                                                      \
  struct {                                                                     \
    T buf[size];                                                               \
    unsigned int r;                                                            \
    unsigned int w;                                                            \
  }
#define pt_queue_init()                                                        \
  { .r = 0, .w = 0 }
#define pt_queue_len(q) (sizeof((q)->buf) / sizeof((q)->buf[0]))
#define pt_queue_cap(q) ((q)->w - (q)->r)
#define pt_queue_empty(q) ((q)->w == (q)->r)
#define pt_queue_full(q) (pt_queue_cap(q) == pt_queue_len(q))
#define pt_queue_reset(q) ((q)->w = (q)->r = 0)

#define pt_queue_push(q, el)                                                   \
  (!pt_queue_full(q) && ((q)->buf[(q)->w++ % pt_queue_len(q)] = (el), 1))
#define pt_queue_peek(q)                                                       \
  (pt_queue_empty(q) ? NULL : &(q)->buf[(q)->r % pt_queue_len(q)])
#define pt_queue_pop(q)                                                        \
  (pt_queue_empty(q) ? NULL : &(q)->buf[(q)->r++ % pt_queue_len(q)])

/*
 * Wrapper for system calls and other functions that return -1 and set errno
 */
#define pt_sys(pt, call)                                                       \
  pt_wait(pt,                                                                  \
          (errno = 0) ||                                                       \
              !(((call) == -1) && (errno == EAGAIN || errno == EWOULDBLOCK ||  \
                                   errno == EINPROGRESS || errno == EINTR)))

#define pt_restart(ptpnt) do {                                                 \
	(ptpnt)->label = 0;                                                        \
	(ptpnt)->status = PT_STATUS_STARTED;                                       \
} while(0)

#define pt_stop(ptpnt) do{                                                     \
	(ptpnt)->label = PT_LABEL_LABELVAL_END,                                    \
	(ptpnt)->status = PT_STATUS_ENDED;                                         \
}while(0)


/* -------------------------------- pt with timeout ----------------------- */

#endif /* PT_H_ */
