#pragma once
#include <vector>

using namespace std;

enum class ItemFlag
{
	CannotSell = 0x02,
	DamageFlying = 0x04,
	IgnoreLicenses = 0x10,
	OffHand = 0x20,
	HeadArmor = 0x40,
	BodyArmor = 0x60,
	Accessory = 0x80
};

class ItemFlagValue
{
public:
	ItemFlagValue();
	ItemFlagValue(int num);
	~ItemFlagValue();
	vector<ItemFlag> flags;
	int getNumValue();
	bool hasItemFlag(ItemFlag flag);
};

