#ifndef __MENU_H

#define MENU_LEVEL      10              //������������ ������� ����������� ����
#define SUB_MENU        7               //������������ ���������� ������� � ����� ����

typedef struct
{
        unsigned char* MenuName;                                //��������� ����
        unsigned int MenuLevel;                                 //������� ���� (0 - ����� ������� � �. �.)
        unsigned int NumberOfSubMenu;                   //���������� �������
        unsigned int CurrentAssignSubMenu;              //������� ���������� ������� (0 - �� �������� �� ���� �������, 1 - �������� ������ ������� � �.�.)
        unsigned int BottomMenu;                                //������� ���������� ���� (���������� ������ ������� ���), 1 - ��������� �������, 0 - �� ���������.
        unsigned int ParentMenu;                                //������������ ����, �� �������� ������ � ������� ����
        unsigned char* SubMenuName[SUB_MENU];   //��������� ������� 1
} _Menu;

void DrawMenu(_Menu* Menu);

extern _Menu* CurrentMenu;     //��������� �� ������� ����
extern _Menu TopMenu;
extern _Menu Submenu1;
extern _Menu Submenu2;

#endif /* __MENU_H */

