/*
**  ������� ��� ������ � ����������� �� ��������� EVAL22.0B
*/
#include "MDR1986VE1T.h"
#include "keyboard.h"

//������������ ��� ����������� ������� ������
//typedef enum _key_ {BOTTOM = 0x0F20, RIGHT = 0x8F00, TOP = 0x8E20, LEFT = 0x8B20, SELECT = 0x8D20, BACK = 0x8720, NOPRESS = 0x8F20} _Key;

void KeysInit(void);
void WaitUntilPress(_Key);
void WaitUntilNotPress(_Key);

//--- ������������� ����� ��� ������ � ����������� ---
void KeysInit()
{
        MDR_PORTE->FUNC &= 0x3F00F3FF;//0xFFFFF000;
        MDR_PORTE->OE &= 0x70DF;
        MDR_PORTE->ANALOG |= 0x8F20;
        MDR_PORTE->PWR |= 0xC0FF0C00;
}

//--- ������� ��� ����������� ������� ������
//--- ���������� ��� ������� ������
//--- ���� ������ ��������� ������, ������� ���������� �������� NOPRESS (��� ������� �������)
_Key PressKey()
{
        switch(MDR_PORTE->RXTX&NOPRESS)
        {
                case BOTTOM: return BOTTOM;
                case RIGHT:      return RIGHT;
                case TOP:        return TOP;
                case LEFT:       return LEFT;
                case SELECT: return SELECT;
                case BACK:       return BACK;
                default:         return NOPRESS;
        }
}

//--- ������� ������� ���� ������ ������ Key
void WaitUntilPress(_Key Key)
{
        while((MDR_PORTE->RXTX&NOPRESS)==Key);
}

//--- ������� ������� ������� ������ Key
void WaitUntilNotPress(_Key Key)
{
        while((MDR_PORTE->RXTX&NOPRESS)!=Key);
}

