#include "stdafx.h"
#include "Enemy.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;


Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = xp;
}

void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

void Enemy::getName(string &name) {
	name = _name;
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
	return 0;
}