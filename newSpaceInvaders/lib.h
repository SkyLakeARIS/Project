#pragma once
#include <ctime>
#include <conio.h>
#include <iostream>
#include <random>
#include <vector>
#include <Windows.h>

#define MAP_SIZE (26) //constexpr

struct Position
{
	int x;
	int y;
	Position() = default;
	Position(int x, int y) :x(x), y(y) {}
};

enum class eControlKey // ?
{
	UP = 72,
	DOWN = 80,
	SPACE = 32
};

enum class eDirection
{
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80
};

enum ePoint
{
	Octopus_Point = 10,
	Crab_Point = 20,
	Squid_Point = 30,
	UFO_Point = 300,
	OSS_Point = 500,
	NoPoint = 0
};

enum class eType
{
	PLAYER,
	ENEMY,
	SQUID,
	CRAB,
	OCTOPUS,
	BARRICADE,
	UFO,
	BOSS,
	UNKNOWN
};

enum eColor
{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY_BLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKY_BLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE
};

//해당 좌표로 커서를 이동 SHORT
inline void gotoxy(short x, short y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//지나간 흔적 지우는 함수
inline void RemoveFootPrint(int x, int y)
{
	gotoxy(x, y);
	std::cout << "  ";
}

//색 지정
inline void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Y값에 맞는 색 출력
inline void PaintColor(int y) {
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
inline void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

inline int GetRandomNumber(const int begin, const int end)
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<int> random(begin, end);
	return random(gen);
}