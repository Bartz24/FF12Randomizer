#include "stdafx.h"
#include "ItemRand.h"

ItemData ItemRand::itemData[63] = {};
LootData ItemRand::lootData[266] = {};
GambitData ItemRand::gambitData[256] = {};

ItemRand::ItemRand()
{
}


ItemRand::~ItemRand()
{
}

void ItemRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 63 * 12; //Num items * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(ItemData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 63; i++)
		{
			itemData[i] = ItemData{ buffer[i * 12], buffer[i * 12 + 1], buffer[i * 12 + 2], buffer[i * 12 + 3],
				buffer[i * 12 + 4], buffer[i * 12 + 5], buffer[i * 12 + 6],	buffer[i * 12 + 7],
				buffer[i * 12 + 8],	buffer[i * 12 + 9],	buffer[i * 12 + 10],	buffer[i * 12 + 11] };
		}

		delete[] buffer;

		char * buffer2;
		size = 266 * 10; //Num loots * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(LootData::getDataIndex()));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 266; i++)
		{
			lootData[i] = LootData{ buffer2[i * 10], buffer2[i * 10 + 1], buffer2[i * 10 + 2], buffer2[i * 10 + 3],
				buffer2[i * 10 + 4], buffer2[i * 10 + 5], buffer2[i * 10 + 6],	buffer2[i * 10 + 7],
				buffer2[i * 10 + 8],	buffer2[i * 10 + 9] };
		}

		delete[] buffer2;

		char * buffer3;
		size = 256 * 32; //Num gambits * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(GambitData::getDataIndex()));
		buffer3 = new char[size];
		file.read(buffer3, size);
		file.close();

		for (int i = 0; i < 256; i++)
		{
			char data[32];
			for (int i2 = 0; i2 < 32; i2++)
			{
				data[i2] = buffer3[i * 32 + i2];
			}
			gambitData[i] = GambitData{ data };
		}

		delete[] buffer3;
	}
}

void ItemRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 63 * 12; //Num items * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(ItemData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 63; i++)
	{
		ItemData d = itemData[i];
		buffer[i * 12] = d.order;
		buffer[i * 12 + 1] = d.unknown1;
		buffer[i * 12 + 2] = d.unknown2;
		buffer[i * 12 + 3] = d.unknown3;
		buffer[i * 12 + 4] = d.icon;
		buffer[i * 12 + 5] = d.unknown4;
		buffer[i * 12 + 6] = d.unknown5;
		buffer[i * 12 + 7] = d.unknown6;
		buffer[i * 12 + 8] = d.unknown7;
		buffer[i * 12 + 9] = d.unknown8;
		buffer[i * 12 + 10] = U{ d.cost }.c[0];
		buffer[i * 12 + 11] = U{ d.cost }.c[1];
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;

	char * buffer2;
	size = 266 * 10; //Num loots * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(LootData::getDataIndex()));
	buffer2 = new char[size];

	for (int i = 0; i < 266; i++)
	{
		LootData d = lootData[i];
		buffer2[i * 10] = U{ d.cost }.c[0];
		buffer2[i * 10 + 1] = U{ d.cost }.c[1];
		buffer2[i * 10 + 2] = U{ d.itemID }.c[0];
		buffer2[i * 10 + 3] = U{ d.itemID }.c[1];
		buffer2[i * 10 + 4] = d.icon;
		buffer2[i * 10 + 5] = d.unknown1;
		buffer2[i * 10 + 6] = d.unknown2;
		buffer2[i * 10 + 7] = d.unknown3;
		buffer2[i * 10 + 8] = U{ d.order }.c[0];
		buffer2[i * 10 + 9] = U{ d.order }.c[1];
	}

	file.write(buffer2, size);
	file.close();


	delete[] buffer2;

	char * buffer3;
	size = 256 * 32; //Num gambits * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(GambitData::getDataIndex()));
	buffer3 = new char[size];

	for (int i = 0; i < 256; i++)
	{
		GambitData d = gambitData[i];
		int index = 0;
		for (int i2 = 0; i2 < 32; i2++)
		{
			if (i2 == 0x06 || i2 == 0x07 || i2 == 0x14 || i2 == 0x15)
				continue;
			buffer3[i * 32 + i2] = d.unknown[index];
			index++;
		}
		buffer3[i * 32 + 0x06] = U{ d.cost }.c[0];
		buffer3[i * 32 + 0x07] = U{ d.cost }.c[1];
		buffer3[i * 32 + 0x14] = U{ d.name }.c[0];
		buffer3[i * 32 + 0x15] = U{ d.name }.c[1];
	}

	file.write(buffer3, size);
	file.close();


	delete[] buffer3;
}

string ItemRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Item Data Randomization Options:" << endl;
		cout << "\t g: Randomize gil cost of gambits (20-64000, more common around 100 G)" << endl;
		cout << "\t i: Randomize gil cost of items (10-64000, more common around 2500 G)" << endl;
		cout << "\t l: Randomize gil cost of loot (2-60000, more common around 500 G)" << endl;
		cout << "\t s: Randomize gil costs in a smart way. Costs are based on how powerful they are. (Applies to i flag)" << endl;
		flags = Helpers::readFlags("gils");
	}
	if (flags.find('g') != string::npos)
	{
		randCostGambit();
	}
	if (flags.find('i') != string::npos)
	{
		if (flags.find('s') != string::npos)
		{
			randCostSmart();
		}
		else
			randCost();
	}
	if (flags.find('l') != string::npos)
	{
		randCostLoot();
	}
	return flags;
}

void ItemRand::randCost()
{
	for (int i = 0; i < 63; i++)
	{
		float ran = float(rand() % 10000) / 100.f;
		itemData[i].cost = unsigned short(87500.f / (1.f + exp(0.09f*ran - 1.f)) - 19);
	}
}

void ItemRand::randCostSmart()
{
	for (int i = 0; i < 63; i++)
	{
		float baseCost = 5;
		if (MagicRand::actionData[i + 82].power > 0)
			baseCost = pow(MagicRand::actionData[i + 82].power / 16.f, 1.6f);
		if (MagicRand::actionData[i + 82].powerMult > 0)
			baseCost *= MagicRand::actionData[i + 82].powerMult;
		if (MagicRand::actionData[i + 82].aoeRange > 0)
			baseCost *= pow(1.22f, MagicRand::actionData[i + 82].aoeRange + 1);
		if (MagicRand::actionData[i + 82].accuracy > 0)
			baseCost *= float(MagicRand::actionData[i + 82].accuracy) / 15.f;
		StatusValue status = StatusValue{ MagicRand::actionData[i + 82].status1, MagicRand::actionData[i + 82].status2, MagicRand::actionData[i + 82].status3, MagicRand::actionData[i + 82].status4 };
		if (status.getNumStatuses() > 0)
			baseCost *= status.getNumStatuses() + 1;
		if (MagicRand::actionData[i + 82].mType == 0xB000)
			baseCost *= 80;
		baseCost = pow(baseCost / 2.5f, 1.42f);

		float ran = float(rand() % 24000) / 24000.f + .60f;
		baseCost *= ran;
		baseCost = max(10.f, min(baseCost, 65535.f));
		itemData[i].cost = unsigned short(baseCost);
	}
}

void ItemRand::randCostLoot()
{
	for (int i = 0; i < 266; i++)
	{
		lootData[i].cost = unsigned short(220000.f / (1.f + exp(0.1f*float(rand() % 10000) / 100.f + 1.f)) + 2.f);
	}
}

void ItemRand::randCostGambit()
{
	for (int i = 0; i < 256; i++)
	{
		float ran = float(rand() % 10000) / 100.f;
		gambitData[i].cost = unsigned short(87500.f / (1.f + exp(0.16f*ran - 1.f)) + 20);
	}
}
