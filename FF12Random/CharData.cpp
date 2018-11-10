#include "stdafx.h"
#include "CharData.h"


CharDataOffset CharData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return CharDataOffset::us;
	return CharDataOffset::us;
}

CharData::CharData(char data[128])
{
	int index = 0;
	for (int i = 0; i < 128; i++)
	{
		if (i >= 0x0A && i <= 0x13 || i == 0x16 || i == 0x17 || i == 0x19 || i == 0x1A || i == 0x1B || i == 0x1D || i == 0x1E || i == 0x1F
			|| i == 0x21 || i == 0x22 || i == 0x24 || i == 0x25 || i == 0x27 || i == 0x28 || i >= 0x34 && i <= 0x3D || i >= 0x58 && i <= 0x6B || i >= 0x4C && i <= 0x4F)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	char weapon[] = { data[0x0A] , data[0x0B] };
	this->weapon = *reinterpret_cast<unsigned short*>(weapon);
	char offHand[] = { data[0x0C] , data[0x0D] };
	this->offHand = *reinterpret_cast<unsigned short*>(offHand);
	char head[] = { data[0x0E] , data[0x0F] };
	this->head = *reinterpret_cast<unsigned short*>(head);
	char body[] = { data[0x10] , data[0x11] };
	this->body = *reinterpret_cast<unsigned short*>(body);
	char accessory[] = { data[0x12] , data[0x13] };
	this->accessory = *reinterpret_cast<unsigned short*>(accessory);
	char hp[] = { data[0x16] , data[0x17] };
	this->hp = *reinterpret_cast<unsigned short*>(hp);
	this->hpModifier = data[0x19];
	char mp[] = { data[0x1A] , data[0x1B] };
	this->mp = *reinterpret_cast<unsigned short*>(mp);
	this->mpModifier = data[0x1D];
	this->str = data[0x1E];
	this->strModifier = data[0x1F];
	this->mag = data[0x21];
	this->magModifier = data[0x22];
	this->vit = data[0x24];
	this->vitModifier = data[0x25];
	this->spd = data[0x27];
	this->spdModifier = data[0x28];
	for (int i = 0; i < 10; i++)
	{
		char item[] = { data[0x58 + i * 2] , data[0x59 + i * 2] };
		this->items[i] = *reinterpret_cast<unsigned short*>(item);
		this->itemCount[i] = data[0x34 + i];
	}
	this->immune1 = data[0x4C];
	this->immune2 = data[0x4D];
	this->immune3 = data[0x4E];
	this->immune4 = data[0x4F];
}

CharData::CharData()
{
}


CharData::~CharData()
{
}
