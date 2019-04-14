#include "Helpers.h"

#pragma once

class CommandPack
{
public:
	unsigned int pointer;
	int abilityCount;
	vector<unsigned short> abilities;
	vector<unsigned short> chances;
	CommandPack();
	CommandPack(unsigned int pointer, int count, char data[]);
	~CommandPack();
};

