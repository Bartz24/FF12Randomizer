#pragma once
#include "AugmentData.h"

class AugmentRand
{
private:
	string fileName;

public:
	static AugmentData augmentData[129];
	AugmentRand();
	~AugmentRand();
	void load();
	void save();
	string process(string preset);
	void randValue();
	void addRangeToVector(vector<int>& data, int low, int high);
};

