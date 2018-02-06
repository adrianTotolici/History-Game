#pragma once
#include "stdafx.h"
#include <string>
#include "Player.h"
#include "Level.h"
#include <vector>
#include "Enemy.h"
#include <conio.h>
#include "UiLogic.h"

using namespace std;

class GameLogic
{
public:
	GameLogic();

	void playerMove();
	void printLevel();
	void updateEnemies();

private:
	Player _player;
	Level _level;
	vector <Enemy> _enemies;
	UiLogic _uiLogica;


	void battleEnemy(Player &player, int targetX, int targetY);
	void movePlayer(char input, Player &player);
	void procesLevel();
	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
};

