#include "stdafx.h"
#include "BazaarData.h"


BazaarDataOffset BazaarData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return BazaarDataOffset::us;
	return BazaarDataOffset::us;
}

BazaarData::BazaarData(char data[36])
{
	int index = 0;
	for (int i = 0; i < 36; i++)
	{
		if (i >= 0x04 && i <= 0x06 || i >= 0x08 && i <= 0x0A || i >= 0x0C && i <= 0x0E || i >= 0x10 && i <= 0x14 || 
			i >= 0x16 && i <= 0x18 || i >= 0x1A && i <= 0x1C || i >= 0x1E && i <= 0x20)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	char res1[] = { data[0x04] , data[0x05] };
	this->result1 = *reinterpret_cast<unsigned short*>(res1);
	this->result1Amt = data[0x06];
	char res2[] = { data[0x08] , data[0x09] };
	this->result2 = *reinterpret_cast<unsigned short*>(res2);
	this->result2Amt = data[0x0A];
	char res3[] = { data[0x0C] , data[0x0D] };
	this->result3 = *reinterpret_cast<unsigned short*>(res3);
	this->result3Amt = data[0x0E];
	char cost[] = { data[0x10] , data[0x11], data[0x12], data[0x13] };
	this->cost = *reinterpret_cast<unsigned int*>(cost);
	this->bazaarType = data[0x14];
	char loot1[] = { data[0x16] , data[0x17] };
	this->loot1 = *reinterpret_cast<unsigned short*>(loot1);
	this->loot1Amt = data[0x18];
	char loot2[] = { data[0x1A] , data[0x1B] };
	this->loot2 = *reinterpret_cast<unsigned short*>(loot2);
	this->loot2Amt = data[0x1C];
	char loot3[] = { data[0x1E] , data[0x1F] };
	this->loot3 = *reinterpret_cast<unsigned short*>(loot3);
	this->loot3Amt = data[0x20];
}

BazaarData::BazaarData()
{
}


BazaarData::~BazaarData()
{
}
