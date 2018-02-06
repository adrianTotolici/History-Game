#include "stdafx.h"
#include "UiLogic.h"
#include <string>

using namespace std;

UiLogic::UiLogic(){}

void UiLogic::print() {
	system("cls");

	if (_screen2.size()>_screen1.size()) {
		_screen2 = _utils.makeNewLogSpace(_screen2);
	}

	string levelData = _utils.concat2Screens(_screen1, _screen2);
	printf(levelData.c_str());
}

void UiLogic::updatePlayerStatus() {
	//todo implement print player status
}

void UiLogic::setScreen1(vector<string>& screen1){
	_screen1 = screen1;
}

vector<string> UiLogic::getScreen1()
{
	return _screen1;
}

void UiLogic::setScreen2(vector<string> screen2){
	_screen2 = screen2;
}

vector<string> UiLogic::getScreen2()
{
	return _screen2;
}

void UiLogic::updateBattleLog(string log) {
	_screen2.push_back(log);
	print();
}