#pragma once
#include "Helpers.h"
#include "TreasureData.h"

class MapData
{
public:
	string fileName;
	int offset;
	int count;
	vector<TreasureData> treasure = vector<TreasureData>();
	MapData();
	MapData(string fileName, int offset);
	~MapData();
	string getFileName();
};