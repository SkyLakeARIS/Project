#include "Boss.h"

bool Boss::OnCollide(int x, int y)
{
	for (int i = 0; i < BODY_SIZE; i++)
	{
		if (x == mPOS[i].x && y == mPOS[i].y)
		{
			mHealthPoint -= 100;
			return true;
		}
	}
	return false;
}

void Boss::Move()
{
	for (int i = 0; i < BODY_SIZE; i++)
	{
		if (mDirection == eDirection::LEFT)
		{
			mPOS[i].x--;
		}
		else
		{
			mPOS[i].x++;
		}
		if (mPOS[i].x <= 0 || mPOS[i].x >= (MAP_SIZE-1))
		{
			mbIsBorder = true;
		}
	}

	if (mbIsBorder)
	{
		switchDirection();
		mbIsBorder = false;
	}
}

void Boss::switchDirection()
{
	if (mDirection == eDirection::LEFT)
	{
		mDirection = eDirection::RIGHT;
	}
	else
	{
		mDirection = eDirection::LEFT;
	}
}

const Position* Boss::GetPOS() const
{
	return mPOS;
}

int Boss::GetHealthPoint() const
{
	return mHealthPoint;
}