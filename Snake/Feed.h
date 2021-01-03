#pragma once
#include "lib.h"

class Feed
{
public:

	Feed()
	{
		mX = 2;
		mY = 2;
	}

	void SetFeed();

	int GetFeedPOS_X() const;

	int GetFeedPOS_Y() const;

private:
	int mX;
	int mY;
};