#pragma once
#include<windows.h>

#define Max_Map_Size (20)
#define SUCCESS (1)
#define FAIL (0)

void gotoxy(int x, int y)
{
    COORD pos = { x * 2,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}