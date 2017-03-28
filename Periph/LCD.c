#include "MDR1986VE1T.h"
#include "core_cm1.h"
#include "lcd.h"

/*
        �������� ������� ����������� �� ������ ��������� 16 ���,
        ��� ��� ����� �� ����� ����������� ��������� �����������
        LCD-������� ����.
        ���� ��� ����� ������� �������� �����������     ����������
        ���������� ������� ������ � LCD ��������� ����� �����/������,
        � �� ������� ��������� ����.
*/

// ������� ������� ������ ��� LCD-������ ���� ��-12864� v5

#define LCD_CMD1        0x68000000
#define LCD_CMD2        0x70000000

#define LCD_DATA1       0x6C000000
#define LCD_DATA2       0x74000000

unsigned int Flag8us, DisableFlag;

void __SysTickInit(void);                               //������� ������������� ���������� �������
void Pause8us(void);                                    //������� ������� ����� 8 ���
unsigned char ReadStatus(_crystal);             //������� ������ ������� � LCD
void PortsForLCD(void);                                 //������� ���������������� ������ �����/������ ��� ������ ������
void SystemBusInit(void);                               //������� ���������������� ������� ��������� ����
void ResetLCD(void);                                    //������� ������ LCD
void SetStartLine(unsigned int);                //������� ��������� ������ ������� LCD
void DisplayOnOff(_display);                    //������� ���������/���������� LCD �������
//void SetPage(unsigned int, _crystal);   //������� ���������� �������� ��� LCD (������ ������� 8 ���)
//void SetAddress(unsigned int);                  //������� ��������� ������ ��� ��� ������ ����������� (�������)

//void WriteByte(unsigned char, unsigned char);   //������� ������ ����� � ������ ��� LCD
unsigned char ReadByte(unsigned int, unsigned int);                     //������� ������ ����� �� ������ ��� LCD
//void ClearLCD(void);                                    //������� ������� ������� LCD
//void ClearPage(unsigned char, _crystal);//������� ��� ������� ����� �������� ������� LCD
//void ClearPageAtTo(unsigned int, unsigned int, unsigned int);   //������� ������� LCD ������ ������ � �������� ����� ��������
//void LCDInit(void);                                             //������� ������������� LCD-������
//*__INLINE*/ void EnableSysTick(void);              //������� ��� ���������� ������ ���������� ������� � ���������� �� ����
//*__INLINE*/ void DisableSysTick(void);             //������� ��� ������� ������ ���������� ������� � ���������� �� ����

void SysTick_Handler(void);                             //���������� ���������� �� ���������� �������


//������� ���������������� ������ �����/������ ��� ������ ������
void PortsForLCD()
{
//���� � - ���� ������
        MDR_RST_CLK->PER_CLOCK |= 0x115<<21;        //������������ ������ A, C, E

        MDR_PORTA->FUNC &= 0xFFFF0000;      //PORTA[7:0] - �������� ������� (���� ������)
        MDR_PORTA->FUNC |= 0x00005555;      //PORTA[7:0] - �������� ������� (���� ������)
        MDR_PORTA->ANALOG |= 0x00FF;        //PORTA[7:0] - digital
        MDR_PORTA->PWR |= 0x0000FFFF;

        MDR_PORTC->FUNC &= 0xFFFFFFCC;      //PORTC 0 - �������� �������
        MDR_PORTC->FUNC |= 0x00000021;      //PORTC 0 - �������� �������
        MDR_PORTC->ANALOG |= 0x0005;
        MDR_PORTC->PWR |= 0x00000031;

        MDR_PORTE->FUNC &= 0xC0FFFFFF;      //PORTE 12 - �������� ������� (���� ������)
        MDR_PORTE->FUNC |= 0x2A000000;      //PORTE 12 - �������� ������� (���� ������)
        MDR_PORTE->ANALOG |= 0x7000;
        MDR_PORTE->PWR |= 0x3F000000;

        MDR_PORTF->FUNC = 0;        //PORTE 12, 13, 14 - �������� ������� (���� ������)
        MDR_PORTF->RXTX = 0;
        MDR_PORTF->OE |= 0x0001;
        MDR_PORTF->ANALOG = 0x0001;
        MDR_PORTF->PWR |= 0x00000003;
}

#define EXT_BUS_CNTRL_BASE        0x400F0000
#define EXT_BUS_CNTRL             ((EXT_BUS_CNTRL_TypeDef *)EXT_BUS_CNTRL_BASE)
#include "opora_ext_bus_cntrl_defs.h"

//������� ���������������� ������� ��������� ����
void SystemBusInit()
{
  MDR_RST_CLK->PER_CLOCK |= 1<<30;    //������������ ������� ��������� ����
  EXT_BUS_CNTRL->EXT_BUS_CONTROL = 0xF002;
}

//������� ������ LCD-������
void ResetLCD()
{
  MDR_PORTF->CLRTX = 1;
  Pause8us();
  MDR_PORTF->SETTX = 1;
  Pause8us();
}

//������� ��������� ������ ������� LCD
//���������: LineNumber - ������ ������ LCD
void SetStartLine(unsigned int LineNumber)
{
        *((unsigned int*)LCD_CMD1) = 0xC0|(LineNumber&0x3F);
        Pause8us();

        *((unsigned int*)LCD_CMD2) = 0xC0|(LineNumber&0x3F);
        Pause8us();
}

//������� ���������/���������� LCD �������
//���������: Function - ��������� ��� ���������� LCD
//����������� �������� ���������: ON - ��������� (0x3F), OFF - ���������� (0x3E).
void DisplayOnOff(_display Function)
{
        *((unsigned int*)LCD_CMD1) = Function;
        Pause8us();

        *((unsigned int*)LCD_CMD2) = Function;
        Pause8us();
}

//������� ���������� �������� ��� LCD (������ ������� 8 ���)
//���������: Page - ����������� �������� LCD (����� ��������� �������� �� 0 �� 7)
//                       Crystal - �������� LCD, �� ������� ��������������� �������� Page.
//                       (����� ��������� �������� First (1) ��� Second (2))
void SetPage(unsigned int Page, _crystal Crystal)
{
        if(Crystal == First)
        {
                *((unsigned int*)LCD_CMD1) = (0xB8|(Page&0x07));
        }
        else
        {
                *((unsigned int*)LCD_CMD2) = (0xB8|(Page&0x07));
        }
        Pause8us();
}

//������� ��������� ������ ��� ��� ������ ����������� (�������).
//���������: Address - �����, � �������� ����� ���������� �����������
//                       �� ������� �������� LCD (����� ��������� �������� �� 0 �� 127).
void SetAddress(unsigned int Address)
{
        if(Address < 64)
        {
                *((unsigned int*)LCD_CMD1) = (0x40|(Address&0x3F));
        }
        else
        {
                *((unsigned int*)LCD_CMD2) = (0x40|(Address&0x3F));
        }
        Pause8us();
}

//������� ������ ������� LCD
//���������: Crystal - �������� LCD, � �������� ����� ��������
//                       ���������� (����� ��������� �������� First (1) ��� Second (2))
unsigned char ReadStatus(_crystal Crystal)
{
        unsigned char Temp;
        if(Crystal == First)
        {
                Temp = *((unsigned int*)LCD_CMD1);
        }
        else
        {
                Temp = *((unsigned int*)LCD_CMD2);
        }
        Pause8us();
        return Temp;
}

//������� ������ ����� � ������ ��� LCD
//���������: Byte - ���� ��� ������ � ���
//                       Address - �����, �� �������� ����� ����������� ������
//                       (����� ��������� �������� �� 0 �� 127).
void WriteByte(unsigned char Byte, unsigned char Address)
{
        if(Address < 64)
        {
                SetAddress(Address);
                *((unsigned int*)LCD_DATA1) = Byte;
        }
        else
        {
                SetAddress(Address);
                *((unsigned int*)LCD_DATA2) = Byte;
        }
        Pause8us();
}

//������� ������ ����� �� ������ ��� LCD
//���������: Page - ��������, � ������� ����������� ����
//                       Address - �����, �� �������� ����� ����������� ����
//                       (����� ��������� �������� �� 0 �� 127).
unsigned char ReadByte(unsigned int Page, unsigned int Address)
{
        unsigned char Temp;
        if(Address < 64)
        {
                SetPage(Page,First);
                SetAddress(Address);
                Temp = *((unsigned int*)LCD_DATA1);
                Pause8us();
                Temp = *((unsigned int*)LCD_DATA1);
        }
        else
        {
                SetPage(Page,Second);
                SetAddress(Address);
                Temp = *((unsigned int*)LCD_DATA2);
                Pause8us();
                Temp = *((unsigned int*)LCD_DATA2);
        }
        Pause8us();
        return Temp;
}

//������� ������� ������� LCD
void ClearLCD()
{
        unsigned int i, j;
        SetAddress(0);
        for(j=0;j<8;j++)
        {
                SetPage(j,First);
                for(i=0;i<64;i++)
                {
                        WriteByte(0x00,i);
                }
        }
        SetAddress(64);
        for(j=0;j<8;j++)
        {
                SetPage(j,Second);
                for(i=64;i<128;i++)
                {
                        WriteByte(0x00,i);
                }
        }
        SetAddress(0);
        SetPage(0,First);
        SetAddress(64);
        SetPage(0,Second);
}

//������� ��� ������� ����� �������� ������� LCD
void ClearPage(unsigned char Page, _crystal Crys)
{
        unsigned char i;
        if(Crys == First)
        {
                SetPage(Page,First);
                SetAddress(0);
                for(i=0;i<64;i++)
                {
                        *((unsigned int*)LCD_DATA1) = 0x00;
                        Pause8us();
                }
        }
        else
        {
                SetPage(Page,Second);
                SetAddress(64);
                for(i=0;i<64;i++)
                {
                        *((unsigned int*)LCD_DATA2) = 0x00;
                        Pause8us();
                }
        }
}

//������� ������� ������� LCD � ������ At �� ����� To �� �������� Page.
void ClearPageAtTo(unsigned int At, unsigned int To, unsigned int Page)
{
        if(At>=To) return;

        SetPage(Page,First);
        SetPage(Page,Second);

        SetAddress(At);
        if(To<64)
                while(At++ < To)
                {
                        *((unsigned int*)LCD_DATA1) = 0x00;
                        Pause8us();
                }
        else
        {
                while(At++ <To)
                {
                        if(At<64)       *((unsigned int*)LCD_DATA1) = 0x00;
                        else            *((unsigned int*)LCD_DATA2) = 0x00;
                        Pause8us();
                }
        }
}
//������� ������������� LCD-������
void LCDInit()
{

        PortsForLCD();
        SystemBusInit();
        Flag8us = 0;
        DisableFlag = 0;
        __SysTickInit();
        if(DisableFlag != 1)
        {
                ResetLCD();
                ClearLCD();
                DisplayOnOff(ON);
                SetStartLine(0);
        }
}

//������� ��� ���������� ������ ���������� ������� � ���������� �� ����
/*__INLINE */void EnableSysTick()
{
        SysTick->CTRL = 0x00000003;     //Enabel SysTick, Enable Interrupt
}

//������� ��� ������� ������ ���������� ������� � ���������� �� ����
/*__INLINE */void DisableSysTick()
{
        SysTick->CTRL = 0x00000000;     //Disable SysTick, Disable Interrupt
}

//������� ������������� ���������� �������
void __SysTickInit()
{
        if((SysTick->CTRL&1) == 1) DisableFlag = 1;
        else SysTick->LOAD = 0x00000080;        //Pause 8 us (HCLK = 16MHz)
}

//���������� ���������� �� ���������� �������
void SysTick_Handler()
{
        Flag8us = 1;
}

//������� ������� ����� 8 ���
void Pause8us()
{
        EnableSysTick();
        while(Flag8us != 1);
        DisableSysTick();
        Flag8us = 0;
}


