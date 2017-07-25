#include "state.h"
#include "state_local.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "cfg.h"

State_t ADFStateOutput;
State_t ADFStateInput;

/**
  * @brief  Инициализация выводов МК
  * @retval Возвращает локальный код ошибки
  */
uint32_t
StateInit( void )
{
  PORT_InitTypeDef init;
  uint32_t pos;
  uint32_t ADF_STATE_PINS_INPUT_COUNT;
  const ADFStatePin_t *ADFStateInputPins;

  if ( CFG_ADFPultType == CFG_PULT_ADF_353 || CFG_ADFPultType == CFG_PULT_ADF_40 )
    {
      ADF_STATE_PINS_INPUT_COUNT = ADF_STATE_PINS_INPUT_ADF40_COUNT;
      ADFStateInputPins = &ADFStateInputPinsADF40;
    }
  else if( CFG_ADFPultType == CFG_PULT_ADF_351 )
  {
      ADF_STATE_PINS_INPUT_COUNT = ADF_STATE_PINS_INPUT_ADF351_COUNT;
      ADFStateInputPins = &ADFStateInputPinsADF351;
      RST_CLK_PCLKcmd( RST_CLK_PCLK_PORTC , ENABLE );
  }

  RST_CLK_PCLKcmd( ( RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTB ) , ENABLE );

  init.PORT_FUNC        = PORT_FUNC_PORT;
  init.PORT_MODE        = PORT_MODE_DIGITAL;
  init.PORT_SPEED       = PORT_SPEED_MAXFAST;
  init.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
  init.PORT_PD_SHM      = PORT_PD_SHM_OFF;
  init.PORT_PD          = PORT_PD_DRIVER;
  init.PORT_GFEN        = PORT_GFEN_OFF;

  /* Configure PORT input pins */
  init.PORT_OE = PORT_OE_IN;
  init.PORT_PULL_UP = PORT_PULL_UP_ON;
  for ( pos = 0; pos < ADF_STATE_PINS_INPUT_COUNT; pos++ )
  {
    init.PORT_Pin = 1 << ADFStateInputPins[ pos ].pin;
    if ( (1 << pos == pinSignalD0) || (1 << pos == pinSignalD1) || (1 << pos == pinSignalD2) || (1 << pos == pinSignalD3) )
      {
	init.PORT_PD          = PORT_PD_OPEN;
      }
    PORT_Init( ADFStateInputPins[ pos ].port , &init );
    init.PORT_PD          = PORT_PD_DRIVER;
  }

  /* Configure PORT output pins */
  init.PORT_OE = PORT_OE_OUT;
  init.PORT_PULL_UP = PORT_PULL_UP_OFF;
  for ( pos = 0; pos < ADF_STATE_PINS_OUTPUT_COUNT; pos++ )
  {
    init.PORT_Pin = 1 << ADFStateOutputPins[ pos ].pin;
    PORT_Init( ADFStateOutputPins[ pos ].port , &init );
  }

  StateSet( ADF_STATE_PINS_OUT_ALL );

  return 0;
}


uint8_t
StatePultDataGet( void )
{
  uint8_t pos = 5;
  uint8_t data = ( ( MDR_PORTC->RXTX >> pos ) & 0x0F );
  return data;
}

uint8_t
StatePultAdressGet( void )
{
  uint8_t pos = 9;
  uint8_t adress = ( ( MDR_PORTC->RXTX >> pos ) & 0x07 );
  return adress;
}

uint16_t
StatePerekluchatelDataGet( void )
{
      return (uint16_t) ( StateGet( pinSignalSA3Plus ) |
			( StateGet( pinSignalSA3Minus ) << 1 ) |
			( StateGet( pinSignalSA4Plus ) << 2 )  |
			( StateGet( pinSignalSA4Minus ) << 3 ) |
			( StateGet( pinSignalSA5Plus ) << 4 )  |
			( StateGet( pinSignalSA5Minus ) << 5 ) |
			( StateGet( pinSignalWrite ) << 6 ) |
			( StateGet( pinSignalControl ) << 7 ) |
			( StateGet( pinSignalTelefonOrTelegraf ) << 8 ) |
			( StateGet( pinSignalCompasOrAntenna ) << 9 ));
}

/**
  * @brief  Получает состояние входного сигнала из порта МК
  * @param  portPin: содержит позицию в позиционном коде
  * @retval Логическое состояние сигнала
  */
State_t
StateGet( State_t pinsIn )
{
   uint32_t pos;
   const ADFStatePin_t *ADFStateInputPins;

   if ( CFG_ADFPultType == CFG_PULT_ADF_353 || CFG_ADFPultType == CFG_PULT_ADF_40 )
     {
       ADFStateInputPins = &ADFStateInputPinsADF40;
     }
   else if( CFG_ADFPultType == CFG_PULT_ADF_351 )
   {
       ADFStateInputPins = &ADFStateInputPinsADF351;
   }

   /* Get position in array values */
   for ( pos = 0; pinsIn != 0; pos++ )
   {
      if ( ! ( pinsIn >>= 1 ) ) break;
   }

   /* Get current PORT values */
   if ( ADFStateInputPins[ pos ].port->RXTX & ( 1 << ADFStateInputPins[ pos ].pin ) )
   {
      ADFStateInput |= 1 << pos;
      return 1;
   }
   else
   {
      ADFStateInput &= ~ ( 1 << pos );
      return 0;
   }
}

/**
  * @brief  Проверяет состояние выходного сигнала из порта МК
  * @param  pinOut: содержит перечеь выводов в позиционном коде
  * @retval Логическое состояние сигнала
  */
uint32_t
StateTest( State_t pinsOut /*, ADFStateSignal_t signal*/ )
{
   uint32_t pos;

   /* Get position in array values */
   for ( pos = 0; pinsOut != 0; pos++ )
   {
      if ( ! ( pinsOut >>= 1 ) ) break;
   }

   /* Get current PORT values */
   if ( ADFStateOutputPins[ pos ].port->RXTX & ( 1 << ADFStateOutputPins[ pos ].pin ) )
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

/**
  * @brief  Устанавливает выходные сигналы в высокий уровень
  * @param  pinOut: содержит перечеь выводов в позиционном коде
  * @retval None
  */
void
StateSet( State_t pinsOut )
{
   uint32_t pos;

   /*  */
   for ( pos = 0; pinsOut != 0; pos++ )
   {
     if ( pinsOut & 0x1 )
     {
       ADFStateOutputPins[ pos ].port->SETTX = 1 << ADFStateOutputPins[ pos ].pin;
       ADFStateOutput |= 1 << pos;
     }
     pinsOut >>= 1;
   }
}

/**
  * @brief  Устанавливает выходные сигналы в низкий уровень
  * @param  pinOut: содержит перечеь выводов в позиционном коде
  * @retval None
  */
void
StateReset( State_t pinsOut )
{
   uint32_t pos;

   /*  */
   for ( pos = 0; pinsOut != 0; pos++ )
   {
     if ( pinsOut & 0x1 )
     {
        ADFStateOutputPins[ pos ].port->CLRTX = 1 << ADFStateOutputPins[ pos ].pin;
        ADFStateOutput &= ~ ( 1 << pos );
     }
     pinsOut >>= 1;
   }
}


