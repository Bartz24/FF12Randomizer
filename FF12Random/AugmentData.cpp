#include "stdafx.h"
#include "AugmentData.h"


AugmentDataOffset AugmentData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return AugmentDataOffset::us;
	return AugmentDataOffset::us;
}

AugmentData::AugmentData(char data[8])
{
	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		if (i == 0x04 || i == 0x05)
			continue;
		this->unknown[index] = data[i];
		index++;
	}
	char val[] = { data[0x04] , data[0x05] };
	this->value = *reinterpret_cast<unsigned short*>(val);
}

AugmentData::AugmentData()
{
}


AugmentData::~AugmentData()
{
}
