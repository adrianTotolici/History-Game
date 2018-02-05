#include "stdafx.h"
#include "GameSystem.h"
#include <conio.h>


GameSystem::GameSystem(){}

void GameSystem::playGame() {
	bool isDone = false;
	GameLogic gameLogic;

	while (isDone != true)
	{
		gameLogic.printLevel();
		gameLogic.playerMove();
		gameLogic.updateEnemies();
	}
}

