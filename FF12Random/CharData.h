#pragma once
#include "Helpers.h"

class CharData
{
public:
	unsigned char unknown[128];
	unsigned short weapon; // 0A-0B
	unsigned short offHand; // 0C-0D
	unsigned short head; // 0E-0F
	unsigned short body; // 10-11
	unsigned short accessory; // 12-13
	unsigned short hp; // 16-17
	unsigned char hpModifier; // 19
	unsigned short mp; // 1A-1B
	unsigned char mpModifier; // 1D
	unsigned char str; // 1E
	unsigned char strModifier; // 1F
	unsigned char mag; // 21
	unsigned char magModifier; // 22
	unsigned char vit; // 24
	unsigned char vitModifier; // 25
	unsigned char spd; // 27
	unsigned char spdModifier; // 28
	unsigned char gambits; // 2C
	unsigned char level; // 2E
	unsigned short items[10]; // 58-6B
	unsigned char itemCount[10]; // 34-3D
	unsigned char auto1; // 48
	unsigned char auto2; // 49
	unsigned char auto3; // 4A
	unsigned char auto4; // 4B
	unsigned char immune1; // 4C
	unsigned char immune2; // 4D
	unsigned char immune3; // 4E
	unsigned char immune4; // 4F
	unsigned char model; // 70
	CharData();
	CharData(char data[128]);
	~CharData();
};