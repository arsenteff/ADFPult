/*
 * adc.c
 *
 *  Created on: 03 марта 2017 г.
 *      Author: alexey
 */
//#include "cfg.h"
#include "adc.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "cfg.h"

#define ADC_GALETNIK_RST_CLK_PCLK_ADC RST_CLK_PCLK_ADC
#define ADC_GALETNIK_RST_CLK_PCLK_PORT RST_CLK_PCLK_PORTD
#define ADC_KUR_PORT MDR_PORTD
#define ADC_KUR_PINS ( PORT_Pin_7 )

#define CFG_ADC_CLOCK_DIV  1

void ADFADCInit( void )
{

  PORT_InitTypeDef init;

  /* ADC Configuration */
  RST_CLK_PCLKcmd( ADC_GALETNIK_RST_CLK_PCLK_PORT, ENABLE );

  init.PORT_FUNC        = PORT_FUNC_PORT;
  init.PORT_SPEED       = PORT_SPEED_SLOW;
  init.PORT_PULL_UP     = PORT_PULL_UP_OFF;
  init.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
  init.PORT_PD_SHM      = PORT_PD_SHM_OFF;
  init.PORT_PD          = PORT_PD_DRIVER;
  init.PORT_GFEN        = PORT_GFEN_OFF;
  init.PORT_OE          = PORT_OE_OUT;
  init.PORT_MODE        = PORT_MODE_ANALOG; //PORT_MODE_DIGITAL;
  init.PORT_Pin         = ADC_KUR_PINS;

  PORT_Init( ADC_KUR_PORT, &init );

  /*Вкючить тактирование АЦП*/
  RST_CLK_PCLKcmd( ADC_GALETNIK_RST_CLK_PCLK_ADC, ENABLE );

  /* Сброс ADC1_CFG */
  MDR_ADC->ADC1_CFG = 0;

  /*Объединение АЦП*/
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_SYNC_CONVER; /*Независимые*/

  /*Источник опорного напряжения АЦП1*/
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_M_REF; /*AUcc и AGND*/

  /*Выбор переключения каналов АЦП1*/
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_CHCH; /*только выбранный канал*/

  /*Способ запуска АЦП1*/
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_SAMPLE; /*одиночное*/

  /*Синхронизация АЦП1*/
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_CLKS; /*CPU*/

  /* Коэффициент деления входной частоты АЦП 25Мгц/2 = 12,5 < 14 */
  MDR_ADC->ADC1_CFG &= ~ ( 0xF << ADC1_CFG_REG_DIVCLK_Pos );
  MDR_ADC->ADC1_CFG &= (CFG_ADC_CLOCK_DIV-1) << ADC1_CFG_REG_DIVCLK_Pos;

  /* Задержки между преобразованиями */
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_DELAY_GO_Msk;
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_DELAY_ADC_Msk;

  /*Включить АЦП*/
  ADC1_Cmd( ENABLE );
}


uint32_t
ADCGaletnikRead( void )
{
  uint8_t delay;

  /* Выбор рабочего канала АЦП */
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_CHS_Msk ;
  MDR_ADC->ADC1_CFG |= 0 << ADC1_CFG_REG_CHS_Pos;
  MDR_ADC->ADC1_CFG |= 1 << ADC1_CFG_REG_GO_Pos;

  /* ЗАДЕРЖКА ДЛЯ ДОСТИЖЕНИЯ БОЛЕЕ 28 ТАКТОВ ОТ CLK ADC */
  for( delay = 0; delay < 12; delay++ )
  {
  }

  return MDR_ADC->ADC1_RESULT;
}

uint8_t ADCGaletnikValueToCanal( uint32_t value )
{
  uint8_t canal;

  if ( CFG_ADFPultType == CFG_PULT_ADF_351 || CFG_ADFPultType == CFG_PULT_ADF_40 )
    {
      if ( value == 0 )
	canal = 1;
      else if( value > (370-100) && value < (370+100) )
	canal = 2;
      else if( value > (740-100) && value < (740+100) )
	canal = 3;
      else if( value > (1115-100) && value < (1115+100) )
	canal = 4;
      else if( value > (1489-100) && value < (1489+100) )
	canal = 5;
      else if( value > (1860-100) && value < (1860+100) )
	canal = 6;
      else if( value > (2235-100) && value < (2235+100) )
	canal = 7;
      else if( value > (2600-100) && value < (2600+100) )
	canal = 8;
      else if( value > (2990-100) && value < (2990+100) )
	canal = 9;
      else if( value > (3350-100) && value < (3350+100) )
	canal = 10;
      else if( value > (3735-100) && value < (3735+100) )
	canal = 11;
      else if( value == 4095 )
	canal = 12;
    }
  return canal;
}
