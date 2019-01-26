#pragma once
#include <string>

using namespace std;

class TrapData
{
public:
	TrapData();
	~TrapData();
	string name;
	string description;
	int power;
	int aoe;
	int effect;
	unsigned int status;
};

