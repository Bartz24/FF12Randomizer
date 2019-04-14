#include "stdafx.h"
#include "StatusValue.h"


char StatusValue::flagMappings[32] = {
		'j', ' ', 'g', 'q', 'S', 'C', 'D', 'B',
		'r', 'a', 'm', 'w', 'n', 'z', 'i', 'o',
		'd', 'u', 'p', 's', 'h', 'y', 't', 'c',
		'v', 'e', 'f', 'k', 'b', ' ', 'l', 'x'
};
int StatusValue::onEquipWeights[32] = {};
int StatusValue::onHitWeights[32] = {};
int StatusValue::immuneWeights[32] = {};

StatusValue::StatusValue()
{
}

StatusValue::StatusValue(unsigned int num)
{
	for (int i = 0; i < 32; i++)
	{
		unsigned int flag = (unsigned int)pow(2, i);
		if ((num & flag) == flag)
			statuses.push_back(Status(*(reinterpret_cast<int*>(&flag))));
	}
}


StatusValue::~StatusValue()
{
}

unsigned int StatusValue::getNumValue()
{
	unsigned int num = 0;
	for (int i = 0; i < statuses.size(); i++)
		num += *reinterpret_cast<unsigned int*>(&statuses[i]);
	return num;
}

void StatusValue::addRandomStatus(int* weights)
{
	int chances[32] = { weights[0] };
	int num0 = weights[0] == 0 ? 1 : 0;
	for (int i = 1; i < 32; i++)
	{
		chances[i] = weights[i] + chances[i - 1];
		if (weights[i] == 0)
			num0++;
	}
	if (statuses.size() == 32 - num0)
		return;
	Status status;
	do
	{
		int chance = Helpers::randInt(0, chances[31]);
		unsigned int val;
		for (int i = 0; i < 32; i++)
		{
			if (chance < chances[i])
			{
				val = pow(2, i);
				break;
			}
		}
		status = Status(*reinterpret_cast<int*>(&val));
	} while (hasStatus(status));
	statuses.push_back(status);
}


bool StatusValue::hasStatus(Status status)
{
	return find(statuses.begin(), statuses.end(), status) != statuses.end();
}

void StatusValue::removeStatus(Status status)
{
	if (hasStatus(status))
		statuses.erase(find(statuses.begin(), statuses.end(), status));
}

void StatusValue::readFlags(int * weights, FlagGroup flags)
{
	for (int i = 0; i < 32; i++)
	{
		string s = string(1, flagMappings[i]);
		if (flags.hasFlag(s))
			weights[i] = flags.getFlag(s).getValue();
		else
			weights[i] = 0;

	}
}
