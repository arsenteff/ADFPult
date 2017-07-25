/*
 * signal.c
 *
 *  Created on: 17 марта 2017 г.
 *      Author: alexey
 */

#include "signal.h"
#include "status.h"
#include "state.h"
#include "timer.h"
#include "controls.h"
#include "cfg.h"

void SignalSet( Signal_t signal, uint8_t value);
void SignalMarkerTest( void );


StateDataInput_t StatusTableSignal[] =
    {
	pinSignalBligniy, pinSignalDalniy, pinSignalShassy, pinSignalMarker, pinSignalKodPult1,
	pinSignalKodPult2, pinSignalDPRSAutomat, pinSignalFuncControl, pinSignalDayOrNightADF351, pinSignalDayOrNightADF353
    };

#define SIGNAL_COUNT 10 /*(sizeof(StatusTableSignal)/(sizeof StateDataInput_t))*/

static Time_t TableTimeSignalOff[ SIGNAL_COUNT ];
static Time_t TableTimeSignalOn[ SIGNAL_COUNT ];

void SignalTimeTest( Signal_t signal );


void SignalTest ( void )
{
  if ( ControlsTimeActive( cntrlCompass, TIME_100_MS ) )
    {
      Status.CompassOrAntenna = STATUS_COMPASS;
      ControlsTimeActiveClear( cntrlCompass );
    }
  else
    {
      if ( ControlsTimeActive( cntrlAntenna, TIME_100_MS ) )
	{
	  Status.CompassOrAntenna = STATUS_ANTENNA;
	  ControlsTimeActiveClear( cntrlAntenna );
	}
    }

  if ( ControlsTimeActive( cntrlTelefon, TIME_100_MS ) )
    {
      Status.TelefonOrTelegraph = STATUS_TELEFON;
      ControlsTimeActiveClear( cntrlTelefon );
    }
  else
    {
      if ( ControlsTimeActive( cntrlTelegraph, TIME_100_MS ) )
	{
	  Status.TelefonOrTelegraph = STATUS_TELEGRAPH;
	  ControlsTimeActiveClear( cntrlTelegraph );
	}
    }

    if ( ControlsTimeActive( cntrlControl, TIME_100_MS ) )
      {
	Status.FunctionalControl = STATUS_FUNCTIONAL_CONTROL_ON;
      }
    else
      {
	if ( Status.FunctionalControl == STATUS_FUNCTIONAL_CONTROL_ON )
	  ControlsTimeActiveClear( cntrlControl );

	Status.FunctionalControl = STATUS_FUNCTIONAL_CONTROL_OFF;
      }


  if ( CFG_ADFPultType == CFG_PULT_ADF_40 )
    {
      SignalTimeTest( SignalBligniy );
      SignalTimeTest( SignalDalniy );
      SignalTimeTest( SignalShassy );

      SignalMarkerTest();

      SignalTimeTest( SignalPult1 );
      SignalTimeTest( SignalPult2 );
      SignalTimeTest( SignalDPRSAutomat);
    }
  else if ( CFG_ADFPultType == CFG_PULT_ADF_351 )
    {
      SignalTimeTest( SignalBligniy );
      SignalTimeTest( SignalDalniy );
      SignalTimeTest( SignalShassy );

      SignalMarkerTest();

      SignalTimeTest( SignalDPRSAutomat);
      SignalTimeTest( SignalDayOrNightADF351 );
    }
  else if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
    {
      SignalTimeTest( SignalDayOrNightADF353 );
    }
}

void SignalTimeTest( Signal_t signal )
{
  if ( StateGet( StatusTableSignal[ signal ] ) == 0 )
    {
      if ( TimeInterval( TableTimeSignalOn[ signal ] ) > TIME_100_MS )
	{
	  SignalSet ( signal, STATUS_BLIGNIY_ON );
	  TableTimeSignalOff[ signal ] = TimeGet();
	}
    }
  else
    {
      if ( TimeInterval( TableTimeSignalOff[ signal ] ) > TIME_100_MS )
	{
	  SignalSet ( signal, STATUS_BLIGNIY_OFF );
	  TableTimeSignalOn[ signal ] = TimeGet();
	}
    }
}

void SignalSet( Signal_t signal, uint8_t value)
{
  switch( signal )
  {
    case SignalBligniy :
      Status.Bligniy = value;
      break;

    case SignalDalniy :
      Status.Dalniy = value;
      break;

    case SignalShassy :
      Status.Shassy = value;
      break;

    case SignalMarker :
      Status.Marker = value;
      break;

    case SignalPult1 :
      Status.IndentifikatorPult &= ~1;
      Status.IndentifikatorPult |= value;
      break;

    case SignalPult2 :
      Status.IndentifikatorPult &= ~2;
      Status.IndentifikatorPult |= value << 1;
      break;

    case SignalDPRSAutomat :
      Status.DPRSAutomat = value;
      break;

    case SignalDayOrNightADF351 :
      Status.DayOrNight = value;
      break;

    case SignalDayOrNightADF353 :
      Status.DayOrNight = value;
      break;

  }
}

void SignalMarkerTest( void )
{
  if ( StateGet( StatusTableSignal[ SignalMarker ] ) == 1 )
    {
    if ( TimeInterval( TableTimeSignalOn[ SignalMarker ] ) > TIME_100_MS )
      {
	SignalSet ( SignalMarker, STATUS_BLIGNIY_ON );
	TableTimeSignalOff[ SignalMarker ] = TimeGet();
      }
    }
  else
    {
      if ( TimeInterval( TableTimeSignalOff[ SignalMarker ] ) > TIME_100_MS )
	{
	  SignalSet ( SignalMarker, STATUS_BLIGNIY_OFF );
	  TableTimeSignalOn[ SignalMarker ] = TimeGet();
	}
    }
}

uint8_t SignalDPRSTest( void );

uint8_t SignalBligniyOrDalniyTest( void )
{
  static uint8_t stateMarker = 0;

  if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
    {
      if ( Status.Bligniy == 1 )
	return 0;
      else
	return 1;
    }
  if ( CFG_ADFPultType == CFG_PULT_ADF_40 )
    {
      if ( Status.Shassy )
	Status.MarkerActive = 0;

      if ( ( Status.Dalniy && Status.Bligniy ) || ( !Status.Bligniy && Status.Dalniy ) )
	{
	  //Дальний, выключить светодиод
	  StateReset( pinSvetodiod );
	  return 1;
	}
      else if ( ( Status.Bligniy && !Status.Dalniy ) )
	{
	  //Ближний, включить светодиод
	  StateSet( pinSvetodiod );
	  return 0;
	}
      else if ( ( !Status.Bligniy && !Status.Dalniy && !Status.Shassy ) )
	{
	  if ( Status.Marker == 1 )
	    {
	      Status.MarkerActive = 1;
	      StateSet( pinSvetodiod );
	      return 0;
	    }
	  else
	    {
	      return SignalDPRSTest();
	    }

	}

	StateReset( pinSvetodiod );
	return 1;
    }
}

uint8_t SignalDPRSTest( void )
{
  if ( Status.MarkerActive == 1 && !Status.Shassy )
    {
      if ( Status.DPRSAutomat == 1 )
	{
	  StateSet( pinSvetodiod );
	  return 0;
	}
      else
	{
	  Status.MarkerActive = 0;
	  StateReset( pinSvetodiod );
	  return 1;
	}
    }
  else
    {
      Status.MarkerActive = 0;
      StateReset( pinSvetodiod );
      return 1;
    }
}
