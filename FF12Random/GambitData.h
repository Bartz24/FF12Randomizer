#pragma once
#include "Helpers.h"

enum class GambitDataOffset
{
	us = 0x0001DF0
};

class GambitData
{
public:
	static GambitDataOffset getDataIndex();
	unsigned char unknown[30];
	unsigned short cost; // 06-07
	unsigned short name; // 14-15
	GambitData();
	GambitData(char data[32]);
	~GambitData();
};