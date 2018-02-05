#include "stdafx.h"
#include "Enemy.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy(int xp)
{
	_experienceValue = xp;
}	

int Enemy::attack() {
	static default_random_engine randomEngine((unsigned int)time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;
		//check if he died;
		if (_health <= 0) {
			return _experienceValue;
		}
	}

	printf("Enemy life %d \n", _health);

	return 0;
}

char Enemy::getMove(int playerX, int playerY) {
	static default_random_engine randEngine((unsigned int)time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);

	int distance;
	int dx = _x - playerX;
	int dy = _y -playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	distance = adx+ady;
	if (distance < 5) {
		if (adx > ady) {
			if (dx > 0) {
				return 'a';
			} else {
				return 'd';
			}
		} else {
			if (dy > 0) {
				return 'w';
			} else {
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}
}