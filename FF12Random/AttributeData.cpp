#include "stdafx.h"
#include "AttributeData.h"

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
	char autostat[] = { data[8] , data[9], data[10], data[11] };
	this->autoStatus = *reinterpret_cast<unsigned int*>(autostat);
	char immstat[] = { data[12] , data[13], data[14], data[15] };
	this->immuneStatus = *reinterpret_cast<unsigned int*>(immstat);
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
