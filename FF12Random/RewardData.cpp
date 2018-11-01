#include "stdafx.h"
#include "RewardData.h"


RewardDataOffset RewardData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return RewardDataOffset::us;
	return RewardDataOffset::us;
}

RewardData::RewardData(char data[12])
{
	char gil[] = { data[0x00] , data[0x01], data[0x02], data[0x03] };
	this->gil = *reinterpret_cast<unsigned int*>(gil);
	char item1[] = { data[0x04] , data[0x05] };
	this->item1 = *reinterpret_cast<unsigned short*>(item1);
	this->item1Amt = data[0x06];
	this->empty1 = data[0x07];
	char item2[] = { data[0x08] , data[0x09] };
	this->item2 = *reinterpret_cast<unsigned short*>(item2);
	this->item2Amt = data[0x0A];
	this->empty2 = data[0x0B];
}

RewardData::RewardData()
{
}


RewardData::~RewardData()
{
}
