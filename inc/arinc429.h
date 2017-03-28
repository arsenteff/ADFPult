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

//����������� ������� ������� ���� ����������� �� 1���
#define ARINC429_DIV_1MGZ      			(CFG_CPU_PLL_MULL * CFG_CPU_QUARTZ_MHZ)
#define ARINC429_DIV_RECEIVER_MAPPING 	(ARINC429_DIV_1MGZ)
#define ARINC429_DIV_RECEIVER_NAVIGATOR (ARINC429_DIV_1MGZ*2)
#define ARINC429_DIV_TRANSMITTER_MAPPING 	ARINC429_DIV_1MGZ

#define ARINC429_DIV_100_KBIT 	ARINC429_DIV_1MGZ
#define ARINC429_DIV_50_KBIT 	(ARINC429_DIV_1MGZ*2)

//0 - �������� 100���, 1 - �������� 12,5���
#define ARINC429_SPEED        	0


typedef enum /* ����� ��� */
{
  adfArinc429KurNumberADF_All,  /* 0: ��� ���� */
  adfArinc429KurNumberADF_1,    /* 1: ��� ��� 1 */
  adfArinc429KurNumberADF_2,    /* 2: ��� ��� 2 */
  adfArinc429KurNumberADF_3,    /* 3: ��� ��� 3 */
}
ADFArinc429NumberADF_t;

typedef enum /* ������� ���� */
{
  adfArinc429KurMatrixError = 0x00,    /* 0: ����� */
  adfArinc429KurMatrixNoData = 0x01,   /* 1: ��� ������ */
  adfArinc429KurMatrixControl = 0x02,  /* 2: �������� */
  adfArinc429KurMatrixNormal = 0x03,   /* 3: ���������� ������ */
}
ADFArinc429KurMatrix_t;

typedef enum /* ������� ������� */
{
  adfArinc429FraquencyMatrixNormal = 0x00,   /* 0: ���������� ������ */
  adfArinc429FraquencyMatrixNoData = 0x01,   /* 1: ��� ������ */
  adfArinc429FraquencyMatrixControl = 0x02,  /* 2: �������� */
  adfArinc429FraquencyMatrixReserve = 0x03,  /* 3: ������ */
}
ADFArinc429FraquencyMatrix_t;

typedef struct /* ����� ���� �� ARINC 429 */
{
  unsigned Label        : 8;    /* �������������� */
  unsigned NumberADF    : 2;    /* ����� ��� */
  unsigned NotUsed      : 6;    /* ������ ���� ���� */
  unsigned Kur          :13;    /* ��� ���� */
  unsigned Matrix       : 2;    /* ������� */
  unsigned Parity       : 1;    /* ������� (����������) */
}
ADFArinc429WordKur_t;

typedef struct __attribute__((packed)) /* ����� ������� �� ARINC 429 */
{
  unsigned Fraquency_05kHz      : 1;    /* 0,5 ��� */
  unsigned Fraquency_1kHz       : 4;    /* ������� ��� */
  unsigned Fraquency_10kHz      : 4;    /* ������� ��� */
  unsigned Fraquency_100kHz     : 4;    /* ����� ��� */
  unsigned Fraquency_1000kHz    : 3;    /* ������ ��� */
}
ADFArinc429Fraquency_t;

typedef struct __attribute__((packed)) /* ����� ������� �� ARINC 429 */
{
  unsigned Label                : 8;    /* �������������� */
  unsigned NumberADF            : 2;    /* ����� ��� */
  unsigned Tlg                  : 1;    /* ��� */
  unsigned CompassOrAntenna     : 1;    /* ������/������� */
  unsigned Reserve              : 1;    /* ������ */
  unsigned Fraq 		: 16;   /* ������� */
  unsigned Matrix               : 2;    /* ������� */
  unsigned Parity               : 1;    /* ������� (����������) */
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
  unsigned LineBreak    : 1; /* ������� ��� ���������� �� ��������� */
  unsigned NoFraquency  : 1; /* ������� ���������� ����� ������ ������� ��������� */
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

