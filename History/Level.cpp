#include "stdafx.h"
#include "Level.h"


Level::Level(){}

void Level::load(string fileName) {
	fstream file;

	//Load level from file
	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;
	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();
}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void Level::loadRandomMap() {
	MapGenerator mapGenerator;
	_levelData = mapGenerator.generateMap();
}


