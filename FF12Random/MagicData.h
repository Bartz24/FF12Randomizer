#pragma once
#include <string>
#include "Helpers.h"

enum class MagicDataOffsetMagick
{
	us = 0x0001D290
};
enum class MagicDataOffsetTechnick
{
	us = 0x0001D540
};

class MagicData
{
public:
	static MagicDataOffsetMagick getMagDataIndex();
	static MagicDataOffsetTechnick getTechDataIndex();
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

