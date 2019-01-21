#pragma once
#include "Helpers.h"

enum class EquipDataOffset
{
	us = 0x000B068
};

class EquipData
{
public:
	static EquipDataOffset getDataIndex();
	unsigned char unknown[41];
	unsigned char equipRequirements; // 11
	unsigned short cost; // 12-13
	unsigned char def; // 18 shield eva
	unsigned char mRes; // 19 shield m.eva
	unsigned char power; // 1A
	unsigned char element; // 1E
	unsigned char hitChance; // 1F
	unsigned char status1; // 20
	unsigned char status2; // 21
	unsigned char status3; // 22
	unsigned char status4; // 23
	unsigned char ct; // 27
	unsigned int attribute; // 28-2B
	unsigned char itemFlag; //07
	EquipData();
	EquipData(char data[52]);
	~EquipData();
};