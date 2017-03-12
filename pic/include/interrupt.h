#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/*
 * based on http://comments.gmane.org/gmane.comp.compilers.sdcc.user/3915
 * response from Raphael Neider thank you
 * */
/* CODE can't touch INTCON register (isn't that obvious ?) */
#define __CRITICAL__(CODE) do { \
  const unsigned char __intcon_save = INTCON; \
  INTCON &= ((~0xC0)); \
  do { CODE } while (0); \
  INTCON = __intcon_save; \
} while(0)

#define ATOMIC_BLOCK(CODE) __CRITICAL__(CODE)

#endif // INTERRUPT_H_
