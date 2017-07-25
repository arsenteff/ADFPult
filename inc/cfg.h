#ifndef __CFG_H
#define __CFG_H

#include <stdint.h>

#define CFG_CPU_QUARTZ_MHZ 	8	//частота в МГц для икорректировки делителей настройки переферии
#define CFG_CPU_PLL_MULL        8 	//коэффициент умножения частоты кварцевого резонатора
#define CFG_CPU_CLOCK 		( CFG_CPU_QUARTZ_MHZ * CFG_CPU_PLL_MULL * 1000000U ) //Частота ядра в Гц

#define CFG_ARINC_DIV       (CFG_CPU_PLL_MULL * CFG_CPU_QUARTZ_MHZ)  //коэффициент деления частоты ядра контроллера до 1МГц

/*Если прошивка будет использоваться с приемником АРК, то закоментируйте строку ниже*/
//#define CFG_ADF_RECEIVER_OFF

#define CFG_PULT_ADF_351 0
#define CFG_PULT_ADF_40 2
#define CFG_PULT_ADF_353 1

extern uint8_t CFG_ADFPultType;

#endif /* __CFG_H */
