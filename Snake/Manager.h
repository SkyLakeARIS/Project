#pragma once
#include "Snake.h"

class Manager
{
public:
	Manager()
	{
		mScore = 0;
		mSpeed = 1000;
	}

	void Run();

private:

	void generateFeed(Snake& snake, Feed& feed);

	bool isGameOver(Snake& snake) const;

	void controlGameSpeed();

	void printMap() const;

	void printScreen(Snake& snake, Feed& feed) const;

private:
	unsigned int mSpeed;
	unsigned int mScore;
};