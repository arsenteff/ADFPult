#include "MDR1986VE1T.h"

typedef enum
{
   adfPortLogicSwith,
   adfPortLogicNull,
   adfPortLogicHigh,
   adfPortLogicStruct
}
ADFPortLogic_t;

typedef enum
{
   adfPortPinNum0,
   adfPortPinNum1,
   adfPortPinNum2,
   adfPortPinNum3,
   adfPortPinNum4,
   adfPortPinNum5,
   adfPortPinNum6,
   adfPortPinNum7,
   adfPortPinNum8,
   adfPortPinNum9,
   adfPortPinNum10,
   adfPortPinNum11,
   adfPortPinNum12,
   adfPortPinNum13,
   adfPortPinNum14,
   adfPortPinNum15
}
ADFPortPinNum_t;

typedef struct
{
   char* description;
   MDR_PORT_TypeDef* port;
   ADFPortPinNum_t pin;
   ADFPortLogic_t logic;
}
ADFStatePin_t;

const ADFStatePin_t
ADFStateOutputPins[] =
{
   // œŒ–“ PE
   { "SEGMENT INDIKATOR A",
     MDR_PORTF, adfPortPinNum1, adfPortLogicNull },

   { "SEGMENT INDIKATOR B",
     MDR_PORTF, adfPortPinNum2, adfPortLogicNull },

   { "SEGMENT INDIKATOR C",
     MDR_PORTF, adfPortPinNum3, adfPortLogicNull },

   { "SEGMENT INDIKATOR D",
     MDR_PORTF, adfPortPinNum4, adfPortLogicNull },

   { "SEGMENT INDIKATOR E",
     MDR_PORTF, adfPortPinNum5, adfPortLogicNull },

   { "SEGMENT INDIKATOR F",
     MDR_PORTF, adfPortPinNum6, adfPortLogicNull },

   { "SEGMENT INDIKATOR G",
     MDR_PORTF, adfPortPinNum7, adfPortLogicNull },

   { "HG 1",
     MDR_PORTF, adfPortPinNum8, adfPortLogicNull },

   { "HG 2",
     MDR_PORTF, adfPortPinNum9, adfPortLogicNull },

   { "HG 3",
     MDR_PORTF, adfPortPinNum10, adfPortLogicNull },

   { "HG 4",
     MDR_PORTF, adfPortPinNum11, adfPortLogicNull },

   { "HG 5",
     MDR_PORTF, adfPortPinNum12, adfPortLogicNull },

   { "SVETODIOD",
     MDR_PORTD, adfPortPinNum8, adfPortLogicNull },

   { "TEST_ZAPIS",
     MDR_PORTC, adfPortPinNum12, adfPortLogicNull },

   { "TEST_CHTENIE",
     MDR_PORTC, adfPortPinNum13, adfPortLogicNull },

   { "TEST_SHIM",
     MDR_PORTC, adfPortPinNum14, adfPortLogicNull },

};

const ADFStatePin_t
ADFStateInputPinsADF40[] =
{
    { "SA3+",
      MDR_PORTF, adfPortPinNum13, adfPortLogicNull },

    { "SA3-",
      MDR_PORTF, adfPortPinNum14, adfPortLogicNull },

    { "SA4+",
      MDR_PORTF, adfPortPinNum15, adfPortLogicNull },

   { "SA4-",
       MDR_PORTD, adfPortPinNum0, adfPortLogicNull },

   { "SA5+",
       MDR_PORTD, adfPortPinNum1, adfPortLogicNull },

   { "SA5-",
       MDR_PORTD, adfPortPinNum2, adfPortLogicNull },

   { "«¿œ»—‹",
       MDR_PORTD, adfPortPinNum3, adfPortLogicNull },

   { " ŒÕ“–ŒÀ‹",
       MDR_PORTD, adfPortPinNum4, adfPortLogicNull },

   { "“À‘",
       MDR_PORTD, adfPortPinNum5, adfPortLogicNull },

   { "“À√",
       MDR_PORTD, adfPortPinNum6, adfPortLogicNull },

   { "DALNIY",
       MDR_PORTB, adfPortPinNum12, adfPortLogicNull },

   { "BLIGNIY",
       MDR_PORTB, adfPortPinNum13, adfPortLogicNull },

   { "SHASSY",
      MDR_PORTB, adfPortPinNum14, adfPortLogicNull },

   { "MARKER",
      MDR_PORTB, adfPortPinNum15, adfPortLogicNull },

   { "KOD PU #1",
      MDR_PORTB, adfPortPinNum8, adfPortLogicNull },

   { "KOD PU #2",
      MDR_PORTB, adfPortPinNum9, adfPortLogicNull },

   { "FUNCTIONAL CONTROL",
      MDR_PORTB, adfPortPinNum10, adfPortLogicNull },

   { "DPRS AUTOMAT",
      MDR_PORTB, adfPortPinNum11, adfPortLogicNull },

};

const ADFStatePin_t
ADFStateInputPinsADF351[] =
{
    { "SA3+",
      MDR_PORTF, adfPortPinNum13, adfPortLogicNull },

    { "SA3-",
      MDR_PORTF, adfPortPinNum14, adfPortLogicNull },

    { "SA4+",
      MDR_PORTF, adfPortPinNum15, adfPortLogicNull },

   { "SA4-",
       MDR_PORTD, adfPortPinNum0, adfPortLogicNull },

   { "SA5+",
       MDR_PORTD, adfPortPinNum1, adfPortLogicNull },

   { "SA5-",
       MDR_PORTD, adfPortPinNum2, adfPortLogicNull },

   { "«¿œ»—‹",
       MDR_PORTD, adfPortPinNum3, adfPortLogicNull },

   { " ŒÕ“–ŒÀ‹",
       MDR_PORTD, adfPortPinNum4, adfPortLogicNull },

   { "“À‘",
       MDR_PORTD, adfPortPinNum5, adfPortLogicNull },

   { "“À√",
       MDR_PORTD, adfPortPinNum6, adfPortLogicNull },

   { "DALNIY",
       MDR_PORTB, adfPortPinNum12, adfPortLogicNull },

   { "BLIGNIY",
       MDR_PORTB, adfPortPinNum13, adfPortLogicNull },

   { "SHASSY",
      MDR_PORTB, adfPortPinNum14, adfPortLogicNull },

   { "MARKER",
      MDR_PORTB, adfPortPinNum15, adfPortLogicNull },

   { "Den/Noch",
      MDR_PORTB, adfPortPinNum10, adfPortLogicNull },

   { "DPRS AUTOMAT",
      MDR_PORTB, adfPortPinNum11, adfPortLogicNull },

   { "D0",
      MDR_PORTC, adfPortPinNum5, adfPortLogicNull },

   { "D1",
      MDR_PORTC, adfPortPinNum6, adfPortLogicNull },

   { "D2",
      MDR_PORTC, adfPortPinNum7, adfPortLogicNull },

   { "D3",
      MDR_PORTC, adfPortPinNum8, adfPortLogicNull },

   { "A0",
      MDR_PORTC, adfPortPinNum9, adfPortLogicNull },

   { "A1",
      MDR_PORTC, adfPortPinNum10, adfPortLogicNull },

   { "A2",
      MDR_PORTC, adfPortPinNum11, adfPortLogicNull },

};

#define ADF_STATE_PINS_OUTPUT_COUNT ( sizeof( ADFStateOutputPins ) / sizeof( ADFStatePin_t ) )
#define ADF_STATE_PINS_INPUT_ADF40_COUNT ( sizeof( ADFStateInputPinsADF40 ) / sizeof( ADFStatePin_t ) )
#define ADF_STATE_PINS_INPUT_ADF351_COUNT ( sizeof( ADFStateInputPinsADF351 ) / sizeof( ADFStatePin_t ) )


