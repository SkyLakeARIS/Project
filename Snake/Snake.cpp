#include "Snake.h"

void Snake::setSnakeINFO()
{
    mHeadDirection = eDirection::STOP;
    mBodyLength = 4;

    //πÏ¿« ¡¬«• √ ±‚»≠
    POS setSnakePOS;
    for (unsigned int y = 0; y < mBodyLength; y++)
    {
        setSnakePOS.x = 5;
        setSnakePOS.y = 4 + y;
        mSnake.push_back(setSnakePOS);
    }
    //vector snakeø° x,y∞™¿ª ¥„¿∫ setting_pos∏¶ ¥„æ∆¡‹.
    mHeadDirection = eDirection::STOP;
}

void Snake::MoveSnake()
{
    //if (_kbhit() == true && _getch() == 224)
    //{
    //    mHeadDirection = static_cast<eDirection>(_getch());
    //} 

    //if (_kbhit() && _getwch() == 224)
    //{
    //    eDirection changeDirection = static_cast<eDirection>(_getwch());
    //    if (!isWrongMove(changeDirection))
    //    {
    //        mHeadDirection = changeDirection;
    //    }
    //}
    eDirection changeDirection = eDirection::STOP;

    if (GetAsyncKeyState(VK_UP))
    {
        changeDirection = eDirection::UP;
    }

    if (GetAsyncKeyState(VK_DOWN))
    {
        changeDirection = eDirection::DOWN;
    }

    if (GetAsyncKeyState(VK_LEFT))
    {
        changeDirection = eDirection::LEFT;
    }

    if (GetAsyncKeyState(VK_RIGHT))
    {
        changeDirection = eDirection::RIGHT;
    }

    if (changeDirection != eDirection::STOP && !isWrongMove(changeDirection))
    {
        mHeadDirection = changeDirection;
    }

    if (mHeadDirection != eDirection::STOP)
    {
        removeFootPrint(mSnake.back().x, mSnake.back().y);

        for (unsigned int body = mBodyLength-1; body > 0; body--)
        {
            mSnake[body] = mSnake[body - 1];
        }
        switch (mHeadDirection)
        {
        case eDirection::UP:
            --mSnake[0].y;
            break;
        case eDirection::DOWN:
            ++mSnake[0].y;
            break;
        case eDirection::LEFT:
            --mSnake[0].x;
            break;
        case eDirection::RIGHT:
            ++mSnake[0].x;
            break;
        default:
            //Assert
            break;
        }
    }
}

bool Snake::isWrongMove(eDirection changeDir) const
{
    if ((mHeadDirection == eDirection::UP && changeDir == eDirection::DOWN) || (mHeadDirection == eDirection::DOWN && changeDir == eDirection::UP))
    {
        return true;
    }
    if ((mHeadDirection == eDirection::LEFT && changeDir == eDirection::RIGHT) || (mHeadDirection == eDirection::RIGHT && changeDir == eDirection::LEFT))
    {
        return true;
    }
    if (mHeadDirection == eDirection::STOP && changeDir == eDirection::DOWN)
    {
        return true;
    }

    return false;
}

bool Snake::CheckCollision() const
{
    if (mSnake[0].x < 0 || mSnake[0].x >= MAPSIZE)
    {
        gotoxy(9, 19);
        std::cout << "¡◊æ˙Ω¿¥œ¥Ÿ. ªÁ¿Ø: ∫Æø° ∫Œµ˙»˚.";
        return true;
    }
    if (mSnake[0].y < 0 || mSnake[0].y >= MAPSIZE)
    {
        gotoxy(9, 19);
        std::cout << "¡◊æ˙Ω¿¥œ¥Ÿ. ªÁ¿Ø: ∫Æø° ∫Œµ˙»˚.";
        return true;
    }
    for (unsigned int body = 1; body < mBodyLength; body++)
    {
        if (mSnake[0].x == mSnake[body].x && mSnake[0].y == mSnake[body].y)
        {
            gotoxy(9, 19);
            std::cout << "¡◊æ˙Ω¿¥œ¥Ÿ. ªÁ¿Ø: ∏ˆø° ∫Œµ˙»˚.";
            return true;
        }
    }
    return false;
}

bool Snake::EatFeed(Feed& feed)
{
    if (feed.GetFeedPOS_X() == mSnake.front().x && feed.GetFeedPOS_Y() == mSnake.front().y)
    {
        addSnakeBody();
        return true;
    }
    return false;
}

void Snake::addSnakeBody()
{
    POS newBody = mSnake.back();
    mSnake.push_back(newBody);
    ++mBodyLength;
}

int Snake::GetHeadPOS_X() const
{
    return mSnake[0].x;
}

int Snake::GetHeadPOS_Y() const
{
    return mSnake[0].y;
}

int Snake::GetSnakePOS_X(unsigned int index) const
{
    return mSnake[index].x;
}

int Snake::GetSnakePOS_Y(unsigned int index) const
{
    return mSnake[index].y;
}

unsigned int Snake::GetSnakeLength() const
{
    return mBodyLength;
}