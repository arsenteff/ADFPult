#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

#define PULT_CFG_ADF_MEMORY_ADRESS  0x0001E000UL

#define PULT_CANAL_MEMORY_ADRESS_START  0x0001F000UL
#define PULT_CANAL_MEMORY_ADRESS_END    0x0001F100UL
#define PULT_CANAL_MEMORY_DATA_EMPTY    0xFFFF
#define PULT_CANAL_COUNT_ADF_351        11
#define PULT_CANAL_COUNT_ADF_40        	11
#define PULT_CANAL_COUNT_ADF_353        18
#define PULT_CANAL_ALL_ADF_351          	(PULT_CANAL_COUNT_ADF_351*2+1)
#define PULT_CANAL_ALL_ADF_40           	(PULT_CANAL_COUNT_ADF_40*2+1)
#define PULT_CANAL_ALL_ADF_353          	(PULT_CANAL_COUNT_ADF_353*2+1)
#define PULT_CANAL_ALL_MAX          		PULT_CANAL_ALL_ADF_353

#define PULT_CANAL_INDIKATOR_NUMBER_ADF_351	PULT_CANAL_ALL_ADF_351
#define PULT_CANAL_INDIKATOR_NUMBER_ADF_40	PULT_CANAL_ALL_ADF_40
#define PULT_CANAL_INDIKATOR_NUMBER_ADF_353	PULT_CANAL_ALL_ADF_353
#define PULT_CANAL_PLAVNO_NUMBER_ADF_351	(PULT_CANAL_COUNT_ADF_351+1)
#define PULT_CANAL_PLAVNO_NUMBER_ADF_40		(PULT_CANAL_COUNT_ADF_40+1)
#define PULT_CANAL_PLAVNO_NUMBER_ADF_353	(PULT_CANAL_COUNT_ADF_353+1)
#define PULT_CANAL_AUTOMAT_P			(PULT_CANAL_COUNT_ADF_353+2)

extern void Memory_EEPROMWriteHalfWord( unsigned int Address, unsigned short int Data );
extern void Memory_EEPROMErasePage( unsigned int Address );

typedef unsigned short int MemoryPultFrequency_t;
typedef unsigned char MemoryPultCanalNum_t;

MemoryPultFrequency_t MemoryPultCanalStore (MemoryPultCanalNum_t canal, MemoryPultFrequency_t frequency);
MemoryPultFrequency_t MemoryPultCanalLoad( MemoryPultCanalNum_t Canal);
void MemoryPultCFGADFStore ( void );
uint16_t MemoryPultCFGADFLoad ( void );

uint8_t PULT_CANAL_COUNT( void );
uint8_t PULT_CANAL_ALL( void );
uint8_t PULT_CANAL_INDIKATOR_NUMBER( void );
uint8_t PULT_CANAL_PLAVNO_NUMBER( void );

#endif /* __MEMORY_H */


