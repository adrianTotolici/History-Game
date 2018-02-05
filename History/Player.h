#pragma once
#include "Units.h"

class Player : public Units {
public:
	Player();
	
	void addExperience(int experience);
	int attack();
	int takeDamage(int attack);

private:
	int _experience;
};
