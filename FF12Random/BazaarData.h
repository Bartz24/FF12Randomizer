#pragma once
#include "Helpers.h"

enum class BazaarDataOffset
{
	us = 0x0025390
};

class BazaarData
{
public:
	static BazaarDataOffset getDataIndex();
	unsigned char unknown[13];
	unsigned short result1; // 04-05
	unsigned char result1Amt; // 06
	unsigned short result2; // 08-09
	unsigned char result2Amt; // 0A
	unsigned short result3; // 0C-0D
	unsigned char result3Amt; // 0E
	unsigned int cost; // 10-13
	unsigned char bazaarType; // 14      00-Not Repeatable 01-Repeatable 02-Monograph
	unsigned short loot1; // 16-17
	unsigned char loot1Amt; // 18
	unsigned short loot2; // 1A-1B
	unsigned char loot2Amt; // 1C
	unsigned short loot3; // 1E-1F
	unsigned char loot3Amt; // 20
	BazaarData();
	BazaarData(char data[36]);
	~BazaarData();
};