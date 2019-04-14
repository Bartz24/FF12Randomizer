#pragma once
#include <string>
#include "Helpers.h"


class MagicData
{
public:
	unsigned short cost;
	unsigned char id1;
	unsigned char icon;
	unsigned char id2;
	unsigned char unknown1;
	unsigned char order;
	unsigned char unknown2;
	MagicData();
	MagicData(char costA, char costB, char id1, char icon, char id2, char unknown1, char order, char unknown2);
	~MagicData();
};

