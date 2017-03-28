#ifndef __LCD_H

typedef enum _dspl {ON = 0x3F, OFF = 0x3E} _display;
typedef enum _crstl {First = 1, Second = 2} _crystal;

void SetPage(unsigned int, _crystal);   //������� ���������� �������� ��� LCD (������ ������� 8 ���)
void SetAddress(unsigned int);                  //������� ��������� ������ ��� ��� ������ ����������� (�������)
void WriteByte(unsigned char, unsigned char);   //������� ������ ����� � ������ ��� LCD
void ClearLCD(void);                                    //������� ������� ������� LCD
void ClearPage(unsigned char, _crystal);//������� ��� ������� ����� �������� ������� LCD
void ClearPageAtTo(unsigned int, unsigned int, unsigned int);   //������� ������� LCD ������ ������ � �������� ����� ��������
void LCDInit(void);                                             //������� ������������� LCD-������

#endif /* __LCD_H */

