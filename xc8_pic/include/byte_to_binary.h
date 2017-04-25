#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

/*
 *
 * from http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
 * usage: printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
 */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (((byte) & 0x80) ? '1' : '0'), \
  (((byte) & 0x40) ? '1' : '0'), \
  (((byte) & 0x20) ? '1' : '0'), \
  (((byte) & 0x10) ? '1' : '0'), \
  (((byte) & 0x08) ? '1' : '0'), \
  (((byte) & 0x04) ? '1' : '0'), \
  (((byte) & 0x02) ? '1' : '0'), \
  (((byte) & 0x01) ? '1' : '0') 

#endif	/* XC_HEADER_TEMPLATE_H */

