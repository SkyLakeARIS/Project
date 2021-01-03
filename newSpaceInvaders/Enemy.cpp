#include "Enemy.h"

bool Enemy::Move()
{
	RemoveFootPrint(mPOS.x, mPOS.y);
	if (mMoveDirection == eDirection::LEFT)
	{
		mPOS.x--;
	}
	if (mMoveDirection == eDirection::RIGHT)
	{
		mPOS.x++;
	}
	if (mMoveDirection == eDirection::DOWN)
	{
		mPOS.y++;
	}

	if (mPOS.x == 0 || mPOS.x == MAP_SIZE - 1)
	{
		return true;
	}

	return false;
}

bool Enemy::OnCollide(int x, int y) const
{
	if (x == mPOS.x && y == mPOS.y)
	{
		RemoveFootPrint(mPOS.x, mPOS.y);
		return true;
	}
	return false;
}

void Enemy::SetDirection(const eDirection dir)
{
	mMoveDirection = dir;
}

int Enemy::GetPOS_X() const
{
	return mPOS.x;
}

int Enemy::GetPOS_Y() const
{
	return mPOS.y;
}

eType Enemy::GetType() const
{
	return mEnemyType;
}