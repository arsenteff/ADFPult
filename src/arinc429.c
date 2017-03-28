#include "arinc429.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_timer.h"
//#include "MDR32F9Qx_arinc429r.h"
//#include "MDR32F9Qx_arinc429t.h"
#include "cfg.h"
#include "timer.h"
#include "status.h"

#define ARINC429_TRANSMITTER_IRQHandler Timer2_IRQHandler

#define ARINC429_TRANSMITTER_TIMER MDR_TIMER2
#define ARINC429_TRANSMITTER_TIMER_RST_CLK_PCLK RST_CLK_PCLK_TIMER2

#define TIMER_TIME_PERIOD_50_MS 50000
#define TIMER_TIME_PERIOD_160_MS 160000
#define TIMER_TIME_PERIOD_100_MS 100000
#define TIMER_TIME_PERIOD_20_MS 20000

uint32_t Arinc429ReceiverWords = 0;
uint32_t Arinc429ReceiverData = 0;
uint32_t Arinc429TransmitterWords = 0;
uint32_t Arinc429TransmitterData = 0;


void
Arinc429Timer_Initialization (void);
void
Arinc429Tx_Initialization (void);
void
Arinc429Rx_Initialization (void);
void
Arinc429Port_Initialization (void);

void Arinc429Init( void )
{
  Arinc429Port_Initialization ();
  Arinc429Tx_Initialization ();
  Arinc429Rx_Initialization ();
  Arinc429Timer_Initialization ();
}


void Arinc429ReceiverChannelOff( char channel )
{
  MDR_ARINC429R->CONTROL1 &= ~( 1 << channel );
}

void Arinc429ReceiverChannelOn( char channel )
{
  MDR_ARINC429R->CONTROL1 |= ( 1 << channel );
}

void
Arinc429Port_Initialization (void)
{
  RST_CLK_PCLKcmd (
      ( RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTE ), ENABLE);

  //Настройка 4 приемников и 4 передатчиков
  //*** Config PortD_13, PortD_14, PORTF_13, PORTF_14 for ARINC429T ***
  //OUT1+ OUT1-
  MDR_PORTD->FUNC |= 0x28000000;       //PortD_13, PortD_14 alternativ function
  MDR_PORTD->ANALOG |= 0x6000;         //PortD_13, PortD_14 digital
  MDR_PORTD->PWR |= 0x3C000000;        //PortD_13, PortD_14 has max edge

  //OUT2+ OUT2-
  /*
  MDR_PORTF->FUNC |= 0x14000000;       //PortF_13, PortF_14 general function
  MDR_PORTF->ANALOG |= 0x6000;         //PortF_13, PortF_14 digital
  MDR_PORTF->PWR |= 0x3C000000;        //PortF_13, PortF_14 has max edge*/

  /*
  //OUT3+
  MDR_PORTD->FUNC |= 0x40000000;       //PortD_13, PortD_14 alternativ function
  MDR_PORTD->ANALOG |= 0x8000;         //PortD_13, PortD_14 digital
  MDR_PORTD->PWR |= 0xC0000000;        //PortD_13, PortD_14 has max edge

  //OUT3-
  MDR_PORTE->FUNC |= 0x00000004;       //PortD_13, PortD_14 alternativ function
  MDR_PORTE->ANALOG |= 0x0002;         //PortD_13, PortD_14 digital
  MDR_PORTE->PWR |= 0x0000000C;        //PortD_13, PortD_14 has max edge

  //OUT4+ OUT4-
  MDR_PORTE->FUNC |= 0x00000011;       //PortF_13, PortF_14 general function
  MDR_PORTE->ANALOG |= 0x0005;         //PortF_13, PortF_14 digital
  MDR_PORTE->PWR |= 0x00000033;        //PortF_13, PortF_14 has max edge
*/
  //*** Config PORTB_0 - PORTB_7 for ARINC429R ***
  //IN1+ IN1- IN2+ IN2- IN3+ IN3- IN4+ IN4-
  MDR_PORTB->FUNC |= 0x0000AAAA;       //PORTB_0 - PORTB_7 alternativ function
  MDR_PORTB->ANALOG |= 0x00FF;         //PORTB_0 - PORTB_7     digital
  MDR_PORTB->PWR |= 0x0000FFFF;        //PORTB_0 - PORTB_7     has max edge
}

void
Arinc429Tx_Initialization (void)
{
  RST_CLK_PCLKcmd ( RST_CLK_PCLK_ARINC429T, ENABLE );

  MDR_ARINC429T->CONTROL1 = 0;
  MDR_ARINC429T->CONTROL2 = 0;

  MDR_ARINC429T->CONTROL1= /*(CFG_ARINC_DIV<<8)|*/(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)/*|(1<<1)*/|1;
  //Задаем делитель, паритет (дополнение до нечётного) для 1 и 2 каналов, передача бита паритета разрешена для 1 и 2 каналов, передача по каналу 1 и 2 разрешена,

  MDR_ARINC429T->CONTROL3= CFG_ARINC_DIV*8;
}

void
Arinc429Rx_Initialization (void)
{
  RST_CLK_PCLKcmd ( RST_CLK_PCLK_ARINC429R, ENABLE );

  MDR_ARINC429R->CONTROL1=0;
  MDR_ARINC429R->CONTROL2=CFG_ARINC_DIV>>4;
  MDR_ARINC429R->CONTROL3=0;
  MDR_ARINC429R->CONTROL3|=(1<<28)|(1<<29);

  MDR_ARINC429R->CONTROL1|=(CFG_ARINC_DIV<<28)|(0xFF<<14)|0x0F;

  NVIC_EnableIRQ( ARINC429R_IRQn );
}

void
Arinc429Timer_Initialization (void)
{
  TIMER_CntInitTypeDef init;

  /* Включить тактирование таймера */
  RST_CLK_PCLKcmd ( ARINC429_TRANSMITTER_TIMER_RST_CLK_PCLK, ENABLE);

  /* Initializes the TIMER Counter */
  init.TIMER_IniCounter = 0x00000000;
  init.TIMER_Prescaler = CFG_CPU_CLOCK / 1000000;
  init.TIMER_Period = TIMER_TIME_PERIOD_160_MS;
  init.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
  init.TIMER_CounterDirection = TIMER_CntDir_Up;
  init.TIMER_EventSource = TIMER_EvSrc_None;
  init.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
  init.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;

  TIMER_CntInit ( ARINC429_TRANSMITTER_TIMER, &init);

  /* Enable TIMER clock */
  TIMER_BRGInit ( ARINC429_TRANSMITTER_TIMER, TIMER_HCLKdiv1);

  /* Разрешение генерировать прерывание при CNT == ARR */
  TIMER_ITConfig ( ARINC429_TRANSMITTER_TIMER, TIMER_IE_CNT_ARR_EVENT_IE,
		  ENABLE);

  /* Enable TIMER */
  TIMER_Cmd ( ARINC429_TRANSMITTER_TIMER, ENABLE);

  NVIC_EnableIRQ (TIMER2_IRQn);

}

void ARINC429_TRANSMITTER_IRQHandler (void)
{
  ARINC429_TRANSMITTER_TIMER->STATUS &= ~TIMER_STATUS_CNT_ARR_EVENT;

  //Отправить данные в 1 и 2 канал
  MDR_ARINC429T->DATA1_T = Arinc429TransmitterData;
  //MDR_ARINC429T->DATA2_T = Arinc429TransmitterData;

  Arinc429TransmitterWords++;

}

void
ARINC429R_IRQHandler (void)
{
  uint32_t err_status, fifo_status, temp, count;
  uint8_t address;
  static uint32_t arincDataOld = 0;

  err_status = ( MDR_ARINC429R->STATUS1 >> 14 ) & 0x0F; //так как включены только 4 канала
  fifo_status = MDR_ARINC429R->STATUS1 & 0x0F;    //так как включены только 4 канала

  if ( err_status != 0 )
    {
      //Сброс ошибки в канале
      if ( err_status & 0x01 )
	{
	  MDR_ARINC429R->CONTROL1 &= ~(0x01);
	  MDR_ARINC429R->CONTROL1 |= 0x01;
	  return;
	}
      else if ( err_status & 0x02 )
	{
	  MDR_ARINC429R->CONTROL1 &= ~(0x02);
	  MDR_ARINC429R->CONTROL1 |= 0x02;
	  return;
	}
      else if ( err_status & 0x04 )
	{
	  MDR_ARINC429R->CONTROL1 &= ~(0x04);
	  MDR_ARINC429R->CONTROL1 |= 0x04;
	  return;
	}
      else if ( err_status & 0x08 )
	{
	  MDR_ARINC429R->CONTROL1 &= ~(0x08);
	  MDR_ARINC429R->CONTROL1 |= 0x08;
	  return;
	}
    }

  //Принимаем данные по 1 каналу
  if ( fifo_status & 0x01 )
    {
      MDR_ARINC429R->CHANNEL = 0;
      while (( MDR_ARINC429R->STATUS1 & 0x01 ) != 0 )
	{
	  temp = MDR_ARINC429R->DATA_R;
	  if ( ( temp & 0xFF ) == ADF_ARINC429_LABEL_FRAQUENCY )
	    {
	      if ( arincDataOld == temp )
		{
		  Arinc429ReceiverData = temp;
		}
		arincDataOld = temp;
	    }
	}
    }
}

void Arinc429Test ( void )
{
  ADFArinc429Word32bit_t arinc429Word32;
  uint16_t fraq;

  arinc429Word32.Fraquency.Label =  ADF_ARINC429_LABEL_FRAQUENCY;
  arinc429Word32.Fraquency.NumberADF = Status.IndentifikatorPult;
  arinc429Word32.Fraquency.Tlg = Status.TelefonOrTelegraph;
  arinc429Word32.Fraquency.CompassOrAntenna = Status.CompassOrAntenna;
  arinc429Word32.Fraquency.Reserve = 0;

  fraq =   FraquencyCurrent & 1;
  fraq +=   ( ( ( FraquencyCurrent >> 1 ) % 10 ) << 1 );
  fraq +=   (( ( ( FraquencyCurrent >> 1 ) / 10 ) % 10 ) << 5);
  fraq +=   (( ( ( FraquencyCurrent >> 1 ) / 100 ) % 10 ) << 9) ;
  fraq +=   (( ( ( FraquencyCurrent >> 1 ) / 1000 ) % 10 ) << 13);
 arinc429Word32.Fraquency.Fraq = fraq;

  if ( Status.FunctionalControl == STATUS_FUNCTIONAL_CONTROL_ON )
    {
      arinc429Word32.Fraquency.Matrix = adfArinc429FraquencyMatrixControl;
    }
  else
    {
      arinc429Word32.Fraquency.Matrix = adfArinc429FraquencyMatrixNormal;
    }

  Arinc429TransmitterData = arinc429Word32.Data;

  arinc429Word32.Data = Arinc429ReceiverData;

  //эта строка нужна для отладки пульта при отсутствии приемника АРК (не подключено к шасси)
#if defined ( CFG_ADF_RECEIVER_OFF )
  arinc429Word32.Data = Arinc429TransmitterData;
#endif


  FraquencyInput =   ( arinc429Word32.Fraquency.Fraq & 1 ) +
			( ( ( arinc429Word32.Fraquency.Fraq >> 1 ) & 0x0F ) << 1 ) +
			( ( ( arinc429Word32.Fraquency.Fraq >> 5 ) & 0x0F ) << 1 ) * 10 +
			( ( ( arinc429Word32.Fraquency.Fraq >> 9 ) & 0x0F ) << 1 ) * 100 +
			( ( ( arinc429Word32.Fraquency.Fraq >> 13 ) & 0x0F ) << 1 ) * 1000;

  StatusInput.Fraquency = FraquencyInput;
  StatusInput.CompassOrAntenna = arinc429Word32.Fraquency.CompassOrAntenna;
  StatusInput.TelefonOrTelegraph = arinc429Word32.Fraquency.Tlg;

  if ( arinc429Word32.Fraquency.Matrix == adfArinc429FraquencyMatrixControl )
    StatusInput.FunctionalControl = 1;
  else
    StatusInput.FunctionalControl = 0;

}

ADFArinc429Fraquency_t FraquencyToArinc429( Fraquency_t fraq )
{
  ADFArinc429Fraquency_t arinc429Fraq;

  arinc429Fraq.Fraquency_05kHz = fraq & 0x01;
  arinc429Fraq.Fraquency_1kHz = ( fraq >> 1 ) % 10;
  arinc429Fraq.Fraquency_10kHz = ( ( fraq >> 1 ) / 10 ) % 10;
  arinc429Fraq.Fraquency_100kHz = ( ( fraq >> 1 ) / 100 ) % 10;
  arinc429Fraq.Fraquency_1000kHz = ( ( fraq >> 1 ) / 1000 ) % 10;

  return arinc429Fraq;
}
