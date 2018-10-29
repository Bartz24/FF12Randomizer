#pragma once
#include "LootData.h"

class LootRand
{
private:
	string fileName;

public:
	static LootData lootData[266];
	LootRand();
	~LootRand();
	void load();
	void save();
	void process();
	void randCost();
};

