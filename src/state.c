#include "state.h"
#include "state_local.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"

State_t ADFStateOutput;
State_t ADFStateInput;

/**
  * @brief  ������������� ������� ��
  * @retval ���������� ��������� ��� ������
  */
uint32_t
StateInit( void )
{
  PORT_InitTypeDef init;
  uint32_t pos;

  RST_CLK_PCLKcmd( ( RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTB ) , ENABLE );

  init.PORT_FUNC        = PORT_FUNC_PORT;
  init.PORT_MODE        = PORT_MODE_DIGITAL;
  init.PORT_SPEED       = PORT_SPEED_SLOW;
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
    PORT_Init( ADFStateInputPins[ pos ].port , &init );
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
  * @brief  �������� ��������� �������� ������� �� ����� ��
  * @param  portPin: �������� ������� � ����������� ����
  * @retval ���������� ��������� �������
  */
State_t
StateGet( State_t pinsIn )
{
   uint32_t pos;

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
  * @brief  ��������� ��������� ��������� ������� �� ����� ��
  * @param  pinOut: �������� ������� ������� � ����������� ����
  * @retval ���������� ��������� �������
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
  * @brief  ������������� �������� ������� � ������� �������
  * @param  pinOut: �������� ������� ������� � ����������� ����
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
  * @brief  ������������� �������� ������� � ������ �������
  * @param  pinOut: �������� ������� ������� � ����������� ����
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

