#pragma once
#include <vector>
#include "ShopData.h"
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
	ShopRand();
	~ShopRand();
	void load();
	void save();
	void process();
	void randShops();
	void addRangeToVector(vector<int> &data, int low, int high);
};

