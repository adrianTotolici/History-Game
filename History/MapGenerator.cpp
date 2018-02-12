#include "stdafx.h"
#include "MapGenerator.h"


MapGenerator::MapGenerator(int height, int width){
	_heightMap = height;
	_widthMap = width;
	static default_random_engine randEngine((unsigned int)time(NULL));
	uniform_int_distribution<int> rollHeight(1, (_heightMap-2));
	uniform_int_distribution<int> rollWidth(1, (_widthMap-2));

	_xRandPosArtefact = rollWidth(randEngine);
	_yRandPosArtefact = rollHeight(randEngine);
}

vector<string> MapGenerator::generateMap() {
	bool artefactInserted = false, playerInserted = false;
		int mapTile;
		string wallRow = "";
		wallRow.append(_widthMap + 2, 0x23);
		_map.push_back(wallRow);
		for (int i = 1; i < _heightMap; i++) {
			string row = "";
			for (int j = 0; j < _widthMap; j++) {
				if (i == _xRandPosArtefact && j == _yRandPosArtefact && !artefactInserted) {
					row.append("*");
					artefactInserted = true;
				} else {
					static default_random_engine randEngine((unsigned int)time(NULL));
					uniform_int_distribution<int> roll(1, 100);
					if (playerInserted) {
						mapTile = roll(randEngine);
						if (mapTile < 10) { row.append("#"); }
						if (mapTile > 9 && mapTile < 11) { row.append("o"); }
						if (mapTile > 10 && mapTile < 95) { row.append("."); }
						if (mapTile > 94) { row.append(generateEnemyTile()); }
					}
					else {
						row.append("@");
						playerInserted = true;
					}
				}
			}
			row = "#" + row + "#";
			_map.push_back(row);
		}
		_map.push_back(wallRow);
	return _map;
}

string MapGenerator::generateEnemyTile() {
	static default_random_engine randEngine((unsigned int)time(NULL));
	uniform_int_distribution<int> roll(1, 5);
	int enemyType = roll(randEngine);
	switch (enemyType) {
	case 1:
		return "s";
	case 2:
		return "g";
	case 3:
		return "B";
	case 4:
		return "O";
	default:
		return "D";
	}
}


