#ifdef _ONEWIRE_CONFIG_H_
#DEFINE _ONEIWRE_CONFIG_H_ 1

#define OW_ONE_BUS

#define OW_GET_IN()   PORTAbits.RA2
#define OW_OUT_LOW()  ( PORTAbits.RA2=0 )
#define OW_OUT_HIGH() ( PORTAbits.RA2=1 )
#define OW_DIR_IN()   ( TRISAbits.RA2=0 )
#define OW_DIR_OUT()  ( TRISAbits.RA2=1 )

#include <pic18fregs.h>

#ENDIF
