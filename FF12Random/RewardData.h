#pragma once
#include "Helpers.h"

enum class RewardDataOffset
{
	us = 0x0001FFE8
};

class RewardData
{
public:
	static RewardDataOffset getDataIndex();
	unsigned int gil; // 00-03
	unsigned short item1; // 04-05
	unsigned char item1Amt; // 06
	unsigned char empty1; // 07
	unsigned short item2; // 08-09
	unsigned char item2Amt; // 0A
	unsigned char empty2; // 0B
	RewardData();
	RewardData(char data[12]);
	~RewardData();
};