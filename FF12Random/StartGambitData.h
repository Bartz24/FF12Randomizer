#pragma once
#include "Helpers.h"

class StartGambitData
{
public:
	unsigned char unknown[64];
	unsigned short gambits[12]; //0-17
	unsigned short actions[12]; //20-37
	StartGambitData();
	StartGambitData(char data[64]);
	~StartGambitData();
};