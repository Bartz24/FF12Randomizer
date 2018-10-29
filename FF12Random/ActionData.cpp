#include "stdafx.h"
#include "ActionData.h"


ActionDataOffset ActionData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return ActionDataOffset::us;
	return ActionDataOffset::us;
}

ActionData::ActionData(char data[60])
{
	int index = 0;
	for (int i = 0; i < 60; i++)
	{
		if (i == 0x06 || i == 0x08 || i == 0x09 || i == 0x0A || i == 0x14 || i >= 0x18 && i <= 0x1B)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	this->aoeRange = data[0x06];
	this->type = data[0x08];
	this->ct = data[0x09];
	this->cost = data[0x0A];
	this->hitChance = data[0x14];
	this->status1 = data[0x18];
	this->status2 = data[0x19];
	this->status3 = data[0x1A];
	this->status4 = data[0x1B];
}

ActionData::ActionData()
{
}


ActionData::~ActionData()
{
}
