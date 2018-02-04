#pragma once
#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);

	void setPosition(int x, int y);
	void getPosition(int &x, int &y);
	void getName(string &name);

	int attack();
	int takeDamage(int attack);
private:
	string _name;
	char _tile;

	int _attack;
	int _defense;
	int _health;
	int _level;
	int _experienceValue;

	int _x;
	int _y;
};
