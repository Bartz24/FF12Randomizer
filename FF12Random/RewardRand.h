#pragma once
#include "RewardData.h"

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
	string process(string preset);
	void randValue();
	void addRangeToVector(vector<int>& data, int low, int high);
};

