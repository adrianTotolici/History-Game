#pragma once
#include <string>

using namespace std;

class Units
{
public:
	Units();

	void init();
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);
	void setName(string name);
	string getName();
	void setTile(char tile);
	char getTile();
	int getLevel();
	int getDefense();
	int getHealth();
	int getAttack();

	string _name;
	int _level;
	int _health;
	int _attack;
	int _defense;
	char _tile;

	int _x;
	int _y;
};