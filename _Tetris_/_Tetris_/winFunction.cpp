#include "winFunction.h"

void Gotoxy(int x, int y) // 1������̨�����У����Խ�����ƶ���ָ��λ��(x,y)��֮��cout��������ݽ���(x,y)��ʼ���
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Setcolor(int color)  // 2������̨�����У���������������ַ�����ɫ����ɫ�Ű�����0��ɫ1��ɫ2��ɫ3��ɫ 4��ɫ5��ɫ6��ɫ7��ɫ + 8��ǿɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor() // 3������̨�����У������ϣ�����������˸���������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}