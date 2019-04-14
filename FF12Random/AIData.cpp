#include "stdafx.h"
#include "AIData.h"


AIData::AIData()
{
}

AIData::~AIData()
{
}

AIData::AIData(char data[], int size)
{
	abilities = vector<AIAbility>();
	for (int pointer = 4; pointer + 3 < size; pointer += 4)
	{
		if (data[pointer + 1] == 0x48 && (data[pointer + 2] == 0x01 || data[pointer + 2] == 0x04 || data[pointer + 2] == 0x06))
		{
			AIAbility ability;
			for (int i = 0; i < 8; i++)
				ability.unknown[i] = data[pointer - 4 + i];
			ability.targetType = Helpers::readShort(data, pointer + 1);
			ability.ability = Helpers::readShort(data, pointer - 4);
			ability.pointer = pointer + 1;
			abilities.push_back(ability);
		}
	}
	unknownByteSize = size;
	unknown = new unsigned char[size];
	for (int i = 0; i < size; i++)
		unknown[i] = *reinterpret_cast<unsigned char*>(&data[i]);
}
