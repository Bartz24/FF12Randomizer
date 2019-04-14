#include "stdafx.h"
#include "MagicData.h"

MagicData::MagicData(char costA, char costB, char id1, char icon, char id2, char unknown1, char order, char unknown2)
{
	char data[] = { costA , costB };
	this->cost = *reinterpret_cast<unsigned short*>(data);
	this->id1 = id1;
	this->icon = icon;
	this->id2 = id2;
	this->unknown1 = unknown1;
	this->order = order;
	this->unknown2 = unknown2;
}

MagicData::MagicData()
{
}


MagicData::~MagicData()
{
}
