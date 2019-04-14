#include "stdafx.h"
#include "ItemData.h"


ItemData::ItemData(char order, char unknown1, char unknown2, char unknown3, char icon, char unknown4, char unknown5, char desc, char unknown7, char unknown8, char costA, char costB)
{
	this->order = order;
	this->unknown1 = unknown1;
	this->unknown2 = unknown2;
	this->unknown3 = unknown3;
	this->icon = icon;
	this->unknown4 = unknown4;
	this->unknown5 = unknown5;
	this->desc = desc;
	this->unknown7 = unknown7;
	this->unknown8 = unknown8;
	char data[] = { costA , costB };
	this->cost = *reinterpret_cast<unsigned short*>(data);
}

ItemData::ItemData()
{
}


ItemData::~ItemData()
{
}
