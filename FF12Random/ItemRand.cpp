#include "stdafx.h"
#include "ItemRand.h"

ItemData ItemRand::itemData[63] = {};

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
}

void ItemRand::process()
{
	cout << "Item Data Randomization Options:" << endl;
	cout << "\t c: Randomize gil cost (10-6000, more common around 2000 G)" << endl;
	string flags = Helpers::readFlags("c");
	if (flags.find('c') != string::npos)
	{
		randCost();
	}
}

void ItemRand::randCost()
{
	for (int i = 0; i < 63; i++)
	{
		float ran = float(rand() % 10000) / 100.f;
		itemData[i].cost = unsigned short(8250.f / (1.f + exp(0.04f*ran - 1.f)) - 39.f * ran + 10);
	}
}
