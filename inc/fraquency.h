#ifndef __ADF_FRAQUENCY_H
#define __ADF_FRAQUENCY_H

#include <stdint.h>

/* вюярнрш упюмърэяъ б дбнхвмн-ьеярмюджюпхвмни тнпле, лкюдьхи пюгпъд 0,5 йцж */
#define ADF_TO_FRAQUENCY( kHz, Hz ) ( ( 0x##kHz << 1 ) + Hz/5 )

/* вюярнрш пюанвецн дхюоюгнмю */
#define ADF_FRAQUENCY_115       ADF_TO_FRAQUENCY( 115,0 )
#define ADF_FRAQUENCY_150       ADF_TO_FRAQUENCY( 150,0 )
#define ADF_FRAQUENCY_1750      ADF_TO_FRAQUENCY( 1750,0 )
#define ADF_FRAQUENCY_2182      ADF_TO_FRAQUENCY( 2182,0 )
#define ADF_FRAQUENCY_2200      ADF_TO_FRAQUENCY( 2200,0 )

/* вюярнрш хмхжхюкхгюжхх, сцксакеммнцн йнмрпнкъ х дкъ яхмрегюрнпю вюярнр */
#define ADF_FRAQUENCY_INIT      ADF_TO_FRAQUENCY( 0,5 )
#define ADF_FRAQUENCY_100       ADF_TO_FRAQUENCY( 100,0 )
#define ADF_FRAQUENCY_14000     ADF_TO_FRAQUENCY( 14000,0 )
#define ADF_FRAQUENCY_2000      ADF_TO_FRAQUENCY( 2000,0 )

/* йпюимхе вюярнрш пюанвху онддхюоюгнмнб йпюрмше 12 йцж */
#define ADF_FRAQUENCY_156       ADF_TO_FRAQUENCY( 156,0 )
#define ADF_FRAQUENCY_192       ADF_TO_FRAQUENCY( 192,0 )
#define ADF_FRAQUENCY_216       ADF_TO_FRAQUENCY( 216,0 )
#define ADF_FRAQUENCY_348       ADF_TO_FRAQUENCY( 348,0 )
#define ADF_FRAQUENCY_540       ADF_TO_FRAQUENCY( 540,0 )
#define ADF_FRAQUENCY_840       ADF_TO_FRAQUENCY( 840,0 )
#define ADF_FRAQUENCY_1284      ADF_TO_FRAQUENCY( 1284,0 )
#define ADF_FRAQUENCY_1740      ADF_TO_FRAQUENCY( 1740,0 )
#define ADF_FRAQUENCY_2196      ADF_TO_FRAQUENCY( 2196,0 )
#define ADF_FRAQUENCY_2208      ADF_TO_FRAQUENCY( 2208,0 )

/* вюярнрш реумнкнцхвеяйху пефхлнб */
#define ADF_FRAQUENCY_082       ADF_TO_FRAQUENCY( 82,0 )
#define ADF_FRAQUENCY_101       ADF_TO_FRAQUENCY( 101,0 )
#define ADF_FRAQUENCY_102       ADF_TO_FRAQUENCY( 102,0 )
#define ADF_FRAQUENCY_103       ADF_TO_FRAQUENCY( 103,0 )
#define ADF_FRAQUENCY_104       ADF_TO_FRAQUENCY( 104,0 )
#define ADF_FRAQUENCY_104_5     ADF_TO_FRAQUENCY( 104,5 )
#define ADF_FRAQUENCY_105_5     ADF_TO_FRAQUENCY( 105,5 )
#define ADF_FRAQUENCY_106_5     ADF_TO_FRAQUENCY( 106,5 )
#define ADF_FRAQUENCY_107_5     ADF_TO_FRAQUENCY( 107,5 )
#define ADF_FRAQUENCY_108_5     ADF_TO_FRAQUENCY( 108,5 )
#define ADF_FRAQUENCY_109_5     ADF_TO_FRAQUENCY( 109,5 )

/* вюярнрш цпюмхж онддхюоюгнмнб */
#define ADF_FRAQUENCY_SUBRANGE_1_MIN    ADF_TO_FRAQUENCY( 150,0 )
#define ADF_FRAQUENCY_SUBRANGE_1_MEAN   ADF_TO_FRAQUENCY( 168,0 )
#define ADF_FRAQUENCY_SUBRANGE_1_MAX    ADF_TO_FRAQUENCY( 229,5 )

#define ADF_FRAQUENCY_SUBRANGE_2_MIN    ADF_TO_FRAQUENCY( 230,0 )
#define ADF_FRAQUENCY_SUBRANGE_2_MEAN   ADF_TO_FRAQUENCY( 300,0 )
#define ADF_FRAQUENCY_SUBRANGE_2_MAX    ADF_TO_FRAQUENCY( 359,5 )

#define ADF_FRAQUENCY_SUBRANGE_3_MIN    ADF_TO_FRAQUENCY( 360,0 )
#define ADF_FRAQUENCY_SUBRANGE_3_MEAN   ADF_TO_FRAQUENCY( 456,0 )
#define ADF_FRAQUENCY_SUBRANGE_3_MAX    ADF_TO_FRAQUENCY( 559,5 )

#define ADF_FRAQUENCY_SUBRANGE_4_MIN    ADF_TO_FRAQUENCY( 560,0 )
#define ADF_FRAQUENCY_SUBRANGE_4_MEAN   ADF_TO_FRAQUENCY( 708,0 )
#define ADF_FRAQUENCY_SUBRANGE_4_MAX    ADF_TO_FRAQUENCY( 859,5 )

#define ADF_FRAQUENCY_SUBRANGE_5_MIN    ADF_TO_FRAQUENCY( 860,0 )
#define ADF_FRAQUENCY_SUBRANGE_5_MEAN   ADF_TO_FRAQUENCY( 1080,0 )
#define ADF_FRAQUENCY_SUBRANGE_5_MAX    ADF_TO_FRAQUENCY( 1299,5 )

#define ADF_FRAQUENCY_SUBRANGE_6_MIN    ADF_TO_FRAQUENCY( 1300,0 )
#define ADF_FRAQUENCY_SUBRANGE_6_MEAN   ADF_TO_FRAQUENCY( 1536,0 )
#define ADF_FRAQUENCY_SUBRANGE_6_MAX    ADF_TO_FRAQUENCY( 1750,5 )

typedef enum
{
  adfFraquencySubrangeError,
  adfFraquencySubrangeFirst,
  adfFraquencySubrangeTwo,
  adfFraquencySubrangeThree,
  adfFraquencySubrangeFour,
  adfFraquencySubrangeFive,
  adfFraquencySubrangeSix
}
FraquencySubrange_t;

typedef uint16_t Fraquency_t;

extern Fraquency_t FraquencyCurrent;
extern Fraquency_t FraquencyCurrentBligniy;
extern Fraquency_t FraquencyInput;

Fraquency_t FraquencyCurrentGet( void );
void FraquencyCurrentSet( Fraquency_t fraquency );
void FraquencyTest( void );
void FraquencyCanalWriteTest ( void );
uint8_t SignalBligniyOrDalniyTest( void );
void FraquencyPultOut( void );

extern uint8_t TableFraquencyCurrent[ 8 ];
extern uint8_t TableSwitchCurrent[ 8 ];

#endif //__ADF_FRAQUENCY_H


