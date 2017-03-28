#ifndef __ADF_ARINC429_H
#define __ADF_ARINC429_H

#include <stdint.h>
#include "fraquency.h"
#include "cpu.h"

#define ADF_ARINC429_LABEL_KUR 0x72 /* 162 (116) */
#define ADF_ARINC429_LABEL_FRAQUENCY 0x1A /* 032 (130) */
#define ADF_ARINC429_LABEL_FRAQUENCY_DISTANT 0x1A /* 032 (130) */
#define ADF_ARINC429_LABEL_FRAQUENCY_NEAREST 0x19 /* 031 (230) */
#define ADF_ARINC429_LABEL_MASK 0x00FF

#define ADF_ARINC429_FRAQUENCY_DISTANT(FRQ) (((FRQ%10 / 5) + ((FRQ/10 % 10) << 1) + ((FRQ/100 % 10) << 5) + ((FRQ/1000 % 10) << 9) + ((FRQ/10000 % 10) << 13))<<13) + 032
#define ADF_ARINC429_FRAQUENCY_NEAREST(FRQ) (((FRQ%10 / 5) + ((FRQ/10 % 10) << 1) + ((FRQ/100 % 10) << 5) + ((FRQ/1000 % 10) << 9) + ((FRQ/10000 % 10) << 13))<<13) + 031

#define ADF_ARINC429_NUMBER_ADF_FOR_ALL 0

//êîýôôèöèåíò äåëåíèÿ ÷àñòîòû ÿäðà êîíòðîëëåðà äî 1ÌÃö
#define ARINC429_DIV_1MGZ      			(CFG_CPU_PLL_MULL * CFG_CPU_QUARTZ_MHZ)
#define ARINC429_DIV_RECEIVER_MAPPING 	(ARINC429_DIV_1MGZ)
#define ARINC429_DIV_RECEIVER_NAVIGATOR (ARINC429_DIV_1MGZ*2)
#define ARINC429_DIV_TRANSMITTER_MAPPING 	ARINC429_DIV_1MGZ

#define ARINC429_DIV_100_KBIT 	ARINC429_DIV_1MGZ
#define ARINC429_DIV_50_KBIT 	(ARINC429_DIV_1MGZ*2)

//0 - ñêîðîñòü 100êÃö, 1 - ñêîðîñòü 12,5êÃö
#define ARINC429_SPEED        	0


typedef enum /* ÍÎÌÅÐ ÀÐÊ */
{
  adfArinc429KurNumberADF_All,  /* 0: ÄËß ÂÑÅÕ */
  adfArinc429KurNumberADF_1,    /* 1: ÄËß ÀÐÊ 1 */
  adfArinc429KurNumberADF_2,    /* 2: ÄËß ÀÐÊ 2 */
  adfArinc429KurNumberADF_3,    /* 3: ÄËß ÀÐÊ 3 */
}
ADFArinc429NumberADF_t;

typedef enum /* ÌÀÒÐÈÖÀ ÊÓÐà */
{
  adfArinc429KurMatrixError = 0x00,    /* 0: ÎÒÊÀÇ */
  adfArinc429KurMatrixNoData = 0x01,   /* 1: ÍÅÒ ÄÀÍÍÛÕ */
  adfArinc429KurMatrixControl = 0x02,  /* 2: ÊÎÍÒÐÎËÜ */
  adfArinc429KurMatrixNormal = 0x03,   /* 3: ÍÎÐÌÀËÜÍÀß ÐÀÁÎÒÀ */
}
ADFArinc429KurMatrix_t;

typedef enum /* ÌÀÒÐÈÖÀ ×ÀÑÒÎÒÛ */
{
  adfArinc429FraquencyMatrixNormal = 0x00,   /* 0: ÍÎÐÌÀËÜÍÀß ÐÀÁÎÒÀ */
  adfArinc429FraquencyMatrixNoData = 0x01,   /* 1: ÍÅÒ ÄÀÍÍÛÕ */
  adfArinc429FraquencyMatrixControl = 0x02,  /* 2: ÊÎÍÒÐÎËÜ */
  adfArinc429FraquencyMatrixReserve = 0x03,  /* 3: ÐÅÇÅÐÂ */
}
ADFArinc429FraquencyMatrix_t;

typedef struct /* ÑËÎÂÎ ÊÓÐà ÏÎ ARINC 429 */
{
  unsigned Label        : 8;    /* ÕÀÐÀÊÒÅÐÈÑÒÈÊÀ */
  unsigned NumberADF    : 2;    /* ÍÎÌÅÐ ÀÐÊ */
  unsigned NotUsed      : 6;    /* Äîëæíû áûòü íóëè */
  unsigned Kur          :13;    /* ÊÎÄ ÊÓÐÀ */
  unsigned Matrix       : 2;    /* ÌÀÒÐÈÖÀ */
  unsigned Parity       : 1;    /* ÏÀÐÈÒÅÒ (ÍÅ×ÅÒÍÎÑÒÜ) */
}
ADFArinc429WordKur_t;

typedef struct __attribute__((packed)) /* ÑËÎÂÎ ×ÀÑÒÎÒÛ ÏÎ ARINC 429 */
{
  unsigned Fraquency_05kHz      : 1;    /* 0,5 ÊãÖ */
  unsigned Fraquency_1kHz       : 4;    /* ÅÄÈÍÈÖÛ êÃö */
  unsigned Fraquency_10kHz      : 4;    /* ÄÅÑßÒÊÈ êÃö */
  unsigned Fraquency_100kHz     : 4;    /* ÑÎÒÍÈ êÃö */
  unsigned Fraquency_1000kHz    : 3;    /* ÒÛÑß×È êÃö */
}
ADFArinc429Fraquency_t;

typedef struct __attribute__((packed)) /* ÑËÎÂÎ ×ÀÑÒÎÒÛ ÏÎ ARINC 429 */
{
  unsigned Label                : 8;    /* ÕÀÐÀÊÒÅÐÈÑÒÈÊÀ */
  unsigned NumberADF            : 2;    /* ÍÎÌÅÐ ÀÐÊ */
  unsigned Tlg                  : 1;    /* ÒËÃ */
  unsigned CompassOrAntenna     : 1;    /* ÊÎÌÏÀÑ/ÀÍÒÅÍÍÀ */
  unsigned Reserve              : 1;    /* ÐÅÇÅÐÂ */
  unsigned Fraq 		: 16;   /* ×ÀÑÒÎÒÀ */
  unsigned Matrix               : 2;    /* ÌÀÒÐÈÖÀ */
  unsigned Parity               : 1;    /* ÏÀÐÈÒÅÒ (ÍÅ×ÅÒÍÎÑÒÜ) */
}
ADFArinc429WordFraquency_t;

typedef union
{
  uint32_t Data;
  ADFArinc429WordFraquency_t Fraquency;
  ADFArinc429WordKur_t Kur;
}
ADFArinc429Word32bit_t;

typedef enum
{
  adfArinc429ReceiverChannelA,
  adfArinc429ReceiverChannelB,
  adfArinc429ReceiverChannelControlA,
  adfArinc429ReceiverChannelControlB,
}
ADFArinc429ReceiverChannel_t;


typedef struct
{
  unsigned Pause4T  : 1;
  unsigned FifoFull : 1;
}
ADFArinc429Error_t;

typedef struct
{
  unsigned LineBreak    : 1; /* ÏÐÈÇÍÀÊ ÍÅÒ ÏÐÅÐÛÂÀÍÈÉ ÎÒ ÏÐÈÅÌÍÈÊÀ */
  unsigned NoFraquency  : 1; /* ÏÐÈÇÍÀÊ ÎÒÑÓÒÑÒÂÈß ÍÎÂÛÕ ÄÀÍÍÛÕ ×ÀÑÒÎÒÀ ÍÀÑÒÐÎÉÊÈ */
  unsigned ErrorCode    : 1;
  unsigned Matrix       : 2;
  unsigned Tlg          : 1;
  unsigned CompassOrAntenna : 1;
  unsigned Fraquency    :16;
  uint32_t CopyADFArinc429Word32bitCount;
  uint32_t CopyADFArinc429WordFraquencyCount;
}
ADFArinc429Status_t;

extern ADFArinc429Status_t ADFArinc429Status;

void ADFArinc429Init( void );
ADFArinc429Fraquency_t FraquencyToArinc429( Fraquency_t fraq );
void Arinc429Test ( void );

#endif //__ADF_ARINC429_H

