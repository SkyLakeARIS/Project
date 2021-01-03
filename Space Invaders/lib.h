#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#define MAP_SIZE (26) //constexpr

struct POS
{
	int x;
	int y;
	POS() = default;
	POS(int x, int y) :x(x), y(y) {}
};

enum eHit
{
	MISS = 1,
	HIT,
};

enum eGetPoint
{
	Get_Octopus_Point = 10,
	Get_Crab_Point = 20,
	Get_Squid_Point = 30,
	Get_UFO_Point = 300,
	Get_BOSS_Point = 500,
	NoPoint = 0
};

enum class eType
{
	PLAYER,
	ENEMY,
	BARRICADE,
	UFO,
	BOSS
};

enum eCursorView
{
	HIDDEN,
	SHOW
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

void Remove_FootPrint(int x, int y);

void SetColor(int color);

void gotoxy(int x, int y);

void PaintColor(int y);

void CursorView(char show);