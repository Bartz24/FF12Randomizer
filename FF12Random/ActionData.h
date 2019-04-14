#pragma once
#include "Helpers.h"

class ActionData
{
public:
	unsigned char unknown[60];
	unsigned short description; //00-01
	unsigned char aoeRange; // 06
	unsigned char type; // 08
	unsigned char ct; // 09
	unsigned char cost; // 0A
	unsigned char target; // 0C
	unsigned char power; // 10
	unsigned char powerMult; // 11
	unsigned char accuracy; // 12
	unsigned char element; // 13
	unsigned char hitChance; // 14
	unsigned int status; // 18-1B
	unsigned char castAnimation; // 21
	unsigned short animation; //24-25
	unsigned short mType; // 2C-2D
	unsigned short name; // 34-35
	unsigned char specialType; // 36
	unsigned char gambitPage; // 38
	unsigned char gambitPageOrder; // 39
	int enemyRarity;
	ActionData();
	ActionData(char data[60]);
	~ActionData();
};