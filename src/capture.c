/*
 * capture.c
 *
 *  Created on: 14 θώνÿ 2017 γ.
 *      Author: alexey
 */
#include "timer.h"

uint32_t captureHigh = 0;
uint32_t captureLow = 0;
uint32_t capturePeriod = 0;
uint32_t capturePeriodSrednee = 0;
uint32_t SignalHigh = 0;
uint32_t SignalHighSrednee = 0;
float SignalSkwagnost = 0;
float ProcentSkwagnost = 0;

void CaptureTimer( void )
{
    if ( capture_flag == 1 )
      {
	capture_flag = 0;
	capturePeriod = capture_value - captureHigh;
	captureHigh = capture_value;
	capturePeriodSrednee = capturePeriodSrednee * 7 / 8;
	capturePeriodSrednee += capturePeriod / 8;
      }

    if ( capture_flag2 == 1 )
      {
	capture_flag2 = 0;
	captureLow = capture_value2;
	if ( captureLow > captureHigh )
	  {
	    SignalHigh = captureLow - captureHigh;
	    SignalHighSrednee = (SignalHighSrednee*7/8) + (SignalHigh)/8;
	    SignalSkwagnost = (float)capturePeriod / SignalHigh;
	    ProcentSkwagnost = (float)100 / SignalSkwagnost;
	    if ( (uint32_t)ProcentSkwagnost == 24 || (uint32_t)ProcentSkwagnost == 25 )
	      {
		SignalHighSrednee = (SignalHighSrednee*7/8) + (SignalHigh)/8;
	      }
	  }
      }

}
