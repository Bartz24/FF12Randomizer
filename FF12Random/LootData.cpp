#include "stdafx.h"
#include "LootData.h"

LootDataOffset LootData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return LootDataOffset::us;
	return LootDataOffset::us;
}

LootData::LootData(char costA, char costB, char idA, char idB, char icon, char unknown1, char unknown2, char unknown3, char orderA, char orderB)
{
	char data[] = { costA , costB };
	this->cost = *reinterpret_cast<unsigned short*>(data);
	char data2[] = { idA , idB };
	this->itemID = *reinterpret_cast<unsigned short*>(data2);
	this->icon = icon;
	this->unknown1 = unknown1;
	this->unknown2 = unknown2;
	this->unknown3 = unknown3;
	char data3[] = { orderA , orderB };
	this->order = *reinterpret_cast<unsigned short*>(data3);
}

LootData::LootData()
{
}


LootData::~LootData()
{
}
