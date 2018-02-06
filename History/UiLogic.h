#pragma once
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

class UiLogic{
public:
	UiLogic();

	void print();
	void updateBattleLog(string log);
	void updatePlayerStatus();

	void setScreen1(vector<string> &screen1);
	vector<string> getScreen1();

	void setScreen2(vector<string> screen2);
	vector<string> getScreen2();

private:
	vector <string> _screen1;
	vector <string> _screen2;
	Utils _utils;
};

