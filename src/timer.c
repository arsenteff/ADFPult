#include "cfg.h"
#include "timer.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_timer.h"
#include "state.h"
#include "adc.h"
#include "fraquency.h"
#include "indikator.h"

uint8_t TimerDlitelnostSkwagnostiIndikator = TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN;

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
	0, 4, 7, 9, 11, 12, 13, 14
    };

#define TIMER_TIME_IRQHandler Timer1_IRQHandler

#define TIMER_TIME MDR_TIMER1
#define TIMER_TIME_RST_CLK_PCLK RST_CLK_PCLK_TIMER1

uint32_t TimerTimeCount;

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

}


void TIMER_TIME_IRQHandler (void)
{
  static uint8_t j = 0;
  static uint8_t i = 0;
  static Time_t time;
  Time_t timeSkwagnosti;

  TIMER_TIME->STATUS &= ~TIMER_STATUS_CNT_ARR_EVENT;

  timeSkwagnosti = TableDlitelnostSkwagnosti[ TimerDlitelnostSkwagnostiIndikator - 1 ];
  if ( TimeInterval( time ) >= TIME_1500_MKS - timeSkwagnosti )
    {
      StateReset( TableIndikatorHG[ j ] );
    }


  if ( TimerTimeCount % TIME_1500_MKS == 0 )
    {
      StateReset( TableIndikatorHG[ j ] );
      j++;
      if ( j >= 5) j = 0;
      IndikatorSymbolOut( TableIndikatorHG[ j ], TableFraquencyCurrent[ j ] );
      StateSet( TableIndikatorHG[ j ] );
      time = TimerTimeCount;
    }

  TimerTimeCount++;
}

Time_t TimeGet( void )
{
  return TimerTimeCount;
}

Time_t TimeInterval( Time_t time )
{
  return TimerTimeCount - time;
}

