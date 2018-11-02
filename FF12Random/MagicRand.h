#pragma once
#include "MagicData.h"
#include "ActionData.h"
#include "StatusValue.h"

class MagicRand
{
private:
	string fileName;

public:
	static ActionData actionData[497];
	static MagicData magicData[105];
	MagicRand();
	~MagicRand();
	void load();
	void save();
	string process(string preset);
	void randCost();
	void randMPCost();
	void randCT();
	void randAoE();
	void randStatus();
	void setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance);
	void addStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4);
};

