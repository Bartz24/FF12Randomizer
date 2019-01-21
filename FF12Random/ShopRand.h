#pragma once
#include <vector>
#include "ShopData.h"
#include "BazaarData.h"
#include "ItemRand.h"
#include "EquipRand.h"
#include "MagicRand.h"

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
	void process(FlagGroup flags);
	void randShops(FlagGroup flags);
	void addAllShopItems(vector<int> &data, FlagGroup flags);
	void addShopItems(vector<int> &data, int low, int high, FlagGroup flags);
	void addRangeToVector(vector<int> &data, int low, int high);
	void replaceBazaarRecipes(FlagGroup flags);
	int setItem(vector<int> &dataVec, unsigned short &data, unsigned char &amt, bool loot, FlagGroup flags);
	int getCostOfItem(int itemID);
};

