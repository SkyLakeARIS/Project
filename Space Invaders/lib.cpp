#include "lib.h"

//������ ���� ����� �Լ�
void Remove_FootPrint(int x, int y)
{
	gotoxy(x, y);
	std::cout << "  ";
}
//�� ����
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//�ش� ��ǥ�� Ŀ���� �̵�
void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//Y���� �´� �� ���
void PaintColor(int y) {
	if (y < 2)
	{
		SetColor(VIOLET);
	}
	if (y >= 3)
	{
		SetColor(GREEN);
	}
	if (y >= 7)
	{
		SetColor(SKY_BLUE);
	}
	if (y >= 10)
	{
		SetColor(VIOLET);
	}
	if (y >= 14)
	{
		SetColor(YELLOW);
	}
	if (y >= 17)
	{
		SetColor(RED);
	}
	if (y >= 22)
	{ 
		SetColor(SKY_BLUE);
	}
}
//ȭ���� Ŀ���� ���̰ų� �����
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}