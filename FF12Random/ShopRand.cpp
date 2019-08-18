#include "stdafx.h"
#include "ShopRand.h"

ShopData ShopRand::shopData[267] = {};
BazaarData ShopRand::bazaarData[128] = {};

ShopRand::ShopRand()
{
}


ShopRand::~ShopRand()
{
}

void ShopRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 0x2E74; //Num shop * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(Helpers::getPointer(fileName, 0x9C, 0xC28));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		int offset = 0;

		int shopCount = 0;

		while (offset < size)
		{
			if (buffer[offset] == 0x64 && buffer[offset + 1] == 0x02 && buffer[offset + 2] == 0x00 && buffer[offset + 3] == 0x00)
			{
				char sizeA[] = { buffer[offset + 4] , buffer[offset + 5] };
				unsigned short size = *reinterpret_cast<unsigned short*>(sizeA);
				char countA[] = { buffer[offset + 6] , buffer[offset + 7] };
				unsigned short count = *reinterpret_cast<unsigned short*>(countA);
				vector<unsigned short> items = vector<unsigned short>();
				for (int i = 0; i < count; i++)
				{
					char itemA[] = { buffer[offset + 12 + i * 2] , buffer[offset + 13 + i * 2] };
					items.push_back(*reinterpret_cast<unsigned short*>(itemA));
				}
				shopData[shopCount] = ShopData{ offset, buffer[offset], buffer[offset + 1] , buffer[offset + 2] , buffer[offset + 3],
					size, count, buffer[offset + 8], buffer[offset + 9], buffer[offset + 10], buffer[offset + 11], items };
				shopCount++;
			}
			offset += 4;
		}

		delete[] buffer;
	}
	char * buffer;
	long size = 128 * 36; //Num bazaar * data size
	ifstream file(fileName, ios::in | ios::binary | ios::ate);
	file.seekg(Helpers::getPointer(fileName, 0xB0));
	buffer = new char[size];
	file.read(buffer, size);
	file.close();

	for (int i = 0; i < 128; i++)
	{
		char data[36];
		for (int i2 = 0; i2 < 36; i2++)
		{
			data[i2] = buffer[i * 36 + i2];
		}
		bazaarData[i] = BazaarData{ data };
	}

	delete[] buffer;
}

void ShopRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	union U2 {
		unsigned int i;
		unsigned char c[2];
	}byte2;

	for (int i = 0; i < 267; i++)
	{
		char * buffer;
		long size = 12 + shopData[i].itemCount * 2; //Num shop * data size
		fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
		file.seekp(Helpers::getPointer(fileName, 0x9C, 0xC28) + shopData[i].position);
		buffer = new char[size];

		ShopData d = shopData[i];
		buffer[0] = d.header1;
		buffer[1] = d.header2;
		buffer[2] = d.empty1;
		buffer[3] = d.empty2;
		buffer[4] = U{ d.itemSize }.c[0];
		buffer[5] = U{ d.itemSize }.c[1];
		buffer[6] = U{ d.itemCount }.c[0];
		buffer[7] = U{ d.itemCount }.c[1];
		buffer[8] = d.address1;
		buffer[9] = d.address2;
		buffer[10] = d.address3;
		buffer[11] = d.address4;
		for (int item = 0; item < d.itemCount; item++)
		{
			buffer[12 + item * 2] = U{ d.items[item] }.c[0];
			buffer[13 + item * 2] = U{ d.items[item] }.c[1];
		}

		file.write(buffer, size);
		file.close();

		delete[] buffer;
	}

	char * buffer;
	long size = 128 * 36; //Num bazaar * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(Helpers::getPointer(fileName, 0xB0));
	buffer = new char[size];

	for (int i = 0; i < 128; i++)
	{
		BazaarData d = bazaarData[i];
		int index = 0;
		for (int i2 = 0; i2 < 36; i2++)
		{
			if (i2 >= 0x04 && i2 <= 0x06 || i2 >= 0x08 && i2 <= 0x0A || i2 >= 0x0C && i2 <= 0x0E || i2 >= 0x10 && i2 <= 0x14 ||
				i2 >= 0x16 && i2 <= 0x18 || i2 >= 0x1A && i2 <= 0x1C || i2 >= 0x1E && i2 <= 0x20)
				continue;
			buffer[i * 36 + i2] = d.unknown[index];
			index++;
		}
		buffer[i * 36 + 0x04] = U{ d.result1 }.c[0];
		buffer[i * 36 + 0x05] = U{ d.result1 }.c[1];
		buffer[i * 36 + 0x06] = d.result1Amt;
		buffer[i * 36 + 0x08] = U{ d.result2 }.c[0];
		buffer[i * 36 + 0x09] = U{ d.result2 }.c[1];
		buffer[i * 36 + 0x0A] = d.result2Amt;
		buffer[i * 36 + 0x0C] = U{ d.result3 }.c[0];
		buffer[i * 36 + 0x0D] = U{ d.result3 }.c[1];
		buffer[i * 36 + 0x0E] = d.result3Amt;
		buffer[i * 36 + 0x10] = U2{ d.cost }.c[0];
		buffer[i * 36 + 0x11] = U2{ d.cost }.c[1];
		buffer[i * 36 + 0x12] = U2{ d.cost }.c[2];
		buffer[i * 36 + 0x13] = U2{ d.cost }.c[3];
		buffer[i * 36 + 0x14] = d.bazaarType;
		buffer[i * 36 + 0x16] = U{ d.loot1 }.c[0];
		buffer[i * 36 + 0x17] = U{ d.loot1 }.c[1];
		buffer[i * 36 + 0x18] = d.loot1Amt;
		buffer[i * 36 + 0x1A] = U{ d.loot2 }.c[0];
		buffer[i * 36 + 0x1B] = U{ d.loot2 }.c[1];
		buffer[i * 36 + 0x1C] = d.loot2Amt;
		buffer[i * 36 + 0x1E] = U{ d.loot3 }.c[0];
		buffer[i * 36 + 0x1F] = U{ d.loot3 }.c[1];
		buffer[i * 36 + 0x20] = d.loot3Amt;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}

void ShopRand::process(FlagGroup flags)
{
	if (flags.hasFlag("s"))
	{
		randShops(flags);
	}
	if (flags.hasFlag("b"))
	{
		replaceBazaarRecipes(flags);
	}
}

//Usable Items:		0-28, 42-63
//Loot:				8192, 8224-8437 8448-8461 8468-8471
//Magic:			12288-12368
//Technicks:		16384-16407
//Gambits:			24576-24831
//Equipment:		4097-4255, 4258-4259, 4264, 4266-4274, 4288-4515

void ShopRand::randShops(FlagGroup flags)
{
	if (flags.hasFlag("n"))
	{
		for (int i = 0; i < 267; i++)
		{
			shopData[i].itemCount = 0;
		}

		return;
	}

	vector<int> data = vector<int>();
	addAllShopItems(data, flags);
	for (int i = 0; i < 267; i++)
	{
		unsigned long gil = 0;
		for (int c = 0; c < shopData[i].itemCount; c++)
		{
			gil += int(double(Helpers::randIntWeibull(0, 60000, 1000, 1.2)) * (1.0 - 0.0025 * shopData[i].itemCount));
		}
		for (int item = 0; item < shopData[i].itemCount; item++)
		{
			if (data.size() == 0)
				addAllShopItems(data, flags);
			int itemID, cost = 99999, attempts = 0, itemIDindex;
			if (gil > 0) {
				do
				{
					itemIDindex = Helpers::randInt(0, data.size() - 1);
					itemID = data[itemIDindex];
					cost = getCostOfItem(itemID);
					attempts++;

				} while (attempts < 100 && (find(shopData[i].items.begin(), shopData[i].items.end(), itemID) != shopData[i].items.end() || cost >= gil));
			}
			
			if (gil <= 0 || attempts >= 100)
			{
				do {
					itemID = Helpers::randInt(24576, 24830);
				} while (find(shopData[i].items.begin(), shopData[i].items.end(), itemID) != shopData[i].items.end());
				gil = 0;
				cost = 0;
			}
			if (itemID < 17000)
				data.erase(data.begin() + itemIDindex);
			gil -= cost;
			shopData[i].items[item] = itemID;
		}
	}
}

void ShopRand::addAllShopItems(vector<int>& data, FlagGroup flags)
{
	addShopItems(data, 0, 28, flags);
	addShopItems(data, 42, 63, flags);
	addShopItems(data, 8192, 8192, flags);
	addShopItems(data, 8224, 8437, flags);
	addShopItems(data, 8448, 8461, flags);
	addShopItems(data, 8468, 8471, flags);
	addShopItems(data, 12288, 12368, flags);
	addShopItems(data, 16384, 16407, flags);
	addShopItems(data, 4097, 4255, flags);
	addShopItems(data, 4258, 4259, flags);
	addShopItems(data, 4264, 4264, flags);
	addShopItems(data, 4266, 4274, flags);
	addShopItems(data, 4288, 4515, flags);
}

void ShopRand::addShopItems(vector<int>& data, int low, int high, FlagGroup flags)
{
	for (int i = low; i <= high; i++)
	{
		if (i == 24 && flags.hasFlag("d"))
			continue;
		if (i < 4600 && i >= 64)
		{
			EquipData equip = EquipRand::equipData[i - 4096];
			ItemFlagValue iFlag{ equip.itemFlag };

			if (flags.hasFlag("a") && (iFlag.hasItemFlag(ItemFlag::BodyArmor) || iFlag.hasItemFlag(ItemFlag::HeadArmor)) && (equip.def > flags.getFlag("a").getValue() || equip.mRes > flags.getFlag("a").getValue()))
				continue;
			if (flags.hasFlag("h") && iFlag.hasItemFlag(ItemFlag::OffHand) && equip.equipRequirements == 0x12 && (equip.def > flags.getFlag("h").getValue() || equip.mRes > flags.getFlag("h").getValue()))
				continue;
			if (flags.hasFlag("w") && !iFlag.hasItemFlag(ItemFlag::OffHand) && !iFlag.hasItemFlag(ItemFlag::Accessory) && !iFlag.hasItemFlag(ItemFlag::BodyArmor)
				&& !iFlag.hasItemFlag(ItemFlag::HeadArmor) && equip.power > flags.getFlag("w").getValue())
				continue;
		}
		if (flags.hasFlag("e") && getCostOfItem(i) > flags.getFlag("e").getValue())
			continue;
		data.push_back(i);
	}
}

void ShopRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}

void ShopRand::replaceBazaarRecipes(FlagGroup flags)
{
	vector<int> data = vector<int>();
	addRangeToVector(data, 0, 28);
	addRangeToVector(data, 42, 63);
	addRangeToVector(data, 8192, 8192);
	addRangeToVector(data, 8224, 8437);
	addRangeToVector(data, 8448, 8461);
	addRangeToVector(data, 8468, 8471);
	addRangeToVector(data, 12288, 12368);
	addRangeToVector(data, 16384, 16407);
	addRangeToVector(data, 4097, 4255);
	addRangeToVector(data, 4258, 4259);
	addRangeToVector(data, 4264, 4264);
	addRangeToVector(data, 4266, 4274);
	addRangeToVector(data, 4288, 4515);

	vector<int> lootData = vector<int>();
	addRangeToVector(lootData, 8192, 8192);
	addRangeToVector(lootData, 8224, 8437);
	addRangeToVector(lootData, 8448, 8461);
	addRangeToVector(lootData, 8468, 8471);

	if (flags.hasFlag("p"))
	{
		for (int i = data.size() - 1; i >= 0; i--)
		{
			int cost = getCostOfItem(data[i]);
			if (cost < flags.getFlag("p").getValue())
				data.erase(data.begin() + i);
		}
	}
	for (int i = 0; i < 127; i++)
	{
		if (bazaarData[i].bazaarType != 0x02)
		{
			bazaarData[i].result1 = bazaarData[i].result2 = bazaarData[i].result3 = 0;
			bazaarData[i].result1Amt = bazaarData[i].result2Amt = bazaarData[i].result3Amt = 0;
			bazaarData[i].loot1 = bazaarData[i].loot2 = bazaarData[i].loot3 = 0;
			bazaarData[i].loot1Amt = bazaarData[i].loot2Amt = bazaarData[i].loot3Amt = 0;
			if (flags.hasFlag("z"))
				bazaarData[i].cost = 0;
			bazaarData[i].bazaarType = 0;
		}
		else
		{
			if (flags.hasFlag("z"))
				bazaarData[i].cost = Helpers::randWeibullControl(100, 10000000, 100000, 1.2, flags.getFlag("z").getValue());
		}
	}
	
	while (data.size() > 0)
	{
		bool filled = false;
		for (int i = 0; i < 127; i++)
		{
			if (bazaarData[i].bazaarType != 0x02)
			{
				if (bazaarData[i].result1 == 0x0000)
				{
					filled = true;
					data.erase(data.begin() + setItem(data, bazaarData[i].result1, bazaarData[i].result1Amt, false, flags));
					setItem(lootData, bazaarData[i].loot1, bazaarData[i].loot1Amt, true, flags);
					int randNum = Helpers::randInt(0, 99);
					if (randNum < 75)
						setItem(lootData, bazaarData[i].loot2, bazaarData[i].loot2Amt, true, flags);
					if (randNum < 50)
						setItem(lootData, bazaarData[i].loot3, bazaarData[i].loot3Amt, true, flags);
					if (flags.hasFlag("z"))
						bazaarData[i].cost = Helpers::randWeibullControl(100, 10000000, 100000, 1.2, flags.getFlag("z").getValue());
				}
				else if (bazaarData[i].result2 == 0x0000)
				{

					filled = true;	data.erase(data.begin() + setItem(data, bazaarData[i].result2, bazaarData[i].result2Amt, false, flags));
				}
				else if (bazaarData[i].result3 == 0x0000)
				{
					filled = true;
					data.erase(data.begin() + setItem(data, bazaarData[i].result3, bazaarData[i].result3Amt, false, flags));
				}

				bazaarData[i].bazaarType = 0x01;
			}
			if (data.size() == 0)
				break;
		}
		if (!filled)
			break;
	}


	data = vector<int>();
	addRangeToVector(data, 0, 28);
	addRangeToVector(data, 42, 63);
	addRangeToVector(data, 8192, 8192);
	addRangeToVector(data, 8224, 8437);
	addRangeToVector(data, 8448, 8461);
	addRangeToVector(data, 8468, 8471);
	addRangeToVector(data, 12288, 12368);
	addRangeToVector(data, 16384, 16407);
	addRangeToVector(data, 4097, 4255);
	addRangeToVector(data, 4258, 4259);
	addRangeToVector(data, 4264, 4264);
	addRangeToVector(data, 4266, 4274);
	addRangeToVector(data, 4288, 4515);

	for (int i = data.size() - 1; i >= 0; i--)
	{
		int cost = getCostOfItem(data[i]);
		if (cost >= 40000)
			data.erase(data.begin() + i);
	}
	for (int i = 0; i < 127; i++)
	{
		if (bazaarData[i].bazaarType != 0x02 && bazaarData[i].result1 == 0 && bazaarData[i].result1Amt == 0)
		{
			data.erase(data.begin() + setItem(data, bazaarData[i].result1, bazaarData[i].result1Amt, false, flags));
			int randNum = Helpers::randInt(0, 99);
			if(randNum < 30)
				data.erase(data.begin() + setItem(data, bazaarData[i].result2, bazaarData[i].result2Amt, false, flags));
			if (randNum < 10)
				data.erase(data.begin() + setItem(data, bazaarData[i].result3, bazaarData[i].result3Amt, false, flags));
			setItem(lootData, bazaarData[i].loot1, bazaarData[i].loot1Amt, true, flags);
			randNum = Helpers::randInt(0, 99);
			if (randNum < 75)
				setItem(lootData, bazaarData[i].loot2, bazaarData[i].loot2Amt, true, flags);
			if (randNum < 50)
				setItem(lootData, bazaarData[i].loot3, bazaarData[i].loot3Amt, true, flags);
			bazaarData[i].cost = unsigned int(100000 / (1.f + exp(0.05f*float(Helpers::randInt(0, 10000)) / 100.f - 2.f)));
			if (bazaarData[i].result1 > 9000 || bazaarData[i].result2 > 9000 || bazaarData[i].result3 > 9000)
				bazaarData[i].bazaarType = 0x00;
			else
				bazaarData[i].bazaarType = 0x01;
		}
	}
}

int ShopRand::setItem(vector<int> &dataVec, unsigned short & data, unsigned char & amt, bool loot, FlagGroup flags)
{
	int index = Helpers::randInt(0, dataVec.size() - 1);
	data = dataVec[index];

	if (loot)
		amt = Helpers::randInt(1, flags.hasFlag("l") ? flags.getFlag("l").getValue() : 1);
	else
	{
		amt = Helpers::randIntNorm(1, 10, 2, 2);
	}
	return index;
}

int ShopRand::getCostOfItem(int itemID)
{
	int cost = 0;
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
	return cost;
}
