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

void PerekluchatelDataScreenOut( void );


void
main ( void )
{
  uint8_t data;

  CPU_Initialization();

  /*
  LCDInit();
  KeysInit();
  CurrentMenu = &TopMenu;*/

  ADFADCInit();

  StateInit();
  Arinc429Init();

  TimerDlitelnostSkwagnostiIndikator = MemoryPultCanalLoad( PULT_CANAL_INDIKATOR_NUMBER );
  if ( TimerDlitelnostSkwagnostiIndikator > TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX )
    {
      TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;
    }

  TimerTime_Initialization();
  ADFIWDGInit();

  StartsMenuMain();

  while( 1 )
  {

    ADFIWDGReset();
    /*PerekluchatelDataScreenOut();

    data = ADCGaletnikValueToCanal( ADCGaletnikRead() );
    PrintConstText(_itoa( data, DEC ), 4, FONT_WIDTH, 0 );*/
    ControlGaletnikCanalTest();
    SignalTest();
    FraquencyTest();
    FraquencyCanalWriteTest();
    Arinc429Test();

  }

}

void PerekluchatelDataScreenOut( void )
{
  uint32_t data = StatePerekluchatelDataGet();

  //data = ( data & 0x01 ) | ( ( data & 0x02 ) << 3 ) | ( ( data & 0x04 ) << 6 ) | ( ( data & 0x08 ) << 9 );
  PrintConstText(_itoa( data , BIN ), 1, FONT_WIDTH, 0 );

}



