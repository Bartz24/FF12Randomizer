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
	unsigned char unknown[51];
	unsigned char aoeRange; // 06
	unsigned char type; // 09
	unsigned char ct; // 09
	unsigned char cost; // 0A
	unsigned char hitChance; // 14
	unsigned char status1; // 18
	unsigned char status2; // 19
	unsigned char status3; // 1A
	unsigned char status4; // 1B
	ActionData();
	ActionData(char data[60]);
	~ActionData();
};