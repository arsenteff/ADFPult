#include "cfg.h"
#include "timer.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_timer.h"
#include "state.h"
#include "adc.h"
#include "fraquency.h"
#include "indikator.h"

uint32_t capture_value = 0;
uint32_t capture_value2 = 0;
uint32_t capture_flag = 0;
uint32_t capture_flag2 = 0;

uint8_t TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;

uint8_t PultDataInput[ 8 ];

static const uint32_t TableIndikatorHG[] =
    {
	pinIndikatorHG1,
	pinIndikatorHG2,
	pinIndikatorHG3,
	pinIndikatorHG4,
	pinIndikatorHG5
    };

static const uint8_t TableDlitelnostSkwagnosti[] =
    {
	0, 16, 25, 32, 39, 44, 49, 53, 56, 60
    };

#define TIMER_TIME_IRQHandler Timer1_IRQHandler

#define TIMER_TIME MDR_TIMER1
#define TIMER_TIME_RST_CLK_PCLK RST_CLK_PCLK_TIMER1

uint32_t TimerTimeCount;

void Timer4ConfigADF353(void);
void Timer4ConfigADF351(void);

void
TimerTime_Initialization (void)
{
  TIMER_CntInitTypeDef init;

  TimerTimeCount = 0;

  /* Включить тактирование таймера */
  RST_CLK_PCLKcmd ( TIMER_TIME_RST_CLK_PCLK, ENABLE);

  /* Initializes the TIMER Counter */
  init.TIMER_IniCounter = 0x00000000;
  init.TIMER_Prescaler = CFG_CPU_CLOCK / 1000000;
  init.TIMER_Period = 1 * TIMER_TIME_PERIOD_MKS;
  init.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
  init.TIMER_CounterDirection = TIMER_CntDir_Up;
  init.TIMER_EventSource = TIMER_EvSrc_None;
  init.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
  init.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;

  TIMER_CntInit ( TIMER_TIME, &init);

  /* Enable TIMER clock */
  TIMER_BRGInit ( TIMER_TIME, TIMER_HCLKdiv1);

  /* Разрешение генерировать прерывание при CNT == ARR */
  TIMER_ITConfig ( TIMER_TIME, TIMER_IE_CNT_ARR_EVENT_IE, ENABLE);

  /* Enable TIMER */
  TIMER_Cmd ( TIMER_TIME, ENABLE);

  NVIC_EnableIRQ (TIMER1_IRQn);

  if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
    {
      Timer4ConfigADF353();
    }
  else if ( CFG_ADFPultType == CFG_PULT_ADF_351 )
    {
      Timer4ConfigADF351();
    }
}


void TIMER_TIME_IRQHandler (void)
{
  static uint8_t j = 0;
  static uint8_t i = 0;
  static Time_t time;
  Time_t timeSkwagnosti;

  TIMER_TIME->STATUS &= ~TIMER_STATUS_CNT_ARR_EVENT;
  TimerTimeCount++;

  timeSkwagnosti = TableDlitelnostSkwagnosti[ TimerDlitelnostSkwagnostiIndikator - 1 ];
  if ( time >= TIME_1500_MKS - timeSkwagnosti )
    {
      StateReset( TableIndikatorHG[ j ] );
    }


  if ( time == TIME_1500_MKS )
    {
      //StateReset( TableIndikatorHG[ j ] );
      j++;
      if ( j >= 5) j = 0;
      IndikatorSymbolOut( TableIndikatorHG[ j ], TableFraquencyCurrent[ j ] );
      StateSet( TableIndikatorHG[ j ] );
      time = 0;
    }
  else
    {
      time++;
    }
}

Time_t TimeGet( void )
{
  return TimerTimeCount;
}

Time_t TimeInterval( Time_t time )
{
  return TimerTimeCount - time;
}


void Timer4ConfigADF353(void)
{
	TIMER_CntInitTypeDef	Timer_Count;
	TIMER_ChnInitTypeDef	Timer_Channel;

	PORT_InitTypeDef init;
	uint32_t pos;

	RST_CLK_PCLKcmd( RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_TIMER4 | RST_CLK_PCLK_TIMER3 , ENABLE );

	init.PORT_FUNC        = PORT_FUNC_ALTER;
	init.PORT_MODE        = PORT_MODE_DIGITAL;
	init.PORT_Pin = 1 << 8;
	PORT_Init( MDR_PORTA , &init );

	init.PORT_FUNC        = PORT_FUNC_OVERRID;
	init.PORT_MODE        = PORT_MODE_DIGITAL;
	init.PORT_Pin = 1 << 0;
	PORT_Init( MDR_PORTB , &init );

	MDR_RST_CLK->PER_CLOCK |= 1 << 19;     // Разрешаем тактирование таймера 4
	MDR_RST_CLK->UART_CLOCK |= 0 << 16;   // Делитель тактовой частоты для таймера 4 = 1
	MDR_RST_CLK->UART_CLOCK |= 1 << 26;   // Разрешаем тактирование таймера 4

	MDR_TIMER4->CNT = 0x00;  // Основной счётчик таймера
	MDR_TIMER4->PSG = 1000;  // Делитель частоты при счёте основного счётчика
	MDR_TIMER4->ARR = 0xFFFFFFFF;  // Основание счёта основного счётчика
	MDR_TIMER4->CNTRL = 0x7 << 8 | 0x0 << 6 | 0x0 << 3 | 0x1 << 0; // Источник события - событие на 1-м канале | счёт вверх | таймер включен
	MDR_TIMER4->CH4_CNTRL = 1 << 15 | 0x3 << 4; // Канал работает в режиме "Захват" | Событие для CAP - положительный фронт по 1-му каналу
	MDR_TIMER4->CH4_CNTRL1 = 0x00000000;
	MDR_TIMER4->CH4_CNTRL2 = 1 << 2 | 0x3 << 0; // CCR используется | Событие для CAP1 - отрицательный фронт по 1-му каналу
	MDR_TIMER4->IE = 0x8 << 13 | 0x8 << 5 ; // Разрешены прерывания при CAP и CAP1

	NVIC_EnableIRQ (TIMER4_IRQn);  // Разрешаем прерывания от таймера 4

	MDR_RST_CLK->TIM_CLOCK |= 1 << 26;

	MDR_TIMER3->CNT = 0x00;  // Основной счётчик таймера
	MDR_TIMER3->PSG = 1000;  // Делитель частоты при счёте основного счётчика
	MDR_TIMER3->ARR = 0xFFFFFFFF;  // Основание счёта основного счётчика
	MDR_TIMER3->CNTRL = 0x4 << 8 | 0x0 << 6 | 0x0 << 3 | 0x1 << 0; // Источник события - событие на 1-м канале | счёт вверх | таймер включен
	MDR_TIMER3->CH1_CNTRL = 1 << 15 | 0x0 << 4; // Канал работает в режиме "Захват" | Событие для CAP - положительный фронт по 1-му каналу
	MDR_TIMER3->CH1_CNTRL1 = 0x00000000;
	MDR_TIMER3->CH1_CNTRL2 = 1 << 2 | 0x1 << 0; // CCR используется | Событие для CAP1 - отрицательный фронт по 1-му каналу
	MDR_TIMER3->IE = 0x1 << 13 | 0x1 << 5 | 0x1 << 0; // Разрешены прерывания при CAP и CAP1

	NVIC_EnableIRQ (TIMER3_IRQn);  // Разрешаем прерывания от таймера 4

	/*
	TIMER_BRGInit(MDR_TIMER4, TIMER_HCLKdiv1);
	TIMER_DeInit(MDR_TIMER4);

	TIMER_CntStructInit(&Timer_Count);
	TIMER_ChnStructInit(&Timer_Channel);

	Timer_Count.TIMER_CounterDirection = TIMER_CntDir_Up;
	Timer_Count.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;
	Timer_Count.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
	Timer_Count.TIMER_EventSource = TIMER_EvSrc_None;
	Timer_Count.TIMER_Prescaler = 0;
	Timer_Count.TIMER_Period = 0xFFFFFFFF;
	Timer_Count.TIMER_IniCounter = 0;

	TIMER_CntInit(MDR_TIMER4, &Timer_Count);

	Timer_Channel.TIMER_CH_Number = TIMER_CHANNEL2;
	Timer_Channel.TIMER_CH_Mode = TIMER_CH_MODE_CAPTURE;
	Timer_Channel.TIMER_CH_EventSource = TIMER_CH_EvSrc_PE;
	Timer_Channel.TIMER_CH_CCR1_Ena = ENABLE;
	Timer_Channel.TIMER_CH_CCR1_EventSource = TIMER_CH_EvSrc_NE;

	TIMER_ChnInit(MDR_TIMER4, &Timer_Channel);

	TIMER_ITConfig(MDR_TIMER4, (TIMER_STATUS_CCR_CAP_CH2 | TIMER_STATUS_CNT_ZERO | TIMER_STATUS_CCR_CAP1_CH2 ), ENABLE);

	TIMER_Cmd(MDR_TIMER4, ENABLE);

	NVIC_EnableIRQ (TIMER4_IRQn);*/
}

void Timer4ConfigADF351(void)
{
	TIMER_CntInitTypeDef	Timer_Count;
	TIMER_ChnInitTypeDef	Timer_Channel;

	PORT_InitTypeDef init;
	uint32_t pos;

	RST_CLK_PCLKcmd( RST_CLK_PCLK_PORTA | RST_CLK_PCLK_TIMER4 , ENABLE );

	init.PORT_FUNC        = PORT_FUNC_ALTER;
	init.PORT_MODE        = PORT_MODE_DIGITAL;
	init.PORT_Pin = 1 << 8 | 1 << 6 | 1 << 10;
	PORT_Init( MDR_PORTA , &init );

	MDR_RST_CLK->PER_CLOCK |= 1 << 19;     // Разрешаем тактирование таймера 4
	MDR_RST_CLK->UART_CLOCK |= 0 << 16;   // Делитель тактовой частоты для таймера 4 = 1
	MDR_RST_CLK->UART_CLOCK |= 1 << 26;   // Разрешаем тактирование таймера 4

	/*
	MDR_TIMER4->CNT = 0x00;  // Основной счётчик таймера
	MDR_TIMER4->PSG = 1000;  // Делитель частоты при счёте основного счётчика
	MDR_TIMER4->ARR = 0xFFFFFFFF;  // Основание счёта основного счётчика
	MDR_TIMER4->CNTRL = 0x5 << 8 | 0x0 << 6 | 0x0 << 3 | 0x1 << 0; // Источник события - событие на 1-м канале | счёт вверх | таймер включен
*/
	MDR_TIMER4->CNT = 0x00;  // Основной счётчик таймера
	MDR_TIMER4->PSG = 1000;  // Делитель частоты при счёте основного счётчика
	MDR_TIMER4->ARR = 0xFFFFFFFF;  // Основание счёта основного счётчика
	MDR_TIMER4->CNTRL = 0x5 << 8 | 0x0 << 6 | 0x0 << 3 | 0x1 << 0; // Источник события - событие на 1-м канале | счёт вверх | таймер включен

	//Сигнал чтение
	MDR_TIMER4->CH4_CNTRL = 1 << 15 | 0x3 << 4 | 0x3 << 0; // Канал работает в режиме "Захват" | Событие для CAP - положительный фронт по 2-му каналу
	MDR_TIMER4->CH4_CNTRL1 = 0x00000000;
	MDR_TIMER4->CH4_CNTRL2 = 1 << 2 | 0x3 << 0; // CCR используется | Событие для CAP1 - отрицательный фронт по 2-му каналу

	//Сигнал запись
	MDR_TIMER4->CH1_CNTRL = 1 << 15 | 0x0 << 4 | 0x3 << 0; // Канал работает в режиме "Захват" | Событие для CAP - положительный фронт по 1-му каналу
	MDR_TIMER4->CH1_CNTRL1 = 0x00000000;
	MDR_TIMER4->CH1_CNTRL2 = 1 << 2 | 0x1 << 0; // CCR используется | Событие для CAP1 - отрицательный фронт по 1-му каналу

	//Сигнал шим яркость индикатора
	MDR_TIMER4->CH2_CNTRL = 1 << 15 | 0x2 << 4; // Канал работает в режиме "Захват" | Событие для CAP - положительный фронт по 3-му каналу
	MDR_TIMER4->CH2_CNTRL1 = 0x00000000;
	MDR_TIMER4->CH2_CNTRL2 = 1 << 2 | 0x2 << 0; // CCR используется | Событие для CAP1 - отрицательный фронт по 3-му каналу

	MDR_TIMER4->IE = 0xB << 13 | 0xB << 5 ; // Разрешены прерывания при CAP и CAP1 по 1,2 и 4 каналам

	NVIC_EnableIRQ (TIMER4_IRQn);  // Разрешаем прерывания от таймера 4
}


void Timer3_IRQHandler()
{
  uint32_t zadr;

	if(TIMER_GetITStatus(MDR_TIMER3, TIMER_STATUS_CCR_CAP_CH1) == SET)
	{
	    MDR_PORTC->SETTX = 1 << 12;
		TIMER_ClearFlag(MDR_TIMER3, TIMER_STATUS_CCR_CAP_CH1);
		capture_value = TIMER_GetChnCapture(MDR_TIMER3, TIMER_CHANNEL1);
		capture_flag = 1;
		for ( zadr = 0; zadr < 1000; zadr++ );
	    MDR_PORTC->CLRTX = 1 << 12;
	}

	if(TIMER_GetITStatus(MDR_TIMER3, TIMER_STATUS_CCR_CAP1_CH1) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER3, TIMER_STATUS_CCR_CAP1_CH1);
		capture_value2 = TIMER_GetChnCapture1(MDR_TIMER3, TIMER_CHANNEL1);
		capture_flag2 = 1;
	}

	if(TIMER_GetITStatus(MDR_TIMER3, TIMER_STATUS_CNT_ZERO) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER3, TIMER_STATUS_CNT_ZERO);
	}
}


void Timer4_IRQHandler()
{
  uint8_t data;
  uint8_t adress;

  if ( CFG_ADFPultType == CFG_PULT_ADF_353 )
    {
	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH4) == SET)
	{
	    MDR_PORTC->SETTX = 1 << 12;
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH4);
		capture_value = TIMER_GetChnCapture(MDR_TIMER4, TIMER_CHANNEL4);
		capture_flag = 1;
	    MDR_PORTC->CLRTX = 1 << 12;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH4) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH4);
		capture_value2 = TIMER_GetChnCapture1(MDR_TIMER4, TIMER_CHANNEL4);
		capture_flag2 = 1;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CNT_ZERO) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CNT_ZERO);
		capture_flag = 3;
	}
    }

  if ( CFG_ADFPultType == CFG_PULT_ADF_351 )
    {
	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH1) == SET)
	{
		MDR_PORTC->SETTX = 1 << 12;
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH1);
		PultDataInput[ StatePultAdressGet() ] = StatePultDataGet();


	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH1) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH1);
		capture_value2 = TIMER_GetChnCapture1(MDR_TIMER4, TIMER_CHANNEL1);
		capture_flag2 = 2;
		MDR_PORTC->CLRTX = 1 << 12;
	}

      if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH4) == SET)
	{
		MDR_PORTC->SETTX = 1 << 13;
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH4);
		//capture_value = TIMER_GetChnCapture(MDR_TIMER4, TIMER_CHANNEL4);
		MDR_PORTC->OE |= 0x0F << 5;
		adress = StatePultAdressGet();
		data = TableSwitchCurrent[ adress ];
		MDR_PORTC->CLRTX =  ~data << 5;
		MDR_PORTC->SETTX = data << 5;
		capture_flag = 1;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH4) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH4);
		capture_value2 = TIMER_GetChnCapture1(MDR_TIMER4, TIMER_CHANNEL4);
		MDR_PORTC->OE &= ~(0x0F << 5);
		MDR_PORTC->CLRTX = 1 << 13;
		capture_flag2 = 1;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH2) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP_CH2);
		capture_value = TIMER_GetChnCapture1(MDR_TIMER4, TIMER_CHANNEL2);
		capture_flag = 1;
		MDR_PORTC->SETTX = 1 << 14;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH2) == SET)
	{

		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CCR_CAP1_CH2);
		capture_value2 = TIMER_GetChnCapture1(MDR_TIMER4, TIMER_CHANNEL2);
		capture_flag2 = 1;
		MDR_PORTC->CLRTX = 1 << 14;
	}

	if(TIMER_GetITStatus(MDR_TIMER4, TIMER_STATUS_CNT_ZERO) == SET)
	{
		TIMER_ClearFlag(MDR_TIMER4, TIMER_STATUS_CNT_ZERO);
		capture_flag = 3;
	}
    }

}

