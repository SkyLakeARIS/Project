#include "GameManager.h"

void GameManager::settingGame()
{
	mEnemyMovement = eDirection::RIGHT;
	mbUFOFlag = false;
	mUFOCountDown = GetRandomNumber(50, 100);
	mStage = 0;
	mScore = 0;
}

void GameManager::settingEntities()
{
	//Enemy
	for (int x = 0; x < 9; x++)
	{
		mEnemies.emplace_back(4 + (x * 2), 3, eType::SQUID);
	}
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			mEnemies.emplace_back(4 + (x * 2), 4 + ((y * 2) - 1), eType::CRAB);
		}
	}
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (y == 2)
			{
				mEnemies.emplace_back(4 + (x * 2), 8 + ((y * 2) - 1), eType::OCTOPUS);
			}
			else
			{
				mEnemies.emplace_back(4 + (x * 2), 8 + ((y * 2) - 1), eType::OCTOPUS);
			}
		}
	}
	mEnemyCount = mEnemies.size();
	//Barricade
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mBarricades.emplace_back(2 + x, 18 + y);
			mBarricades.emplace_back(8 + x, 18 + y);
			mBarricades.emplace_back(14 + x, 18 + y);
			mBarricades.emplace_back(20 + x, 18 + y);
		}
	}
	for (int x = 0; x < 8; x++)
	{
		mBarricades.emplace_back(2 + (3 * x), 20);
	}
}

void GameManager::ControlPlayer()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		mPlayer.Move(eDirection::LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		mPlayer.Move(eDirection::RIGHT);
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		bool bFindPlayerBullet = false;
		for (unsigned int i = 0; i < mBullets.size(); i++)
		{
			if (mBullets[i].GetOwner() == eType::PLAYER)
			{
				bFindPlayerBullet = true;
			}
		}
		if (!bFindPlayerBullet)
		{
			mBullets.emplace_back(eType::PLAYER, mPlayer.GetPOS_X(0), mPlayer.GetPOS_Y(0));
		}
	}
}

int GameManager::Run()
{
	CursorView(HIDDEN);

	uint64_t begin = 0;
	uint64_t delta1 = 0;
	uint64_t delta2 = 0;
	uint64_t delta3 = 0;
	uint64_t delta4 = 0;
	uint64_t delta5 = 0;
	bool bChangeDirection = false;

	if (!menu())
	{
		return 0;
	}

	settingGame();
	settingEntities();

	system("mode con:cols=70 lines=30");

	for (int y = 0; y < 30; y++)
	{
		gotoxy(26, y);
		SetColor(WHITE); std::cout << "┃";
	}

	while (!isGameOver())
	{
		begin = GetTickCount64();
		printEntities();
		printINFO();

		delta1 += GetTickCount64() - begin;
		if (delta1 > 30) //bullet
		{
			for (unsigned int i = 0; i < mBullets.size(); i++)
			{
				mBullets[i].Move();
			}
			onCollide();
			delta1 = 0;
		}
		delta2 += GetTickCount64() - begin;
		if (delta2 > 30) //Player
		{
			ControlPlayer();
			delta2 = 0;
		}
		delta3 += GetTickCount64() - begin;
		if (delta3 > 90) //UFO
		{
			if (mbUFOFlag)
			{
				mUFO->Move();
			}
			delta3 = 0;
		}
		delta4 += GetTickCount64() - begin;
		//적의 숫자에 따라 움직이는 속도 조작
		if (mbBossStage) //보스 스테이지
		{
			if (delta4 > 700) //mEnemies
			{

			}
			//보스 잡으면 mbBossStage = false;
		}
		else // 일반 적
		{
			if (delta4 > 200 + (18 * static_cast<uint64_t>(mEnemyCount))) //mEnemies
			{
				if (bChangeDirection)
				{
					for (unsigned int i = 0; i < mEnemyCount; i++)
					{
						mEnemies[i].SetDirection(eDirection::DOWN);
						mEnemies[i].Move();
					}

					if (mEnemyMovement == eDirection::RIGHT)
					{
						mEnemyMovement = eDirection::LEFT;
					}
					else
					{
						mEnemyMovement = eDirection::RIGHT;
					}

					for (unsigned int i = 0; i < mEnemyCount; i++)
					{
						mEnemies[i].SetDirection(mEnemyMovement);
					}
					bChangeDirection = false;
				}
				else
				{
					for (unsigned int i = 0; i < mEnemyCount; i++)
					{
						if (mEnemies[i].Move())
						{
							bChangeDirection = true;
						}
					}
				}

				shootingEnemy();

				delta4 = 0;
			}
		}


		delta5 += GetTickCount64() - begin;
		if (delta5 > 1000)
		{
			mUFOCountDown--;
			if (mUFOCountDown <= 0)
			{
				//UFO의 인자값은 가는 방향을 의미함. LEFT == 오른쪽에서 왼쪽으로.
				if (mPlayer.GetPOS_X(0) < MAP_SIZE / 2)
				{
					mUFO = new UFO(eDirection::LEFT);
				}
				else
				{
					mUFO = new UFO(eDirection::RIGHT);
				}
				mbUFOFlag = true;
			}
			delta5 = 0;
		}

		if (mEnemyCount == 0)	//reset
		{
			settingGame();
			settingEntities();
			mStage++;
			if ((mStage % 5) == 0)
			{
				mbBossStage = true;
				mBoss = new Boss();
			}

		}
	}
	CursorView(SHOW);

//	ResultMenu();

	return 0;
}

void GameManager::onCollide()
{
	std::vector<Bullet>::iterator bullet = mBullets.begin();
	std::vector<Barricade>::iterator barricades;

	bool bCollideCheck = false;
	while (bullet != mBullets.end())
	{
		if (bullet->GetOwner() == eType::PLAYER)
		{
			std::vector<Enemy>::iterator enemies = mEnemies.begin();
			while(enemies != mEnemies.end())
			{
				if (enemies->OnCollide(bullet->GetPOS_X(), bullet->GetPOS_Y()))
				{
					getPoint(enemies->GetType());
					enemies = mEnemies.erase(enemies);
					--mEnemyCount;
					bCollideCheck = true;
					break;
				}
				else
				{
					enemies++;
				}
			}
			if (mbUFOFlag)
			{
				if (mUFO->OnCollide(bullet->GetPOS_X(), bullet->GetPOS_Y()))
				{
					delete mUFO;
					getPoint(eType::UFO);
					mbUFOFlag = false;
					bCollideCheck = true;
				}
			}
			if (mbBossStage)
			{
				if (mBoss->OnCollide(bullet->GetPOS_X(), bullet->GetPOS_Y()))
				{
					if (mBoss->GetHealthPoint() == 0)
					{
						getPoint(eType::BOSS);
						delete mBoss;
						mBoss = nullptr;
					}
				}
			}
		}
		if (bullet->GetOwner() == eType::ENEMY)
		{
			if (mPlayer.OnCollide(bullet->GetPOS_X(), bullet->GetPOS_Y()))
			{
				bCollideCheck = true;
			}
		}
		barricades = mBarricades.begin();
		while (barricades != mBarricades.end())
		{
			if (barricades->OnCollide(bullet->GetPOS_X(), bullet->GetPOS_Y()))
			{
				bCollideCheck = true;
				barricades = mBarricades.erase(barricades);
				break;
			}
			else
			{
				barricades++;
			}
		}
		//총알이 아무것도 맞히지 못했을때.
		if (bullet->GetPOS_Y() > 23 || bullet->GetPOS_Y() < 0)
		{
			bCollideCheck = true;
		}
		//총알 처리
		if (bCollideCheck)
		{
			bullet = mBullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
		bCollideCheck = false;
	}

	//적이 바리케이트를 밀었는지
	for(int i = 0; i < mEnemyCount; i++)
	{
		barricades = mBarricades.begin();
		while (barricades != mBarricades.end())
		{
			if (barricades->OnCollide(mEnemies[i].GetPOS_X(), mEnemies[i].GetPOS_Y()))
			{
				barricades = mBarricades.erase(barricades);
			}
			else
			{
				barricades++;
			}
		}
	}
	if (mbUFOFlag)
	{
		if (mUFO->GetDirection() == eDirection::LEFT)
		{
			if (mUFO->GetPOS_X(0) <= 0)
			{
				delete mUFO;
			}
		}
		else
		{
			if (mUFO->GetPOS_X(2) >= MAP_SIZE -1)
			{
				delete mUFO;
			}
		}
	}
}

void GameManager::getPoint(eType type)
{
	if (type == eType::SQUID)
	{
		mScore += 30;
	}
	if (type == eType::CRAB)
	{
		mScore += 20;
	}
	if (type == eType::OCTOPUS)
	{
		mScore += 10;
	}
	if (type == eType::UFO)
	{
		mScore += 300;
	}
	if (type == eType::BOSS)
	{
		mScore += 1500;
	}
}

bool GameManager::isGameOver() const
{
	if (mPlayer.GetLife() == 0)
	{
		return true;
	}

	for (unsigned int i = 0; i < mEnemyCount; i++)
	{
		if (mEnemies[i].GetPOS_X() == MAP_SIZE - 1 && mEnemies[i].GetPOS_Y() == 20)
		{
			return true;
		}
		if (mEnemies[i].GetPOS_Y() >= 21)
		{
			return true;
		}
	}

	return false;
}

int GameManager::menu()
{
	const int EXIT_GAME = 0;
	const int PLAY_GAME = 1;

	system("mode con:cols=50 lines=30");
	gotoxy(8, 2);
	SetColor(RED); std::cout <<"   ／▤▤＼";
	gotoxy(8, 3);
	SetColor(RED); std::cout <<"   ○####○";

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
	SetColor(SKY_BLUE); std::cout << "SkyLake_ARIS 2020.07.21-2020.09.21";

	int Flag = 1;
	int selection = PLAY_GAME;
	while (1)
	{
		if (Flag == 1)
		{
			gotoxy(7, 22);
			SetColor(RED); std::cout << "  >> PLAY GAME <<  ";
			gotoxy(7, 24);
			SetColor(WHITE); std::cout << "     EXIT GAME     ";
			selection = PLAY_GAME;
		}
		else
		{
			gotoxy(7, 22);
			SetColor(WHITE); std::cout << "     PLAY GAME     ";
			gotoxy(7, 24);
			SetColor(RED); std::cout << "  >> EXIT GAME <<  ";
			selection = EXIT_GAME;
		}

		int key = _getch();

		switch (static_cast<eControlKey>(key))
		{
		case eControlKey::UP:
		case eControlKey::DOWN:
			Flag *= -1;
			break;
		case eControlKey::SPACE:
			return selection;

		default:
			//Assert();
			break;
		}
	}

	return EXIT_GAME;
}

void GameManager::printEntities() const
{
	//플레이어 출력
	PaintColor(mPlayer.GetPOS_Y(0));
	gotoxy(mPlayer.GetPOS_X(0), mPlayer.GetPOS_Y(0));
	std::cout << "A";
	gotoxy(mPlayer.GetPOS_X(1), mPlayer.GetPOS_Y(1));
	std::cout << "〓▤〓";

	//Boss 출력
	if (mbBossStage)
	{
		SetColor(RED); std::cout << "   ／▤▤＼";
		gotoxy(8, 3);
		SetColor(RED); std::cout << "   ○####○";
	}


	//적 타입에 따른 출력
	for (unsigned int i = 0; i < mEnemyCount; i++)
	{
		PaintColor(mEnemies[i].GetPOS_Y());
		gotoxy(mEnemies[i].GetPOS_X(), mEnemies[i].GetPOS_Y());
		switch (mEnemies[i].GetType())
		{
		case eType::SQUID:
			std::cout << "♨";
			break;
		case eType::CRAB:
			std::cout << "ㆄ";
			break;
		case eType::OCTOPUS:
			std::cout << "♧";
			break;
		}
	}
	//바리케이드 출력
	for (unsigned int i = 0; i < mBarricades.size(); i++)
	{
		PaintColor(mBarricades[i].GetPOS_Y());
		gotoxy(mBarricades[i].GetPOS_X(), mBarricades[i].GetPOS_Y());
		std::cout << "▦";
	}
	//UFO 출력
	if (mbUFOFlag)
	{
		gotoxy(mUFO->GetPOS_X(0), mUFO->GetPOS_Y(0)-1);
		PaintColor(mUFO->GetPOS_Y(0));
		std::cout << "／Ａ＼";
		gotoxy(mUFO->GetPOS_X(0), mUFO->GetPOS_Y(0));
		PaintColor(mUFO->GetPOS_Y(0));
		std::cout << "☜♨☞";
	}

	//총알 출력
	unsigned int bulletCount = mBullets.size();
	for (unsigned int i = 0; i < bulletCount; i++)
	{
		PaintColor(14);
		gotoxy(mBullets[i].GetPOS_X(), mBullets[i].GetPOS_Y());
		std::cout << "‡";
	}
}

void GameManager::printINFO() const
{
	gotoxy(30, 10);
	SetColor(BLUE);
	std::cout << "SCORE";
	gotoxy(27, 11);
	std::cout << mScore;

	gotoxy(2, 27);
	SetColor(SKY_BLUE);
	if (mPlayer.GetLife() == 3)
	{
		std::cout << "Life   A  A";
	}
	if (mPlayer.GetLife() == 2)
	{
		std::cout << "Life   A   ";
	}
	if (mPlayer.GetLife() == 1)
	{
		std::cout << "Life       ";
	}
}

void GameManager::shootingEnemy()
{
	int maxY = 0;
	for (int i = 0; i < mEnemyCount; i++)
	{
		Enemy* enemy = &mEnemies[i];
		maxY = mEnemies[i].GetPOS_Y();
		for (int j = i; j < mEnemyCount; j++)
		{
			if (mEnemies[i].GetPOS_X() == mEnemies[j].GetPOS_X())
			{
				if (maxY < mEnemies[j].GetPOS_Y())
				{
					maxY = mEnemies[j].GetPOS_Y();
					enemy = &mEnemies[j];
				}
			}
		}
		switch (enemy->GetType())
		{
		case eType::SQUID:
			if (GetRandomNumber(0, 15) > 12)
			{
				mBullets.emplace_back(eType::ENEMY, enemy->GetPOS_X(), enemy->GetPOS_Y());
			}
			break;
		case eType::CRAB:
			if (GetRandomNumber(0, 15) > 13)
			{
				mBullets.emplace_back(eType::ENEMY, enemy->GetPOS_X(), enemy->GetPOS_Y());
			}
			break;
		case eType::OCTOPUS:
			if (GetRandomNumber(0, 15) == 15)
			{
				mBullets.emplace_back(eType::ENEMY, enemy->GetPOS_X(), enemy->GetPOS_Y());
			}
			break;
		}
	}
}