#pragma once
#include <cstdlib>
#include <iostream>
#include <Windows.h>

#define MAPSIZE 12

#define SUCCESS 1
#define FAIL 0

enum eCursorView
{
    HIDDEN,
    SHOW
};

inline void gotoxy(int x, int y)
{
    COORD pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

inline void removeFootPrint(const int x, const int y)
{
    gotoxy(9 + x, 3 + y);
    std::cout << "  ";
}

inline void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}