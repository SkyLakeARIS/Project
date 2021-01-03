#pragma once
#include "lib.h"

class Player
{
public:
	Player()
	{
		initializePOS();
		mLife = 3;
	}

	bool Move(eDirection dir);

	bool OnCollide(int x, int y);

	int GetPOS_X(unsigned int index) const;

	int GetPOS_Y(unsigned int index) const;

	unsigned int GetLife() const;

private:

	void initializePOS();

private:
	std::vector<Position> mBody;
	unsigned int mLife;
};