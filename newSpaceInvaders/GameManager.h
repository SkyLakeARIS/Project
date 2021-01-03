#pragma once
#include "Barricade.h"
#include "Bullet.h"
#include "Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "UFO.h"

#include<map>
class GameManager
{
private:

	enum eCursorView
	{
		HIDDEN,
		SHOW
	};

public:

	int Run();

private:

	void settingGame();

	void settingEntities();

	int menu();

	void onCollide();
	
	bool isGameOver() const;
	
	void ControlPlayer();

	void printEntities() const;

	void printINFO() const;
	
	void shootingEnemy();

	void getPoint(eType type);

private:
	std::vector<Enemy> mEnemies;
	std::vector<Bullet> mBullets;
	std::vector<Barricade> mBarricades;
	Player mPlayer;
	UFO* mUFO;
	Boss* mBoss;
	eDirection mEnemyMovement;
	unsigned int mEnemyCount;
	unsigned int mScore;
	unsigned int mStage;
	bool mbBossStage;
	bool mbUFOFlag;
	int mUFOCountDown;
};