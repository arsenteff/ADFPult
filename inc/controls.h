/*
 * controls.h
 *
 *  Created on: 06 марта 2017 г.
 *      Author: alexey
 */

#ifndef INC_CONTROLS_H_
#define INC_CONTROLS_H_

#include <stdint.h>
#include "timer.h"

#define CONTROLS_COUNT 12
typedef enum
{
  cntrlOnes_Plus,
  cntrlOnes_Minus,
  cntrlTens_Plus,
  cntrlTens_Minus,
  cntrlHundreds_Plus,
  cntrlHundreds_Minus,
  cntrlWriteFraquency,
  cntrlControl,
  cntrlTelefon,
  cntrlTelegraph,
  cntrlCompass,
  cntrlAntenna,
  cntrlDayOrNight
}
ControlsElements_t;

uint8_t ControlsTimeActive( ControlsElements_t control, Time_t time );
void ControlsTimeActiveClear( ControlsElements_t control );
uint8_t ControlGaletnikCanalTest( void );
uint8_t ControlGaletnikCanalGet( void );
uint8_t ControlsTest ( ControlsElements_t control );

#endif /* INC_CONTROLS_H_ */
