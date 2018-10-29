#include "stdafx.h"
#include "LootRand.h"

LootData LootRand::lootData[266] = {};

LootRand::LootRand()
{
}


LootRand::~LootRand()
{
}

void LootRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 266 * 10; //Num loots * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(LootData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 266; i++)
		{
			lootData[i] = LootData{ buffer[i * 10], buffer[i * 10 + 1], buffer[i * 10 + 2], buffer[i * 10 + 3],
				buffer[i * 10 + 4], buffer[i * 10 + 5], buffer[i * 10 + 6],	buffer[i * 10 + 7],
				buffer[i * 10 + 8],	buffer[i * 10 + 9] };
		}

		delete[] buffer;
	}
}

void LootRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 266 * 10; //Num loots * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(LootData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 266; i++)
	{
		LootData d = lootData[i];
		buffer[i * 10] = U{ d.cost }.c[0];
		buffer[i * 10 + 1] = U{ d.cost }.c[1];
		buffer[i * 10 + 2] = U{ d.itemID }.c[0];
		buffer[i * 10 + 3] = U{ d.itemID }.c[1];
		buffer[i * 10 + 4] = d.icon;
		buffer[i * 10 + 5] = d.unknown1;
		buffer[i * 10 + 6] = d.unknown2;
		buffer[i * 10 + 7] = d.unknown3;
		buffer[i * 10 + 8] = U{ d.order }.c[0];
		buffer[i * 10 + 9] = U{ d.order }.c[1];
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}

void LootRand::process()
{
	cout << "Loot Data Randomization Options:" << endl;
	cout << "\t c: Randomize gil cost (1-22000, more common around 200 G)" << endl; 
	string flags = Helpers::readFlags("c");
	if (flags.find('c') != string::npos)
	{
		randCost();
	}
}

void LootRand::randCost()
{
	for (int i = 0; i < 266; i++)
	{
		lootData[i].cost = unsigned short(82500.f / (1.f + exp(0.1f*float(rand() % 10000) / 100.f + 1.f)));
	}
}
