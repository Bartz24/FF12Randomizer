#pragma once

#include "Flag.h"

class FlagGroup
{
public:
	vector<Flag> flags = vector<Flag>();

	FlagGroup();
	FlagGroup(string flagData);
	~FlagGroup();

	bool hasFlag(string flagID);
	Flag getFlag(string flagID);
};

