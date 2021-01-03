#pragma once
#include "GameManager.h"

class UI
{
public:
	UI()
	{
		mFlag = 1;
	}

	enum eControl
	{
		UP = 72,
		DOWN = 80,
		SPACE = 32
	};

	enum eMenuSelection
	{
		PlayGame = 1,
		ExitGame = 0
	};

	int Menu();
	
	void PrintMap() const;
	
	void PrintInfo() const;
	
	void RUN();

private:
	int mFlag;
	eMenuSelection mSelection;
	GameManager mGM;
};