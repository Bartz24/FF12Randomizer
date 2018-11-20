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
		file.seekg(int(ShopData::getDataIndex()));
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
	file.seekg(int(BazaarData::getDataIndex()));
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
		file.seekp(int(ShopData::getDataIndex()) + shopData[i].position);
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
	file.seekp(int(BazaarData::getDataIndex()));
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

string ShopRand::process(string preset)
{
	string flags = preset;
	string aFlags = "!", aFlagsOut = ".";
	if (flags.find("a-") != string::npos)
	{
		string second = flags.substr(flags.find("a-") + 2, flags.length() - flags.find("a-") - 1);
		aFlags = flags.substr(flags.find("a-") + 2, flags.length() - (second.length() - second.find("-")) - flags.find("a-") - 2);
		flags = flags.substr(0, flags.find('a') + 1) + flags.substr(flags.find('a') + 3 + aFlags.length(), flags.length() - flags.find('a') - 2 - aFlags.length());
	}
	if (flags.find('a') != string::npos)
	{
		aFlagsOut = randShops(aFlags);
		flags = flags.substr(0, flags.find('a') + 1) + "-" + aFlagsOut + "-" + flags.substr(flags.find('a') + 1, flags.length() - flags.find('a'));
	}
	if (flags.find('b') != string::npos)
	{
		replaceBazaarRecipes();
	}
	return flags;
}

//Usable Items:		0-28, 42-63
//Loot:				8192, 8224-8437 8448-8461 8468-8471
//Magic:			12288-12368
//Technicks:		16384-16407
//Gambits:			24576-24831
//Equipment:		4097-4255, 4258-4259, 4264, 4266-4274, 4288-4515

string ShopRand::randShops(string preset)
{
	string flags = preset;
	vector<int> data = vector<int>();
	for (int i = 0; i < 5; i++)
	{
		addRangeToVector(data, 0, 23);
		if (flags.find('e') == string::npos)
		{
			addRangeToVector(data, 24, 24);
		}
		addRangeToVector(data, 25, 28);
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
		addRangeToVector(data, 4266, 4268);
		if (flags.find('w') == string::npos)
		{
			addRangeToVector(data, 4269, 4269);
		}
		addRangeToVector(data, 4270, 4273);
		if (flags.find('m') == string::npos)
		{
			addRangeToVector(data, 4274, 4274);
		}
		addRangeToVector(data, 4288, 4515);
	}
	for (int i = 0; i < 267; i++)
	{
		unsigned long gil = 0;
		for (int c = 0; c < shopData[i].itemCount; c++)
		{
			gil += sqrt(float(rand() % 40000))*float(rand() % 150)*(1.f-shopData[i].itemCount * 0.0035) + rand() % 500 - 250;
		}
		for (int item = 0; item < shopData[i].itemCount; item++)
		{
			int itemID, cost = 99999, attempts = 0, itemIDindex;
			do
			{
				itemIDindex = rand() % data.size();
				itemID = data[itemIDindex];
				if (itemID < 64)
					cost = ItemRand::itemData[itemID].cost;
				else if (itemID < 4600)
					cost = EquipRand::equipData[itemID - 4096].cost;
				else if (itemID < 9000)
				{
					cost = ItemRand::lootData[itemID - 8192].cost * 1000; //Make loot rarer in shops
				}
				else if (itemID < 13000)
					cost = MagicRand::magicData[itemID - 12288].cost;
				else if (itemID < 17000)
					cost = MagicRand::magicData[itemID - 16384 + 81].cost;
				else
					cost = ItemRand::gambitData[itemID - 24576].cost;
				attempts++;

			} while (attempts < 100 && (find(shopData[i].items.begin(), shopData[i].items.end(), itemID) != shopData[i].items.end() || cost >= gil || cost >= 40000 || rand() % 255 < int(sqrt(cost))));
			if (attempts >= 100)
			{
				do {
					itemID = rand() % (24831 - 24576 + 1) + 24576;
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
	return flags;
}

void ShopRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}

void ShopRand::replaceBazaarRecipes()
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
	addRangeToVector(lootData, 8466, 8471);

	for (int i = data.size() - 1; i >= 0; i--)
	{
		int itemID = data[i], cost;
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
		if (cost < 40000)
			data.erase(data.begin() + i);
	}
	for (int i = 0; i < 127; i++)
	{
		if (bazaarData[i].bazaarType != 0x02)
		{
			bazaarData[i].result1 = bazaarData[i].result2 = bazaarData[i].result3 = 0;
			bazaarData[i].result1Amt = bazaarData[i].result2Amt = bazaarData[i].result3Amt = 0;
			bazaarData[i].loot1 = bazaarData[i].loot2 = bazaarData[i].loot3 = 0;
			bazaarData[i].loot1Amt = bazaarData[i].loot2Amt = bazaarData[i].loot3Amt = 0;
			bazaarData[i].cost = 0;
			bazaarData[i].bazaarType = 0;
		}
		else
		{
			bazaarData[i].cost = unsigned int(300000 / (1.f + exp(0.05f*float(rand() % 10000) / 100.f - 2.f)));
		}
	}

	while (data.size() > 0)
	{
		for (int i = 0; i < 127; i++)
		{
			if (bazaarData[i].bazaarType != 0x02)
			{
				if (bazaarData[i].result1 == 0x0000)
				{
					data.erase(data.begin() + setItem(data, bazaarData[i].result1, bazaarData[i].result1Amt));
					setItem(lootData, bazaarData[i].loot1, bazaarData[i].loot1Amt, true);
					int randNum = rand() % 100;
					if (randNum < 75)
						setItem(lootData, bazaarData[i].loot2, bazaarData[i].loot2Amt, true);
					if (randNum < 50)
						setItem(lootData, bazaarData[i].loot3, bazaarData[i].loot3Amt, true);
					bazaarData[i].cost = unsigned int(3000000 / (1.f + exp(0.05f*float(rand() % 10000) / 100.f - 2.f)));
				}
				else if (bazaarData[i].result2 == 0x0000)
					data.erase(data.begin() + setItem(data, bazaarData[i].result2, bazaarData[i].result2Amt));
				else if (bazaarData[i].result3 == 0x0000)
					data.erase(data.begin() + setItem(data, bazaarData[i].result3, bazaarData[i].result3Amt));

				if (bazaarData[i].result1 > 9000 || bazaarData[i].result2 > 9000 || bazaarData[i].result3 > 9000)
					bazaarData[i].bazaarType = 0x00;
				else
					bazaarData[i].bazaarType = 0x01;
			}
			if (data.size() == 0)
				break;
		}
	}


	data = vector<int>();
	addRangeToVector(data, 0, 28);
	addRangeToVector(data, 42, 63);
	addRangeToVector(data, 8192, 8192);
	addRangeToVector(data, 8224, 8437);
	addRangeToVector(data, 8448, 8461);
	addRangeToVector(data, 8466, 8471);
	addRangeToVector(data, 12288, 12368);
	addRangeToVector(data, 16384, 16407);
	addRangeToVector(data, 4097, 4255);
	addRangeToVector(data, 4258, 4259);
	addRangeToVector(data, 4264, 4264);
	addRangeToVector(data, 4266, 4274);
	addRangeToVector(data, 4288, 4515);

	for (int i = data.size() - 1; i >= 0; i--)
	{
		int itemID = data[i], cost;
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
		if (cost >= 40000)
			data.erase(data.begin() + i);
	}
	for (int i = 0; i < 127; i++)
	{
		if (bazaarData[i].bazaarType != 0x02 && bazaarData[i].result1 == 0 && bazaarData[i].result1Amt == 0)
		{
			data.erase(data.begin() + setItem(data, bazaarData[i].result1, bazaarData[i].result1Amt));
			int randNum = rand() % 100;
			if(randNum < 30)
				data.erase(data.begin() + setItem(data, bazaarData[i].result2, bazaarData[i].result2Amt));
			if (randNum < 10)
				data.erase(data.begin() + setItem(data, bazaarData[i].result3, bazaarData[i].result3Amt));
			setItem(lootData, bazaarData[i].loot1, bazaarData[i].loot1Amt, true);
			randNum = rand() % 100;
			if (randNum < 75)
				setItem(lootData, bazaarData[i].loot2, bazaarData[i].loot2Amt, true);
			if (randNum < 50)
				setItem(lootData, bazaarData[i].loot3, bazaarData[i].loot3Amt, true);
			bazaarData[i].cost = unsigned int(100000 / (1.f + exp(0.05f*float(rand() % 10000) / 100.f - 2.f)));
			if (bazaarData[i].result1 > 9000 || bazaarData[i].result2 > 9000 || bazaarData[i].result3 > 9000)
				bazaarData[i].bazaarType = 0x00;
			else
				bazaarData[i].bazaarType = 0x01;
		}
	}
}

int ShopRand::setItem(vector<int> &dataVec, unsigned short & data, unsigned char & amt, bool loot)
{
	int index = rand() % dataVec.size();
	data = dataVec[index];

	if (loot)
		amt = unsigned char(150 / (1.f + exp(0.05f*float(rand() % 10000) / 100.f + 1.f)) + 1.f);
	else
	{
		if (data < 9000)
			amt = unsigned char(30 / (1.f + exp(0.05f*float(rand() % 10000) / 100.f + 1.f)) + 1.f);
		else
			amt = 1;
	}
	return index;
}
