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
	for (int i = 0; i < 60; i++)
	{
		this->unknown[i] = data[i];
	}
	char desc[] = { data[0x00] , data[0x01] };
	this->description = *reinterpret_cast<unsigned short*>(desc);
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
	char stat[] = { data[0x18] , data[0x19], data[0x1A], data[0x1B] };
	this->status = *reinterpret_cast<unsigned int*>(stat);
	this->castAnimation = data[0x21];
	char animation[] = { data[0x24] , data[0x25] };
	this->animation = *reinterpret_cast<unsigned short*>(animation);
	char type[] = { data[0x2C] , data[0x2D] };
	this->mType = *reinterpret_cast<unsigned short*>(type);
	this->specialType = data[0x36];
	this->gambitPage = data[0x38];
	this->gambitPageOrder = data[0x39];
}

ActionData::ActionData()
{
}


ActionData::~ActionData()
{
}
