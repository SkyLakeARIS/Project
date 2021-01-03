#include "Bullet.h"


void Bullet::Move()
{
	RemoveFootPrint(mPOS.x, mPOS.y);
	if (mOwner == eType::PLAYER)
	{
		--mPOS.y;
	}
	if (mOwner == eType::ENEMY)
	{
		++mPOS.y;
	}
}

eType Bullet::GetOwner() const
{
	return mOwner;
}

int Bullet::GetPOS_X() const
{
	return mPOS.x;
}

int Bullet::GetPOS_Y() const
{
	return mPOS.y;
}