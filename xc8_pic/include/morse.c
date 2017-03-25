
#include "system.h"


#define MORSE_ON() do { PORTA = PORTB = PORTC = 0xff; }while(0)
#define MORSE_OFF() do { PORTA = PORTB = PORTC = 0x00; }while(0)
#define MORSE_DELAY() __delay_ms(100)


// Lookup table for Morse code.  Index is calculated from LCD char
// value.  Reading from least to most sig. bit:
//
//   Filler zeros (not sent)
//   Start bit (not sent)
//   Bits to be sent, 1 = dit, 0 = dah (reverse order)

const char CODE_TABLE[54] = { 0b00000001,  // Flag to send blank
                              0b10000110,  // '
                              0b10010100,  // (
                              0b01001010,  // )
                              0b00000000,  // * - not used
                              0b10101100,  // + or AR
                              0b00110010,  // comma
                              0b01111010,  // minus or long break
                              0b01010110,  // period
                              0b10110100,  // slash
                              0b00000100,  // 0
                              0b00001100,  // 1
                              0b00011100,  // 2
                              0b00111100,  // 3
                              0b01111100,  // 4
                              0b11111100,  // 5
                              0b11110100,  // 6
                              0b11100100,  // 7
                              0b11000100,  // 8
                              0b10000100,  // 9
                              0b11100010,  // colon
                              0b10101010,  // semicolon
                              0b00000000,  // less than - not used
                              0b01110100,  // equals or short break BT
                              0b01011110,  // grtr than = SK
                              0b11001110,  // question mark
                              0b10100110,  // @ symbol
                              0b01100000,  // A
                              0b11101000,  // B
                              0b10101000,  // C
                              0b11010000,  // D
                              0b11000000,  // E
                              0b10111000,  // F
                              0b10010000,  // G
                              0b11111000,  // H
                              0b11100000,  // I
                              0b00011000,  // J
                              0b01010000,  // K
                              0b11011000,  // L
                              0b00100000,  // M
                              0b10100000,  // N
                              0b00010000,  // O
                              0b10011000,  // P
                              0b01001000,  // Q
                              0b10110000,  // R
                              0b11110000,  // S
                              0b01000000,  // T
                              0b01110000,  // U
                              0b01111000,  // V
                              0b00110000,  // W
                              0b01101000,  // X
                              0b00101000,  // Y
                              0b11001000,  // Z
                              0b00000000}; // Null - send nothing

void morse_send_char(char c)
{
  unsigned char k, j, n_elts;
  char code;

  if (c == 32) {
	  k = 0; // Blank
  } else if ((c > 38) && (c < 91)) {
	  k = c - 38; // All others
  } else if ((c > 96) && (c < 123)) {
	  k = (c-97+65) - 38; // convert small letters to big letters
  } else {
	  k = 53; // Send nothing
  }
  code = CODE_TABLE[k];

  if (code == 1)  // For additional space btwn words
  {
	MORSE_DELAY();
    MORSE_DELAY();
    MORSE_DELAY();
    MORSE_DELAY();
  }
  else if (code > 1)  // Send Morse character
  {
    for (j=0; j<8; j++)  // Find start bit
    {
      if ((code & 1) == 1) break;
      code = code >> 1;
    }
    code = code >> 1;  // Shift out start bit
    n_elts = 7 - j;    // Number of character elements

    for (j=0; j<n_elts; j++)  // Send character elements
    {
  	  MORSE_ON();
  	  MORSE_DELAY();  // Delay for one Morse element (dit)
      if ( !(code & 1) ) {
    	  MORSE_DELAY();  // Delay for 3 Morse elements (dah)
      	  MORSE_DELAY();
      }
	  MORSE_OFF();
	  MORSE_DELAY();
      code = code >> 1;        // Shift to next element
    }
    MORSE_DELAY();     // For additional space btwn char
    MORSE_DELAY(); // subtract a few ms to
                                  // allow for delay from LCD updating
  }
}

