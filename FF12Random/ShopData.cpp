#include "stdafx.h"
#include "ShopData.h"

ShopData::ShopData()
{
}

ShopData::ShopData(int pos, char headerA, char headerB, char empty1, char empty2, unsigned short size, unsigned short count, char addressA, char addressB, char addressC, char addressD, vector<unsigned short> items)
{
	this->position = pos;
	this->header1 = headerA;
	this->header2 = headerB;
	this->empty1 = empty1;
	this->empty2 = empty2;
	this->itemSize = size;
	this->itemCount = count;
	this->address1 = addressA;
	this->address2 = addressB;
	this->address3 = addressC;
	this->address4 = addressD;
	this->items = items;
}

ShopData::~ShopData()
{
}
