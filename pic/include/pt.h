/*
 * pt.h
 *
 *  Created on: 30.01.2017
 *      Author: Kamil Cukrowski
 */

#ifndef PT_H_
#define PT_H_

/* ----------------------------------------------------------------------------------------- */
/** from https://github.com/zserge/pt/blob/master/pt.h */
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

#include <stddef.h>
#include <stdint.h>

/* Protothread status values */
#define PT_STATUS_STARTED    0x00
#define PT_STATUS_BLOCKED    0x01
#define PT_STATUS_FINISHED   0x02
#define PT_STATUS_YIELDED    0x04
#define PT_STATUS_TIMER_WAIT 0x08

/* Helper macros to generate unique labels */
#define _pt_line3(name, line) _pt_##name##line
#define _pt_line2(name, line) _pt_line3(name, line)
#define _pt_line(name) _pt_line2(name, __LINE__)

#if defined(PT_USE_SETJMP)
/*
 * Local continuation that uses setjmp()/longjmp() to keep thread state.
 *
 * Pros: local variables are preserved, works with all control structures.
 * Cons: slow, may erase global register variables.
 */
#include <setjmp.h>
#include <stdbool.h>
struct pt {
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
struct pt {
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
 * BUG: __LINE__ is assigned to label and label is uint16_t
 * This implementation may break on files longer then 32768 lines.
 * Probably this could be fixed using smth like BOOST_PP_COUNTER.
 */
struct pt {
  uint16_t label;
  uint8_t status;
};
#define pt_init()                                                              \
  { .label = 0, .status = PT_STATUS_STARTED }
#define pt_begin(pt)                                                           \
  switch ((pt)->label) {                                                       \
  case 0:
#define pt_label(pt, stat)                                                     \
  do {                                                                         \
    (pt)->status = (stat);                                                     \
    (pt)->label = __LINE__;                                                    \
  case __LINE__:;                                                              \
  } while (0)
#define pt_end(pt)                                                             \
  pt_label(pt, PT_STATUS_FINISHED);                                            \
  }
#endif

/*
 * Core protothreads API
 */
#define pt_status(pt) (pt)->status

#define pt_wait(pt, cond)                                                      \
  do {                                                                         \
    pt_label(pt, PT_STATUS_BLOCKED);                                           \
    if (!(cond)) {                                                             \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define pt_wait_for(pt, cond)                                                  \
  pt_wait((pt), (cond))

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

#define pt_reset(ptpnt) do { *(ptpnt) = (struct pt)pt_init(); } while(0)
#define pt_restart(ptpnt) pt_reset(ptpnt)

#endif /* PT_H_ */
