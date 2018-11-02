#include "stdafx.h"
#include "GambitData.h"


GambitDataOffset GambitData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return GambitDataOffset::us;
	return GambitDataOffset::us;
}

GambitData::GambitData(char data[32])
{
	int index = 0;
	for (int i = 0; i < 32; i++)
	{
		if (i == 0x06 || i == 0x07)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	char cost[] = { data[0x06] , data[0x07] };
	this->cost = *reinterpret_cast<unsigned short*>(cost);
}

GambitData::GambitData()
{
}


GambitData::~GambitData()
{
}
