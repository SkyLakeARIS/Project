#pragma once
#include "lib.h"

#define BODY_SIZE (10)

class Boss
{
public:
	Boss()
	{
		mDirection = eDirection::LEFT;
		mbIsBorder = false;
		mHealthPoint = 5000;
	}
	void Move();

	bool OnCollide(int x, int y);

	const Position* GetPOS() const;

	int GetHealthPoint() const;

private:

	void switchDirection();

private:
	Position mPOS[BODY_SIZE];
	eDirection mDirection;
	int mHealthPoint;
	bool mbIsBorder;
};