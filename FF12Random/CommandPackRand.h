#pragma once

#include "CommandPack.h"
#include "FlagGroup.h"

class CommandPackRand
{
private:
	string fileName;

public:
	static vector<int> targetTypesSeen;
	static CommandPack commandPackData[826];
	static bool isBlackListedEnemyAbility(unsigned short ab);
	CommandPackRand();
	~CommandPackRand();
	void load();
	void save();
	void process(FlagGroup flags);
	void shuffle(int value);
};

