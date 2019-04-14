#pragma once
#include "Helpers.h"

class GambitData
{
public:
	unsigned char unknown[30];
	unsigned short cost; // 06-07
	unsigned short name; // 14-15
	GambitData();
	GambitData(char data[32]);
	~GambitData();
};