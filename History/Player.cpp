#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	_x = 0;
	_y = 0;
}

void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}