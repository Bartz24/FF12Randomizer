#pragma once
#include "RewardData.h"
#include "FlagGroup.h"

class RewardRand
{
private:
	string fileName;

public:
	static RewardData rewardData[512];
	RewardRand();
	~RewardRand();
	void load();
	void save();
	void process(FlagGroup flags);
	void randValue(FlagGroup flags);
	void addRangeToVector(vector<int>& data, int low, int high);
};

