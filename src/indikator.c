/*
 * indikator.c
 *
 *  Created on: 03 марта 2017 г.
 *      Author: alexey
 */
#include "indikator.h"
#include "state.h"
#include "timer.h"

void IndikatorSegmentSet( uint8_t segmentSymbol, StateDataOutput_t segmentPin);


/*Таблица преобразования кода символа в 7 сегментный*/
const SegmentSymbol_t IndikatorSegmentSymbol[] =
    {
	/*Символ 0*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff
	},
	/*Символ 1*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*Символ 2*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*Символ 3*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*Символ 4*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ 5*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ 6*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ 7*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*Символ 8*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ 9*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ A*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ b*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ C*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff
	},
	/*Символ d*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*Символ E*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ F*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*Символ ГАШЕНИЕ*/
	{
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*Символ P*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	}

    };

void IndikatorSymbolOut( uint8_t numberIndikator, uint8_t symbol )
{
  //symbol &= 0x0F;
  if ( symbol == 0 )
    symbol = 0;
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentA, pinIndikatorSegmentA );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentB, pinIndikatorSegmentB );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentC, pinIndikatorSegmentC );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentD, pinIndikatorSegmentD );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentE, pinIndikatorSegmentE );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentF, pinIndikatorSegmentF );
  IndikatorSegmentSet( IndikatorSegmentSymbol[ symbol ].SegmentG, pinIndikatorSegmentG );

  //ADFStateSet( numberIndikator );

}

void IndikatorSegmentSet( uint8_t segmentSymbol, StateDataOutput_t segmentPin)
{
  if ( segmentSymbol == pltSegmentSwitchOn )
    StateSet( segmentPin );
  else
    StateReset( segmentPin );

}

void IndikatorOff ( void )
{
  Time_t time = TimeGet();
  TableFraquencyCurrent[ 4 ] = Symbol_OFF;
  TableFraquencyCurrent[ 3 ] = Symbol_OFF;
  TableFraquencyCurrent[ 2 ] = Symbol_OFF;
  TableFraquencyCurrent[ 1 ] = Symbol_OFF;
  TableFraquencyCurrent[ 0 ] = Symbol_OFF;

  while ( TimeInterval( time ) < TIME_10_MS );
}
