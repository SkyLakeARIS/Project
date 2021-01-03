#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "lib.h"

/*
 skylake aris
������: 20'05.16~17
�ڵ� ����, ����üũ ���� ����, �ڵ����Ĵٵ� ���� ��
���� �ڷ�
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
                if (LoopY == 0) // ù�� �׸���
                {
                    if (LoopX == 0)
                    {
                        std::cout << "��";
                    }
                    if (LoopX == (Max_Map_Size - 1))
                    {
                        std::cout << "��";
                    }
                    if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
                    {
                        std::cout << "��";
                    }
                }
                else // ������ �� �׸���
                {
                    if (LoopY == (Max_Map_Size - 1))
                    {
                        if (LoopX == 0)
                        {
                            std::cout << "��";
                        }
                        if (LoopX == (Max_Map_Size - 1))
                        {
                            std::cout << "��";
                        }
                        if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
                        {
                            std::cout << "��";
                        }
                    }
                    else //�߰� �� �׸���
                    {
                        if (LoopX == 0)
                        {
                            std::cout << "��";
                        }
                        if (LoopX == (Max_Map_Size - 1))
                        {
                            std::cout << "��";
                        }
                        if (LoopX != 0 && LoopX != (Max_Map_Size - 1))
                        {
                            std::cout << "��";
                        }
                    }
                }
            }
        }
        Message(eMessage::TurnOfBlackStone);
    }
    //���� ����۽� �������� �ʱ�ȭ �ϴ� �Լ�
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
    //������ ����� �Ұ���
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
    //���� �Լ�
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
    // Ŀ����ǥ �̵��Լ� �� ���� ���� �Լ�
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
    //���忡 ���� �δ� �Լ�
    int PlaceStone() //enum or define
    {
        if (mboard[mCursorY][mCursorX] == eStoneType::EmptySpace) //���� ������ ���� ������
        {
            mboard[mCursorY][mCursorX] = mStoneColor;
            gotoxy(mCursorX, mCursorY);
            if (mStoneColor == eStoneType::BlackStone) //�浹�̸� ��, �鵹�̸� ���� ����
            { 
                std::cout << "��";
            }
            else
            {
                std::cout << "��";
            }
            return SUCCESS;
        }
        else
        {
            Message(eMessage::CantPlaceStone);
            return FAIL;
        }
    }
    //�� �� ���� �����ϴ� �Լ�
    void ChangeTurn()
    {
        if (mStoneColor == eStoneType::BlackStone) //�� �� ����
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
    //������ �Ǿ����� �˻��ϴ� �Լ�
    int CheckStone()
    {
        //���� ��ġ�� ����� ������ ����
        int omokCount = 1;
        int i = 1;
        //�� �� üũ
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

        //������ �ϼ��Ǹ� SUCCESS ��ȯ -> ���� ����  /�Ʒ� ����/
        //else üũ ���� �ʱ�ȭ �� ���� ���� �˻�
        if (static_cast<eGameState>(omokCount) == eGameState::Complete_Omok)
        {
            return SUCCESS;
        }
        else
        {
            omokCount = 1;
            i = 1;
        }

        //�� �� üũ
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

        //�»� ���� �밢 üũ
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

        //��� ���� �밢 üũ
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
    //���� ����� or ���� ����
    void Message(eMessage message)
    {
        switch (message)
        {
        case eMessage::TurnOfBlackStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "���浹 ���� �Դϴ�.          ";
            break;
        case eMessage::TurnOfWhiteStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "�ܹ鵹 ���� �Դϴ�.          ";
            break;
        case eMessage::WinBlackStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "�浹�� �̰���ϴ�!              ";
            break;
        case eMessage::WinWhiteStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "�鵹�� �̰���ϴ�!              ";
            break;
        case eMessage::CantPlaceStone:
            gotoxy(1, Max_Map_Size + 2);
            std::cout << "���� ���� �� ���� �� �Դϴ�!";
            break;
        case eMessage::ContinueOrExit:
            gotoxy(2, Max_Map_Size + 3);
            std::cout << "������� Y ����� �ٸ�Ű�� �Է��ϼ���....";
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