#pragma once

#include "Helpers.h"
#include <regex>

class Flag
{
private:
	string flagType;
	bool smart;
	int value;

public:
	Flag();
	Flag(string flag, string flagID);
	~Flag();

	string getType();
	bool isSmart();
	int getValue();
	const int noValue = -9999;
};

