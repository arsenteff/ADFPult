#include "lcd.h"
#include "font.h"

/************************************************
*** Функции для работы с дисплеем МЭЛТ МТ-12864А
***     функции высокого уровня
************************************************/

void ClearPage(unsigned char, _crystal);
void PrintSymbol(unsigned char, unsigned char, unsigned char);
void PrintConstText(unsigned char*, unsigned char, unsigned char, unsigned char);
void DigitalToChar(unsigned char*, unsigned int, unsigned int*);
void PrintText(unsigned char*, unsigned int,unsigned char, unsigned char, unsigned char);
unsigned int StrLen(unsigned char*);
//--------------------------------------------------------------------------------------
//*** Функция для отображения одного символа на экране размером 6х8 пикселей (6 - ширина, 8 - высота)
//*** параметры:        Symbol - символ, который надо отобразить
//***                           Crystal - кристалл LCD, на котором надо отобразить символ
//*** возвращаемых значений нет
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
//*** Функция для отображения константной строки на экране
//*** параметры:        Text - указатель на константную строку, которую надо вывести
//***                           Page - страница ОЗУ LCD, на которой требуется отобразить текст
//***                           Address - адрес, с которого необходимо выводить текст на LCD
//*** возвращаемых значений нет
//*** в строке последний байт должен быть 0х00!
//--------------------------------------------------------------------------------------

void PrintConstText(unsigned char* String, unsigned char Page, unsigned char Address, unsigned char Method)
{
//используется страничное деление экрана!
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
//*** Функция для отображения текста на экране
//*** параметры:        Text - указатель на строку, которую надо вывести
//***                           Value - значение, которое необходимо отобразить на экране
//***                           Page - страница ОЗУ LCD, на которой требуется отобразить текст
//***                           Address - адрес, с которого необходимо выводить текст на LCD
//*** возвращаемых значений нет
//*** в строке последний байт должен быть 0х00!
//--------------------------------------------------------------------------------------
void PrintText(unsigned char* String, unsigned int Value,unsigned char Page, unsigned char Address, unsigned char Method)
{
//используется страничное деление экрана!
        unsigned int LenWord=0, Length=0, PositionForInsert=0, Temp, ValNumOfChar;
        unsigned char NewStr[21], CharVal[11];
        unsigned char* ms;

//вычисляем длину строки
        ms = String;
        while(*(ms++)!=0) Length++;
        if(Length>21) Length = 21;

//вычисляем место вставки значения Value
        ms = String;
        while(LenWord++ < Length)
        {
                if(ms[LenWord]=='%')
                {
                        PositionForInsert = LenWord;
                        break;
                }
        }

//Переводим значение Value в массив символов
        DigitalToChar(&CharVal[0],Value,&ValNumOfChar);

//Формируем новую строку до вставки
        for(Temp=0;Temp<PositionForInsert;Temp++)       NewStr[Temp] = ms[Temp];

//Вычисляем длину сформированной новой строки вместе со вставкой Value
        ValNumOfChar+=Temp;
        if(ValNumOfChar>21)     ValNumOfChar = 21;

//Делаем вставку массива символов Value в новую строку
        for(LenWord=0;Temp<ValNumOfChar;Temp++) NewStr[Temp] = CharVal[LenWord++];

//Дописываем то, что осталось после вставки
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
//*** Функция для перевода числа Val в массив символов, на который указывает MyStr
//*** параметры:        MyStr - указатель на строку, в которую будет помещен результат
//***                           (массив должен содержать 11 символов)
//***                           Value - значение, которое необходимо отобразить на экране
//***                           Len - указатель, по которому будет находиться кол-во элементов в
//***                           массиве (не включая терминальный 0)
//*** возвращаемых значений нет
//--------------------------------------------------------------------------------------
void DigitalToChar(unsigned char* MyStr, unsigned int Val, unsigned int* Len)
{
        unsigned int i,f,Temp,j,non=0;
        unsigned char Arr[11];

//Переводим значение Val в строку символов (символы расположены в обратном порядке, Arr[0] - единицы, Arr[1] - десякти, и т.д.)
        for(Temp=0;Temp<8;Temp++)
        {
                i = Val/16;
                f = Val%16;
                if(f<10)        Arr[Temp] = 0x30+f;
                else            Arr[Temp] = 0x41+(f-10);
                Val = i;
                if(i==0)        //отбрасываем лишние нули
                {
                        non = Temp;
                        break;
                }
        }

//Начинаем формировать результирующий массив символов
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
//*** Функция для вычисления длины строки символов
//*** параметры:        Str - указатель на строку, размер которой необходимо узнать
//*** возвращаемые значеня: кол-во байт, занимаемое строкой
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

