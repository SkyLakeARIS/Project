#pragma once
#include "lib.h"

class UFO
{
public:
	UFO(eDirection dir)
	{
		if (dir == eDirection::LEFT)
		{
			for (int i = 0; i < 3; i++)
			{
				mBody.emplace_back(22 + i, 1);
			}
		}
		if(dir == eDirection::RIGHT)
		{
			for (int i = 0; i < 3; i++)
			{
				mBody.emplace_back(0 + i, 1);
			}
		}
		mMoveDirection = dir;
	}

	void Move();

	bool OnCollide(int x, int y);

	int GetPOS_X(unsigned int index) const;

	int GetPOS_Y(unsigned int index) const;

	eDirection GetDirection() const;

private:
	std::vector<Position> mBody;
	eDirection mMoveDirection;
};