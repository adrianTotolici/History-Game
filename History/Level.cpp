#include "stdafx.h"
#include "Level.h"
#include <fstream>


Level::Level()
{
}

void Level::load(string fileName, Player &player) {
	fstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;
	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	char tile;
	for (int i = 0; i<_levelData.size(); i++) {
		for (int j = 0; j<_levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			}
		}
	}
}

void Level::print() {
	system("cls");
	for (int i = 0; i <_levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	switch (input) {
	case 'w':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid input !");
		system("PAUSE");
		break;
	}
}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	}
}