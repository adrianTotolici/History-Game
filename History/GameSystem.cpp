#include "stdafx.h"
#include "GameSystem.h"
#include <conio.h>


GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);
	_level.load(levelFileName, _player);
}

void GameSystem::playGame() {
	bool isDone = false;

	while (isDone != true)
	{
		_level.print();
		playerMove();
	}
}

void GameSystem::playerMove() {
	char input;
	input = _getch();
	_level.movePlayer(input, _player);
}