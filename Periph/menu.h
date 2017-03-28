#ifndef __MENU_H

#define MENU_LEVEL      10              //максимальный уровень вложенности меню
#define SUB_MENU        7               //максимальное количество подменю в одном меню

typedef struct
{
        unsigned char* MenuName;                                //Заголовок меню
        unsigned int MenuLevel;                                 //Уровень меню (0 - самый верхний и т. д.)
        unsigned int NumberOfSubMenu;                   //Количество подменю
        unsigned int CurrentAssignSubMenu;              //Текущее выделенное подменю (0 - не выделено ни одно подменю, 1 - выделено первое подменю и т.д.)
        unsigned int BottomMenu;                                //Признак последнего меню (следующего уровня подменю нет), 1 - последнее подменю, 0 - не последнее.
        unsigned int ParentMenu;                                //Родительское меню, из которого попали в текущее меню
        unsigned char* SubMenuName[SUB_MENU];   //Заголовок подменю 1
} _Menu;

void DrawMenu(_Menu* Menu);

extern _Menu* CurrentMenu;     //указатель на текущее меню
extern _Menu TopMenu;
extern _Menu Submenu1;
extern _Menu Submenu2;

#endif /* __MENU_H */

