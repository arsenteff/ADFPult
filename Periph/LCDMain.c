/* Демонстрационная программа "LCDProject"
Программа демонстрирует работу с LCD дисплеем
Программа выводит на экран 3 строки: Главное меню,
Алфавит и Описание. С помощью кнопок TOP и BOTTOM
можно перемещаться по пунктам Алфавит и Описание.
С помощью кнопок BACK и SELECT возвращаться в
Главное меню или заходить в подменю и видеть
либо символы, которые возможно отобразить на LCD,
либо информацию о плате названием платы.

Тактирование контроллера: HSE 16 MHz
При изменении тактовой частоты необходимо менять
перегружаемое значение в системном таймере
(подробнее см. файл LCD.c).

На плате должны быть установлены следующие перемычки:
XP151 - Operating Mode LCD
XP159 - OSC
XP163 - замкнута
PE15 - BOTTOM
PE14 - замкнута
PE13 - замкнута
PE12 - замкнута
PE11 - BACK
PE10 - LEFT
PE9 - SELECT
PE8 - TOP
PE5 - RIGTH
PA7 - D7
PA6 - D6
PC2 - замкнута
PC0 - замкнута
PF0 - замкнута
*/

#include "MDR1986VE1T.h"
#include "lcdcfg.h"
#include "lcd.h"
#include "lcd_b.h"
#include "menu.h"
#include "keyboard.h"
#include "font.h"
#include "mystring.h"

extern uint32_t Status;
extern uint32_t countFraquency;
extern uint32_t glbErrorLabel;
extern uint32_t glbErrorFraquency;

void OprosKey( void );

unsigned int Temp;
_Key KeyNum;

uint8_t bufStr[32];

void bufStrSplit( uint32_t data, uint32_t pos )
{
  bufStr[pos] = data + 0x30 ;
}

void LCDmain( uint32_t frqOutput,
              uint32_t frqInput,
              uint32_t CompassOrAntenna,
              uint32_t TLG,
              uint32_t NumberADF,
              uint32_t ind,
              uint32_t error )
{
  uint32_t i;
  static uint32_t er = 0;

  for ( i=0; i<20; i++) bufStr[i]=0x20;
  bufStr[21] = '/0';

  bufStrSplit( NumberADF, 7 );
  bufStrSplit( TLG, 11 );
  bufStrSplit( CompassOrAntenna, 15 );
  bufStrSplit( ind, 19 );

  PrintConstText( bufStr, 2, 0, 0);

//        ClkConfig();
//        LCDInit();
//        KeysInit();
//        CurrentMenu = &TopMenu;
//        DrawMenu(CurrentMenu);

        //PrintConstText("ЧАСТ:",1,(64-(7*FONT_WIDTH/2)),0);
        PrintConstText(_itoa(frqOutput,DEC),1,FONT_WIDTH,0);
        PrintConstText(_itoa(error,DEC),4,FONT_WIDTH,0);
        if ( error != er )
        {
          er = error;
          PrintConstText(_itoa(frqInput,HEX),5,FONT_WIDTH,0);
        }

        //PrintConstText(_itoa(frqInput,HEX),3,FONT_WIDTH,0);
        //PrintConstText(_itoa(NumberADF,DEC),4,FONT_WIDTH*7,0);
        //PrintConstText(_itoa(TLG,DEC),5,FONT_WIDTH*11,0);
        //PrintConstText(_itoa(CompassOrAntenna,DEC),6,FONT_WIDTH*15,0);

        if ( glbErrorLabel == 0 )
        {
          PrintConstText("ЧАСТО НМР ТЛГ КМП ИНД",0,0,0);
          PrintConstText(_itoa(frqInput,HEX),3,FONT_WIDTH,0);

          if ( glbErrorFraquency != 0 )
          {
            /*while ( Status & 2 )
            {
              OprosKey();
            }*/
          }
        }
        else
        {
          PrintConstText("МАТРИ НМР ТЛГ КМП ИНД",0,0,0);
          PrintConstText(_itoa(frqInput,OCT),3,FONT_WIDTH,0);

          while ( Status & 2 )
          {
            OprosKey();
          }
        }

        /*
        switch ( ind )
        {
          case 0:
                PrintConstText("НЕТ",7,FONT_WIDTH*17,0);
                break;
          case 1:
                PrintConstText("АРК1",7,FONT_WIDTH*17,0);
                break;
          case 2:
                PrintConstText("АРК2",7,FONT_WIDTH*17,0);
                break;
          case 3:
                PrintConstText("АРК3",7,FONT_WIDTH*17,0);
                break;
        }*/
}

void OprosKey( void )
{
//        while(1)
//        {
                switch(KeyNum=PressKey())
                {
                        case TOP:
                                countFraquency += 100<<1;
                                WaitUntilPress(TOP);
                                break;

                                if(CurrentMenu->CurrentAssignSubMenu < 2) CurrentMenu->CurrentAssignSubMenu = CurrentMenu->NumberOfSubMenu;
                                else CurrentMenu->CurrentAssignSubMenu--;
                                ClearLCD();
                                DrawMenu(CurrentMenu);
                                WaitUntilPress(TOP);
                                break;

                        case BOTTOM:
                                if ( Status & 4) Status &= 0xFFFFFFFB;
                                else Status |= 0x4;
                                //countFraquency += 10<<1;
                                WaitUntilPress(BOTTOM);
                                break;

                                if(CurrentMenu->CurrentAssignSubMenu == CurrentMenu->NumberOfSubMenu) CurrentMenu->CurrentAssignSubMenu = 1;
                                else CurrentMenu->CurrentAssignSubMenu++;
                                ClearLCD();
                                DrawMenu(CurrentMenu);
                                WaitUntilPress(BOTTOM);
                                break;

                        case BACK:

                                if ( Status & 1) Status &= 0xFFFFFFFE;
                                else Status |= 0x1;
                                WaitUntilPress(BACK);
                                break;

                                if(CurrentMenu->MenuLevel != 0)
                                {
                                        CurrentMenu = &TopMenu;
                                        ClearLCD();
                                        DrawMenu(CurrentMenu);
                                }
                                WaitUntilPress(BACK);
                                break;

                        case SELECT:

                                if ( Status & 2) Status &= 0xFFFFFFFD;
                                else Status |= 0x2;
                                WaitUntilPress(SELECT);
                                break;

                                if(CurrentMenu->BottomMenu != 1)
                                {
                                        switch(CurrentMenu->CurrentAssignSubMenu)
                                        {
                                                case 1:
                                                        CurrentMenu = &Submenu1;
                                                        break;
                                                case 2:
                                                        CurrentMenu = &Submenu2;
                                                        break;
                                        }
                                        ClearLCD();
                                        DrawMenu(CurrentMenu);
                                        if(CurrentMenu->BottomMenu == 1)
                                        {
                                                DrawFunction(CurrentMenu);
                                                WaitUntilNotPress(BACK);
                                        }
                                }
                                WaitUntilPress(SELECT);
                                break;
                }
//        }
}

