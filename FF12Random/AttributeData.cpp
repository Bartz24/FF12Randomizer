#include "stdafx.h"
#include "AttributeData.h"


AttributeDataOffset AttributeData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return AttributeDataOffset::us;
	return AttributeDataOffset::us;
}

AttributeData::AttributeData(char data[24])
{
	char hp[] = { data[0] , data[1] };
	this->hp = *reinterpret_cast<unsigned short*>(hp);
	char mp[] = { data[2] , data[3] };
	this->mp = *reinterpret_cast<unsigned short*>(mp);
	this->str = data[4];
	this->mag = data[5];
	this->vit = data[6];
	this->spd = data[7];
	this->autoStatus1 = data[8];
	this->autoStatus2 = data[9];
	this->autoStatus3 = data[10];
	this->autoStatus4 = data[11];
	this->immuneStatus1 = data[12];
	this->immuneStatus2 = data[13];
	this->immuneStatus3 = data[14];
	this->immuneStatus4 = data[15];
	this->absorbElement = data[16];
	this->immuneElement = data[17];
	this->halfElement = data[18];
	this->weakElement = data[19];
	this->boostElement = data[20];
	this->empty1 = data[21];
	this->empty2 = data[22];
	this->empty3 = data[23];
}

AttributeData::AttributeData()
{
}


AttributeData::~AttributeData()
{
}
