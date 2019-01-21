#include "stdafx.h"
#include "Flag.h"


Flag::Flag()
{
}

Flag::Flag(string flag, string flagID)
{
	flagType = flagID;
	regex pattern = regex(flagID + "(\\*|)(\\d+|)");
	smatch matches;
	if (regex_search(flag, matches, pattern))
	{
		smart = (matches[1].str() == "*");
		if (matches[2] != "")
			value = stoi(matches[2].str());
		else
			value = noValue;
	}
}


Flag::~Flag()
{
}

string Flag::getType()
{
	return flagType;
}

bool Flag::isSmart()
{
	return smart;
}

int Flag::getValue()
{
	return value;
}
