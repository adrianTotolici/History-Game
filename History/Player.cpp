#include "stdafx.h"
#include "Player.h"
#include <random>
#include <ctime>

using namespace std;


Player::Player()
{
	_x = 0;
	_y = 0;
}

int Player::getExperience() {
	return _experience;
}

void Player::addExperience(int experience) {
	_experience += experience;

	// level up
	while (_experience > 50) {
		printf("Leveled Up!\n");
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health += 10;
		_level++;
		system("PAUSE");
	}
}

void Player::addHealth(char item) {
	switch (item){
	case 'o':
		_health += 5;
		break;
	}
}

int Player::attack() {
	static default_random_engine randomEngine((unsigned int) time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;
		//check if he died;
		if (_health <= 0) {
			return 1;
		}
	}
	return 0;
}