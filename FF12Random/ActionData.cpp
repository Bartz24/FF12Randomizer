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
		if (i == 0x06 || i == 0x08 || i == 0x09 || i == 0x0A || i == 0x0C || i >= 0x10 && i <= 0x14 || i >= 0x18 && i <= 0x1B || i == 0x24 || i == 0x25 || i == 0x2C || i == 0x2D)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	this->aoeRange = data[0x06];
	this->type = data[0x08];
	this->ct = data[0x09];
	this->cost = data[0x0A];
	this->target = data[0x0C];
	this->power = data[0x10];
	this->powerMult = data[0x11];
	this->accuracy = data[0x12];
	this->element = data[0x13];
	this->hitChance = data[0x14];
	this->status1 = data[0x18];
	this->status2 = data[0x19];
	this->status3 = data[0x1A];
	this->status4 = data[0x1B];
	char animation[] = { data[0x24] , data[0x25] };
	this->animation = *reinterpret_cast<unsigned short*>(animation);
	char type[] = { data[0x2C] , data[0x2D] };
	this->mType = *reinterpret_cast<unsigned short*>(type);
}

ActionData::ActionData()
{
}


ActionData::~ActionData()
{
}
