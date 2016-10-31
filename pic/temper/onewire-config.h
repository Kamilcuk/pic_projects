
#define OW_ONE_BUS

#define OW_GET_IN()   (( PORTBbits.RB6 ))
#define OW_OUT_LOW()  ( PORTBbits.RB6=0 )
#define OW_OUT_HIGH() ( PORTBbits.RB6=1 )
#define OW_DIR_IN()   ( TRISBbits.RB6=1 )
#define OW_DIR_OUT()  ( TRISBbits.RB6=0 )
#define OW_STRONG_PULLUP_ON()  ( PORTBbits.RB7 = 1 )
#define OW_STRONG_PULLUP_OFF() ( PORTBbits.RB7 = 0 )

#define ow_parasite_enable() do { OW_DIR_OUT(); OW_OUT_HIGH(); OW_STRONG_PULLUP_ON(); } while(0)
#define ow_parasite_disable() do { OW_DIR_IN(); OW_STRONG_PULLUP_OFF(); } while(0)

#include <pic18fregs.h>
