#pragma once
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "MapData.h"
#include "MagicRand.h"
#include "ItemRand.h"
#include "EquipRand.h"

class TreasureRand
{
private:
	string fileName;

public:
	static MapData mapData[279];
	TreasureRand();
	~TreasureRand();
	void load();
	void save();
	string process(string preset);
	void randTreasures();
	int getItem(std::vector<int> &data, int minCost, int maxCost, bool remove);
	int getCost(int itemID);
	void addRangeToVector(vector<int> &data, int low, int high);
};

