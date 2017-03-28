
/*
**      Функции для работы с меню, отображаемым на ЖК индикаторе.
*/
#include "lcd.h"
#include "lcd_b.h"
#include "menu.h"
#include "font.h"

//unsigned int strlen(unsigned char*);

_Menu* CurrentMenu;     //указатель на текущее меню

_Menu TopMenu = {"--- Главное меню ---",0,2,0,0,0,{"Отображаемые символы","Описание"}};

_Menu Submenu1 = {"Отображаемые символы",1,0,0,1,0};
_Menu Submenu2 = {"Описание",1,0,0,1,0};

//Функция отображения меню на LCD-диссплее
//Параметры: Menu - указатель на меню, которое необходимо отобразить на LCD
void DrawMenu(_Menu* Menu)
{
        unsigned int i;

        PrintConstText(Menu->MenuName,0,(64-(StrLen(Menu->MenuName)*FONT_WIDTH/2)),0);
        for(i=1;i<(Menu->NumberOfSubMenu+1);i++)
        {
                if(Menu->CurrentAssignSubMenu != i)     PrintConstText(Menu->SubMenuName[i-1],i,(64-(StrLen(Menu->SubMenuName[i-1])*FONT_WIDTH/2)),0);
                else PrintConstText(Menu->SubMenuName[i-1],i,(64-(StrLen(Menu->SubMenuName[i-1])*FONT_WIDTH/2)),1);
        }
}

//Функция вывода действий на дисплей
//Параметры: Menu - указатель на меню, при выборе которого надо выполнить какие-либо действия
void DrawFunction(_Menu* Menu)
{
        unsigned int Symbol,i,j;
        unsigned char* Text1={"Демоплата EVAL22.0B"};
        unsigned char* Text2={"для 32-разрядного "};
        unsigned char* Text3={"микрконтроллера "};
        unsigned char* Text4={"1986ВЕ1"};

        if(Menu == &Submenu1)
        {
                Symbol = 0;
                for(i=0;i<8;i++)
                {
                        SetPage(i,First);
                        SetPage(i,Second);
                        for(j=0;j<126;j++)
                        {
                                WriteByte(Font_6x8_Data[Symbol++],j);
                                if(Symbol == 42) Symbol = 192;
                                if(Symbol == 762) Symbol = 1008;
                                if(Symbol == 1014) Symbol = 1104;
                                if(Symbol == 1110) Symbol = 1152;
                        }
                }
        }
        if(CurrentMenu == &Submenu2)
        {
                ClearLCD();
                PrintConstText(Text1,2,(64-(19*FONT_WIDTH/2)),0);
                PrintConstText(Text2,3,(64-(17*FONT_WIDTH/2)),0);
                PrintConstText(Text3,4,(64-(15*FONT_WIDTH/2)),0);
                PrintConstText(Text4,5,(64-(7*FONT_WIDTH/2)),0);
        }
}


