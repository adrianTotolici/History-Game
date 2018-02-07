#include "stdafx.h"
#include "UiLogic.h"

using namespace std;

UiLogic::UiLogic(){}

void UiLogic::print() {
	system("cls");	
	if ((_screen2.size()+_screen3.size())>_screen1.size()-1) {
		_screen2 = _utils.makeNewLogSpace(_screen2);
	}
	string levelData = _utils.concat3Screens(_screen1, _screen2, _screen3);	
	printf(levelData.c_str());
}

void UiLogic::updatePlayerStatus(string logRow1, string logRow2) {
	if (_screen3.size() > 0) {
		_screen3.clear();
	}
	_screen3.push_back(logRow1);
	_screen3.push_back(logRow2);
}

void UiLogic::setScreen1(vector<string> &screen1){
	_screen1 = screen1;
}

vector<string> UiLogic::getScreen1()
{
	return _screen1;
}

void UiLogic::setScreen2(vector<string> &screen2){
	_screen2 = screen2;
}

vector<string> UiLogic::getScreen3() {
	return _screen3;
}

void UiLogic::setScreen3(vector<string> &screen3) {
	_screen3 = screen3;
}

vector<string> UiLogic::getScreen2()
{
	return _screen2;
}

void UiLogic::updateBattleLog(string log) {
	_screen2.push_back(log);
	print();
}