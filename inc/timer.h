#ifndef __TIMER_H
#define __TIMER_H

#include "stdint.h"

void TimerTime_Initialization (void);

typedef uint32_t Time_t;
Time_t TimeGet( void );
Time_t TimeInterval( Time_t time );

#define TIME_6_SEC ((Time_t) 60000)
#define TIME_10_SEC ((Time_t) 100000)
#define TIME_1_SEC ((Time_t) 10000)
#define TIME_400_MSC ((Time_t) 4000)
#define TIME_750_MSC ((Time_t) 7500)
#define TIME_850_MSC ((Time_t) 8500)
#define TIME_800_MSC ((Time_t) 8000)
#define TIME_900_MSC ((Time_t) 9000)
#define TIME_500_MS ((Time_t) 5000)
#define TIME_200_MS ((Time_t) 2000)
#define TIME_320_MS ((Time_t) 3200)
#define TIME_200_MS ((Time_t) 2000)
#define TIME_100_MS ((Time_t) 1000)
#define TIME_NULL ((Time_t) 0)
#define TIME_30_SEC ((Time_t) 300000)

#define TIME_1_MS ((Time_t) 10)
#define TIME_3_MS ((Time_t) 30)
#define TIME_1500_MKS 16
#define TIME_5_MS ((Time_t) 50)
#define TIME_10_MS ((Time_t) 100)
#define TIME_2_MS ((Time_t) 20)

#define TIMER_TIME_PERIOD_MKS 100

#define TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MAX 8
#define TIMER_DLITELNOST_SKWAGNOSTI_INDIKATOR_MIN 1

extern uint8_t TimerDlitelnostSkwagnostiIndikator;
#endif /*__TIMER_H*/
