#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/*
 * based on http://comments.gmane.org/gmane.comp.compilers.sdcc.user/3915
 * response from Raphael Neider thank you
 * */
/* CODE can't touch INTCON register (isn't that obvious ?) */
#define _CRITICAL_(CODE) do { \
  const unsigned char __intcon_save = INTCON; \
  INTCON &= ((~0xC0)); \
  do { CODE } while (0); \
  INTCON = __intcon_save; \
} while(0)

#define ATOMIC_BLOCK(CODE) _CRITICAL_(CODE)
#define NO_INTERRUPT_BLOCK(CODE) _CRITICAL_(CODE)

#endif // INTERRUPT_H_
