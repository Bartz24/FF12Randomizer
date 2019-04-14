#include "stdafx.h"
#include "GambitData.h"

GambitData::GambitData(char data[32])
{
	int index = 0;
	for (int i = 0; i < 32; i++)
	{
		if (i == 0x06 || i == 0x07 || i == 0x14 || i == 0x15)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	char cost[] = { data[0x06] , data[0x07] };
	this->cost = *reinterpret_cast<unsigned short*>(cost);
	char name[] = { data[0x14] , data[0x15] };
	this->name = *reinterpret_cast<unsigned short*>(name);
}

GambitData::GambitData()
{
}


GambitData::~GambitData()
{
}
