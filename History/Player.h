#pragma once
#include "Units.h"

class Player : public Units {
public:
	Player();
	
	void addExperience(int experience);
	void addHealth(char item);
	int attack();
	int takeDamage(int attack);

	int getExperience();

private:
	int _experience;
};
