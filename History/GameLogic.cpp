#include "stdafx.h"
#include "GameLogic.h"

GameLogic::GameLogic() {
	_player.init(1, 100, 20, 10);
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

			switch (tile) {
			case '@': //Player
				_player.setPosition(j, i);
				break;
			case 's': //snake
				_enemies.push_back(Enemy(10));
				_enemies.back().init(1, 2, 1, 10);
				_enemies.back().setName("Snake");
				_enemies.back().setTile(tile);
				_enemies.back().setPosition(j, i);
				break;
			case 'g': //goblin
				_enemies.push_back(Enemy(10));
				_enemies.back().init(1, 2, 1, 10);
				_enemies.back().setName("Goblin");
				_enemies.back().setTile(tile);
				_enemies.back().setPosition(j, i);
				break;
			case 'B': //bandit
				_enemies.push_back(Enemy(10));
				_enemies.back().init(1, 2, 1, 10);
				_enemies.back().setName("Bandit");
				_enemies.back().setTile(tile);
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //Ogre
				_enemies.push_back(Enemy(10));
				_enemies.back().init(1, 2, 1, 10);
				_enemies.back().setName("Ogre");
				_enemies.back().setTile(tile);
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //Dragon
				_enemies.push_back(Enemy(10));
				_enemies.back().init(1, 2, 1, 10);
				_enemies.back().setName("Dragon");
				_enemies.back().setTile(tile);
				_enemies.back().setPosition(j, i);
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
		printf("You have won !");
		system("PAUSE");
		exit(0);
	}
}
