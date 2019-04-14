#pragma once
#include "Helpers.h"

class AugmentData
{
public:
	unsigned char unknown[6];
	unsigned short value; // 04-05
	AugmentData();
	AugmentData(char data[8]);
	~AugmentData();
};