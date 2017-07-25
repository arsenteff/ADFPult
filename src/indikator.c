/*
 * indikator.c
 *
 *  Created on: 03 ����� 2017 �.
 *      Author: alexey
 */
#include "indikator.h"
#include "state.h"
#include "timer.h"

void IndikatorSegmentSet( uint8_t segmentSymbol, StateDataOutput_t segmentPin);


/*������� �������������� ���� ������� � 7 ����������*/
const SegmentSymbol_t IndikatorSegmentSymbol[] =
    {
	/*������ 0*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff
	},
	/*������ 1*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*������ 2*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*������ 3*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*������ 4*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ 5*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ 6*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ 7*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*������ 8*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ 9*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ A*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ b*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ C*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOff
	},
	/*������ d*/
	{ pltSegmentSwitchOff, pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOn
	},
	/*������ E*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOn,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ F*/
	{ pltSegmentSwitchOn, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff,
	  pltSegmentSwitchOn, pltSegmentSwitchOn, pltSegmentSwitchOn
	},
	/*������ �������*/
	{
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff,
	  pltSegmentSwitchOff, pltSegmentSwitchOff, pltSegmentSwitchOff
	},
	/*������ P*/
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
