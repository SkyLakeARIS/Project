#include <conio.h>
#include "UI.h"

//시작 메뉴 출력
int UI::Menu()
{
	system("mode con:cols=50 lines=30");
	gotoxy(8, 3);
	SetColor(RED); std::cout << "보스 모습";

	gotoxy(8, 4);
	SetColor(GREEN); std::cout << "SPACE INVADERS";
	gotoxy(5, 7);
	SetColor(SKY_BLUE); std::cout << "*SCORE   ADVANCE   TABLE*";

	gotoxy(7, 9);
	SetColor(RED); std::cout << "BOSS =   ? POINTS";
	gotoxy(6, 11);
	SetColor(VIOLET);  std::cout << "／Ａ＼";
	gotoxy(6, 12);
	std::cout << "☜♨☞ = 300 POINTS";
	gotoxy(7, 14);
	std::cout << "♨   =  30 POINTS";
	gotoxy(7, 16);
	SetColor(YELLOW); std::cout << "ㆄ   =  20 POINTS";
	gotoxy(7, 18);
	std::cout << "♧   =  10 POINTS";

	gotoxy(3, 28);
	SetColor(SKY_BLUE); std::cout << "SkyLake_ARIS 2020.02.28-2020.03.21";

	while (1)
	{
		if (mFlag == 1)
		{
			gotoxy(7, 22);
			SetColor(RED); std::cout << "  >> PLAY GAME <<  ";
			gotoxy(7, 24);
			SetColor(WHITE); std::cout << "     EXIT GAME     ";
			mSelection = PlayGame;
		}
		else
		{
			gotoxy(7, 22);
			SetColor(WHITE); std::cout << "     PLAY GAME     ";
			gotoxy(7, 24);
			SetColor(RED); std::cout << "  >> EXIT GAME <<  ";
			mSelection = ExitGame;
		}

		int key = _getch();

		switch (key)
		{
		case UP:
		case DOWN:
			mFlag *= -1;
			break;
		case SPACE:
			return mSelection;
		
		default:
			//Assert();
			break;
		}
	}
	return 0;
}
//세로라인 형태 출력
void UI::PrintMap() const
{
	system("mode con:cols=70 lines=30");

	for (int y = 0; y < 30; y++)
	{
		gotoxy(26, y);
		SetColor(WHITE); std::cout << "┃";
	}
}
//각종 정보 형태 출력
void UI::PrintInfo() const
{
	gotoxy(30, 10);
	SetColor(BLUE);
	std::cout << "SCORE";
	gotoxy(27, 11);
	SetColor(BLUE);
	std::cout << "0";
	gotoxy(2, 27);
	SetColor(SKY_BLUE);
	std::cout << "Life   A  A";
}
//게임 루프 시작
void UI::RUN()
{
	while (Menu())
	{
		system("cls");
		PrintMap();
		PrintInfo();
		mGM.PlayGame();
	}
}