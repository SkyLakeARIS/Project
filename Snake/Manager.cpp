#include "Manager.h"

void Manager::Run()
{
    Snake snake;
    Feed feed;
    uint64_t begin = 0;
    uint64_t delta = 0;

    printMap();
    printScreen(snake, feed);
    CursorView(eCursorView::HIDDEN);
    while (!isGameOver(snake))
    {
        begin = GetTickCount64();
        if (delta >= mSpeed)
        {
            snake.MoveSnake();
            generateFeed(snake, feed);

            controlGameSpeed();

            delta = 0;
        }

        printScreen(snake, feed);

        delta += GetTickCount64() - begin;
    }
    CursorView(eCursorView::SHOW);
}

void Manager::generateFeed(Snake& snake, Feed& feed) 
{
    if (snake.EatFeed(feed))
    {
        mScore += 100;

        bool isGenerateSuccess = SUCCESS;
        do {
            feed.SetFeed();
            isGenerateSuccess = SUCCESS;

            for (unsigned int index = 0; index < snake.GetSnakeLength(); index++)
            {
                if (index == 0)
                {
                    if (snake.GetHeadPOS_X() == feed.GetFeedPOS_X() && snake.GetHeadPOS_Y() == feed.GetFeedPOS_Y())
                    {
                        isGenerateSuccess = FAIL;
                    }
                }
                else
                {
                    if (snake.GetSnakePOS_X(index) == feed.GetFeedPOS_X() && snake.GetSnakePOS_Y(index) == feed.GetFeedPOS_Y())
                    {
                        isGenerateSuccess = FAIL;
                    }
                }
            }
        } while (!isGenerateSuccess);
    }
}

bool Manager::isGameOver(Snake& snake) const
{
    if (snake.CheckCollision())
    {
        return true;
    }

    return false;
}
void Manager::controlGameSpeed()
{
    switch (mScore)
    {
    case 1000:
        mSpeed = 800;
        break;
    case 1500:
        mSpeed = 700;
        break;
    case 2000:
        mSpeed = 600;
        break;
    }
}

void Manager::printMap() const
{
    for (int i = 0; i < 13; i++)
    {
        gotoxy(8, 3 + i);
        std::cout << "■";
        gotoxy(9 + i, 15);
        std::cout << "■";
        gotoxy(21, 2 + i);
        std::cout << "■";
        gotoxy(8 + i, 2);
        std::cout << "■";
    }
}
void Manager::printScreen(Snake& snake, Feed& feed) const
{
    gotoxy(9 + feed.GetFeedPOS_X(), 3 + feed.GetFeedPOS_Y());
    std::cout << "&";

    for (unsigned int index = 0; index < snake.GetSnakeLength(); index++)
    {
        if (index == 0)
        {
            gotoxy(9 + snake.GetHeadPOS_X(), 3 + snake.GetHeadPOS_Y());
            std::cout << "□";
        }
        else
        {
            gotoxy(9 + snake.GetSnakePOS_X(index), 3 + snake.GetSnakePOS_Y(index));
            std::cout << "■";
        }
    }
    gotoxy(9, 16);
    std::cout << "현재 점수 : " << mScore << "점";
}