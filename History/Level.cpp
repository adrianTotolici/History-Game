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

void Level::print() {
	//_utils.cls(_hStdout);
	system("cls");
	for (size_t i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}


