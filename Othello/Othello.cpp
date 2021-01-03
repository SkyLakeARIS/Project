#include<conio.h>
#include<iostream>
#include<Windows.h>

#define MAX_BOARD_SIZE (8)  
#define SUCCESS (1)
#define FAIL (0)

class Othello
{
private:
	enum class eStoneType
	{
		WhiteStone = -1,
		EmptySpace,
		BlackStone
	};

	enum class eControlKey
	{
		Up = 119,
		Down = 115,
		Left = 97,
		Right = 100,
		Stop = 0,
		Space = 32,
		X = 120
	};

	enum class eDirection
	{
		UP = 1,
		DOWN,
		LEFT,
		RIGHT,
		DIAGONAL1,
		DIAGONAL2,
		DIAGONAL3,
		DIAGONAL4,
	};

	enum class eGameState
	{
		Exit = 0,
		Continue
	};

	enum class eMessage
	{
		TurnOfBlackStone,
		TurnOfWhiteStone,
		WinBlackStone,
		WinWhiteStone,
		WrongLocation,
		StoneIsAlreadyPlaced,
		ContinueOrExit
	};

public:
	Othello()
	{
		SettingBoard();
	}

	void SettingBoard();

	void Run();

	void PrintLine();

	void PrintBoard();

	void ControlKey();

	int PlaceStone();

	int CheckCompetitorStone();

	void ReverseStone(eDirection dir);

	int CheckGameOver();

	eGameState ContinueOrExit();

	void ChangeTurn();

	void Message(eMessage message);

	void gotoxy(int x, int y)
	{
		COORD pos = { x * 2, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

private:
	int mCursorX;
	int mCursorY;
	eStoneType mStoneColor;
	eStoneType mBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

void Othello::SettingBoard()
{
	for (int i = 0; i < MAX_BOARD_SIZE; i++)
	{
		for (int j = 0; j < MAX_BOARD_SIZE; j++)
		{
			mBoard[i][j] = eStoneType::EmptySpace;
		}
	}

	mCursorX = MAX_BOARD_SIZE / 2;
	mCursorY = MAX_BOARD_SIZE / 2;

	mBoard[3][3] = eStoneType::WhiteStone;
	mBoard[4][4] = eStoneType::WhiteStone;
	mBoard[3][4] = eStoneType::BlackStone;
	mBoard[4][3] = eStoneType::BlackStone;

	mStoneColor = eStoneType::BlackStone;

	PrintLine();
	PrintBoard();

	Message(eMessage::TurnOfBlackStone);
}
//���� ���� �Լ�(Loop)
void Othello::Run()
{
	system("mode con:cols=50 lines=20");
	eGameState bGameFlag = eGameState::Continue;
	while (bGameFlag == eGameState::Continue)
	{
		SettingBoard();
		while (!CheckGameOver())
		{
			ControlKey();
		}
		bGameFlag = ContinueOrExit();
	}
}
//�������� �׸��� �Լ�
void Othello::PrintLine()
{
	system("cls");
	for (int LoopY = 0; LoopY < MAX_BOARD_SIZE; LoopY++)
	{
		for (int LoopX = 0; LoopX < MAX_BOARD_SIZE; LoopX++)
		{

			gotoxy(LoopX, LoopY);

			if (LoopY == 0) // ù�� �׸���
			{
				if (LoopX == 0)
				{
					std::cout << "��";
				}
				if (LoopX == (MAX_BOARD_SIZE - 1))
				{
					std::cout << "��";
				}
				if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
				{
					std::cout << "��";
				}
			}
			else // ������ �� �׸���
			{
				if (LoopY == (MAX_BOARD_SIZE - 1))
				{
					if (LoopX == 0)
					{
						std::cout << "��";
					}
					if (LoopX == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "��";
					}
					if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
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
					if (LoopX == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "��";
					}
					if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
					{
						std::cout << "��";
					}
				}
			}
		}
	}
	gotoxy(10, 1);
	std::cout << "W key : cursor move up";
	gotoxy(10, 2);
	std::cout << "A key : cursor move left";
	gotoxy(10, 3);
	std::cout << "S key : cursor move right";
	gotoxy(10, 4);
	std::cout << "D key : cursor move down";
	gotoxy(10, 5);
	std::cout << "SPACE key : place stone";
	gotoxy(10, 6);
	std::cout << "X key : give up turn";
}
//���忡 ���� ���� ����ϴ� �Լ�
void Othello::PrintBoard()
{
	for (int LoopY = 0; LoopY < MAX_BOARD_SIZE; LoopY++)
	{
		for (int LoopX = 0; LoopX < MAX_BOARD_SIZE; LoopX++)
		{
			if (mBoard[LoopY][LoopX] == eStoneType::BlackStone)
			{
				gotoxy(LoopX, LoopY);
				std::cout << "��";
			}
			if (mBoard[LoopY][LoopX] == eStoneType::WhiteStone)
			{
				gotoxy(LoopX, LoopY);
				std::cout << "��";
			}
		}
	}
}
//Ŀ����ǥ �̵�, ���� ����, ���� �ѱ��
void Othello::ControlKey()
{
	switch (static_cast<eControlKey>(_getch()))
	{
	case eControlKey::Up:   // W key, cursor up
		if (mCursorY - 1 >= 0)
		{
			mCursorY--;
		}
		break;
	case eControlKey::Left:   // A key, cursor left
		if (mCursorX - 1 >= 0)
		{
			mCursorX--;
		}
		break;
	case eControlKey::Down:   // S key, cursor down
		if (mCursorY + 1 < MAX_BOARD_SIZE)
		{
			mCursorY++;
		}
		break;
	case eControlKey::Right:   // D key , cursor right
		if (mCursorX + 1 < MAX_BOARD_SIZE)
		{
			mCursorX++;
		}
		break;
	case eControlKey::Space:   // space key , place stone
		PlaceStone();
		break;
	case eControlKey::X:   // x key , give up turn
		ChangeTurn();
		break;
	default:
		//Assert
		break;
	}
	gotoxy(mCursorX, mCursorY);
}
//���� ���� �� �ִ��� üũ�ϴ� �Լ�
int Othello::PlaceStone()
{
	if (mBoard[mCursorY][mCursorX] == eStoneType::EmptySpace) //�������� ���� ���� ������
	{
		if (SUCCESS == CheckCompetitorStone())
		{
			mBoard[mCursorY][mCursorX] = mStoneColor;
			PrintBoard();
			ChangeTurn();
			return SUCCESS;
		}
		else
		{
			Message(eMessage::WrongLocation);
			return FAIL;
		}
	}
	else
	{
		Message(eMessage::StoneIsAlreadyPlaced);
		return FAIL;
	}
}
//�ڽ��� �� ���̿� ��� ���� �ִ��� üũ�ϰ� ������ �Լ�
int Othello::CheckCompetitorStone()
{
	int i = 1;
	bool bCanPlaceStone = false;
	eStoneType competitorStone = mStoneColor == eStoneType::BlackStone ? eStoneType::WhiteStone : eStoneType::BlackStone;

	//���� �˻�
	while (mBoard[mCursorY - i][mCursorX] == competitorStone && mCursorY - i > 0)
	{
		++i;
	}
	if (mBoard[mCursorY - i][mCursorX] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::UP);
		bCanPlaceStone = true;
	}
	i = 1;
	//�Ʒ��� �˻�
	while (mBoard[mCursorY + i][mCursorX] == competitorStone && mCursorY + i < MAX_BOARD_SIZE - 1)
	{
		++i;
	}
	if (mBoard[mCursorY + i][mCursorX] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::DOWN);
		bCanPlaceStone = true;
	}
	i = 1;
	//�·� �˻�
	while (mBoard[mCursorY][mCursorX - i] == competitorStone && mCursorX - i > 0)
	{
		++i;
	}
	if (mBoard[mCursorY][mCursorX - i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::LEFT);
		bCanPlaceStone = true;
	}
	i = 1;
	//��� �˻�
	while (mBoard[mCursorY][mCursorX + i] == competitorStone && mCursorX + i < MAX_BOARD_SIZE - 1)
	{
		++i;
	}
	if (mBoard[mCursorY][mCursorX + i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::RIGHT);
		bCanPlaceStone = true;
	}
	i = 1;
	//�»�밢 �˻�
	while (mBoard[mCursorY - i][mCursorX - i] == competitorStone && mCursorX - i > 0 && mCursorY - i > 0)
	{
		++i;
	}
	if (mBoard[mCursorY - i][mCursorX - i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::DIAGONAL1);
		bCanPlaceStone = true;
	}
	i = 1;
	//���ϴ밢 �˻�
	while (mBoard[mCursorY + i][mCursorX - i] == competitorStone && mCursorX - i > 0 && mCursorY + i < MAX_BOARD_SIZE - 1)
	{
		++i;
	}
	if (mBoard[mCursorY + i][mCursorX - i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::DIAGONAL2);
		bCanPlaceStone = true;
	}
	i = 1;
	//���밢 �˻�
	while (mBoard[mCursorY - i][mCursorX + i] == competitorStone && mCursorX + i < MAX_BOARD_SIZE - 1 && mCursorY - i > 0)
	{
		++i;
	}
	if (mBoard[mCursorY - i][mCursorX + i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::DIAGONAL3);
		bCanPlaceStone = true;
	}
	i = 1;
	//���ϴ밢 �˻�
	while (mBoard[mCursorY + i][mCursorX + i] == competitorStone && mCursorX + i < MAX_BOARD_SIZE - 1 && mCursorY + i < MAX_BOARD_SIZE - 1)
	{
		++i;
	}
	if (mBoard[mCursorY + i][mCursorX + i] == mStoneColor && i != 1)
	{
		ReverseStone(eDirection::DIAGONAL4);
		bCanPlaceStone = true;
	}

	if (bCanPlaceStone == true)
	{
		return SUCCESS;
	}

	return FAIL;
}

//������ ��ǥ�� ���� �� �� �ִ��� ���θ� ���� ���� ���� �������� ���� ������ �Լ�
void Othello::ReverseStone(eDirection dir)
{
	eStoneType competitorStone = mStoneColor == eStoneType::BlackStone ? eStoneType::WhiteStone : eStoneType::BlackStone;
	int i = 1;
	switch (dir)
	{
	case eDirection::UP: //���� ������
		// && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DOWN: //�Ʒ��� ������
		// && mCursorY + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY + i][mCursorX] == competitorStone)
		{
			mBoard[mCursorY + i][mCursorX] = mStoneColor;
			++i;
		}
		break;
	case eDirection::LEFT: //�·� ������
		// && mCursorX - i > 0
		while (mBoard[mCursorY][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::RIGHT: // ��� ������
		// && mCursorX + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY][mCursorX + i] == competitorStone)
		{
			mBoard[mCursorY][mCursorX + i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL1: //�»� �밢���� ������
		//&& mCursorX - i > 0 && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL2: //���� �밢 ������
		// && mCursorX - i > 0 && mCursorY + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY + i][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY + i][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL3: //��� �밢���� ������
		// && mCursorX + i < MAX_BOARD_SIZE - 1 && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX + i] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX + i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL4: //���� �밢 ������
		//&& mCursorX + i < MAX_BOARD_SIZE - 1 && mCursorY + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY + i][mCursorX + i] == competitorStone)
		{
			mBoard[mCursorY + i][mCursorX + i] = mStoneColor;
			++i;
		}
		break;
	default:
		//Assert
		break;
	}
}
//������ �������� üũ�ϴ� �Լ�
int Othello::CheckGameOver()
{
	int BlackStoneCount = 0;
	int WhiteStoneCount = 0;
	int EmptySpaceCount = 0;
	//�� �̻� �� ���� ������ �� ���� ���� üũ
	for (int LoopY = 0; LoopY < MAX_BOARD_SIZE; LoopY++)
	{
		for (int LoopX = 0; LoopX < MAX_BOARD_SIZE; LoopX++)
		{
			if (mBoard[LoopY][LoopX] == eStoneType::BlackStone)
			{
				BlackStoneCount++;
			}
			if (mBoard[LoopY][LoopX] == eStoneType::WhiteStone)
			{
				WhiteStoneCount++;
			}
			if (mBoard[LoopY][LoopX] == eStoneType::EmptySpace)
			{
				EmptySpaceCount++;
			}
		}
	}
	//���� ���� �� ���� ��
	if (BlackStoneCount > WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "��:" << BlackStoneCount << "��:" << WhiteStoneCount << "    �浹�� �¸�!";
		return SUCCESS;
	}
	if (BlackStoneCount < WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "��:" << BlackStoneCount << "��:" << WhiteStoneCount << "    �鵹�� �¸�!";
		return SUCCESS;
	}
	//����� ��
	if (BlackStoneCount == WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "��:" << BlackStoneCount << "��:" << WhiteStoneCount;
		return SUCCESS;
	}
	//���� ���� �ϳ��� ���� ��
	if (BlackStoneCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "��:" << BlackStoneCount << "��:" << WhiteStoneCount;
		return SUCCESS;
	}
	if (WhiteStoneCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "��:" << BlackStoneCount << "��:" << WhiteStoneCount;
		return SUCCESS;
	}

	return FAIL;
}
//������ ����� �� ���� ������ ���� 
Othello::eGameState Othello::ContinueOrExit()
{
	char selection;
	Message(eMessage::ContinueOrExit);
	std::cin >> selection;
	if (selection == 'Y' || selection == 'y')
	{
		return eGameState::Continue;
	}
	return eGameState::Exit;
}
//�� �� ���� �����ϴ� �Լ�
void Othello::ChangeTurn()
{
	if (mStoneColor == eStoneType::BlackStone)
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
//�޼��� ��� �Լ�
void Othello::Message(eMessage message)
{
	switch (message)
	{
	case eMessage::TurnOfBlackStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "�� �� ���� �Դϴ�.                      ";
		break;
	case eMessage::TurnOfWhiteStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "�� �� ���� �Դϴ�.                      ";
		break;
	case eMessage::WinBlackStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "�浹�� �̰���ϴ�!              ";
		break;
	case eMessage::WinWhiteStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "�鵹�� �̰���ϴ�!              ";
		break;
	case eMessage::WrongLocation:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "�ڽ��� �� ���̿� ��� ���� �־�� �մϴ�";
		break;
	case eMessage::StoneIsAlreadyPlaced:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "���� ���� �� ���� �� �Դϴ�!";
		break;
	case eMessage::ContinueOrExit:
		gotoxy(0, MAX_BOARD_SIZE + 3);
		std::cout << "������� Y, ����� �ƹ�Ű�� �Է��� �ּ���. :";
		break;
	default:
		//Assert
		break;
	}
}
/*
�������� 19'11.26
�ϼ����� 19'11.28
�������� 19'12.01 (�� ����)
		19'12.10 (enum �߰� �� �ڵ� ����)
		20'05.17~18 �ڵ� ����, �밢�� ���� ����, �ڵ� ���Ĵٵ� ���� ��
		20'05.19 eStoneType enum class�� ����
		����: https://docs.popekim.com/ko/coding-standards/cpp
made.SkyLakeARIS
*/
int main()
{
	Othello game;
	game.Run();
	return 0;
}