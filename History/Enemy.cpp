#include "stdafx.h"
#include "Enemy.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy() {}	

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

void Enemy::randomiseAttributes(char tile) {
	static default_random_engine randEngine((unsigned int)time(NULL));
	int health;
	int attack;
	int defense;
	int level;
	int experience;

	switch (tile){
	case 's':
		health = 5;
		attack = 2;
		defense = 1;
		level = 1;
		experience = 5;
		break;
	
	case 'g':
		health = 10;
		attack = 5;
		defense = 3;
		level = 2;
		experience = 10;
		break;

	case 'B':
		health = 12;
		attack = 6;
		defense = 3;
		level = 2;
		experience = 12;
		break;
		
	case 'O':
		health = 30;
		attack = 15;
		defense = 10;
		level = 3;
		experience = 20;
		break;

	case 'D':
		health = 50;
		attack = 25;
		defense = 20;
		level = 4;
		experience = 30;
		break;
	}

	uniform_int_distribution<int> moveRollHealth((health/2), health);
	uniform_int_distribution<int> moveRollAttack((attack/2), attack);
	uniform_int_distribution<int> moveRollDefense((defense / 2), defense);
	uniform_int_distribution<int> moveRollExperience((experience - (experience / 2)), experience);

	_health = moveRollHealth(randEngine);
	_attack = moveRollAttack(randEngine);
	_defense = moveRollDefense(randEngine);
	_experienceValue = moveRollExperience(randEngine);
	_level = level;
}