#include "stdafx.h"
#include "Units.h"
#include <string>


Units::Units(){}

void Units::init() {}

void Units::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Units::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

void Units::setName(string name) {
	_name = name;
}

string Units::getName() {
	return _name;
}

void Units::setTile(char tile) {
	_tile = tile;
}

char Units::getTile() {
	return _tile;
}

int Units::getLevel() {
	return _level;
}

int Units::getDefense() {
	return _defense;
}

int Units::getHealth() {
	return _health;
}

int Units::getAttack() {
	return _attack;
}