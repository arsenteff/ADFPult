/*
 * starts.c
 *
 *  Created on: 17 марта 2017 г.
 *      Author: alexey
 */
#include "indikator.h"
#include "fraquency.h"
#include "timer.h"
#include "controls.h"
#include "cfg.h"
#include "memory.h"

static void StartsStringOut( const Symbol_t *string );

const Symbol_t StartsStringADF351[] = { Symbol_P, Symbol_OFF, Symbol_3, Symbol_5, Symbol_1 };
const Symbol_t StartsStringADF353[] = { Symbol_P, Symbol_OFF, Symbol_3, Symbol_5, Symbol_3 };
const Symbol_t StartsStringADF40[] = { Symbol_P, Symbol_OFF, Symbol_4, Symbol_0, Symbol_0 };

const Symbol_t StartsStringOFF[] = { Symbol_OFF, Symbol_OFF, Symbol_OFF, Symbol_OFF, Symbol_OFF };

const Symbol_t StartsString88888[] = { Symbol_8, Symbol_8, Symbol_8, Symbol_8, Symbol_8 };
const Symbol_t StartsString0123456789[] = { Symbol_OFF, Symbol_OFF, Symbol_OFF, Symbol_OFF, Symbol_0, Symbol_1, Symbol_2, Symbol_3, Symbol_4, Symbol_5, Symbol_6, Symbol_7, Symbol_8, Symbol_9, Symbol_OFF, Symbol_OFF, Symbol_OFF, Symbol_OFF  };

const Symbol_t *StartsTableADF[] = { StartsStringADF351, StartsStringADF353, StartsStringADF40 };

void StartsMenuMain( void )
{
  Time_t time;
  uint32_t i = 0;

  //Если конфигурация пульта была сохранена ранее, то не начинать начальную настройку
  if ( MemoryPultCFGADFLoad() != PULT_CANAL_MEMORY_DATA_EMPTY )
    {
      return;
    }


  //Выдача на индикаторы все символы "8"
  StartsStringOut( StartsString88888 );
  time = TimeGet();
  while( TimeInterval( time ) < TIME_6_SEC );

  time = TimeGet();
  const Symbol_t *string = StartsString0123456789;
  i = 0;

  //Ожидание нажатия кнопки ЗАПИСЬ
  while( !ControlsTimeActive( cntrlWriteFraquency, TIME_800_MSC ) )
    {
      //Бегущая строка 0123456789
      StartsStringOut( string + i );
      if ( TimeInterval( time ) > TIME_320_MS )
	{
	  if ( ++i > 13 ) i = 0;
	  time = TimeGet();
	}

    }

  //Выключить индикаторы
  StartsStringOut( StartsStringOFF );
  //Ожидание отжатия кнопки ЗАПИСЬ
  while ( ControlsTest( cntrlWriteFraquency ) );

  i = 0;
  while( 1 )
    {
      StartsStringOut( StartsTableADF[ i ] );

      //Перебор конфигураций пульта по типам компасов по тумблеру десятков кГц ПЛЮС
      if ( ControlsTimeActive( cntrlTens_Plus, TIME_800_MSC ) )
	{
	  ControlsTimeActiveClear( cntrlTens_Plus );
	  if ( ++i >= 3 ) i = 0;
	}

      //Если нажата клавиша контроль, то завершить начальную настройку
      if ( ControlsTimeActive( cntrlControl, TIME_800_MSC ) )
	{
	  break;
	}

    }

  CFG_ADFPultType = i;
  //Сохранить конфигурацию типа АРК для пульта в FLASH
  MemoryPultCFGADFStore ();
}

void StartsStringOut( const Symbol_t *string )
{
  TableFraquencyCurrent[ 4 ] = string[0];
  TableFraquencyCurrent[ 3 ] = string[1];
  TableFraquencyCurrent[ 2 ] = string[2];
  TableFraquencyCurrent[ 1 ] = string[3];
  TableFraquencyCurrent[ 0 ] = string[4];
}
