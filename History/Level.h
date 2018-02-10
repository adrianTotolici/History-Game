#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>

#include "MapGenerator.h"

using namespace std;

class Level
{
public:
	Level();

	void load(string fileName); 
	void loadRandomMap();
	char getTile(int x, int y);
	void setTile(int x, int y, char tile);

	vector <string> _levelData;

};
