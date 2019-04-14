#pragma once

#include "ShopRand.h"
#include "CharRand.h"
#include "EnemyRand.h"
#include "TreasureRand.h"
#include "RewardRand.h"

class NoChallengeRand
{
public:
	NoChallengeRand();
	~NoChallengeRand();

	void process(bool noArmor, bool noAccessories, bool noItems, bool noMagick, bool noTechnicks, bool noStarting);
	bool removeItem(int item, bool noArmor, bool noAccessories, bool noItems, bool noMagick, bool noTechnicks);
};

