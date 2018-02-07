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
	void updatePlayerStatus(string logRow1, string logRow2);

	void setScreen1(vector<string> &screen1);
	vector<string> getScreen1();
	void setScreen2(vector<string> &screen2);
	vector<string> getScreen2();
	void setScreen3(vector<string> &screen3);
	vector<string> getScreen3();

private:
	vector <string> _screen1;
	vector <string> _screen2;
	vector <string> _screen3;
	Utils _utils;
};

