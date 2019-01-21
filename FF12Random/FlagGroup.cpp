#include "stdafx.h"
#include "FlagGroup.h"


FlagGroup::FlagGroup()
{
}

FlagGroup::FlagGroup(string flagData)
{
	for (char c : flagData)
	{
		if (isalpha(c))
			flags.push_back(Flag(flagData, string(1, c)));
	}
}


FlagGroup::~FlagGroup()
{
}

bool FlagGroup::hasFlag(string flagID)
{
	for (Flag f : flags)
	{
		if (f.getType() == flagID)
			return true;
	}
	return false;
}

Flag FlagGroup::getFlag(string flagID)
{
	for (Flag f : flags)
	{
		if (f.getType() == flagID)
			return f;
	}
	return Flag();
}
