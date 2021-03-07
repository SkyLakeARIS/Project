#include "Board.h"

void Board::printBoard()
{
    for (int LoopY = 0; LoopY < BOARD_SIZE; LoopY++)
    {
        for (int LoopX = 0; LoopX < BOARD_SIZE; LoopX++)
        {
            gotoxy(LoopX*2, LoopY);
            if (LoopY == 0) // ù�� �׸���
            {
                if (LoopX == 0)
                {
                    std::cout << "��";
                }
                if (LoopX == (BOARD_SIZE - 1))
                {
                    std::cout << "��";
                }
                if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
                {
                    std::cout << "��";
                }
            }
            else // ������ �� �׸���
            {
                if (LoopY == (BOARD_SIZE - 1))
                {
                    if (LoopX == 0)
                    {
                        std::cout << "��";
                    }
                    if (LoopX == (BOARD_SIZE - 1))
                    {
                        std::cout << "��";
                    }
                    if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
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
                    if (LoopX == (BOARD_SIZE - 1))
                    {
                        std::cout << "��";
                    }
                    if (LoopX != 0 && LoopX != (BOARD_SIZE - 1))
                    {
                        std::cout << "��";
                    }
                }
            }
        }
    }
    message(eMessage::TurnOfBlackStone);
}

//���� ����۽� �������� �ʱ�ȭ �ϴ� �Լ�
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
    //���� ���� ��ġ�� �̸� ī��Ʈ�ϰ� ����Լ��� �ֺ��� ���� �ڽ��� ���� üũ��.
    int omokCount = 1;
    //�ڽ��� �� ���̿� �����ν� ������ �ϼ��Ǵ� ��츦 ����ؼ� �� �Լ��� ���ϰ���
    //���� �� ������ üũ��.
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

//���� �Լ�
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

                    //Ư�����ڰ� 2ĭ(2����Ʈ)�� ���������μ� ����� ��ǥ����(Ŭ���ϴ� ��ġ�� ���� ���̴� ��ġ)
                    //���ֱ����� /2�� ��µǴ� ��ġ�� ���߱����� *2�� ��
                    gotoxy((mouse.dwMousePosition.X/2)*2, mouse.dwMousePosition.Y);
                    if (placeStone() && !checkOmok())
                    {
                        //���� ����
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

//���忡 ���� �δ� �Լ�
int Board::placeStone()
{
    if (mBaord[mCursorY][mCursorX] == eStoneType::EmptySpace)
    {
        mBaord[mCursorY][mCursorX] = mStoneColor;
        if (mStoneColor == eStoneType::BlackStone)
        {
            std::cout << "��";
        }
        else
        {
            std::cout << "��";
        }

        return true;
    }
    else
    {
        message(eMessage::CanNotPlaceStone);
        return false;
    }
}

//���� ����� or ���� ����
void Board::message(eMessage message)
{
    switch (message)
    {
    case eMessage::TurnOfBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "���浹 ���� �Դϴ�.          ";
        break;
    case eMessage::TurnOfWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "�ܹ鵹 ���� �Դϴ�.          ";
        break;
    case eMessage::WinBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "�浹�� �̰���ϴ�!              ";
        break;
    case eMessage::WinWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "�鵹�� �̰���ϴ�!              ";
        break;
    case eMessage::CanNotPlaceStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "���� ���� �� ���� �� �Դϴ�!";
        break;
    case eMessage::ContinueOrExit:
        gotoxy(2, BOARD_SIZE + 3);
        std::cout << "������� Y ����� �ٸ�Ű�� �Է��ϼ���....";
        break;
    default:
        //Assert
        break;
    }
}