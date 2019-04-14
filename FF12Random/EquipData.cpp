#include "stdafx.h"
#include "EquipData.h"

EquipData::EquipData(char data[52])
{
	for (int i = 0; i < 52; i++)
	{
		this->unknown[i] = data[i];
	}
	this->id = Helpers::readShort(data, 0x02);
	this->equipRequirements = data[0x11];
	char cost[] = { data[0x12] , data[0x13] };
	this->cost = *reinterpret_cast<unsigned short*>(cost);
	this->def = data[0x18];
	this->mRes = data[0x19];
	this->power = data[0x1A];
	this->knockback = data[0x1B];
	this->critChance = data[0x1C];
	this->evasion = data[0x1D];
	this->element = data[0x1E];
	this->hitChance = data[0x1F];
	char stat[] = { data[0x20], data[0x21], data[0x22], data[0x23] };
	this->status = *reinterpret_cast<unsigned int*>(stat);
	this->ct = data[0x27];
	char attr[] = { data[0x28] , data[0x29], data[0x2A], data[0x2B] };
	this->attribute = *reinterpret_cast<unsigned int*>(attr);
	this->itemFlag = data[0x07];
}

EquipData::EquipData()
{
}


EquipData::~EquipData()
{
}
