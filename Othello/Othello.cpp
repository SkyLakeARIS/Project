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
//게임 실행 함수(Loop)
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
//보드판을 그리는 함수
void Othello::PrintLine()
{
	system("cls");
	for (int LoopY = 0; LoopY < MAX_BOARD_SIZE; LoopY++)
	{
		for (int LoopX = 0; LoopX < MAX_BOARD_SIZE; LoopX++)
		{

			gotoxy(LoopX, LoopY);

			if (LoopY == 0) // 첫출 그리기
			{
				if (LoopX == 0)
				{
					std::cout << "┌";
				}
				if (LoopX == (MAX_BOARD_SIZE - 1))
				{
					std::cout << "┐";
				}
				if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
				{
					std::cout << "┬";
				}
			}
			else // 마지막 줄 그리기
			{
				if (LoopY == (MAX_BOARD_SIZE - 1))
				{
					if (LoopX == 0)
					{
						std::cout << "└";
					}
					if (LoopX == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "┘";
					}
					if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
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
					if (LoopX == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "┤";
					}
					if (LoopX != 0 && LoopX != (MAX_BOARD_SIZE - 1))
					{
						std::cout << "┼";
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
//보드에 놓인 돌을 출력하는 함수
void Othello::PrintBoard()
{
	for (int LoopY = 0; LoopY < MAX_BOARD_SIZE; LoopY++)
	{
		for (int LoopX = 0; LoopX < MAX_BOARD_SIZE; LoopX++)
		{
			if (mBoard[LoopY][LoopX] == eStoneType::BlackStone)
			{
				gotoxy(LoopX, LoopY);
				std::cout << "○";
			}
			if (mBoard[LoopY][LoopX] == eStoneType::WhiteStone)
			{
				gotoxy(LoopX, LoopY);
				std::cout << "●";
			}
		}
	}
}
//커서좌표 이동, 돌을 놓고, 차례 넘기기
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
//돌을 놓을 수 있는지 체크하는 함수
int Othello::PlaceStone()
{
	if (mBoard[mCursorY][mCursorX] == eStoneType::EmptySpace) //놓으려는 곳에 돌이 없는지
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
//자신의 돌 사이에 상대 돌이 있는지 체크하고 뒤집는 함수
int Othello::CheckCompetitorStone()
{
	int i = 1;
	bool bCanPlaceStone = false;
	eStoneType competitorStone = mStoneColor == eStoneType::BlackStone ? eStoneType::WhiteStone : eStoneType::BlackStone;

	//위로 검사
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
	//아래로 검사
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
	//좌로 검사
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
	//우로 검사
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
	//좌상대각 검사
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
	//좌하대각 검사
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
	//우상대각 검사
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
	//우하대각 검사
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

//선택한 좌표에 돌을 둘 수 있는지 여부를 통해 놓은 돌을 기점으로 돌을 뒤집는 함수
void Othello::ReverseStone(eDirection dir)
{
	eStoneType competitorStone = mStoneColor == eStoneType::BlackStone ? eStoneType::WhiteStone : eStoneType::BlackStone;
	int i = 1;
	switch (dir)
	{
	case eDirection::UP: //위로 뒤집기
		// && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DOWN: //아래로 뒤집기
		// && mCursorY + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY + i][mCursorX] == competitorStone)
		{
			mBoard[mCursorY + i][mCursorX] = mStoneColor;
			++i;
		}
		break;
	case eDirection::LEFT: //좌로 뒤집기
		// && mCursorX - i > 0
		while (mBoard[mCursorY][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::RIGHT: // 우로 뒤집기
		// && mCursorX + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY][mCursorX + i] == competitorStone)
		{
			mBoard[mCursorY][mCursorX + i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL1: //좌상 대각으로 뒤집기
		//&& mCursorX - i > 0 && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL2: //좌하 대각 뒤집기
		// && mCursorX - i > 0 && mCursorY + i < MAX_BOARD_SIZE - 1
		while (mBoard[mCursorY + i][mCursorX - i] == competitorStone)
		{
			mBoard[mCursorY + i][mCursorX - i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL3: //우상 대각으로 뒤집기
		// && mCursorX + i < MAX_BOARD_SIZE - 1 && mCursorY - i > 0
		while (mBoard[mCursorY - i][mCursorX + i] == competitorStone)
		{
			mBoard[mCursorY - i][mCursorX + i] = mStoneColor;
			++i;
		}
		break;
	case eDirection::DIAGONAL4: //우하 대각 뒤집기
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
//게임이 끝났는지 체크하는 함수
int Othello::CheckGameOver()
{
	int BlackStoneCount = 0;
	int WhiteStoneCount = 0;
	int EmptySpaceCount = 0;
	//더 이상 둘 곳이 없을때 각 돌의 개수 체크
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
	//한쪽 돌이 더 많을 때
	if (BlackStoneCount > WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "○:" << BlackStoneCount << "●:" << WhiteStoneCount << "    흑돌의 승리!";
		return SUCCESS;
	}
	if (BlackStoneCount < WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "○:" << BlackStoneCount << "●:" << WhiteStoneCount << "    백돌의 승리!";
		return SUCCESS;
	}
	//비겼을 때
	if (BlackStoneCount == WhiteStoneCount && EmptySpaceCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "○:" << BlackStoneCount << "●:" << WhiteStoneCount;
		return SUCCESS;
	}
	//한쪽 돌이 하나도 없을 때
	if (BlackStoneCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "○:" << BlackStoneCount << "●:" << WhiteStoneCount;
		return SUCCESS;
	}
	if (WhiteStoneCount == 0)
	{
		gotoxy(0, MAX_BOARD_SIZE + 2);
		std::cout << "○:" << BlackStoneCount << "●:" << WhiteStoneCount;
		return SUCCESS;
	}

	return FAIL;
}
//게임을 재시작 할 건지 종료할 건지 
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
//흑 백 차례 교대하는 함수
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
//메세지 출력 함수
void Othello::Message(eMessage message)
{
	switch (message)
	{
	case eMessage::TurnOfBlackStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "○ 의 차례 입니다.                      ";
		break;
	case eMessage::TurnOfWhiteStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "● 의 차례 입니다.                      ";
		break;
	case eMessage::WinBlackStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "흑돌이 이겼습니다!              ";
		break;
	case eMessage::WinWhiteStone:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "백돌이 이겼습니다!              ";
		break;
	case eMessage::WrongLocation:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "자신의 돌 사이에 상대 돌이 있어야 합니다";
		break;
	case eMessage::StoneIsAlreadyPlaced:
		gotoxy(0, MAX_BOARD_SIZE + 1);
		std::cout << "돌을 놓을 수 없는 곳 입니다!";
		break;
	case eMessage::ContinueOrExit:
		gotoxy(0, MAX_BOARD_SIZE + 3);
		std::cout << "재시작은 Y, 종료는 아무키나 입력해 주세요. :";
		break;
	default:
		//Assert
		break;
	}
}
/*
시작일자 19'11.26
완성일자 19'11.28
수정일자 19'12.01 (논리 개선)
		19'12.10 (enum 추가 및 코드 개선)
		20'05.17~18 코드 개선, 대각선 로직 개선, 코딩 스탠다드 적용 중
		20'05.19 eStoneType enum class로 변경
		참고: https://docs.popekim.com/ko/coding-standards/cpp
made.SkyLakeARIS
*/
int main()
{
	Othello game;
	game.Run();
	return 0;
}