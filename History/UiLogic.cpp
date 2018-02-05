#include "stdafx.h"
#include "UiLogic.h"
#include <string>

using namespace std;

UiLogic::UiLogic(){}

void UiLogic::print() {
	//todo implement print UI 
}

void UiLogic::updatePlayerStatus() {
	//todo implement print player status
}

void UiLogic::updateBattleLog(string log) {
	printf(log.c_str());
}

void UiLogic::updateBattleLog(string log, string name) {
	printf(log.c_str(), name.c_str());
}

void UiLogic::updateBattleLog(string log, string name, int attackValue) {
	printf(log.c_str(), name.c_str(), attackValue);
}