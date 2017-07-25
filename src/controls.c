/*
 * controls.c
 *
 *  Created on: 06 марта 2017 г.
 *      Author: alexey
 */

#include "controls.h"
#include "timer.h"
#include "state.h"
#include "memory.h"
#include "adc.h"

static uint16_t Controls = 0;
static uint8_t ControlGaletnikCanal = 0;

Time_t TableControlsTimeActive[ CONTROLS_COUNT ];

void ControlsRead( void )
{
  Controls = StatePerekluchatelDataGet();

}

uint8_t ControlsTest ( ControlsElements_t control )
{
  ControlsRead();

  switch (control)
  {
    case cntrlOnes_Plus:
      if ( Controls & pinSignalSA3Plus )
	return 0;
      else return 1;

    case cntrlOnes_Minus:
      if ( Controls & pinSignalSA3Minus )
	return 0;
      else return 1;

    case cntrlTens_Plus:
      if ( Controls & pinSignalSA4Plus )
	return 0;
      else return 1;

    case cntrlTens_Minus:
      if ( Controls & pinSignalSA4Minus )
	return 0;
      else return 1;

    case cntrlHundreds_Plus:
      if ( Controls & pinSignalSA5Plus )
	return 0;
      else return 1;

    case cntrlHundreds_Minus:
      if ( Controls & pinSignalSA5Minus )
	return 0;
      else return 1;

    case cntrlWriteFraquency:
      if ( Controls & pinSignalWrite )
	return 0;
      else return 1;

    case cntrlControl:
      if ( Controls & pinSignalControl )
	return 0;
      else return 1;

    case cntrlTelefon:
      if ( Controls & pinSignalTelefonOrTelegraf )
	return 0;
      else return 1;

    case cntrlTelegraph:
      if ( Controls & pinSignalTelefonOrTelegraf )
	return 1;
      else return 0;

    case cntrlCompass:
      if ( Controls & pinSignalCompasOrAntenna )
	return 0;
      else return 1;

    case cntrlAntenna:
      if ( Controls & pinSignalCompasOrAntenna )
	return 1;
      else return 0;

    default:
      return 0;
  }
}

uint8_t ControlGaletnikCanalTest( void )
{
  static Time_t time = 0;
  static uint8_t canalPrevious = 0;

  uint8_t canalNew = ADCGaletnikValueToCanal( ADCGaletnikRead() );
  uint8_t canalCurrent = ControlGaletnikCanal;

  if ( canalPrevious != canalNew )
    {
      time = TimeGet();
    }
  else if  ( TimeInterval( time ) > TIME_100_MS )
    {
	ControlGaletnikCanal = canalNew;
    }
  canalPrevious = canalNew;

  return ControlGaletnikCanal;
}

uint8_t ControlGaletnikCanalGet( void )
{
  return ControlGaletnikCanal;
}

uint8_t ControlsTimeActive( ControlsElements_t control, Time_t time )
{
  if ( ControlsTest( control ) )
    {
      if ( !TableControlsTimeActive[ control ] )
	TableControlsTimeActive[ control ] = TimeGet();
      else
	if ( TimeInterval( TableControlsTimeActive[ control ] ) >= time )
	  return 1;
	return 0;
    }
  else
    {
      TableControlsTimeActive[ control ] = 0;
      return 0;
    }
}

void ControlsTimeActiveClear( ControlsElements_t control )
{
  TableControlsTimeActive[ control ] = 0;
}
