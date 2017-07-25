#ifndef __ADF_STATE_H
#define __ADF_STATE_H

#include <stdint.h>
#include "fraquency.h"

typedef uint32_t State_t;

typedef enum
{
   pinIndikatorSegmentA = 0x01,
   pinIndikatorSegmentB = 0x02,
   pinIndikatorSegmentC = 0x04,
   pinIndikatorSegmentD = 0x08,
   pinIndikatorSegmentE = 0x10,
   pinIndikatorSegmentF = 0x20,
   pinIndikatorSegmentG = 0x40,

   pinIndikatorHG1 = 0x80,
   pinIndikatorHG2 = 0x100,
   pinIndikatorHG3 = 0x200,
   pinIndikatorHG4 = 0x400,
   pinIndikatorHG5 = 0x800,

   pinSvetodiod = 0x1000
}
StateDataOutput_t;

#define ADF_STATE_PINS_OUT_ALL 0

typedef enum
{
  pinSignalSA3Plus = 0x1,
  pinSignalSA3Minus = 0x2,
  pinSignalSA4Plus = 0x4,
  pinSignalSA4Minus = 0x8,
  pinSignalSA5Plus = 0x10,
  pinSignalSA5Minus = 0x20,

  pinSignalWrite = 0x40,
  pinSignalControl = 0x80,
  pinSignalTelefonOrTelegraf = 0x100,
  pinSignalCompasOrAntenna = 0x200,

  pinSignalDalniy	  = 0x400,
  pinSignalBligniy	  = 0x800,
  pinSignalShassy	  = 0x1000,
  pinSignalMarker	  = 0x2000,
  pinSignalDayOrNightADF351 = 0x4000,
  pinSignalKodPult1	  = 0x4000,
  pinSignalDPRSAutomatADF351 = 0x8000,
  pinSignalKodPult2	  = 0x8000,
  pinSignalFuncControl	  = 0x10000,
  pinSignalDPRSAutomat	  = 0x20000,
  pinSignalDayOrNightADF353 = 0x20000,
  pinSignalD0 = 0x10000,
  pinSignalD1 = 0x20000,
  pinSignalD2 = 0x400000,
  pinSignalD3 = 0x800000,
  pinSignalA0 = 0x1000000,
  pinSignalA1 = 0x2000000,
  pinSignalA2 = 0x4000000
}
StateDataInput_t;

typedef enum
{
  adfStateChannelA,
  adfStateChannelB,
  adfStateChannelC,

}
StateChannel_t;

uint32_t StateInit( void );
uint32_t StateGet( State_t portPin );
uint32_t StateTest( State_t pinsOut );
void StateSet( State_t portPins );
void StateReset( State_t portPins );

uint32_t StateNumberADF( void );

uint16_t StatePerekluchatelDataGet( void );
uint8_t StatePultDataGet( void );
uint8_t StatePultAdressGet( void );

#endif //__ADF_STATE_H

