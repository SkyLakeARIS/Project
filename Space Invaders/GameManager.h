#pragma once
#include "Barricade.h"
#include "Enemy.h"
#include "Player.h"
#include "UFO.h"

class GameManager
{
public:
	GameManager() {}

	int PlayGame();
	
	bool GameOver(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::shared_ptr<Barricade> barri);

	void ResultMenu(std::shared_ptr<Player> pplayer) const;
};