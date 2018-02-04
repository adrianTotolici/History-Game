#pragma once
#include <string>
#include "Player.h"
#include "Level.h"

using namespace std;

class GameSystem
{
public:
	GameSystem(string levelFileName);

	void playGame();
	void playerMove();

private:
	Player _player;
	Level _level;
};