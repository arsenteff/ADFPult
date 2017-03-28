/*
 * indikator.h
 *
 *  Created on: 03 марта 2017 г.
 *      Author: alexey
 */

#ifndef INC_INDIKATOR_H_
#define INC_INDIKATOR_H_

#include <stdint.h>

#define pltSegmentSwitchOff 0
#define pltSegmentSwitchOn 1

#define INDIKATOR_SYMBOL_OFF 0x10

typedef struct
{
  unsigned SegmentA : 1;
  unsigned SegmentB : 1;
  unsigned SegmentC : 1;
  unsigned SegmentD : 1;
  unsigned SegmentE : 1;
  unsigned SegmentF : 1;
  unsigned SegmentG : 1;
}
SegmentSymbol_t;

typedef enum
{
  Symbol_0,
  Symbol_1,
  Symbol_2,
  Symbol_3,
  Symbol_4,
  Symbol_5,
  Symbol_6,
  Symbol_7,
  Symbol_8,
  Symbol_9,
  Symbol_A,
  Symbol_B,
  Symbol_C,
  Symbol_D,
  Symbol_E,
  Symbol_F,
  Symbol_OFF,
  Symbol_P
}
Symbol_t;

extern const SegmentSymbol_t IndikatorSegmentSymbol[];

void IndikatorSymbolOut( uint8_t numberIndikator, uint8_t symbol );
void IndikatorOff ( void );
void IndikatorSymbolOut( uint8_t numberIndikator, uint8_t symbol );

#endif /* INC_INDIKATOR_H_ */
