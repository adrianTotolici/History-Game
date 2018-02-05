#pragma once
#include <string>
#include "Units.h"

using namespace std;

class Enemy : public Units
{
public:
	Enemy(int xp);

	int attack();
	int takeDamage(int attack);
	char getMove(int playerX, int playerY);

private:
	int _experienceValue;
};

