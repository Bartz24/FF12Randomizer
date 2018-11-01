#pragma once
#include "Helpers.h"

enum class AugmentDataOffset
{
	us = 0x00267D0
};

class AugmentData
{
public:
	static AugmentDataOffset getDataIndex();
	unsigned char unknown[6];
	unsigned short value; // 04-05
	AugmentData();
	AugmentData(char data[8]);
	~AugmentData();
};