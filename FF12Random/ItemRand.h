#pragma once
#include "ItemData.h"

class ItemRand
{
private:
	string fileName;

public:
	static ItemData itemData[63];
	ItemRand();
	~ItemRand();
	void load();
	void save();
	void process();
	void randCost();
};

