#include "stdafx.h"
#include "TreasureData.h"

TreasureData::TreasureData(char data[24])
{
	int index = 0;
	for (int i = 0; i < 24; i++)
	{
		if (i >= 0x09 && i <= 0x17)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	this->respawn = data[0x09];
	this->spawnChance = data[0x0A];
	this->gilChance = data[0x0B];
	char com1[] = { data[0x0C] , data[0x0D] };
	this->common1 = *reinterpret_cast<unsigned short*>(com1);
	char com2[] = { data[0x0E] , data[0x0F] };
	this->common2 = *reinterpret_cast<unsigned short*>(com2);
	char rare1[] = { data[0x10] , data[0x11] };
	this->rare1 = *reinterpret_cast<unsigned short*>(rare1);
	char rare2[] = { data[0x12] , data[0x13] };
	this->rare2 = *reinterpret_cast<unsigned short*>(rare2);
	char gil1[] = { data[0x14] , data[0x15] };
	this->gil1 = *reinterpret_cast<unsigned short*>(gil1);
	char gil2[] = { data[0x16] , data[0x17] };
	this->gil2 = *reinterpret_cast<unsigned short*>(gil2);
}

TreasureData::TreasureData()
{
}


TreasureData::~TreasureData()
{
}
