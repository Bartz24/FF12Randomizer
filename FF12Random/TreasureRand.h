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
	void process(FlagGroup flags);
	void randTreasures(FlagGroup flags);
	int getItem(std::vector<int> &data, int center, int std, int value, bool remove);
	int getCost(int itemID);
	bool canAddItem(int actualCost, int center, int std, int value);
	void addRangeToVector(vector<int> &data, int low, int high);
};

