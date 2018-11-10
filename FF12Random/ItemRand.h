#pragma once
#include "ItemData.h"
#include "LootData.h"
#include "GambitData.h"
#include "MagicRand.h"

class ItemRand
{
private:
	string fileName;

public:
	static ItemData itemData[63];
	static LootData lootData[266];
	static GambitData gambitData[256];
	ItemRand();
	~ItemRand();
	void load();
	void save();
	string process(string preset);
	void randCost();
	void randCostSmart();
	void randCostLoot();
	void randCostGambit();
};

