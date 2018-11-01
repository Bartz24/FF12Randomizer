#pragma once
#include "Helpers.h"

class TreasureData
{
public:
	unsigned char unknown[9];
	unsigned char respawn; // 09 FF=always
	unsigned char spawnChance; // 0A
	unsigned char gilChance; // 0B
	unsigned short common1; // 0C-0D
	unsigned short common2; // 0E-0F
	unsigned short rare1; // 10-11
	unsigned short rare2; // 12-13
	unsigned short gil1; // 14-15
	unsigned short gil2; // 16-17
	TreasureData();
	TreasureData(char data[24]);
	~TreasureData();
};