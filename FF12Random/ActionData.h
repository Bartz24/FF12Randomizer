#pragma once
#include "Helpers.h"

enum class ActionDataOffset
{
	us = 0x0013230
};

class ActionData
{
public:
	static ActionDataOffset getDataIndex();
	unsigned char unknown[48];
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
	unsigned char status1; // 18
	unsigned char status2; // 19
	unsigned char status3; // 1A
	unsigned char status4; // 1B
	unsigned short animation; //24-25
	unsigned short mType; // 2C-2D
	ActionData();
	ActionData(char data[60]);
	~ActionData();
};