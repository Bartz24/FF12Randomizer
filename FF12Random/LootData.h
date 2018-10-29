#pragma once
#include "Helpers.h"

enum class LootDataOffset
{
	us = 0x0001D720
};

class LootData
{
public:
	static LootDataOffset getDataIndex();
	unsigned short cost;
	unsigned short itemID;
	unsigned char icon;
	unsigned char unknown1;
	unsigned char unknown2;
	unsigned char unknown3;
	unsigned short order;
	LootData();
	LootData(char costA, char costB, char idA, char idB, char icon, char unknown1, char unknown2, char unknown3, char orderA, char orderB);
	~LootData();
};

