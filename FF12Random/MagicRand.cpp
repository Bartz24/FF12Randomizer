#include "stdafx.h"
#include "MagicRand.h"

MagicData MagicRand::magicData[105] = {};
ActionData MagicRand::actionData[497] = {};

MagicRand::MagicRand()
{
}


MagicRand::~MagicRand()
{
}

void MagicRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 81 * 8; //Num magic * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(MagicData::getMagDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 81; i++)
		{
			magicData[i] = MagicData{ buffer[i * 8], buffer[i * 8 + 1], buffer[i * 8 + 2], buffer[i * 8 + 3],
				buffer[i * 8 + 4], buffer[i * 8 + 5], buffer[i * 8 + 6],	buffer[i * 8 + 7]};
		}

		delete[] buffer;

		char * buffer2;
		size = 24 * 8; //Num tech * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(MagicData::getTechDataIndex()));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 24; i++)
		{
			magicData[i + 81] = MagicData{ buffer2[i * 8], buffer2[i * 8 + 1], buffer2[i * 8 + 2], buffer2[i * 8 + 3],
				buffer2[i * 8 + 4], buffer2[i * 8 + 5], buffer2[i * 8 + 6],	buffer2[i * 8 + 7] };
		}

		delete[] buffer2;

		char * buffer3;
		size = 497 * 60; //Num action * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(ActionData::getDataIndex()));
		buffer3 = new char[size];
		file.read(buffer3, size);
		file.close();

		for (int i = 0; i < 497; i++)
		{
			char data[60];
			for (int i2 = 0; i2 < 60; i2++)
			{
				data[i2] = buffer3[i * 60 + i2];
			}
			actionData[i] = ActionData{ data };
		}

		delete[] buffer3;
	}
}

void MagicRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 81 * 8; //Num magic * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(MagicData::getMagDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 81; i++)
	{
		MagicData d = magicData[i];
		buffer[i * 8] = U{ d.cost }.c[0];
		buffer[i * 8 + 1] = U{ d.cost }.c[1];
		buffer[i * 8 + 2] = d.id1;
		buffer[i * 8 + 3] = d.icon;
		buffer[i * 8 + 4] = d.id2;
		buffer[i * 8 + 5] = d.unknown1;
		buffer[i * 8 + 6] = d.order;
		buffer[i * 8 + 7] = d.unknown2;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;

	char * buffer2;
	size = 24 * 8; //Num tech * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(MagicData::getTechDataIndex()));
	buffer2 = new char[size];

	for (int i = 0; i < 24; i++)
	{
		MagicData d = magicData[i + 81];
		buffer2[i * 8] = U{ d.cost }.c[0];
		buffer2[i * 8 + 1] = U{ d.cost }.c[1];
		buffer2[i * 8 + 2] = d.id1;
		buffer2[i * 8 + 3] = d.icon;
		buffer2[i * 8 + 4] = d.id2;
		buffer2[i * 8 + 5] = d.unknown1;
		buffer2[i * 8 + 6] = d.order;
		buffer2[i * 8 + 7] = d.unknown2;
	}

	file.write(buffer2, size);
	file.close();


	delete[] buffer2;

	char * buffer3;
	size = 497 * 60; //Num actions * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(ActionData::getDataIndex()));
	buffer3 = new char[size];

	for (int i = 0; i < 497; i++)
	{
		ActionData d = actionData[i];
		int index = 0;
		for (int i2 = 0; i2 < 60; i2++)
		{
			if (i2 == 0x06 || i2 == 0x08 || i2 == 0x09 || i2 == 0x0A || i2 == 0x14 || i2 >= 0x18 && i2 <= 0x1B)
				continue;
			buffer3[i * 60 + i2] = d.unknown[index];
			index++;
		}
		buffer3[i * 60 + 0x06] = d.aoeRange;
		buffer3[i * 60 + 0x08] = d.type;
		buffer3[i * 60 + 0x09] = d.ct;
		buffer3[i * 60 + 0x0A] = d.cost;
		buffer3[i * 60 + 0x14] = d.hitChance;
		buffer3[i * 60 + 0x18] = d.status1;
		buffer3[i * 60 + 0x19] = d.status2;
		buffer3[i * 60 + 0x1A] = d.status3;
		buffer3[i * 60 + 0x1B] = d.status4;
	}

	file.write(buffer3, size);
	file.close();


	delete[] buffer3;
}

string MagicRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Magic Data Randomization Options:" << endl;
		cout << "\t a: Randomize AoE range (80%-no range, 20% 2-20, where 10 is normal for AoE abilities)" << endl;
		cout << "\t c: Randomize gil cost (20-62000, more common around 9000 G)" << endl;
		cout << "\t m: Randomize MP cost (1-99, only affects abilites that had a MP cost)" << endl;
		cout << "\t s: Randomize status effects on enemy attacks" << endl;
		cout << "\t t: Randomize charge time (only affects abilities that had a charge time)" << endl;
		flags = Helpers::readFlags("acmst");
	}
	if (flags.find('a') != string::npos)
	{
		randAoE();
	}
	if (flags.find('c') != string::npos)
	{
		randCost();
	}
	if (flags.find('m') != string::npos)
	{
		randMPCost();
	}
	if (flags.find('s') != string::npos)
	{
		randStatus();
	}
	if (flags.find('t') != string::npos)
	{
		randCT();
	}
	return flags;
}

void MagicRand::randCost()
{
	for (int i = 0; i < 105; i++)
	{
		magicData[i].cost = unsigned short(350000.f / (1.f + exp(0.04f*float(rand() % 10000) / 100.f + 1.5f)) - 1400.f);
	}
}

void MagicRand::randMPCost()
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].cost > 0 && !(i>=262 && i <= 274))
			actionData[i].cost = rand() % 99 + 1;
	}
}

void MagicRand::randCT()
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].ct > 0 && !(i >= 262 && i <= 274))
			actionData[i].ct = unsigned char(45.f / (1.f + exp(0.02f*float(rand() % 10000) / 100.f - 0.5f)));
	}
}

void MagicRand::randAoE()
{
	for (int i = 0; i < 497; i++)
	{
		if(!(i >= 262 && i <= 274))
		actionData[i].aoeRange = rand() % 100 < 80 ? 0 : (rand() % 19 + 2);
	}
}

void MagicRand::randStatus()
{
	for (int i = 278; i < 497; i++)
	{
		StatusValue orig{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 };
		actionData[i].status1 = actionData[i].status2 = actionData[i].status3 = actionData[i].status4 = 0;
		while (StatusValue{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 }.getNumStatuses() < orig.getNumStatuses())
			addStatus(actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4);
		setStatus(actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4, 15);
		StatusValue status{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 };
		if (status.getNumStatuses() > 0)
			actionData[i].hitChance = rand() % 96 + 5;
		else
			actionData[i].hitChance = 0;
	}
}


void MagicRand::setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance)
{
	StatusValue status = StatusValue(num1, num2, num3, num4);
	while (rand() % 100 < chance)
	{
		status.addRandomStatus();
	}
	num1 = status.getNumValue(1);
	num2 = status.getNumValue(2);
	num3 = status.getNumValue(3);
	num4 = status.getNumValue(4);
}

void MagicRand::addStatus(unsigned char & num1, unsigned char & num2, unsigned char & num3, unsigned char & num4)
{
	StatusValue status = StatusValue(num1, num2, num3, num4);
	status.addRandomStatus();
	num1 = status.getNumValue(1);
	num2 = status.getNumValue(2);
	num3 = status.getNumValue(3);
	num4 = status.getNumValue(4);
}
