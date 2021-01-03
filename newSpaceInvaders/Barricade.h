#pragma once
#include "lib.h"

class Barricade
{
public:
	Barricade(int x, int y)
	{
		mPOS.x = x;
		mPOS.y = y;
	}

	bool OnCollide(int x, int y);

	int GetPOS_X() const;

	int GetPOS_Y() const;

private:
	Position mPOS;
};