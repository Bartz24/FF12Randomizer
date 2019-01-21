#pragma once
#include "AugmentData.h"
#include "FlagGroup.h"

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
	void process(FlagGroup flags);
	void randHPLores(int value);
	void randBattleLores(int value);
	void randMagickLores(int value);
	void randChannelling(int value);
	void randSwiftness(int value);
	void randShieldBlock(int value);
	void randPotionLores(int value);
	void randEtherLores(int value);
	void randPhoenixLores(int value);
};

