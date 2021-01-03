#include "Player.h"

void Player::initializePOS()
{
	mBody.emplace_back(12, 22);
	for (int x = 0; x < 3; x++)
	{
		mBody.emplace_back(11 + x, 23);
	}
}

bool Player::Move(eDirection dir)
{
	if (dir == eDirection::LEFT && mBody[1].x > 0)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			RemoveFootPrint(mBody[i].x, mBody[i].y);
			mBody[i].x--;
		}
	}
	if (dir == eDirection::RIGHT && mBody[3].x < MAP_SIZE-1)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			RemoveFootPrint(mBody[i].x, mBody[i].y);
			mBody[i].x++;
		}
	}

	return false;
}

bool Player::OnCollide(int x, int y)
{
	unsigned int bodySize = mBody.size();
	for (unsigned int i = 0;  i < bodySize; i++)
	{
		if (x == mBody[i].x && y == mBody[i].y)
		{
			--mLife;
			unsigned int bodySize = mBody.size();
			for (unsigned int i = 0; i < bodySize; i++)
			{
				RemoveFootPrint(mBody[i].x, mBody[i].y);
			}
			initializePOS();

			PaintColor(mBody[0].y);
			gotoxy(mBody[0].x, mBody[0].y);
			std::cout << "A";
			gotoxy(mBody[1].x, mBody[1].y);
			std::cout << "быв╟бы";

			return true;
		}
	}
	return false;
}

int Player::GetPOS_X(unsigned int index) const
{
	return mBody[index].x;
}

int Player::GetPOS_Y(unsigned int index) const
{
	return mBody[index].y;
}

unsigned int Player::GetLife() const
{
	return mLife;
}