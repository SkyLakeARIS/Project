#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "lib.h"

/*
 skylake aris
수정일: 20'05.16~17
코드 개선, 오목체크 로직 개선, 코딩스탠다드 적용 중
참고 자료
https://docs.popekim.com/ko/coding-standards/cpp
*/

class Board
{
private:
    enum class eMessage
    {
        TurnOfBlackStone,
        TurnOfWhiteStone,
        WinBlackStone,
        WinWhiteStone,
        CantPlaceStone,
        ContinueOrExit
    };

    enum class eStoneType
    {
        BlackStone = 1,
        WhiteStone,
        EmptySpace = 0
    };

    enum class eControlKey
    {
        Up = 119,
        Down = 115,
        Left = 97,
        Right = 100,
        Stop = 0,
        Space = 32
    };
    
    enum class eGameState
    {
        Exit = 0,
        Continue,
        Complete_Omok = 5
    };

public:
    Board()
    {
        SettingGame();
    }

    void PrintBoard()
    {
        system("cls");
        for (int LoopY = 0; LoopY < Max_Map_Size; LoopY++)
        {
            for (int LoopX = 0; LoopX < Max_Map_Size; LoopX++)
            {
                gotoxy(LoopX, LoopY);
                if (LoopY == 0) // 첫출 그리기
                {
                    if (LoopX == 0)
                    {
                        std::cout << "┌";
                    }
                    if (LoopX == (Max_Map_Size - 1))
                    {
                        std::cout << "┐";
                    }
                    if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
                    {
                        std::cout << "┬";
                    }
                }
                else // 마지막 줄 그리기
                {
                    if (LoopY == (Max_Map_Size - 1))
                    {
                        if (LoopX == 0)
                        {
                            std::cout << "└";
                        }
                        if (LoopX == (Max_Map_Size - 1))
                        {
                            std::cout << "┘";
                        }
                        if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
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
                        if (LoopX == (Max_Map_Size - 1))
                        {
                            std::cout << "┤";
                        }
                        if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
                        {
                            std::cout << "┼";
                        }
                    }
                }
            }
        }
        Message(eMessage::TurnOfBlackStone);
    }
    //게임 재시작시 정보들을 초기화 하는 함수
    void SettingGame()
    {
        for (int LoopY = 0; LoopY < Max_Map_Size; LoopY++)
        {
            for (int LoopX = 0; LoopX < Max_Map_Size; LoopX++)
            {
                mboard[LoopY][LoopX] = eStoneType::EmptySpace;
            }
        }
        mCursorX = Max_Map_Size / 2;
        mCursorY = Max_Map_Size / 2;

        mStoneColor = eStoneType::BlackStone;

        bmIsCompleteOmok = false;
    }
    //게임을 재시작 할건지
    eGameState GameOver()
    {
        char selection;
        Message(eMessage::ContinueOrExit);
        std::cin >> selection;
        if (selection == 'y' || selection == 'Y')
        {
            return eGameState::Continue;
        }
        else
        {
            return eGameState::Exit;
        }
    }
    //실행 함수
    void Run()
    {
        eGameState loopFlag = eGameState::Continue;
        while(eGameState::Continue == loopFlag)
        {
            PrintBoard();
            while (!bmIsCompleteOmok)
            {
                ControlKey();
            }
            if (mStoneColor == eStoneType::BlackStone)
            {
                Message(eMessage::WinBlackStone);
            }
            else
            {
                Message(eMessage::WinWhiteStone);
            }
            loopFlag = GameOver();
            if (loopFlag == eGameState::Continue)
            {
                SettingGame();
            }
        }
    }
    // 커서좌표 이동함수 및 돌을 놓는 함수
    void ControlKey()
    {
        switch (static_cast<eControlKey>(_getch()))
        {
        case eControlKey::Up: //UP , w
            if (mCursorY > 0)
            {
                mCursorY--;
            }
            break;
        case eControlKey::Left: //Left , a
            if (mCursorX > 0)
            {
                mCursorX--;
            }
            break;
        case eControlKey::Down: //Down, s
            if (mCursorY < Max_Map_Size)
            {
                mCursorY++;
            }
            break;
        case eControlKey::Right: //Right, d
            if (mCursorX < Max_Map_Size)
            {
                mCursorX++;
            }
            break;
        case eControlKey::Space: //place stone, space
            if (PlaceStone() == SUCCESS)
            {
                if (CheckStone())
                {
                    bmIsCompleteOmok = true;
                }
                else
                {
                    ChangeTurn();
                }
            }
            break;
        default:
            //Assert
            break;
        }
        gotoxy(mCursorX, mCursorY);
    }
    //보드에 돌을 두는 함수
    int PlaceStone() //enum or define
    {
        if (mboard[mCursorY][mCursorX] == eStoneType::EmptySpace) //돌이 놓이지 않은 곳인지
        {
            mboard[mCursorY][mCursorX] = mStoneColor;
            gotoxy(mCursorX, mCursorY);
            if (mStoneColor == eStoneType::BlackStone) //흑돌이면 참, 백돌이면 거짓 실행
            { 
                std::cout << "○";
            }
            else
            {
                std::cout << "●";
            }
            return SUCCESS;
        }
        else
        {
            Message(eMessage::CantPlaceStone);
            return FAIL;
        }
    }
    //흑 백 차례 교대하는 함수
    void ChangeTurn()
    {
        if (mStoneColor == eStoneType::BlackStone) //흑 백 교대
        {
            mStoneColor = eStoneType::WhiteStone;
            Message(eMessage::TurnOfWhiteStone);
        }
        else
        {
            mStoneColor = eStoneType::BlackStone;
            Message(eMessage::TurnOfBlackStone);
        }
    }
    //오목이 되었는지 검사하는 함수
    int CheckStone()
    {
        //놓은 위치는 계산한 값으로 시작
        int omokCount = 1;
        int i = 1;
        //상 하 체크
        while (mboard[mCursorY - i][mCursorX] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }
        i = 1;
        while (mboard[mCursorY + i][mCursorX] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }

        //오목이 완성되면 SUCCESS 반환 -> 게임 오버  /아래 동일/
        //else 체크 변수 초기화 후 다음 방향 검사
        if (static_cast<eGameState>(omokCount) == eGameState::Complete_Omok)
        {
            return SUCCESS;
        }
        else
        {
            omokCount = 1;
            i = 1;
        }

        //좌 우 체크
        while (mboard[mCursorY][mCursorX - i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }
        i = 1;
        while (mboard[mCursorY][mCursorX + i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }

        if (static_cast<eGameState>(omokCount) == eGameState::Complete_Omok)
        {
            return SUCCESS;
        }
        else
        {
            omokCount = 1;
            i = 1;
        }

        //좌상 우하 대각 체크
        while (mboard[mCursorY - i][mCursorX - i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }
        i = 1;
        while (mboard[mCursorY + i][mCursorX + i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }

        if (static_cast<eGameState>(omokCount) == eGameState::Complete_Omok)
        {
            return SUCCESS;
        }
        else
        {
            omokCount = 1;
            i = 1;
        }

        //우상 좌하 대각 체크
        while (mboard[mCursorY - i][mCursorX + i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }
        i = 1;
        while (mboard[mCursorY + i][mCursorX - i] == mStoneColor)
        {
            ++omokCount;
            ++i;
        }

        if (static_cast<eGameState>(omokCount) == eGameState::Complete_Omok)
        {
            return SUCCESS;
        }

        return FAIL;
    }
    //게임 재시작 or 종료 결정
    void Message(eMessage message)
    {
        switch (message)
        {
        case eMessage::TurnOfBlackStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "○흑돌 차례 입니다.          ";
            break;
        case eMessage::TurnOfWhiteStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "●백돌 차례 입니다.          ";
            break;
        case eMessage::WinBlackStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "흑돌이 이겼습니다!              ";
            break;
        case eMessage::WinWhiteStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "백돌이 이겼습니다!              ";
            break;
        case eMessage::CantPlaceStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "돌을 놓을 수 없는 곳 입니다!";
            break;
        case eMessage::ContinueOrExit:
            gotoxy(2, Max_Map_Size + 3);
            std::cout << "재시작은 Y 종료는 다른키를 입력하세요....";
            break;
        default:
            //Assert
            break;
        }
    }
private:
    eStoneType mboard[Max_Map_Size][Max_Map_Size];
    eStoneType mStoneColor;
    int mCursorX;
    int mCursorY;
    bool bmIsCompleteOmok;
};

int main()
{
    Board game;
    game.Run();
    return 0;
}