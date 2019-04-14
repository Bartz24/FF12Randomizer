#pragma once
#include "Helpers.h"

class EquipData
{
public:
	unsigned char unknown[52];
	unsigned short id; // 02-03
	unsigned char equipRequirements; // 11
	unsigned short cost; // 12-13
	unsigned char def; // 18 shield eva weapon range
	unsigned char mRes; // 19 shield m.eva weapon formula
	unsigned char power; // 1A
	unsigned char knockback; // 1B
	unsigned char critChance; // 1C combo rate
	unsigned char evasion; // 1D
	unsigned char element; // 1E
	unsigned char hitChance; // 1F
	unsigned int status; // 20-23
	unsigned char ct; // 27
	unsigned int attribute; // 28-2B
	unsigned char itemFlag; //07
	EquipData();
	EquipData(char data[52]);
	~EquipData();
};