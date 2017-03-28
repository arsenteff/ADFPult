#include "memory.h"
#include "indikator.h"
//#include "MDR1986VE1T.h"
#include "MDR32F9Qx_eeprom.h"
#include "cfg.h"

typedef uint16_t MemoryPultFrequency_t;

static int InterruptsSave;
static MemoryPultFrequency_t MemoryTableFraquencyCanal[ PULT_CANAL_ALL ];

static void MemoryFraquencyCanalSaveAll( void );
static void MemoryFraquencyCanalResaveAll( uint8_t canal, MemoryPultFrequency_t frq );

static void
InterruptsDisable(void)
{
  InterruptsSave = NVIC->ICER[0];
  NVIC->ICER[0] = 0xFFFFFFFF;
}

static void
InterruptsEnable(void)
{
  NVIC->ISER[0] = InterruptsSave;
}

void
Memory_EEPROMWriteHalfWord( unsigned int Address, unsigned short int Data )
{
        InterruptsDisable();
        EEPROM_ProgramHalfWord( Address, 0, Data );
        InterruptsEnable();
}

void
Memory_EEPROMErasePage( unsigned int Address )
{
        InterruptsDisable();
        EEPROM_ErasePage(Address, 0);
        InterruptsEnable();
}

void MemoryPultCFGADFStore ( void )
{
  uint16_t* memoryPtrCFGADF = (MemoryPultFrequency_t*)(PULT_CFG_ADF_MEMORY_ADRESS);

  if ( *memoryPtrCFGADF == PULT_CANAL_MEMORY_DATA_EMPTY )
    {
      Memory_EEPROMWriteHalfWord ( (unsigned int) memoryPtrCFGADF, CFG_ADFPultType );
    }

}

uint16_t MemoryPultCFGADFLoad ( void )
{
  uint16_t* memoryPtrCFGADF = (MemoryPultFrequency_t*)(PULT_CFG_ADF_MEMORY_ADRESS);

  return *memoryPtrCFGADF;
}

MemoryPultFrequency_t MemoryPultCanalStore (MemoryPultCanalNum_t canal, MemoryPultFrequency_t frequency)
{
        MemoryPultFrequency_t* p;
        MemoryPultFrequency_t* memoryPtr = (MemoryPultFrequency_t*)(PULT_CANAL_MEMORY_ADRESS_START);
        MemoryPultFrequency_t  memoryFrequency;
        int offset, step;

        if (canal && (canal <= PULT_CANAL_ALL))
        {
                step = (canal - 1);

                for (offset = step;
                     offset < (PULT_CANAL_MEMORY_ADRESS_END - PULT_CANAL_MEMORY_ADRESS_START )/sizeof(MemoryPultFrequency_t);
                     offset += ( PULT_CANAL_ALL ) )
                {
			p = (memoryPtr + offset);
                        memoryFrequency = *p;
                        if (memoryFrequency == PULT_CANAL_MEMORY_DATA_EMPTY)
                        {
                                memoryFrequency = *(memoryPtr + offset - PULT_CANAL_ALL);
                                if (memoryFrequency != frequency)
                                        Memory_EEPROMWriteHalfWord ((unsigned int) p, frequency);
                                return frequency;
                        }
                }
                //спасение индикаторов от выгорания во время стирания страницы памяти FLASH
                IndikatorOff();
                MemoryFraquencyCanalSaveAll();
                Memory_EEPROMErasePage ( PULT_CANAL_MEMORY_ADRESS_START );
                MemoryFraquencyCanalResaveAll( canal, frequency );
                //Memory_EEPROMWriteHalfWord ((unsigned int)( memoryPtr + step ), frequency);
                return frequency;
        }
        return 0;
}

MemoryPultFrequency_t MemoryPultCanalLoad( MemoryPultCanalNum_t Canal)
{
  MemoryPultFrequency_t *p,d=0;
        uint32_t step;

        step = ((Canal - 1) * sizeof(MemoryPultFrequency_t));

        if (Canal) {
                p=(MemoryPultFrequency_t*)(PULT_CANAL_MEMORY_ADRESS_START+step);
                for (; p<(MemoryPultFrequency_t *)(PULT_CANAL_MEMORY_ADRESS_END); p+=PULT_CANAL_ALL)
                {
		  if (*p == 0xFFFF)
		  {
			  d=*(p-PULT_CANAL_ALL);
			  return d;
		  }
                }
                return d=*(p-PULT_CANAL_ALL);
        }
        return d;
}

void MemoryFraquencyCanalSaveAll( void )
{
  for ( int i = 0; i < PULT_CANAL_ALL; i++ )
    {
      MemoryTableFraquencyCanal[ i ] = MemoryPultCanalLoad( i + 1 );
    }
}

void MemoryFraquencyCanalResaveAll( uint8_t canal, MemoryPultFrequency_t frq )
{
  for ( int i = 1; i <= PULT_CANAL_ALL; i++ )
    {
      if ( canal != i )
	{
	  MemoryPultCanalStore( i , MemoryTableFraquencyCanal[ i - 1 ] );
	}
      else
	{
	  MemoryPultCanalStore( i , frq );
	}
    }
}
