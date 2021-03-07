#include "Board.h"

void Board::printBoard()
{
    for (int LoopY = 0; LoopY < BOARD_SIZE; LoopY++)
    {
        for (int LoopX = 0; LoopX < BOARD_SIZE; LoopX++)
        {
            gotoxy(LoopX*2, LoopY);
            if (LoopY == 0) // 첫출 그리기
            {
                if (LoopX == 0)
                {
                    std::cout << "┌";
                }
                if (LoopX == (BOARD_SIZE - 1))
                {
                    std::cout << "┐";
                }
                if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
                {
                    std::cout << "┬";
                }
            }
            else // 마지막 줄 그리기
            {
                if (LoopY == (BOARD_SIZE - 1))
                {
                    if (LoopX == 0)
                    {
                        std::cout << "└";
                    }
                    if (LoopX == (BOARD_SIZE - 1))
                    {
                        std::cout << "┘";
                    }
                    if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
                    {
                        std::cout << "┴";
                    }
                }
                else //중간 줄 그리기
                {
                    if (LoopX == 0)
                    {
                        std::cout << "├";
                    }
                    if (LoopX == (BOARD_SIZE - 1))
                    {
                        std::cout << "┤";
                    }
                    if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
                    {
                        std::cout << "┼";
                    }
                }
            }
        }
    }
    message(eMessage::TurnOfBlackStone);
}

//게임 재시작시 정보들을 초기화 하는 함수
void Board::settingGame()
{
    for (int LoopY = 0; LoopY < BOARD_SIZE; LoopY++)
    {
        for (int LoopX = 0; LoopX < BOARD_SIZE; LoopX++)
        {
            mBaord[LoopY][LoopX] = eStoneType::EmptySpace;
        }
    }
    mCursorX = 0;
    mCursorY = 0;

    mStoneColor = eStoneType::BlackStone;

    mbCompleteOmok = false;
}


int Board::recurUp(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurUp(x, y - 1, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurDown(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurDown(x, y + 1, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurLeft(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurLeft(x - 1, y, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurRight(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurRight(x + 1, y, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurDiagonalUpLeft(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurDiagonalUpLeft(x - 1, y - 1, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurDiagonalUpRight(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurDiagonalUpRight(x + 1, y - 1, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurDiagonalDownRight(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone)
    {
        return recurDiagonalDownRight(x + 1, y + 1, mStoneColor) + 1;
    }

    return 0;
}

int Board::recurDiagonalDownLeft(int x, int y, eStoneType stone)
{
    if (mBaord[y][x] == stone )
    {
        return recurDiagonalDownLeft(x - 1, y + 1, mStoneColor) + 1;
    }

    return 0;
}

bool Board::checkOmok()
{
    const int OMOK = 5;
    //돌을 놓은 위치는 미리 카운트하고 재귀함수는 주변에 놓인 자신의 돌을 체크함.
    int omokCount = 1;
    //자신의 돌 사이에 둠으로써 오목이 완성되는 경우를 고려해서 두 함수의 리턴값을
    //더한 후 조건을 체크함.
    omokCount += recurUp(mCursorX, mCursorY - 1, mStoneColor);
    if (omokCount + recurDown(mCursorX, mCursorY + 1, mStoneColor) == OMOK)
    {
        mbCompleteOmok = true;
        return true;
    }

    omokCount = 1;
    omokCount += recurLeft(mCursorX - 1, mCursorY / 2, mStoneColor);
    if (omokCount + recurRight(mCursorX + 1, mCursorY / 2, mStoneColor) == OMOK)
    {
        mbCompleteOmok = true;
        return true;
    }

    omokCount = 1;
    omokCount += recurDiagonalUpLeft(mCursorX - 1, mCursorY - 1, mStoneColor);
    if (omokCount + recurDiagonalDownRight(mCursorX + 1, mCursorY + 1, mStoneColor) == OMOK)
    {
        mbCompleteOmok = true;
        return true;
    }

    omokCount = 1;
    omokCount += recurDiagonalUpRight(mCursorX + 1, mCursorY - 1, mStoneColor);
    if (omokCount + recurDiagonalDownLeft(mCursorX - 1, mCursorY + 1, mStoneColor) == OMOK)
    {
        mbCompleteOmok = true;
        return true;
    }

    return false;
}

//실행 함수
void Board::Run()
{
    HANDLE hStdin;
    DWORD fdwSaveOldMode;
    INPUT_RECORD mouseInput;
    DWORD numRead;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE)
    {
        std::cout << "GetStdHandle";
    }

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
    {
        std::cout << "GetConsoleMode";
    }

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        std::cout << "SetConsoleMode";
    }

    settingGame();

    printBoard();

    while (!mbCompleteOmok)
    {
        if (!ReadConsoleInput(hStdin, &mouseInput, 1, &numRead))
        {
            std::cout << "ReadConsoleInput";
        }

        if (mouseInput.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = mouseInput.Event.MouseEvent;
            switch (mouse.dwEventFlags)
            {
            case 0:
                if (mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < BOARD_SIZE*2))
                    {
                        gotoxy((mouse.dwMousePosition.X / 2) * 2, mouse.dwMousePosition.Y);
                    }
                }
                break;
            case DOUBLE_CLICK:
                if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < BOARD_SIZE*2))
                {
                    mCursorX = mouse.dwMousePosition.X/2;
                    mCursorY = mouse.dwMousePosition.Y;

                    //특수문자가 2칸(2바이트)를 차지함으로서 생기는 좌표차이(클릭하는 위치와 돌이 놓이는 위치)
                    //없애기위해 /2후 출력되는 위치를 맞추기위해 *2를 함
                    gotoxy((mouse.dwMousePosition.X/2)*2, mouse.dwMousePosition.Y);
                    if (placeStone() && !checkOmok())
                    {
                        //차례 교대
                        if (mStoneColor == eStoneType::BlackStone)
                        {
                            mStoneColor = eStoneType::WhiteStone;
                            message(eMessage::TurnOfWhiteStone);
                        }
                        else
                        {
                            mStoneColor = eStoneType::BlackStone;
                            message(eMessage::TurnOfBlackStone);
                        }
                    }
                }
                break;
            }
        }
    }
    if (mStoneColor == eStoneType::BlackStone)
    {
        message(eMessage::WinBlackStone);
    }
    else
    {
        message(eMessage::WinWhiteStone);
    }
    SetConsoleMode(hStdin, fdwSaveOldMode);
}

//보드에 돌을 두는 함수
int Board::placeStone()
{
    if (mBaord[mCursorY][mCursorX] == eStoneType::EmptySpace)
    {
        mBaord[mCursorY][mCursorX] = mStoneColor;
        if (mStoneColor == eStoneType::BlackStone)
        {
            std::cout << "○";
        }
        else
        {
            std::cout << "●";
        }

        return true;
    }
    else
    {
        message(eMessage::CanNotPlaceStone);
        return false;
    }
}

//게임 재시작 or 종료 결정
void Board::message(eMessage message)
{
    switch (message)
    {
    case eMessage::TurnOfBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "○흑돌 차례 입니다.          ";
        break;
    case eMessage::TurnOfWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "●백돌 차례 입니다.          ";
        break;
    case eMessage::WinBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "흑돌이 이겼습니다!              ";
        break;
    case eMessage::WinWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "백돌이 이겼습니다!              ";
        break;
    case eMessage::CanNotPlaceStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "돌을 놓을 수 없는 곳 입니다!";
        break;
    case eMessage::ContinueOrExit:
        gotoxy(2, BOARD_SIZE + 3);
        std::cout << "재시작은 Y 종료는 다른키를 입력하세요....";
        break;
    default:
        //Assert
        break;
    }
}