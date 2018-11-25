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
	for (int i = 0; i < 128; i++)
	{
		this->unknown[i] = data[i];
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
	this->gambits = data[0x2C];
	for (int i = 0; i < 10; i++)
	{
		char item[] = { data[0x58 + i * 2] , data[0x59 + i * 2] };
		this->items[i] = *reinterpret_cast<unsigned short*>(item);
		this->itemCount[i] = data[0x34 + i];
	}
	this->auto1 = data[0x48];
	this->auto2 = data[0x49];
	this->auto3 = data[0x4A];
	this->auto4 = data[0x4B];
	this->immune1 = data[0x4C];
	this->immune2 = data[0x4D];
	this->immune3 = data[0x4E];
	this->immune4 = data[0x4F];
	this->model = data[0x70];
}

CharData::CharData()
{
}


CharData::~CharData()
{
}
