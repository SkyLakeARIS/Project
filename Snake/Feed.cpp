#include <ctime>
#include "Feed.h"

void Feed::SetFeed()
{
	srand((unsigned int)time(NULL));

    mX = rand() % MAPSIZE;
    mY = rand() % MAPSIZE;
}

int Feed::GetFeedPOS_X() const
{
    return mX;
}

int Feed::GetFeedPOS_Y() const
{
    return mY;
}