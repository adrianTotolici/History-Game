#pragma once
#include <string>
#include "Units.h"

using namespace std;

class Enemy : public Units
{
public:
	Enemy();

	int attack();
	int takeDamage(int attack);
	char getMove(int playerX, int playerY);
	void randomiseAttributes(char c);

private:
	int _experienceValue;
};

