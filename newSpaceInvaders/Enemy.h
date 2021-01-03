#pragma once
#include "lib.h"

class Enemy
{
public:
	Enemy(int x, int y, eType enemyType)
	{
		mPOS.x = x;
		mPOS.y = y;
		mEnemyType = enemyType;
		mMoveDirection = eDirection::RIGHT;
	}

	bool Move();

	bool OnCollide(int x, int y) const;

	void SetDirection(const eDirection dir);

	int GetPOS_X() const;

	int GetPOS_Y() const;

	eType GetType() const;
 
private:
	eType mEnemyType;
	eDirection mMoveDirection;
	Position mPOS;
};