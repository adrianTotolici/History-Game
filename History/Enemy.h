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

	void setXl(bool xl);
	void setXr(bool xr);
	void setYu(bool yu);
	void setYd(bool yd);

private:
	int _experienceValue;
	bool _xl;
	bool _xr;
	bool _yu;
	bool _yd;
};

