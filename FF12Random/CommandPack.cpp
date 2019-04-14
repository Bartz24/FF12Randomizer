#include "stdafx.h"
#include "CommandPack.h"


CommandPack::CommandPack()
{
}

CommandPack::CommandPack(unsigned int pointer, int count, char data[])
{
	this->pointer = pointer;
	this->abilityCount = count;
	for (int i = 0; i < count; i++)
	{
		this->abilities.push_back(Helpers::readShort(data, i * 4));
		this->chances.push_back(Helpers::readShort(data, 2 + i * 4));
	}
}


CommandPack::~CommandPack()
{
}
