#include "Barricade.h"

bool Barricade::OnCollide(int x, int y)
{
	if (x == mPOS.x && y == mPOS.y)
	{
		return true;
	}
	return false;
}

int Barricade::GetPOS_X() const
{
	return mPOS.x;
}

int Barricade::GetPOS_Y() const
{
	return mPOS.y;
}