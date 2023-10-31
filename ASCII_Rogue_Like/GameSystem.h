#pragma once

#include "Level.h"
#include "Player.h"

class GameSystem
{
public:
	GameSystem();

	void playGame();

private:

	Level _level;
	Player _player;

};

