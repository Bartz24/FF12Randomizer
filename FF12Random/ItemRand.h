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
	static ItemData itemData[64];
	static LootData lootData[266];
	static GambitData gambitData[256];
	ItemRand();
	~ItemRand();
	void load();
	void save();
	void process(FlagGroup flags);
	void randCost(int value);
	void randCostSmart(int value);
	void randCostLoot(int value);
	void randCostGambit(int value);
};

