#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <random>

using namespace std;

class MapGenerator
{
public:
	MapGenerator(int height, int width);

	vector<string> generateMap();

private:
	string generateEnemyTile();

	vector<string> _map;
	int _xRandPosArtefact, _yRandPosArtefact;
	int _heightMap, _widthMap;
};

