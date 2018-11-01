#pragma once
#include <vector>
#include "ShopData.h"
#include "BazaarData.h"
#include "ItemRand.h"
#include "EquipRand.h"
#include "MagicRand.h"
#include "LootRand.h"

class ShopRand
{
private:
	string fileName;

public:
	static ShopData shopData[267];
	static BazaarData bazaarData[128];
	ShopRand();
	~ShopRand();
	void load();
	void save();
	void process();
	void randShops();
	void addRangeToVector(vector<int> &data, int low, int high);
	void replaceBazaarRecipes();
	int setItem(vector<int> &dataVec, unsigned short &data, unsigned char &amt, bool loot = false);
};

