/*
 * fraquency.c
 *
 *  Created on: 06 марта 2017 г.
 *      Author: alexey
 */

#include "fraquency.h"
#include "controls.h"
#include "timer.h"
#include "adc.h"
#include "memory.h"
#include "status.h"
#include "indikator.h"
#include "cfg.h"

uint8_t TableFraquencyCurrent[ 8 ];
uint8_t TableSwitchCurrent[ 8 ];

/*‘ормат хранени€ частоты двоичный, но самый младший разр€д подразумевает 0,5 к√ц
 *1 - частота 0,5 к√ц
 *10 - 5,0 к√ц
 *100 - 50,0 к√ц
 *201 - 100,5 к√ц
 *300 - 150,0 к√ц
 *3500 - 1750,0 к√ц
 *4364 - 2182,0 к√ц*/

Fraquency_t FraquencyCurrent = 0;
Fraquency_t FraquencyCurrentBligniy = 0;
Fraquency_t ADFFraquencyPlavno = 0;
Fraquency_t FraquencyInput = 0;

uint8_t FraquencyMiganie = 0;
Time_t FraquencyMiganieTime = 0;

Fraquency_t FraquencyCurrentGet( void )
{
  return FraquencyCurrent;
}


void FraquencyCurrentSet( Fraquency_t fraquency )
{
  FraquencyCurrent = fraquency;
}


void FraquencyTest( void )
{
  uint8_t frqCurrentHG1;
  uint8_t frqCurrentHG2;
  uint8_t frqCurrentHG3;
  uint8_t frqCurrentHG4;
  uint8_t frqCurrentHG5;

  static uint8_t boolIndikatorBrightnessSave = 0;
  static Time_t timeIndikatorBrightnessSave;

  if ( ControlGaletnikCanalGet() == PULT_CANAL_PLAVNO_NUMBER() )
    {
    if ( ControlsTimeActive( cntrlOnes_Plus, TIME_800_MSC ) )
      {
	if ( ADFFraquencyPlavno % 20 == 19 )
	  ADFFraquencyPlavno -= 19;
	else
	  ADFFraquencyPlavno += 1;
	ControlsTimeActiveClear( cntrlOnes_Plus );
      }

    if ( ControlsTimeActive( cntrlOnes_Minus, TIME_800_MSC ) )
      {
	if ( ADFFraquencyPlavno % 20 == 00 )
	  ADFFraquencyPlavno += 19;
	else
	  ADFFraquencyPlavno -= 1;
	ControlsTimeActiveClear( cntrlOnes_Minus );
      }

    if ( ControlsTimeActive( cntrlTens_Plus, TIME_800_MSC ) )
      {
	if ( ( ( ADFFraquencyPlavno >> 1 ) / 10 ) % 10 == 9 )
	  ADFFraquencyPlavno -= ( 90 << 1 );
	else
	  ADFFraquencyPlavno += 10 << 1;
	ControlsTimeActiveClear( cntrlTens_Plus );
      }

    if ( ControlsTimeActive( cntrlTens_Minus, TIME_800_MSC ) )
      {
	if ( ( ( ADFFraquencyPlavno >> 1 ) / 10 ) % 10 == 0 )
	  ADFFraquencyPlavno += ( 90 << 1 );
	else
	  ADFFraquencyPlavno -= 10 << 1;
	ControlsTimeActiveClear( cntrlTens_Minus );
      }

    if ( ControlsTimeActive( cntrlHundreds_Plus, TIME_800_MSC ) )
      {
	if ( ( ( ADFFraquencyPlavno >> 1 ) / 100 ) % 20 == 19 )
	  ADFFraquencyPlavno -= ( 1900 << 1 );
	else
	  ADFFraquencyPlavno += 100 << 1;
	ControlsTimeActiveClear( cntrlHundreds_Plus );
      }

    if ( ControlsTimeActive( cntrlHundreds_Minus, TIME_800_MSC ) )
      {
	if ( ( ( ADFFraquencyPlavno >> 1 ) / 100 ) % 20 == 0 )
	  ADFFraquencyPlavno += ( 1900 << 1 );
	else
	  ADFFraquencyPlavno -= 100 << 1;
	ControlsTimeActiveClear( cntrlHundreds_Minus );
      }

      FraquencyCurrent = ADFFraquencyPlavno;
      if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
	{
	  FraquencyCurrentBligniy = ADFFraquencyPlavno;
	}
    }
  else
    {
      if ( ControlsTimeActive( cntrlTens_Plus, TIME_800_MSC ) )
      {
	if ( --TimerDlitelnostSkwagnostiIndikator < TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN )
	       TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;
	ControlsTimeActiveClear( cntrlTens_Plus );
	timeIndikatorBrightnessSave = TimeGet();
	boolIndikatorBrightnessSave = 1;
      }

      if ( ControlsTimeActive( cntrlTens_Minus, TIME_800_MSC ) )
      {
	if ( ++TimerDlitelnostSkwagnostiIndikator > TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX )
	       TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX;
	ControlsTimeActiveClear( cntrlTens_Minus );
	timeIndikatorBrightnessSave = TimeGet();
	boolIndikatorBrightnessSave = 1;
      }

      if ( CFG_ADFPultType == CFG_PULT_ADF_40 )
	{
	  if ( SignalBligniyOrDalniyTest() )
	    FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() );
	  else
	    FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() + PULT_CANAL_COUNT() );
	}
      else if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
	{
	  FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() );
	  FraquencyCurrentBligniy = MemoryPultCanalLoad( ControlGaletnikCanalGet() + PULT_CANAL_COUNT() );
	}

      if ( boolIndikatorBrightnessSave == 1 && TimeInterval( timeIndikatorBrightnessSave ) > TIME_10_SEC )
	{
	  MemoryPultCanalStore ( PULT_CANAL_INDIKATOR_NUMBER(), TimerDlitelnostSkwagnostiIndikator );
	  boolIndikatorBrightnessSave = 0;
	}

    }

  //—имволы дл€ индикации на основе входной частоты
  frqCurrentHG1 = (FraquencyInput & 0x01) * 5;
  frqCurrentHG2 = ( FraquencyInput >> 1 ) % 10;
  frqCurrentHG3 = ( ( FraquencyInput >> 1 ) / 10) % 10;
  frqCurrentHG4 = ( ( FraquencyInput >> 1 ) / 100) % 10;
  frqCurrentHG5 = ( ( FraquencyInput >> 1 ) / 1000) % 10;

  //√ашение старших индикаторов соответствующих символу 0
  if ( frqCurrentHG5 == 0 )
    {
      frqCurrentHG5 = INDIKATOR_SYMBOL_OFF;
      if ( frqCurrentHG4 == 0 )
	{
	  frqCurrentHG4 = INDIKATOR_SYMBOL_OFF;
	      if ( frqCurrentHG3 == 0 )
		{
		  frqCurrentHG3 = INDIKATOR_SYMBOL_OFF;
		}
	}
    }

  if ( ( FraquencyInput >= 300 &&
       FraquencyInput <= 3500 ||
       FraquencyInput == 4364 ) && Status.FunctionalControl == STATUS_FUNCTIONAL_CONTROL_OFF )
    {
      TableFraquencyCurrent[ 4 ] = frqCurrentHG5;
      TableFraquencyCurrent[ 3 ] = frqCurrentHG4;
      TableFraquencyCurrent[ 2 ] = frqCurrentHG3;
      TableFraquencyCurrent[ 1 ] = frqCurrentHG2;
      TableFraquencyCurrent[ 0 ] = frqCurrentHG1;
    }
  else
    {
      if ( FraquencyMiganie == 1 )
	{
          TableFraquencyCurrent[ 4 ] = INDIKATOR_SYMBOL_OFF;
          TableFraquencyCurrent[ 3 ] = INDIKATOR_SYMBOL_OFF;
          TableFraquencyCurrent[ 2 ] = INDIKATOR_SYMBOL_OFF;
          TableFraquencyCurrent[ 1 ] = INDIKATOR_SYMBOL_OFF;
          TableFraquencyCurrent[ 0 ] = INDIKATOR_SYMBOL_OFF;

          if ( TimeInterval( FraquencyMiganieTime ) > TIME_500_MS )
            {
              FraquencyMiganie = 0;
              FraquencyMiganieTime = TimeGet();
            }
	}
      else
	{
	  TableFraquencyCurrent[ 4 ] = frqCurrentHG5;
	  TableFraquencyCurrent[ 3 ] = frqCurrentHG4;
	  TableFraquencyCurrent[ 2 ] = frqCurrentHG3;
	  TableFraquencyCurrent[ 1 ] = frqCurrentHG2;
	  TableFraquencyCurrent[ 0 ] = frqCurrentHG1;

	  if ( TimeInterval( FraquencyMiganieTime ) > TIME_500_MS )
	    {
	      FraquencyMiganie = 1;
	      FraquencyMiganieTime = TimeGet();
	    }
	}
    }
}

void FraquencyCanalWriteTest ( void )
{
  uint8_t canal;
  static Time_t time = TIME_NULL;
  static uint8_t writeStatus = 0;

  if ( !Status.Dalniy && !Status.Bligniy )
    return;

  if ( writeStatus == 0 )
      {
	//Ћовим первое нажатие кнопки
	if ( ControlGaletnikCanalTest() == PULT_CANAL_PLAVNO_NUMBER() && ControlsTimeActive( cntrlWriteFraquency, TIME_200_MS ) )
	  {
	    writeStatus = 1;
	    ControlsTimeActiveClear( cntrlWriteFraquency );
	    time = TimeGet();
	  }
      }
  else if ( writeStatus == 1 )
    {
      if ( TimeInterval( time ) > TIME_6_SEC )
	writeStatus = 0;
      //Ћовим отжатие кнопки
      if ( !ControlsTest( cntrlWriteFraquency ) )
	writeStatus = 2;
    }

  else if ( writeStatus == 2 )
    {
      if ( TimeInterval( time ) > TIME_6_SEC )
	writeStatus = 0;

      canal = ControlGaletnikCanalTest();
      //Ћовим второе нажатие кнопки
      if ( canal != PULT_CANAL_PLAVNO_NUMBER() && ControlsTimeActive( cntrlWriteFraquency, TIME_200_MS ) )
	{
	  if ( canal <= PULT_CANAL_COUNT() )
	    {
	      if ( SignalBligniyOrDalniyTest() )
		MemoryPultCanalStore ( canal, ADFFraquencyPlavno );
	      else
		MemoryPultCanalStore ( canal + PULT_CANAL_COUNT(), ADFFraquencyPlavno );

	    }
	  writeStatus = 3;
	}
      }
  else if ( writeStatus == 3 )
    {
      //Ћовим отжатие кнопки
      if ( !ControlsTest( cntrlWriteFraquency ) )
	writeStatus = 0;
    }


}

void FraquencyPultOut( void )
{
  static uint8_t boolIndikatorBrightnessSave = 0;
  static Time_t timeIndikatorBrightnessSave;

  TableFraquencyCurrent[ 4 ] = PultDataInput[ 3 ];
  TableFraquencyCurrent[ 3 ] = PultDataInput[ 2 ];
  TableFraquencyCurrent[ 2 ] = PultDataInput[ 1 ];
  TableFraquencyCurrent[ 1 ] = PultDataInput[ 0 ];
  TableFraquencyCurrent[ 0 ] = PultDataInput[ 4 ];

  if ( ControlGaletnikCanalGet() == PULT_CANAL_PLAVNO_NUMBER() )
    {
      TableSwitchCurrent[ 0 ] = 0x00;
      TableSwitchCurrent[ 1 ] = 0x02;
      TableSwitchCurrent[ 2 ] = 0x00;
      TableSwitchCurrent[ 3 ] = 0x00;
      /*
      TableSwitchCurrent[ 4 ] = 0x05;
      TableSwitchCurrent[ 5 ] = 0x05;
      TableSwitchCurrent[ 6 ] = 0x05;
      TableSwitchCurrent[ 7 ] = 0x05;*/
    }

  if ( ControlGaletnikCanalGet() != PULT_CANAL_PLAVNO_NUMBER() )
    {
      if ( ControlsTimeActive( cntrlTens_Plus, TIME_800_MSC ) )
      {
	    if ( --TimerDlitelnostSkwagnostiIndikator < TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN )
		   TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;
	    ControlsTimeActiveClear( cntrlTens_Plus );
	    timeIndikatorBrightnessSave = TimeGet();
	    boolIndikatorBrightnessSave = 1;
      }

      if ( ControlsTimeActive( cntrlTens_Minus, TIME_800_MSC ) )
      {
	    if ( ++TimerDlitelnostSkwagnostiIndikator > TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX )
		   TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX;
	    ControlsTimeActiveClear( cntrlTens_Minus );
	    timeIndikatorBrightnessSave = TimeGet();
	    boolIndikatorBrightnessSave = 1;
      }

      if ( CFG_ADFPultType == CFG_PULT_ADF_40 )
	    {
	      if ( SignalBligniyOrDalniyTest() )
		FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() );
	      else
		FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() + PULT_CANAL_COUNT() );
	    }
      else if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
	    {
	      FraquencyCurrent = MemoryPultCanalLoad( ControlGaletnikCanalGet() );
	      FraquencyCurrentBligniy = MemoryPultCanalLoad( ControlGaletnikCanalGet() + PULT_CANAL_COUNT() );
	    }

      if ( boolIndikatorBrightnessSave == 1 && TimeInterval( timeIndikatorBrightnessSave ) > TIME_10_SEC )
	    {
	      MemoryPultCanalStore ( PULT_CANAL_INDIKATOR_NUMBER(), TimerDlitelnostSkwagnostiIndikator );
	      boolIndikatorBrightnessSave = 0;
	    }
    }
}
