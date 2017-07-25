#ifndef __TIMER_H
#define __TIMER_H

#include "stdint.h"

void TimerTime_Initialization (void);

typedef uint32_t Time_t;
Time_t TimeGet( void );
Time_t TimeInterval( Time_t time );

#define TIME_6_SEC ((Time_t) 240000)
#define TIME_10_SEC ((Time_t) 400000)
#define TIME_1_SEC ((Time_t) 40000)
#define TIME_400_MSC ((Time_t) 16000)
#define TIME_750_MSC ((Time_t) 30000)
#define TIME_850_MSC ((Time_t) 38000)
#define TIME_800_MSC ((Time_t) 32000)
#define TIME_900_MSC ((Time_t) 36000)
#define TIME_500_MS ((Time_t) 20000)
#define TIME_200_MS ((Time_t) 8000)
#define TIME_320_MS ((Time_t) 12800)
#define TIME_200_MS ((Time_t) 8000)
#define TIME_100_MS ((Time_t) 4000)
#define TIME_NULL ((Time_t) 0)
#define TIME_30_SEC ((Time_t) 1200000)

#define TIME_1_MS ((Time_t) 40)
#define TIME_3_MS ((Time_t) 120)
#define TIME_1500_MKS 64
#define TIME_5_MS ((Time_t) 200)
#define TIME_10_MS ((Time_t) 400)
#define TIME_2_MS ((Time_t) 80)

#define TIMER_TIME_PERIOD_MKS 25

#define TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX 10
#define TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN 1

extern uint32_t capture_value;
extern uint32_t capture_value2;
extern uint32_t capture_flag;
extern uint32_t capture_flag2;

extern uint8_t TimerDlitelnostSkwagnostiIndikator;
extern uint8_t PultDataInput[ 8 ];
#endif /*__TIMER_H*/
