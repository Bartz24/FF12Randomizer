#include "stdafx.h"
#include "LicenseRand.h"

LicenseData LicenseRand::licenseData[361] = {};

LicenseRand::LicenseRand()
{
}


LicenseRand::~LicenseRand()
{
}

void LicenseRand::load()
{
	fileName = Helpers::mainPS2DataFolder+"\\image\\ff12\\test_battle\\"+Helpers::language+"\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 361 * 24; //Num licenses * license size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(LicenseData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 361; i++)
		{
			char data[16] = { buffer[i * 24 + 8], buffer[i * 24 + 9], buffer[i * 24 + 10], buffer[i * 24 + 11],
				buffer[i * 24 + 12], buffer[i * 24 + 13], buffer[i * 24 + 14],	buffer[i * 24 + 15],
				buffer[i * 24 + 16], buffer[i * 24 + 17], buffer[i * 24 + 18],	buffer[i * 24 + 19],
				buffer[i * 24 + 20], buffer[i * 24 + 21], buffer[i * 24 + 22], buffer[i * 24 + 23] };
			licenseData[i] = LicenseData{ buffer[i * 24], buffer[i * 24 + 1], buffer[i * 24 + 2], buffer[i * 24 + 3],
				buffer[i * 24 + 4], buffer[i * 24 + 5], buffer[i * 24 + 6],	buffer[i * 24 + 7],
				data };
		}

		delete[] buffer;
	}
}

string LicenseRand::process(string preset)
{
	string flags = preset;
	string eFlags = "!", eFlagsOut = ".", mFlags = "!", mFlagsOut = ".";
	if (flags.find("e-") != string::npos)
	{
		string second = flags.substr(flags.find("e-") + 2, flags.length() - flags.find("e-") - 1);
		eFlags = flags.substr(flags.find("e-") + 2, flags.length() - (second.length() - second.find("-")) - flags.find("e-") - 2);
		flags = flags.substr(0, flags.find('e') + 1) + flags.substr(flags.find('e') + 3 + eFlags.length(), flags.length() - flags.find('e') - 2 - eFlags.length());
	}
	if (flags.find("m-") != string::npos)
	{
		string second = flags.substr(flags.find("m-") + 2, flags.length() - flags.find("m-") - 1);
		mFlags = flags.substr(flags.find("m-") + 2, flags.length() - (second.length() - second.find("-")) - flags.find("m-") - 2);
		flags = flags.substr(0, flags.find('m') + 1) + flags.substr(flags.find('m') + 3 + mFlags.length(), flags.length() - flags.find('m') - 2 - mFlags.length());
	}
	if (flags.find('a') != string::npos)
	{
		randAugments(flags.find('b') != string::npos);
	}
	if (flags.find('e') != string::npos)
	{
		eFlagsOut = randEquipment(eFlags);
		flags = flags.substr(0, flags.find('e')+1) + "-" + eFlagsOut + "-" + flags.substr(flags.find('e') + 1, flags.length() - flags.find('e'));
	}
	if (flags.find('m') != string::npos)
	{
		mFlagsOut = randAbilities(mFlags);
		flags = flags.substr(0, flags.find('m')+1) + "-" + mFlagsOut + "-" + flags.substr(flags.find('m') + 1, flags.length() - flags.find('m'));
	}
	if (flags.find('c') != string::npos)
	{
		if (flags.find('s') != string::npos)
			randCostSmart();
		else
			randCost();
	}
	return flags;
}

void LicenseRand::randCost()
{
	for (int i = 0; i < 361; i++)
	{
		licenseData[i].lpCost = rand() % 256;
	}
}

void LicenseRand::randCostSmart()
{
	for (int i = 0; i < 361; i++)
	{
		//Equip & Magic
		if (i >= 32 && i <= 218 || i >= 276 && i <= 299 || i >= 329 && i <= 359)
		{
			int cost = 0;
			for (int item = 0; item < 8; item++)
			{
				int itemID = licenseData[i].otherData[item];
				if (itemID == 0xFFFF)
					continue;
				if (itemID < 64)
					cost = ItemRand::itemData[itemID].cost;
				else if (itemID < 4600)
					cost = EquipRand::equipData[itemID - 4096].cost;
				else if (itemID < 9000)
					cost = ItemRand::lootData[itemID - 8192].cost;
				else if (itemID < 13000)
					cost = MagicRand::magicData[itemID - 12288].cost;
				else if (itemID < 17000)
					cost = MagicRand::magicData[itemID - 16384 + 81].cost;
				else
					cost = ItemRand::gambitData[itemID - 24576].cost;
			}
			float lpCost = sqrt(float(cost)) / 1.4f;
			lpCost += rand() % 30 - 15;
			licenseData[i].lpCost = unsigned char(max(0.f, min(lpCost, 255.f)));
		}
		else if (i >= 300 && i <= 328 || i >= 219 && i <= 265)
		{
			int augmentID = licenseData[i].otherData[0];
			float lpCost = augmentWorth(augmentID);
			lpCost += rand() % 30 - 15;
			licenseData[i].lpCost = unsigned char(max(0.f, min(lpCost, 255.f)));
		}
		else
		{
			if (rand() % 100 < 77)
				licenseData[i].lpCost = rand() % 128;
			else
				licenseData[i].lpCost = rand() % 256;
		}
	}
}

int LicenseRand::augmentWorth(int index)
{
	AugmentData data = AugmentRand::augmentData[index];

	switch (index)
	{
	case 12: //Gillionaire
	case 15: //Item Reverse
	case 29: //No EXP
	case 31: //Ignore Reflect
	case 32: //Gil Cost
	case 39: //Magick Deprived
	case 50: //Double Edged
	case 116: //Remedy Lore 1
		return 20;
	case 3: //Tactician
	case 4: //Alert
	case 20: //Warmage
	case 21: //Martyr
	case 23: //Headsman
	case 30: //Spellbound
	case 37: //Ignore Traps
	case 86: //Inquisitor
	case 117: //Remedy Lore 2
		return 30;
	case 8: //Spellbreaker
	case 9: //Brawler
	case 10: //Adreneline
	case 40: //Impenetrable Defense
		return 65;
	case 0: //No Knockback
	case 5: //Last Stand
	case 6: //Counter
	case 11: //Focus
	case 14: //Pharmacology
	case 16: //Ignore Environment
	case 58: //Return Damage
	case 103: //Serenity
	case 118: //Remedy Lore 3
		return 70;
	case 2: //Ignore Evasion
	case 7: //Counter Plus
	case 17: //Master Thief
	case 18: //Piercing Magick
	case 25: //Treasure Hunter
	case 48: //Strong Defense
	case 49: //Heavy Hitter
		return 130;
	case 13: //Trigger Happy
	case 36: //Half MP Cost
		return 190;
	case 1: //Safety
	case 27: //Double EXP
	case 28: //Double LP
	case 51: //Mana Spring
	case 53: //Quick Hit
	case 54: //Quick Cast
		return 220;
	case 19: //Magick Lore
	case 22: //Magick Lore
	case 24: //Magick Lore
	case 26: //Magick Lore
	case 35: //Battle Lore
	case 42: //Battle Lore
	case 43: //Battle Lore
	case 44: //Battle Lore
	case 45: //Battle Lore
	case 46: //Battle Lore
	case 47: //Battle Lore
	case 60: //Battle Lore
	case 61: //Battle Lore
	case 62: //Battle Lore
	case 63: //Battle Lore
	case 64: //Battle Lore
	case 65: //Battle Lore
	case 66: //Battle Lore
	case 67: //Battle Lore
	case 68: //Battle Lore
	case 69: //Magick Lore
	case 70: //Magick Lore
	case 71: //Magick Lore
	case 72: //Magick Lore
	case 73: //Magick Lore
	case 87: //Magick Lore
	case 97: //Magick Lore
	case 98: //Magick Lore
	case 99: //Magick Lore
	case 100: //Magick Lore
	case 101: //Magick Lore
	case 102: //Magick Lore
		return int(14.5f * pow(2.1f, data.value));
	case 74: //HP Lore
	case 75: //HP Lore
	case 76: //HP Lore
	case 77: //HP Lore
	case 78: //HP Lore
	case 79: //HP Lore
	case 80: //HP Lore
	case 81: //HP Lore
	case 82: //HP Lore
	case 83: //HP Lore
	case 84: //HP Lore
	case 85: //HP Lore
		return int(sqrt(60.f*data.value));
	case 88: //Shield Block
	case 89: //Shield Block
	case 90: //Shield Block
	case 91: //Channeling
	case 92: //Channeling
	case 93: //Channeling
	case 94: //Swiftness
	case 95: //Swiftness
	case 96: //Swiftness
	case 119: //Potion Lore
	case 120: //Potion Lore
	case 121: //Potion Lore
	case 122: //Ether Lore
	case 123: //Ether Lore
	case 124: //Ether Lore
	case 125: //Phoenix Lore
	case 126: //Phoenix Lore
	case 127: //Phoenix Lore
		return int(12.5f * pow(1.1f, data.value));
	default:
		return 50;
	}
}

//Swords		License IDs: 32-39, 329-331
//				Equip IDs:	 4097-4113, 4256-4257, 4260-4264, 4273, 4288, 4290
//Greatswords	License IDs: 40-44, 332-333
//				Equip IDs:	 4114-4120, 4258-4259, 4262, 4265, 4269, 4289
//Katanas		License IDs: 45-49, 334-335
//				Equip IDs:	 4121-4130, 4266
//Ninja Swords	License IDs: 50-52, 336
//				Equip IDs:	 4131-4137, 4267
//Spears		License IDs: 53-59, 337
//				Equip IDs:	 4138-4149, 4270
//Poles			License IDs: 60-65, 338-339
//				Equip IDs:	 4150-4161, 4294
//Bows			License IDs: 66-72, 340-341
//				Equip IDs:	 4162-4175, 4274, 4295
//Crossbows		License IDs: 73-76
//				Equip IDs:	 4177-4182, 4272
//Guns			License IDs: 77-82, 342
//				Equip IDs:	 4183-4193, 4293
//Axes&Hammers	License IDs: 83-89, 343
//				Equip IDs:	 4194-4205, 4292
//Daggers		License IDs: 90-95, 344
//				Equip IDs:	 4206-4216, 4268
//Rods			License IDs: 96-100
//				Equip IDs:	 4217-4224
//Staves		License IDs: 101-105, 345
//				Equip IDs:	 4225-4234
//Maces			License IDs: 106-110
//				Equip IDs:	 4235-4243, 4255, 4271
//Measures		License IDs: 111-113, 346
//				Equip IDs:	 4244-4249
//Hand-bombs	License IDs: 114-116, 347
//				Equip IDs:	 4250-4254, 4291
//Shields		License IDs: 117-125, 348
//				Equip IDs:	 4297-4315
//Heavy Armor	License IDs: 126-136, 349-350
//				Equip IDs:	 4358-4375, 4418-4435
//Light Armor	License IDs: 137-148, 351
//				Equip IDs:	 4316-4336, 4376-4396
//Mystic Armor	License IDs: 149-160, 352
//				Equip IDs:	 4337-4357, 4397-4417
//Accessories	License IDs: 161-181, 353-354
//				Equip IDs:	 4436-4483
//All			License IDs: 32-181, 329-354
//				Equip IDs:	 4097-4255, 4258-4259, 4264, 4266-4274, 4288-4483


string LicenseRand::randEquipment(string preset)
{
	string flags = preset;
	if (flags.find('a') != string::npos)
	{
		if (flags.find('n') != string::npos)
		{
			vector<unsigned short> equip = vector<unsigned short>();
			extractAbilities(equip, 32, 181, true);
			extractAbilities(equip, 329, 354, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(32, 181, equip);
				replaceAbilitiesChance(329, 354, equip);
			}
		}
		else
		{
			vector<unsigned short> equip = vector<unsigned short>();
			extractAbilities(equip, 32, 181, false);
			extractAbilities(equip, 329, 354, false);
			replaceAbilities(32, 181, equip);
			replaceAbilities(329, 354, equip);
		}
	}
	else
	{
		if (flags.find('n') != string::npos)
		{
			//Swords
			vector<unsigned short> equip = vector<unsigned short>();
			extractAbilities(equip, 32, 39, true);
			extractAbilities(equip, 329, 331, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(32, 39, equip);
				replaceAbilitiesChance(329, 331, equip);
			}
			//Greatswords
			equip = vector<unsigned short>();
			extractAbilities(equip, 40, 44, true);
			extractAbilities(equip, 332, 333, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(40, 44, equip);
				replaceAbilitiesChance(332, 333, equip);
			}

			//Katanas
			equip = vector<unsigned short>();
			extractAbilities(equip, 45, 49, true);
			extractAbilities(equip, 334, 335, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(45, 49, equip);
				replaceAbilitiesChance(334, 335, equip);
			}

			//Ninja Swords
			equip = vector<unsigned short>();
			extractAbilities(equip, 50, 52, true);
			extractAbilities(equip, 336, 336, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(50, 52, equip);
				replaceAbilitiesChance(336, 336, equip);
			}

			//Spears
			equip = vector<unsigned short>();
			extractAbilities(equip, 53, 59, true);
			extractAbilities(equip, 337, 337, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(53, 59, equip);
				replaceAbilitiesChance(337, 337, equip);
			}

			//Poles
			equip = vector<unsigned short>();
			extractAbilities(equip, 60, 65, true);
			extractAbilities(equip, 338, 339, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(60, 65, equip);
				replaceAbilitiesChance(338, 339, equip);
			}

			//Bows
			equip = vector<unsigned short>();
			extractAbilities(equip, 66, 72, true);
			extractAbilities(equip, 340, 341, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(60, 72, equip);
				replaceAbilitiesChance(340, 341, equip);
			}

			//Crossbows
			equip = vector<unsigned short>();
			extractAbilities(equip, 73, 76, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(73, 76, equip);
			}

			//Guns
			equip = vector<unsigned short>();
			extractAbilities(equip, 77, 82, true);
			extractAbilities(equip, 342, 342, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(77, 82, equip);
				replaceAbilitiesChance(342, 342, equip);
			}

			//Axes & Hammers
			equip = vector<unsigned short>();
			extractAbilities(equip, 83, 89, true);
			extractAbilities(equip, 343, 343, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(83, 89, equip);
				replaceAbilitiesChance(343, 343, equip);
			}

			//Daggers
			equip = vector<unsigned short>();
			extractAbilities(equip, 90, 95, true);
			extractAbilities(equip, 344, 344, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(90, 95, equip);
				replaceAbilitiesChance(344, 344, equip);
			}

			//Rods
			equip = vector<unsigned short>();
			extractAbilities(equip, 96, 100, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(96, 100, equip);
			}

			//Staves
			equip = vector<unsigned short>();
			extractAbilities(equip, 101, 105, true);
			extractAbilities(equip, 345, 345, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(101, 105, equip);
				replaceAbilitiesChance(345, 345, equip);
			}

			//Maces
			equip = vector<unsigned short>();
			extractAbilities(equip, 106, 110, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(106, 110, equip);
			}

			//Measures
			equip = vector<unsigned short>();
			extractAbilities(equip, 111, 113, true);
			extractAbilities(equip, 346, 346, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(111, 113, equip);
				replaceAbilitiesChance(346, 346, equip);
			}

			//Hand-bombs
			equip = vector<unsigned short>();
			extractAbilities(equip, 114, 116, true);
			extractAbilities(equip, 347, 347, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(114, 116, equip);
				replaceAbilitiesChance(347, 347, equip);
			}

			//Shields
			equip = vector<unsigned short>();
			extractAbilities(equip, 117, 125, true);
			extractAbilities(equip, 348, 348, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(117, 125, equip);
				replaceAbilitiesChance(348, 348, equip);
			}

			//Heavy Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 126, 136, true);
			extractAbilities(equip, 349, 350, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(126, 136, equip);
				replaceAbilitiesChance(349, 350, equip);
			}

			//Light Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 137, 148, true);
			extractAbilities(equip, 351, 351, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(137, 148, equip);
				replaceAbilitiesChance(351, 351, equip);
			}

			//Mystic Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 149, 160, true);
			extractAbilities(equip, 352, 352, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(149, 160, equip);
				replaceAbilitiesChance(352, 352, equip);
			}

			//Accessories
			equip = vector<unsigned short>();
			extractAbilities(equip, 161, 181, true);
			extractAbilities(equip, 353, 354, true);
			while (equip.size() > 0)
			{
				replaceAbilitiesChance(161, 181, equip);
				replaceAbilitiesChance(353, 354, equip);
			}

		}
		else
		{
			//Swords
			vector<unsigned short> equip = vector<unsigned short>();
			extractAbilities(equip, 32, 39, false);
			extractAbilities(equip, 329, 331, false);
			replaceAbilities(32, 39, equip);
			replaceAbilities(329, 331, equip);

			//Greatswords
			equip = vector<unsigned short>();
			extractAbilities(equip, 40, 44, false);
			extractAbilities(equip, 332, 333, false);
			replaceAbilities(40, 44, equip);
			replaceAbilities(332, 333, equip);

			//Katanas
			equip = vector<unsigned short>();
			extractAbilities(equip, 45, 49, false);
			extractAbilities(equip, 334, 335, false);
			replaceAbilities(45, 49, equip);
			replaceAbilities(334, 335, equip);

			//Ninja Swords
			equip = vector<unsigned short>();
			extractAbilities(equip, 50, 52, false);
			extractAbilities(equip, 336, 336, false);
			replaceAbilities(50, 52, equip);
			replaceAbilities(336, 336, equip);

			//Spears
			equip = vector<unsigned short>();
			extractAbilities(equip, 53, 59, false);
			extractAbilities(equip, 337, 337, false);
			replaceAbilities(53, 59, equip);
			replaceAbilities(337, 337, equip);

			//Poles
			equip = vector<unsigned short>();
			extractAbilities(equip, 60, 65, false);
			extractAbilities(equip, 338, 339, false);
			replaceAbilities(60, 65, equip);
			replaceAbilities(338, 339, equip);

			//Bows
			equip = vector<unsigned short>();
			extractAbilities(equip, 66, 72, false);
			extractAbilities(equip, 340, 341, false);
			replaceAbilities(60, 72, equip);
			replaceAbilities(340, 341, equip);

			//Crossbows
			equip = vector<unsigned short>();
			extractAbilities(equip, 73, 76, false);
			replaceAbilities(73, 76, equip);

			//Guns
			equip = vector<unsigned short>();
			extractAbilities(equip, 77, 82, false);
			extractAbilities(equip, 342, 342, false);
			replaceAbilities(77, 82, equip);
			replaceAbilities(342, 342, equip);

			//Axes & Hammers
			equip = vector<unsigned short>();
			extractAbilities(equip, 83, 89, false);
			extractAbilities(equip, 343, 343, false);
			replaceAbilities(83, 89, equip);
			replaceAbilities(343, 343, equip);

			//Daggers
			equip = vector<unsigned short>();
			extractAbilities(equip, 90, 95, false);
			extractAbilities(equip, 344, 344, false);
			replaceAbilities(90, 95, equip);
			replaceAbilities(344, 344, equip);

			//Rods
			equip = vector<unsigned short>();
			extractAbilities(equip, 96, 100, false);
			replaceAbilities(96, 100, equip);

			//Staves
			equip = vector<unsigned short>();
			extractAbilities(equip, 101, 105, false);
			extractAbilities(equip, 345, 345, false);
			replaceAbilities(101, 105, equip);
			replaceAbilities(345, 345, equip);

			//Maces
			equip = vector<unsigned short>();
			extractAbilities(equip, 106, 110, false);
			replaceAbilities(106, 110, equip);

			//Measures
			equip = vector<unsigned short>();
			extractAbilities(equip, 111, 113, false);
			extractAbilities(equip, 346, 346, false);
			replaceAbilities(111, 113, equip);
			replaceAbilities(346, 346, equip);

			//Hand-bombs
			equip = vector<unsigned short>();
			extractAbilities(equip, 114, 116, false);
			extractAbilities(equip, 347, 347, false);
			replaceAbilities(114, 116, equip);
			replaceAbilities(347, 347, equip);

			//Shields
			equip = vector<unsigned short>();
			extractAbilities(equip, 117, 125, false);
			extractAbilities(equip, 348, 348, false);
			replaceAbilities(117, 125, equip);
			replaceAbilities(348, 348, equip);

			//Heavy Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 126, 136, false);
			extractAbilities(equip, 349, 350, false);
			replaceAbilities(126, 136, equip);
			replaceAbilities(349, 350, equip);

			//Light Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 137, 148, false);
			extractAbilities(equip, 351, 351, false);
			replaceAbilities(137, 148, equip);
			replaceAbilities(351, 351, equip);

			//Mystic Armor
			equip = vector<unsigned short>();
			extractAbilities(equip, 149, 160, false);
			extractAbilities(equip, 352, 352, false);
			replaceAbilities(149, 160, equip);
			replaceAbilities(352, 352, equip);

			//Accessories
			equip = vector<unsigned short>();
			extractAbilities(equip, 161, 181, false);
			extractAbilities(equip, 353, 354, false);
			replaceAbilities(161, 181, equip);
			replaceAbilities(353, 354, equip);
		}
	}
	return flags;
}

void LicenseRand::randAugments(bool includeBad)
{
	vector<int> augments = vector<int>();
	addRangeToVector(augments, 0, 11);
	addRangeToVector(augments, 13, 14);
	addRangeToVector(augments, 16, 28);
	augments.push_back(30);
	addRangeToVector(augments, 35, 37);
	augments.push_back(40);
	addRangeToVector(augments, 42, 49);
	augments.push_back(51);
	addRangeToVector(augments, 53, 54);
	augments.push_back(58);
	addRangeToVector(augments, 60, 103);
	addRangeToVector(augments, 116, 127);
	if (includeBad)
	{
		augments.push_back(12);
		augments.push_back(15);
		augments.push_back(29);
		augments.push_back(31);
		augments.push_back(32);
		augments.push_back(39);
		augments.push_back(50);
	}
	for (int i = 0; i < 361; i++)
	{
		if (i >= 300 && i <= 328 || i >= 219 && i <= 265)
		{
			int index = rand() % augments.size();
			licenseData[i].otherData[0] = augments[index];
			augments.erase(augments.begin() + index);
		}
	}
}

void LicenseRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}

//White		License IDs:	182-189, 355, 208-211
//			Magic IDs:		0-17,51-56,69
//Black		License IDs:	190-197, 356, 358, 215-217
//			Magic IDs:		18-33,35,57,59-65
//Time		License IDs:	198-204, 357, 359, 218
//			Magic IDs:		36-50,67,71-72,79-80
//Green		License IDs:	205-207
//			Magic IDs:		58,66,70,73-75
//Arcane	License IDs:	212-214
//			Magic IDs:		76-78,68,34
//Technick	License IDs:	276-299
//			Magic IDs:		158-181
//All		License IDs:	182-218, 276-299, 355-359



string LicenseRand::randAbilities(string preset)
{
	string flags = preset;
	if (flags.find('a') != string::npos)
	{
		if (flags.find('n') != string::npos)
		{
			vector<unsigned short> abilities = vector<unsigned short>();
			extractAbilities(abilities, 182, 218, true);
			extractAbilities(abilities, 276, 299, true);
			extractAbilities(abilities, 355, 359, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(182, 218, abilities);
				replaceAbilitiesChance(276, 299, abilities);
				replaceAbilitiesChance(355, 359, abilities);
			}
		}
		else
		{
			vector<unsigned short> abilities = vector<unsigned short>();
			extractAbilities(abilities, 182, 218, false);
			extractAbilities(abilities, 276, 299, false);
			extractAbilities(abilities, 355, 359, false);
			replaceAbilities(182, 218, abilities);
			replaceAbilities(276, 299, abilities);
			replaceAbilities(355, 359, abilities);
		}
	}
	else
	{
		if (flags.find('n') != string::npos)
		{
			//White
			vector<unsigned short> abilities = vector<unsigned short>();
			extractAbilities(abilities, 182, 189, true);
			extractAbilities(abilities, 355, 355, true);
			extractAbilities(abilities, 208, 211, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(182, 189, abilities);
				replaceAbilitiesChance(355, 355, abilities);
				replaceAbilitiesChance(208, 211, abilities);
			}

			//Black
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 190, 197, true);
			extractAbilities(abilities, 356, 356, true);
			extractAbilities(abilities, 358, 358, true);
			extractAbilities(abilities, 215, 217, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(190, 197, abilities);
				replaceAbilitiesChance(356, 356, abilities);
				replaceAbilitiesChance(358, 358, abilities);
				replaceAbilitiesChance(215, 217, abilities);
			}

			//Time
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 198, 204, true);
			extractAbilities(abilities, 357, 357, true);
			extractAbilities(abilities, 359, 359, true);
			extractAbilities(abilities, 218, 218, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(198, 204, abilities);
				replaceAbilitiesChance(357, 357, abilities);
				replaceAbilitiesChance(359, 359, abilities);
				replaceAbilitiesChance(218, 218, abilities);
			}

			//Green
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 205, 207, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(205, 207, abilities);
			}

			//Arcane
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 212, 214, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(212, 214, abilities);
			}

			//Technicks
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 276, 299, true);
			while (abilities.size() > 0)
			{
				replaceAbilitiesChance(276, 299, abilities);
			}
		}
		else
		{
			//White
			vector<unsigned short> abilities = vector<unsigned short>();
			extractAbilities(abilities, 182, 189, false);
			extractAbilities(abilities, 355, 355, false);
			extractAbilities(abilities, 208, 211, false);
			replaceAbilities(182, 189, abilities);
			replaceAbilities(355, 355, abilities);
			replaceAbilities(208, 211, abilities);

			//Black
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 190, 197, false);
			extractAbilities(abilities, 356, 356, false);
			extractAbilities(abilities, 358, 358, false);
			extractAbilities(abilities, 215, 217, false);
			replaceAbilities(190, 197, abilities);
			replaceAbilities(356, 356, abilities);
			replaceAbilities(358, 358, abilities);
			replaceAbilities(215, 217, abilities);

			//Time
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 198, 204, false);
			extractAbilities(abilities, 357, 357, false);
			extractAbilities(abilities, 359, 359, false);
			extractAbilities(abilities, 218, 218, false);
			replaceAbilities(198, 204, abilities);
			replaceAbilities(357, 357, abilities);
			replaceAbilities(359, 359, abilities);
			replaceAbilities(218, 218, abilities);

			//Green
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 205, 207, false);
			replaceAbilities(205, 207, abilities);

			//Arcane
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 212, 214, false);
			replaceAbilities(212, 214, abilities);

			//Technicks
			abilities = vector<unsigned short>();
			extractAbilities(abilities, 276, 299, false);
			replaceAbilities(276, 299, abilities);
		}
	}
	return flags;
}

void LicenseRand::replaceAbilitiesChance(int start, int end, std::vector<unsigned short> &abilities)
{
	for (int i = start; i <= end; i++)
	{
		if (abilities.size() == 0)
			break;
		int slots = 0;
		for (int slot = 0; slot < 8; slot++)
		{
			if (licenseData[i].otherData[slot] != 0xFFFF)
				slots++;
		}
		if (slots == 0 || (slots < 4 && rand() % 100 < 20))
		{
			int index = rand() % abilities.size();
			licenseData[i].otherData[slots] = abilities[index];
			abilities.erase(abilities.begin() + index);
		}
	}
}

void LicenseRand::replaceAbilities(int start, int end, std::vector<unsigned short> &abilities)
{
	for (int i = start; i <= end; i++)
	{
		int slots = 0;
		for (int slot = 0; slot < 8; slot++)
		{
			if (licenseData[i].otherData[slot] != 0xFFFF)
				slots++;
		}
		for (int slot = 0; slot<slots; slot++)
		{
			int index = rand() % abilities.size();
			licenseData[i].otherData[slot] = abilities[index];
			abilities.erase(abilities.begin() + index);
		}
	}
}

void LicenseRand::extractAbilities(vector<unsigned short> &abilities, int start, int end, bool clear)
{
	for (int i = start; i <= end; i++)
	{
		for (int slot = 0; slot < 8; slot++)
		{
			if (licenseData[i].otherData[slot] != 0xFFFF)
				abilities.push_back(licenseData[i].otherData[slot]);
			if (clear)
				licenseData[i].otherData[slot] = 0xFFFF;
		}
	}
}


void LicenseRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 361 * 24; //Num licenses * license size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(LicenseData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 361; i++)
	{
		LicenseData d = licenseData[i];
		buffer[i * 24] = U{ d.licenseName }.c[1];
		buffer[i * 24 + 1] = U{ d.licenseName }.c[0];
		buffer[i * 24 + 2] = d.licenseGroup;
		buffer[i * 24 + 3] = d.unknown;
		buffer[i * 24 + 4] = d.lpCost;
		buffer[i * 24 + 5] = d.licenseSubgroup;
		buffer[i * 24 + 6] = d.licenseMechanic;
		buffer[i * 24 + 7] = d.startingCharacters;
		for (int i2 = 0; i2 < 8; i2++)
		{
			buffer[i * 24 + i2 * 2 + 8] = U{ d.otherData[i2] }.c[0];
			buffer[i * 24 + i2 * 2 + 9] = U{ d.otherData[i2] }.c[1];
		}
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}
