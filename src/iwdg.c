// Watchdog Timer

//#include "iwdg.h"
#include "MDR1986VE1T.h"
//#include "hardware.h"

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload       ((uint32_t)0xAAAA)
#define KR_KEY_Enable       ((uint32_t)0xCCCC)
#define KR_KEY_WriteEnable  ((uint32_t)0x5555)
#define KR_KEY_WriteDisable ((uint32_t)0x0000)

void
ADFIWDGInit( void )
{
  /*������� ������������ ����� IWDG */
  MDR_RST_CLK->PER_CLOCK |= 1<<13;

  /* ������� ����������� ������� */
  MDR_IWDG->KR = 0x0;

  /* ���������� ������ �� LSI/16 = 40000/16 = 2500 � ��� */
  MDR_IWDG->KR = KR_KEY_WriteEnable;      /* ��������� ������ � ���������*/

  /* ���� ���������� �������� ������� */
  while(MDR_IWDG->SR & IWDG_SR_PVU);
  MDR_IWDG->PR = 0x2;                         /* �������� ������� */

  /* ���� ���������� �������� ����������� ������� */
  while(MDR_IWDG->SR & IWDG_SR_RVU);
  /* ������� 10 �� */
  MDR_IWDG->RLR = 10;                      /* ��������� ����� - ������� ��������*/

  /* ������ ����������� ������� */
  MDR_IWDG->KR = KR_KEY_Reload;
  MDR_IWDG->KR = KR_KEY_Enable;
}

void
ADFIWDGReset( void )
{
  MDR_IWDG->KR = KR_KEY_Reload;
}

