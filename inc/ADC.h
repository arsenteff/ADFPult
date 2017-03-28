/*
 * ADC.h
 *
 *  Created on: 03 марта 2017 г.
 *      Author: alexey
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>

void ADFADCInit( void );
uint32_t ADCGaletnikRead( void );
uint8_t ADCGaletnikValueToCanal( uint32_t value );

#endif /* INC_ADC_H_ */
