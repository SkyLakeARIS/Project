#pragma once
#include <conio.h>
#include <vector>
#include "Feed.h"

class Snake
{
private:

    enum class eDirection
    {
        LEFT = 75,
        RIGHT = 77,
        UP = 72,
        DOWN = 80,
        STOP = 0
    };

    struct POS
    {
        int x;
        int y;
    };

public:
    Snake()
    {
        setSnakeINFO();
    }

    void MoveSnake();

    bool EatFeed(Feed& feed);

    bool CheckCollision() const;

    int GetHeadPOS_X() const;

    int GetHeadPOS_Y() const;

    int GetSnakePOS_X(unsigned int index) const;

    int GetSnakePOS_Y(unsigned int index) const;

    unsigned int GetSnakeLength() const;

private:

    void setSnakeINFO();

    void addSnakeBody();

    bool isWrongMove(eDirection changeDir) const;

private:
    eDirection mHeadDirection;
    std::vector<POS> mSnake;
    unsigned int mBodyLength;
};