/*
 * signal.h
 *
 *  Created on: 17 марта 2017 г.
 *      Author: alexey
 */

#ifndef INC_SIGNAL_H_
#define INC_SIGNAL_H_

typedef enum
{
  SignalBligniy = 0,
  SignalDalniy = 1,
  SignalShassy = 2,
  SignalMarker = 3,
  SignalPult1  = 4,
  SignalPult2  = 5,
  SignalDPRSAutomat = 6,
  SignalFunctionalControl = 7,
  SignalDayOrNightADF351 = 8,
  SignalDayOrNightADF353 = 9
}
Signal_t;

void SignalTest ( void );

#endif /* INC_SIGNAL_H_ */
