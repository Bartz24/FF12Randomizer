#include "stdafx.h"
#include "ShopRand.h"

ShopData ShopRand::shopData[267] = {};

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
}

void ShopRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

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
}

void ShopRand::process()
{
	cout << "Shop Data Randomization Options:" << endl;
	cout << "\t a: Randomize all the items in all the shops" << endl;
	string flags = Helpers::readFlags("a");
	if (flags.find('a') != string::npos)
	{
		randShops();
	}
}

//Usable Items:		0-28, 42-63
//Loot:				8192, 8224-8437 8448-8461 8466-8471
//Magic:			12288-12368
//Technicks:		16384-16407
//Gambits:			24576-24830
//Equipment:		4097-4255, 4258-4259, 4264, 4266-4274, 4288-4483

void ShopRand::randShops()
{
	vector<int> data = vector<int>();
	addRangeToVector(data, 0, 28);
	addRangeToVector(data, 42, 63);
	addRangeToVector(data, 8192, 8192);
	addRangeToVector(data, 8224, 8437);
	addRangeToVector(data, 8448, 8461);
	addRangeToVector(data, 8466, 8471);
	addRangeToVector(data, 12288, 12368);
	addRangeToVector(data, 16384, 16407);
	addRangeToVector(data, 24576, 24830);
	addRangeToVector(data, 4097, 4255);
	addRangeToVector(data, 4258, 4259);
	addRangeToVector(data, 4264, 4264);
	addRangeToVector(data, 4266, 4274);
	addRangeToVector(data, 4288, 4483);

	for (int i = 0; i < 267; i++)
	{
		for (int item = 0; item < shopData[i].itemCount; item++)
		{
			int itemID, cost = 99999;
			do
			{
				itemID = data[rand() % data.size()];
				if (itemID < 64)
					cost = ItemRand::itemData[itemID].cost;
				else if (itemID < 4600)
					cost = EquipRand::equipData[itemID - 4097].cost;
				else if (itemID < 9000)
					cost = LootRand::lootData[itemID - 8192].cost;
				else if (itemID < 13000)
					cost = MagicRand::magicData[itemID - 12288].cost;
				else if (itemID < 17000)
					cost = MagicRand::magicData[itemID - 16483 + 81].cost;
				else
					cost = 100;

			} while (rand() % 500 < sqrt(cost));

			shopData[i].items[item] = itemID;
		}
	}
}

void ShopRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
