/*
 * main.c
 *
 *  Created on: 02 марта 2017 г.
 *      Author: alexey
 */
#include "menu.h"
#include <stdint.h>
#include "mystring.h"
#include "state.h"
#include "font.h"
#include "adc.h"
#include "timer.h"
#include "indikator.h"
#include "memory.h"
#include "status.h"
#include "arinc429.h"
#include "controls.h"
#include "signal.h"
#include "capture.h"
#include "fraquency.h"

void PerekluchatelDataScreenOut( void );


void
main ( void )
{
  uint8_t data;

  /* Задаем частоту микроконтроллера */
  CPU_Initialization();


  /*LCDInit();
  KeysInit();
  CurrentMenu = &TopMenu;*/

  /* Инициализация АЦП галетника каналов */
  ADFADCInit();

  /* Инициализация пинов всех внешних сигналов */
  StateInit();

  /* Начальное состояние яркости индикаторов */
  TimerDlitelnostSkwagnostiIndikator = MemoryPultCanalLoad( PULT_CANAL_INDIKATOR_NUMBER() );
  if ( TimerDlitelnostSkwagnostiIndikator > TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX )
    {
      TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;
    }

  /* Инициализация таймера времени */
  TimerTime_Initialization();

  /* Инициализация ватчдога */
  //ADFIWDGInit();

  /* Стартовое меню настройки конфигурации прошивки */
  StartsMenuMain();

  /* Отладки пульта АРК-35-3*/
  CFG_ADFPultType = CFG_PULT_ADF_351;

  if ( CFG_ADFPultType == CFG_PULT_ADF_353 || CFG_ADFPultType == CFG_PULT_ADF_40 )
    {
      Arinc429Init();
    }

  while( 1 )
  {
    //Сброс ватчдога
    ADFIWDGReset();

    ControlGaletnikCanalTest();
    SignalTest();

    if ( CFG_ADFPultType == CFG_PULT_ADF_40 || CFG_ADFPultType == CFG_PULT_ADF_353 )
      {
	FraquencyTest();
	FraquencyCanalWriteTest();
      }


    if ( CFG_ADFPultType == CFG_PULT_ADF_353 || CFG_ADFPultType == CFG_PULT_ADF_40 )
      {
	Arinc429Test();
      }

    if ( CFG_ADFPultType == CFG_PULT_ADF_353 || CFG_ADFPultType == CFG_PULT_ADF_351 )
      {
	CaptureTimer();
      }

    if ( CFG_ADFPultType == CFG_PULT_ADF_351 )
      {
	FraquencyPultOut();
      }

  }

}

void PerekluchatelDataScreenOut( void )
{
  uint32_t data = StatePerekluchatelDataGet();

  //data = ( data & 0x01 ) | ( ( data & 0x02 ) << 3 ) | ( ( data & 0x04 ) << 6 ) | ( ( data & 0x08 ) << 9 );
  PrintConstText(_itoa( (int32_t)ProcentSkwagnost , DEC ), 1, FONT_WIDTH, 0 );

}



