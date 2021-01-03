#pragma once
#include "lib.h"

class Bullet
{
public:
	Bullet()
	{
		mPOS.x = 0;
		mPOS.y = 0;
		mOwner = eType::UNKNOWN;
	}
	Bullet(eType owner, int x, int y)
	{
		mPOS.x = x;
		mPOS.y = y;
		mOwner = owner;
	}

	void Move();

	eType GetOwner() const;

	int GetPOS_X() const;

	int GetPOS_Y() const;

private:
	Position mPOS;
	eType mOwner;
};

