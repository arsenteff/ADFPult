#ifndef __LCD_H

typedef enum _dspl {ON = 0x3F, OFF = 0x3E} _display;
typedef enum _crstl {First = 1, Second = 2} _crystal;

void SetPage(unsigned int, _crystal);   //Функция устаноовки страницы ОЗУ LCD (строка шириной 8 бит)
void SetAddress(unsigned int);                  //Функция установки адреса ОЗУ для вывода изображения (столбец)
void WriteByte(unsigned char, unsigned char);   //Функция записи байта в память ОЗУ LCD
void ClearLCD(void);                                    //Функция очистки дисплея LCD
void ClearPage(unsigned char, _crystal);//Функция для очистки одной страницы дисплея LCD
void ClearPageAtTo(unsigned int, unsigned int, unsigned int);   //Функция очистки LCD внутри строки в пределах одной страницы
void LCDInit(void);                                             //Функция инициализации LCD-модуля

#endif /* __LCD_H */

