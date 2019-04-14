#pragma once
#include <vector>
#include "Helpers.h"

class ShopData
{
public:
	int position;
	unsigned char header1;
	unsigned char header2;
	unsigned char empty1;
	unsigned char empty2;
	unsigned short itemSize;
	unsigned short itemCount;
	unsigned char address1;
	unsigned char address2;
	unsigned char address3;
	unsigned char address4;
	vector<unsigned short> items;
	ShopData();
	ShopData(int pos, char headerA, char headerB, char empty1, char empty2, unsigned short size, unsigned short count, char addressA, char addressB, char addressC, char addressD, vector<unsigned short> items);
	~ShopData();
};