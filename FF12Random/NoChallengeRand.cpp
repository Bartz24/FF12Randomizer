#include "stdafx.h"
#include "NoChallengeRand.h"


NoChallengeRand::NoChallengeRand()
{
}


NoChallengeRand::~NoChallengeRand()
{
}

void NoChallengeRand::process(bool noArmor, bool noAccessories, bool noItems, bool noMagick, bool noTechnicks, bool noStarting)
{
	for (int i = 0; i < 40; i++)
	{
		if (noStarting && i < 6)
			CharRand::charData[i].weapon = 0xFFFF;
		if (noStarting && i < 6)
			CharRand::charData[i].offHand = 0xFFFF;
		if (noStarting || noArmor)
			CharRand::charData[i].head = 0xFFFF;
		if (noStarting || noArmor)
			CharRand::charData[i].body = 0xFFFF;
		if (noStarting || noAccessories)
			CharRand::charData[i].accessory = 0xFFFF;

		for (int item = 0; item < 10; item++)
		{
			if (noStarting || noItems && CharRand::charData[i].items[item] < 64
				|| noMagick && CharRand::charData[i].items[item] >9000 && CharRand::charData[i].items[item] < 13000
				|| noTechnicks && CharRand::charData[i].items[item] >13000 && CharRand::charData[i].items[item] < 17000)
			{
				CharRand::charData[i].itemCount[item] = 0;
				CharRand::charData[i].items[item] = 0xFFFF;
			}
		}
	}

	if (noStarting)
	{
		for (int data = 32; data < 359; data++)
		{
			LicenseRand::licenseData[data].startingCharacters = 0;
		}
	}

	for (int i = 0; i < 267; i++)
	{
		for (int a = 0; a < ShopRand::shopData[i].itemCount; a++)
		{
			if (removeItem(ShopRand::shopData[i].items[a], noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				ShopRand::shopData[i].items.erase(ShopRand::shopData[i].items.begin() + a);
				ShopRand::shopData[i].itemCount--;
				a--;
			}
		}
	}

	for (int i = 0; i < 127; i++)
	{
		if (ShopRand::bazaarData[i].bazaarType != 0x02)
		{
			if (ShopRand::bazaarData[i].result1Amt > 0 && removeItem(ShopRand::bazaarData[i].result1, noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				ShopRand::bazaarData[i].result1 = 0;
				ShopRand::bazaarData[i].result1Amt = 0;
			}
			if (ShopRand::bazaarData[i].result2Amt > 0 && removeItem(ShopRand::bazaarData[i].result2, noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				ShopRand::bazaarData[i].result2 = 0;
				ShopRand::bazaarData[i].result2Amt = 0;
			}
			if (ShopRand::bazaarData[i].result3Amt > 0 && removeItem(ShopRand::bazaarData[i].result3, noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				ShopRand::bazaarData[i].result3 = 0;
				ShopRand::bazaarData[i].result3Amt = 0;
			}
			if (ShopRand::bazaarData[i].result1Amt == 0 && ShopRand::bazaarData[i].result2Amt == 0 && ShopRand::bazaarData[i].result3Amt == 0)
			{
				ShopRand::bazaarData[i].result1 = Helpers::randInt(24576, 24831);
				ShopRand::bazaarData[i].result1Amt = 1;
			}
		}
	}

	for (int i = 0; i < 279; i++)
	{
		for (int t = 0; t < TreasureRand::mapData[i].count; t++)
		{
			if (removeItem(TreasureRand::mapData[i].treasure[t].common1, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				TreasureRand::mapData[i].treasure[t].common1 = Helpers::randInt(24576, 24831);
			if (removeItem(TreasureRand::mapData[i].treasure[t].common2, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				TreasureRand::mapData[i].treasure[t].common2 = Helpers::randInt(24576, 24831);
			if (removeItem(TreasureRand::mapData[i].treasure[t].rare1, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				TreasureRand::mapData[i].treasure[t].rare1 = Helpers::randInt(24576, 24831);
			if (removeItem(TreasureRand::mapData[i].treasure[t].rare2, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				TreasureRand::mapData[i].treasure[t].rare2 = Helpers::randInt(24576, 24831);
		}
	}

	for (int i = 0; i < 512; i++)
	{
		if (removeItem(RewardRand::rewardData[i].item1, noArmor, noAccessories, noItems, noMagick, noTechnicks))
		{
			RewardRand::rewardData[i].item1 = 0xFFFF;
			RewardRand::rewardData[i].item1Amt = 0xFF;
		}
		if (removeItem(RewardRand::rewardData[i].item2, noArmor, noAccessories, noItems, noMagick, noTechnicks))
		{
			RewardRand::rewardData[i].item2 = 0xFFFF;
			RewardRand::rewardData[i].item2Amt = 0xFF;
		}
		if (RewardRand::rewardData[i].item1 == 0xFFFF && RewardRand::rewardData[i].item2 == 0xFFFF && RewardRand::rewardData[i].gil == 0)
			RewardRand::rewardData[i].gil = 420;
	}

	for (int i = 0; i < EnemyRand::ardData.size(); i++)
	{
		for (int s = 0; s < EnemyRand::ardData[i].section2Data.size(); s++)
		{
			if (removeItem(EnemyRand::ardData[i].section2Data[s].drop01, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].drop01 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].drop05, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].drop05 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].drop25, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].drop25 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].drop40, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].drop40 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].drop100, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].drop100 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].steal03, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].steal03 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].steal10, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].steal10 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].steal55, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].steal55 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].poach05, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].poach05 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].poach95, noArmor, noAccessories, noItems, noMagick, noTechnicks))
				EnemyRand::ardData[i].section2Data[s].poach95 = 0xFFFF;
			if (removeItem(EnemyRand::ardData[i].section2Data[s].monographDrop, noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				EnemyRand::ardData[i].section2Data[s].monographDrop = 0xFFFF;
				EnemyRand::ardData[i].section2Data[s].monographType = 0xFFFF;
				EnemyRand::ardData[i].section2Data[s].monographDropRate = 0;

			}
			if (removeItem(EnemyRand::ardData[i].section2Data[s].canopicJarDrop, noArmor, noAccessories, noItems, noMagick, noTechnicks))
			{
				EnemyRand::ardData[i].section2Data[s].canopicJarDrop = 0xFFFF;
				EnemyRand::ardData[i].section2Data[s].canopicJarType = 0xFFFF;
				EnemyRand::ardData[i].section2Data[s].canopicJarDropRate = 0;
			}
		}
	}
}

bool NoChallengeRand::removeItem(int item, bool noArmor, bool noAccessories, bool noItems, bool noMagick, bool noTechnicks)
{
	bool remove = false;
	if (item < 4600 && item >= 64)
	{
		EquipData equip = EquipRand::equipData[item - 4096];
		ItemFlagValue iFlag{ equip.itemFlag };

		if (noArmor && (iFlag.hasItemFlag(ItemFlag::HeadArmor) || iFlag.hasItemFlag(ItemFlag::BodyArmor)))
			remove = true;

		if (noAccessories && iFlag.hasItemFlag(ItemFlag::Accessory))
			remove = true;
	}

	if (item < 64 && noItems)
		remove = true;

	if (item > 9000 && item < 13000 && noMagick)
		remove = true;

	if (item > 13000 && item < 17000 && noTechnicks)
		remove = true;

	return remove;
}
