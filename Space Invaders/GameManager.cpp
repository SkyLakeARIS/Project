#include <conio.h>
#include <cstdint>
#include "GameManager.h"

//게임 루프 담당 함수
int GameManager::PlayGame()
{
	CursorView(HIDDEN);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	std::shared_ptr<Barricade> barri = std::make_shared<Barricade>();
	std::shared_ptr<UFO> ufo = std::make_shared<UFO>();

	uint64_t begin = 0;
	uint64_t delta = 0;
	uint64_t delta2 = 0;
	uint64_t delta3 = 0;

	while (GameOver(player, enemy, barri))
	{
		begin = GetTickCount64();
		barri->PrintEntity();
		delta += GetTickCount64() - begin;
		if (delta2 > 10)
		{
			enemy->MoveBullet();
			player->MoveEntity();
			player->PrintEntity();
			player->Shooting(enemy);
			player->Shooting(barri);
			player->Shooting(ufo);
			delta = 0;
		}
		delta2 += GetTickCount64() - begin;
		if (delta3> 90)
		{
			ufo->MoveEntity();
			ufo->PrintEntity();
			delta2 = 0;
		}
		delta3 += GetTickCount64() - begin;
		//적의 숫자에 따라 움직이는 속도 조작
		if (delta3 > 200 + (18 * enemy->GetEnemySize()))
		{
			enemy->MoveEntity();
			enemy->PrintEntity();
			enemy->Shooting(player);
			enemy->Shooting(barri);
			delta3 = 0;
		}
	}
	CursorView(SHOW);
	
	ResultMenu(player);

	return 0;
}

bool GameManager::GameOver(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::shared_ptr<Barricade> barri)
{
	if (player->GetLife() <= 0)
	{
		return false;
	}
	if (enemy->IsEnemyGoToEndLine())
	{
		return false;
	}
	//적들을 다 잡으면 다음 라운드를 위해 초기화
	if (0 == enemy->GetEnemySize())
	{
		player->ClearData();
		enemy->ClearData();
		barri->ClearData();

		return true;
	}
	return true;
}
//게임오버 후 결과화면 출력
void GameManager::ResultMenu(std::shared_ptr<Player> player) const
{
	system("cls");

	gotoxy(11, 9);
	SetColor(YELLOW); std::cout << "GAME  OVER";

	gotoxy(11, 11);
	SetColor(SKY_BLUE); std::cout << "My Score ";
	gotoxy(12, 12);
	SetColor(SKY_BLUE); std::cout << player->GetScore() << "Points";

	gotoxy(7, 20);
	SetColor(RED); std::cout << "Press Enter Key return to Menu";
	while (13 != _getch()) {};
}