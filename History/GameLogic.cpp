#include "stdafx.h"
#include "GameLogic.h"

GameLogic::GameLogic() {
	_player.init();
	//to be added when player load custom map
	//_level.load("C:\\game-proj\\History\\History\\Level\\level1.txt");
	_level.loadRandomMap();
	procesLevel();
	printLevel();

}

void GameLogic::playerMove() {
	char input;
	input = _getch();
	movePlayer(input, _player);
}

void GameLogic::printLevel() {
	_uiLogica.setScreen1(_level._levelData);
	stringstream logPlayer1;
	stringstream logPlayer2;

	// Player Name: ----- Level: ---- Experience: ----
	// Attack: ----- Defense: -----  Health: ----
	logPlayer1.str(std::string());
	logPlayer1 << "Name: " << _player.getName() << " Level: " << _player.getLevel() << " Experience: " << _player.getExperience();
	logPlayer2 << "Attack: " << _player.getAttack() << " Defense: "  << _player.getDefense() << " Health: " << _player.getHealth();
	_uiLogica.updatePlayerStatus(logPlayer1.str(), logPlayer2.str());
	_uiLogica.print();
}

void GameLogic::updateEnemies() {
	char aiMove;
	int playerX, playerY;
	int enemyX, enemyY;

	_player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++) {
		rangeView(_enemies[i]);
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

			switch (aiMove) {
			case 'w':
				processEnemyMove(_player, i, enemyX, enemyY - 1);
				break;
			case 's':
				processEnemyMove(_player, i, enemyX, enemyY + 1);
				break;
			case 'a':
				processEnemyMove(_player, i, enemyX - 1, enemyY);
				break;
			case 'd':
				processEnemyMove(_player, i, enemyX + 1, enemyY);
				break;
			}
	}
}

void GameLogic::movePlayer(char input, Player &player) {
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

void GameLogic::battleEnemy(Player &player, int targetX, int targetY) {
	int enemyX, enemyY;
	int playerX, playerY;
	int attackRoll;
	int attackResult;
	string enemyName;
	stringstream log;
	stringstream logPlayer1, logPlayer2;

	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY) {
			//Battle
			//Player attack;
			attackRoll = player.attack();
			log.str(std::string());
			log << _player.getName() << " attacked " << enemyName.c_str() << " whit roll of " << attackRoll;
			_uiLogica.updateBattleLog(log.str());
			attackResult = _enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				_level.setTile(targetX, targetY, '.');
				log.str(std::string());
				log << enemyName << " died !";
				_uiLogica.updateBattleLog(log.str());
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				player.addExperience(attackResult);

				// Player Name: ----- Level: ---- Experience: ----
				// Attack: ----- Defense: -----  Health: ----
				logPlayer1.str(std::string());
				logPlayer1 << "Name: " << _player.getName() << " Level: " << _player.getLevel() << " Experience: " << _player.getExperience();
				logPlayer2 << "\n" << "Attack: " << _player.getAttack() << " Defense: " << _player.getDefense() << " Health: " << _player.getHealth();
				_uiLogica.updatePlayerStatus(logPlayer1.str(), logPlayer2.str());

				return;
			}
			//Enemy attack
			attackRoll = _enemies[i].attack();
			log.str(std::string());
			log << enemyName << " attacked " << _player.getName() << " whit roll of " << attackRoll;
			_uiLogica.updateBattleLog(log.str());
			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {
				_level.setTile(playerX, playerY, 'x');
				_uiLogica.updateBattleLog("You died!");
				system("PAUSE");
				exit(0);
			}

			// Player Name: ----- Level: ---- Experience: ----
			// Attack: ----- Defense: -----  Health: ----
			logPlayer1.str(std::string());
			logPlayer1 << "Name: " << _player.getName() << " Level: " << _player.getLevel() << " Experience: " << _player.getExperience();
			logPlayer2 << "\n" << "Attack: " << _player.getAttack() << " Defense: " << _player.getDefense() << " Health: " << _player.getHealth();
			_uiLogica.updatePlayerStatus(logPlayer1.str(), logPlayer2.str());
			return;
		}
	}
}

void GameLogic::procesLevel() {
	char tile;
	for (size_t i = 0; i < _level._levelData.size(); i++) {
		for (size_t j = 0; j <_level._levelData[i].size(); j++) {
			tile = _level._levelData[i][j];
			Enemy enemy;
			switch (tile) {
			case '@': //Player
				_player.setPosition(j, i);
				break;
			case 's': //snake
				enemy.randomiseAttributes('s');
				enemy.setName("Snake");
				enemy.setTile(tile);
				enemy.setPosition(j, i);
				_enemies.push_back(enemy);
				break;
			case 'g': //goblin			
				enemy.randomiseAttributes('g');
				enemy.setName("Goblin");
				enemy.setTile(tile);
				enemy.setPosition(j, i);
				_enemies.push_back(enemy);
				break;
			case 'B': //bandit		
				enemy.randomiseAttributes('B');
				enemy.setName("Bandit");
				enemy.setTile(tile);
				enemy.setPosition(j, i);
				_enemies.push_back(enemy);
				break;
			case 'O': //Ogre				
				enemy.randomiseAttributes('O');
				enemy.setName("Ogre");
				enemy.setTile(tile);
				enemy.setPosition(j, i);
				_enemies.push_back(enemy);
				break;
			case 'D': //Dragon		
				enemy.randomiseAttributes('D');
				enemy.setName("Dragon");
				enemy.setTile(tile);
				enemy.setPosition(j, i);
				_enemies.push_back(enemy);
				break;
			}
		}
	}
}

void GameLogic::processPlayerMove(Player &player, int targetX, int targetY) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);
	char moveTile = _level.getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		_level.setTile(playerX, playerY, '.');
		_level.setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case 'o':
		_player.addHealth('o');
		_level.setTile(targetX, targetY, '.');
		break;
	case '*':
		system("cls");
		printf("You have found the Artefact, You have won !");
		system("PAUSE");
	default:
		battleEnemy(player, targetX, targetY);
	}
}

void GameLogic::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
	int playerX, playerY;
	int enemyX, enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);
	char moveTile = _level.getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		_level.setTile(enemyX, enemyY, '.');
		_level.setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void GameLogic::verifyIfGameEnds() {
	if (_enemies.size() < 1) {
		system("cls");
		printf("All enemy Have been defeted, You have won !");
		system("PAUSE");
	}
}

void GameLogic::rangeView(Enemy units) {
	int xr_range, xl_range, yu_range, yd_range;

	if (units._x < 5) {
		xr_range = units._x;
	} else {
		xr_range = 5;
	}

	if ((units._x + 5) > _level._levelData[0].size()) {
		xl_range = _level._levelData[0].size();
	} else {
		xl_range = 5;
	}

	if (units._y < 5) {
		yu_range = units._y-1;
	} else {
		yu_range = 5;
	}

	if ((units._y + 5) > _level._levelData.size()) {
		yd_range = _level._levelData.size();
	} else {
		yd_range = 5;
	}
		for (int i = units._y; i<yu_range; i--) {
			if (_level._levelData[i].at(units._x) == '#') {
				units.setYu(false);
			} else {
				units.setYu(true);
			}
		}

		for (int i = units._x; i < xr_range; i++) {
			if (_level._levelData[units._y].at(i) == '#') {
				units.setXr(false);
			} else {
				units.setXr(true);
			}
		}

		for (int i = units._y; i > yd_range; i++) {
			if (_level._levelData[i].at(units._x) == '#') {
				units.setYd(false);
			} else {
				units.setYd(true);
			}
		}

		for (int i = units._x; i > xl_range; i--) {
			if (_level._levelData[units._y].at(i) == '#') {
				units.setXr(false);
			} else {
				units.setXr(true);
			}
		}
}