#include "lcd.h"
#include "font.h"

/************************************************
*** ������� ��� ������ � �������� ���� ��-12864�
***     ������� �������� ������
************************************************/

void ClearPage(unsigned char, _crystal);
void PrintSymbol(unsigned char, unsigned char, unsigned char);
void PrintConstText(unsigned char*, unsigned char, unsigned char, unsigned char);
void DigitalToChar(unsigned char*, unsigned int, unsigned int*);
void PrintText(unsigned char*, unsigned int,unsigned char, unsigned char, unsigned char);
unsigned int StrLen(unsigned char*);
//--------------------------------------------------------------------------------------
//*** ������� ��� ����������� ������ ������� �� ������ �������� 6�8 �������� (6 - ������, 8 - ������)
//*** ���������:        Symbol - ������, ������� ���� ����������
//***                           Crystal - �������� LCD, �� ������� ���� ���������� ������
//*** ������������ �������� ���
//--------------------------------------------------------------------------------------
void PrintSymbol(unsigned char Symbol, unsigned char Address, unsigned char Method)
{
        unsigned int Offset= Symbol*6;
        if(Method==0)
        {
                WriteByte(Font_6x8_Data[Offset],Address);
                Address++;
                WriteByte(Font_6x8_Data[Offset+1],Address);
                Address++;
                WriteByte(Font_6x8_Data[Offset+2],Address);
                Address++;
                WriteByte(Font_6x8_Data[Offset+3],Address);
                Address++;
                WriteByte(Font_6x8_Data[Offset+4],Address);
                Address++;
                WriteByte(Font_6x8_Data[Offset+5],Address);
        }
        else
        {
                WriteByte(~Font_6x8_Data[Offset],Address);
                Address++;
                WriteByte(~Font_6x8_Data[Offset+1],Address);
                Address++;
                WriteByte(~Font_6x8_Data[Offset+2],Address);
                Address++;
                WriteByte(~Font_6x8_Data[Offset+3],Address);
                Address++;
                WriteByte(~Font_6x8_Data[Offset+4],Address);
                Address++;
                WriteByte(~Font_6x8_Data[Offset+5],Address);
        }
}
//--------------------------------------------------------------------------------------
//*** ������� ��� ����������� ����������� ������ �� ������
//*** ���������:        Text - ��������� �� ����������� ������, ������� ���� �������
//***                           Page - �������� ��� LCD, �� ������� ��������� ���������� �����
//***                           Address - �����, � �������� ���������� �������� ����� �� LCD
//*** ������������ �������� ���
//*** � ������ ��������� ���� ������ ���� 0�00!
//--------------------------------------------------------------------------------------

void PrintConstText(unsigned char* String, unsigned char Page, unsigned char Address, unsigned char Method)
{
//������������ ���������� ������� ������!
        int LenWord, Length=0;
        unsigned char* ms;

        ClearPage(Page,First);
        ClearPage(Page,Second);

        if(Address<64)
        {
                SetAddress(Address);
                SetAddress(64);
        }
        else
        {
                SetAddress(0);
                SetAddress(Address);
        }

        SetPage(Page,First);
        SetPage(Page,Second);

        ms = String;
        while(*(ms++)!=0) Length++;

        for(LenWord=0;LenWord<Length;LenWord++,Address+=6)      PrintSymbol(String[LenWord],Address,Method);

}

//--------------------------------------------------------------------------------------
//*** ������� ��� ����������� ������ �� ������
//*** ���������:        Text - ��������� �� ������, ������� ���� �������
//***                           Value - ��������, ������� ���������� ���������� �� ������
//***                           Page - �������� ��� LCD, �� ������� ��������� ���������� �����
//***                           Address - �����, � �������� ���������� �������� ����� �� LCD
//*** ������������ �������� ���
//*** � ������ ��������� ���� ������ ���� 0�00!
//--------------------------------------------------------------------------------------
void PrintText(unsigned char* String, unsigned int Value,unsigned char Page, unsigned char Address, unsigned char Method)
{
//������������ ���������� ������� ������!
        unsigned int LenWord=0, Length=0, PositionForInsert=0, Temp, ValNumOfChar;
        unsigned char NewStr[21], CharVal[11];
        unsigned char* ms;

//��������� ����� ������
        ms = String;
        while(*(ms++)!=0) Length++;
        if(Length>21) Length = 21;

//��������� ����� ������� �������� Value
        ms = String;
        while(LenWord++ < Length)
        {
                if(ms[LenWord]=='%')
                {
                        PositionForInsert = LenWord;
                        break;
                }
        }

//��������� �������� Value � ������ ��������
        DigitalToChar(&CharVal[0],Value,&ValNumOfChar);

//��������� ����� ������ �� �������
        for(Temp=0;Temp<PositionForInsert;Temp++)       NewStr[Temp] = ms[Temp];

//��������� ����� �������������� ����� ������ ������ �� �������� Value
        ValNumOfChar+=Temp;
        if(ValNumOfChar>21)     ValNumOfChar = 21;

//������ ������� ������� �������� Value � ����� ������
        for(LenWord=0;Temp<ValNumOfChar;Temp++) NewStr[Temp] = CharVal[LenWord++];

//���������� ��, ��� �������� ����� �������
        LenWord = Length - (PositionForInsert + 1);
        PositionForInsert++;
        if((Temp < 21)&&(LenWord!=0))
                for(;(Temp < 21)&&(LenWord!=0);Temp++,LenWord--)        NewStr[Temp] = ms[PositionForInsert++];

        ClearPageAtTo(Address,Length+Address,Page);

        if(Address<64)
        {
                SetAddress(Address);
                SetAddress(64);
        }
        else
        {
                SetAddress(0);
                SetAddress(Address);
        }

        SetPage(Page,First);
        SetPage(Page,Second);



        for(LenWord=0;LenWord<Temp;LenWord++)
        {
                PrintSymbol(NewStr[LenWord],Address,Method);
                Address += 6;
        }
}

//--------------------------------------------------------------------------------------
//*** ������� ��� �������� ����� Val � ������ ��������, �� ������� ��������� MyStr
//*** ���������:        MyStr - ��������� �� ������, � ������� ����� ������� ���������
//***                           (������ ������ ��������� 11 ��������)
//***                           Value - ��������, ������� ���������� ���������� �� ������
//***                           Len - ���������, �� �������� ����� ���������� ���-�� ��������� �
//***                           ������� (�� ������� ������������ 0)
//*** ������������ �������� ���
//--------------------------------------------------------------------------------------
void DigitalToChar(unsigned char* MyStr, unsigned int Val, unsigned int* Len)
{
        unsigned int i,f,Temp,j,non=0;
        unsigned char Arr[11];

//��������� �������� Val � ������ �������� (������� ����������� � �������� �������, Arr[0] - �������, Arr[1] - �������, � �.�.)
        for(Temp=0;Temp<8;Temp++)
        {
                i = Val/16;
                f = Val%16;
                if(f<10)        Arr[Temp] = 0x30+f;
                else            Arr[Temp] = 0x41+(f-10);
                Val = i;
                if(i==0)        //����������� ������ ����
                {
                        non = Temp;
                        break;
                }
        }

//�������� ����������� �������������� ������ ��������
        MyStr[0] = '0';
        MyStr[1] = 'x';

        if(non == 0)
        {
                MyStr[2] = Arr[0];
                MyStr[3] = 0;
                *Len = 3;
                return;
        }

        *Len = 2;
        j = non;
        for(Temp=0;Temp<=j;Temp++)
        {
                MyStr[Temp+2] = Arr[non--];
                (*Len)++;
        }
        MyStr[Temp+2] = 0;
}

//--------------------------------------------------------------------------------------
//*** ������� ��� ���������� ����� ������ ��������
//*** ���������:        Str - ��������� �� ������, ������ ������� ���������� ������
//*** ������������ �������: ���-�� ����, ���������� �������
//--------------------------------------------------------------------------------------
unsigned int StrLen(unsigned char* Str)
{
        unsigned char* ptr;
        unsigned int Len;

        ptr = Str;
        Len = 0;
        while(*(ptr++)!=0x00)   Len++;

        return Len;
}

