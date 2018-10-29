#include "stdafx.h"
#include "ItemFlagValue.h"


ItemFlagValue::ItemFlagValue()
{
}

ItemFlagValue::ItemFlagValue(int num)
{
	if ((num & 0x02) == 0x02)
		flags.push_back(ItemFlag::CannotSell);
	if ((num & 0x04) == 0x04)
		flags.push_back(ItemFlag::DamageFlying);
	if ((num & 0x10) == 0x10)
		flags.push_back(ItemFlag::IgnoreLicenses);
	if ((num & 0x20) == 0x20)
		flags.push_back(ItemFlag::OffHand);
	if ((num & 0x40) == 0x40)
		flags.push_back(ItemFlag::HeadArmor);
	if ((num & 0x60) == 0x60)
		flags.push_back(ItemFlag::BodyArmor);
	if ((num & 0x80) == 0x80)
		flags.push_back(ItemFlag::Accessory);
}


ItemFlagValue::~ItemFlagValue()
{
}

int ItemFlagValue::getNumValue()
{
	int num = 0;
	for (int i = 0; i < flags.size(); i++)
		num += int(flags[i]);
	return num;
}

bool ItemFlagValue::hasItemFlag(ItemFlag flag)
{
	return find(flags.begin(), flags.end(), flag) != flags.end();
}
