// History.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameSystem.h"

using namespace std;

int main()
{
	GameSystem gameSystem("C:\\game-proj\\History\\History\\Level\\level1.txt");
	gameSystem.playGame();

	return 0;
}