#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "lib.h"

#define BOARD_SIZE (20)

class Board
{
public:

    void Run();

private:

    int placeStone();

    int recurUp(int , int , eStoneType );

    int recurDown(int, int, eStoneType);

    int recurLeft(int, int, eStoneType);

    int recurRight(int, int, eStoneType);

    int recurDiagonalUpLeft(int, int, eStoneType);

    int recurDiagonalUpRight(int, int, eStoneType);

    int recurDiagonalDownLeft(int, int, eStoneType);

    int recurDiagonalDownRight(int, int, eStoneType);

    void message(eMessage);

    bool checkOmok();

    void settingGame();

    void printBoard();

private:
    eStoneType mBaord[BOARD_SIZE][BOARD_SIZE];
    eStoneType mStoneColor;
    int mCursorX;
    int mCursorY;
    bool mbCompleteOmok;
};