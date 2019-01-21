#pragma once
#include "Helpers.h"

enum class ItemDataOffset
{
	us = 0x0001CB60
};

class ItemData
{
public:
	static ItemDataOffset getDataIndex();
	unsigned char order;
	unsigned char unknown1;
	unsigned char unknown2;
	unsigned char unknown3;
	unsigned char icon;
	unsigned char unknown4;
	unsigned char unknown5;
	unsigned char desc;
	unsigned char unknown7;
	unsigned char unknown8;
	unsigned short cost;
	ItemData();
	ItemData(char order, char unknown1, char unknown2, char unknown3, char icon, char unknown4, char unknown5, char desc, char unknown7, char unknown8, char costA, char costB);
	~ItemData();
};

