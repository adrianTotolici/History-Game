#include "stdafx.h"
#include "Level.h"
#include "Enemy.h"
#include <fstream>


Level::Level()
{
}

void Level::load(string fileName, Player &player) {
	fstream file;

	//Load level from file
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


	//Proccess level
	char tile;
	for (size_t i = 0; i < _levelData.size(); i++) {
		for (size_t j = 0; j <_levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@': //Player
				player.setPosition(j, i);
				break;
			case 's': //snake
				_enemies.push_back(Enemy("Snake",tile,1,2,1,10,10));
				_enemies.back().setPosition(j, i);
				break;
			case 'g': //goblin
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 15));
				_enemies.back().setPosition(j, i);
				break;
			case 'B': //bandit
				_enemies.push_back(Enemy("Banidit", tile, 3, 25, 10, 20, 20));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //Ogre
				_enemies.push_back(Enemy("Ogre", tile, 5, 20, 35, 50, 30));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //Dragon
				_enemies.push_back(Enemy("Dragon", tile, 10, 35, 50, 100, 70));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}

void Level::print() {
	system("cls");
	for (size_t i = 0; i < _levelData.size(); i++) {
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

void Level::updateEnemies(Player &player) {
	char aiMove;
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX,playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) {
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			processEnemyMove(player, i ,enemyX + 1, enemyY);
			break;
		}
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
	case '#':
		break;
	default:
		battleEnemy(player, targetX, targetY);
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
	int playerX, playerY;
	int enemyX, enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::battleEnemy(Player &player, int targetX, int targetY) {
	int enemyX, enemyY;
	int playerX, playerY;
	int attackRoll;
	int attackResult;
	string enemyName;

	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		_enemies[i].getName(enemyName);
		if (targetX == enemyX && targetY == enemyY) {
			//Battle
			//Player attack;
			attackRoll = player.attack();
			printf("Player attacked %s whit roll of %d \n",enemyName.c_str(),attackRoll);
			attackResult=_enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("%s died!\n",enemyName.c_str());
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				system("PAUSE");
				player.addExperience(attackResult);
				
				return;
			}
			//Enemy attack
			attackRoll = _enemies[i].attack();
			printf("%s attacked player whit roll of %d \n",enemyName.c_str(), attackRoll);
			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print();
				printf("You died!\n");
				system("PAUSE");

				exit(0);
			}
			system("PAUSE");
			return;
		}
	}
}