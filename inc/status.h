/*
 * status.h
 *
 *  Created on: 10 марта 2017 г.
 *      Author: alexey
 */

#ifndef INC_STATUS_H_
#define INC_STATUS_H_

#define STATUS_COMPASS 0
#define STATUS_ANTENNA 1

#define STATUS_TELEFON 0
#define STATUS_TELEGRAPH 1

#define STATUS_BLIGNIY_OFF 0
#define STATUS_BLIGNIY_ON 1

#define STATUS_DALNIY_OFF 0
#define STATUS_DALNIY_ON 1

#define STATUS_BLIGNIY_DALNIY_AUTOMAT 1

#define STATUS_SHASSY_ZEMLYA 0
#define STATUS_SHASSY_VOZDUH 1

#define STATUS_MARKER_OFF 0
#define STATUS_MARKER_ON  1

#define STATUS_DPRS_AUTOMAT_OFF  0
#define STATUS_DPRS_AUTOMAT_ON   1

#define STATUS_INDENTIFIKATOR_0 0
#define STATUS_INDENTIFIKATOR_1 1
#define STATUS_INDENTIFIKATOR_2 2
#define STATUS_INDENTIFIKATOR_3 3

#define STATUS_FUNCTIONAL_CONTROL_OFF 0
#define STATUS_FUNCTIONAL_CONTROL_ON  1

typedef struct __attribute__((packed))
{
  unsigned CompassOrAntenna 	: 1;
  unsigned TelefonOrTelegraph 	: 1;
  unsigned FunctionalControl	: 1;
  unsigned Fraquency		:16;
}
StatusInput_t;

typedef struct
{
  unsigned CompassOrAntenna 	: 1;
  unsigned TelefonOrTelegraph 	: 1;
  unsigned Bligniy 		: 1;
  unsigned Dalniy 		: 1;
  unsigned Shassy		: 1;
  unsigned Marker		: 1;
  unsigned MarkerActive		: 1;
  unsigned DPRSAutomat		: 1;
  unsigned IndentifikatorPult	: 2;
  unsigned FunctionalControl	: 1;
  unsigned DayOrNight		: 1;
}
Status_t;

extern Status_t Status;
extern StatusInput_t StatusInput;

#endif /* INC_STATUS_H_ */
