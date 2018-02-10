#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <random>

using namespace std;

class MapGenerator
{
public:
	MapGenerator();

	vector<string> generateMap();

private:
	vector<string> _map;
	int _wallProcent;
	int _emptySpaceProcent;
	int _enemyProcent;

	char generateEnemyTile();
};

