#pragma once

#include "Helpers.h"
#include "AIAbility.h"

class AIData
{
public:
	unsigned char* unknown = nullptr;
	int unknownByteSize;
	vector<AIAbility> abilities;
	AIData();
	AIData(char data[], int size);
	~AIData();
};

