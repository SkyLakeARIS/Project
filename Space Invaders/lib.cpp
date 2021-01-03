#include "lib.h"

//지나간 흔적 지우는 함수
void Remove_FootPrint(int x, int y)
{
	gotoxy(x, y);
	std::cout << "  ";
}
//색 지정
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//해당 좌표로 커서를 이동
void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//Y값에 맞는 색 출력
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
//화면의 커서를 보이거나 숨기기
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}