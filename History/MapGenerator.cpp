#include "stdafx.h"
#include "MapGenerator.h"


MapGenerator::MapGenerator(){}

vector<string> MapGenerator::generateMap() {
	int width = 50, height = 25;
	int mapTile;
	string wallRow="";
	wallRow.append(width+2, 0x23);
	_map.push_back(wallRow);
	for (int i = 1; i < height; i++) {
		string row = "";
		for (int j = 0; j < width; j++) {
			static default_random_engine randEngine((unsigned int)time(NULL));
			uniform_int_distribution<int> roll(1, 100);
			mapTile = roll(randEngine);

			// insert a procent system for each tile to be generated;

			string ty = "";

			switch (mapTile) {
			case 1:
				row.append("#");
				break;
			case 2:
				row.append(".");
				break;
			case 3:
				char test = generateEnemyTile();
				//fix enemy generation;
				ty.push_back(test);
				row.append();
				break;
			default:
				row.append("#");
				break;
			}
		}
		row = "#" + row + "#";
		_map.push_back(row);
	}
	_map.push_back(wallRow);
	return _map;
}

char MapGenerator::generateEnemyTile() {
	static default_random_engine randEngine((unsigned int)time(NULL));
	uniform_int_distribution<int> roll(1, 5);
	int enemyType = roll(randEngine);
	switch (enemyType) {
	case 1:
		return 's';
	case 2:
		return 'g';
	case 3:
		return 'B';
	case 4:
		return 'O';
	default:
		return 'D';
	}
}
