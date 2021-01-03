#include "UFO.h"


void UFO::Move()
{
	if (mMoveDirection == eDirection::RIGHT)
	{
		for (unsigned int i = 0; i < 6; i++)
		{
			RemoveFootPrint(mBody[i].x, mBody[i].y);
			++mBody[i].x;
		}
	}
	if (mMoveDirection == eDirection::LEFT)
	{
		for (unsigned int i = 0; i < 6; i++)
		{
			RemoveFootPrint(mBody[i].x, mBody[i].y);
			--mBody[i].x;
		}
	}
}

bool UFO::OnCollide(int x, int y)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (x == mBody[i].x && y == mBody[i].y)
		{
			for (unsigned int j = 0; j < 6; j++)
			{
				RemoveFootPrint(mBody[j].x, mBody[j].y);
			}
			return true;
		}
	}
	return false;
}

int UFO::GetPOS_X(unsigned int index) const
{
	return mBody[index].x;
}

int UFO::GetPOS_Y(unsigned int index) const
{
	return mBody[index].y;
}

eDirection UFO::GetDirection() const
{
	return mMoveDirection;
}
