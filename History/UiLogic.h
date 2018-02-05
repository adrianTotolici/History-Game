#pragma once
#include <string>

using namespace std;

class UiLogic{
public:
	UiLogic();

	void print();
	void updateBattleLog(string log, string name, int attackValue);
	void updateBattleLog(string log, string name);
	void updateBattleLog(string log);
	void updatePlayerStatus();
};

