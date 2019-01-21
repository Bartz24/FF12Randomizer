#include "stdafx.h"
#include "RewardRand.h"

RewardData RewardRand::rewardData[512] = {};

RewardRand::RewardRand()
{
}


RewardRand::~RewardRand()
{
}

void RewardRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 512 * 12; //Num Rewards * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(RewardData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 512; i++)
		{
			char data[12];
			for (int i2 = 0; i2 < 12; i2++)
			{
				data[i2] = buffer[i * 12 + i2];
			}
			rewardData[i] = RewardData{ data };
		}

		delete[] buffer;
	}
}

void RewardRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	union U2 {
		unsigned int i;
		unsigned char c[2];
	}byte2;

	char * buffer;
	long size = 512 * 12; //Num Rewards * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(RewardData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 512; i++)
	{
		RewardData d = rewardData[i];
		buffer[i * 12 + 0x00] = U2{ d.gil }.c[0];
		buffer[i * 12 + 0x01] = U2{ d.gil }.c[1];
		buffer[i * 12 + 0x02] = U2{ d.gil }.c[2];
		buffer[i * 12 + 0x03] = U2{ d.gil }.c[3];
		buffer[i * 12 + 0x04] = U{ d.item1 }.c[0];
		buffer[i * 12 + 0x05] = U{ d.item1 }.c[1];
		buffer[i * 12 + 0x06] = d.item1Amt;
		buffer[i * 12 + 0x07] = d.empty1;
		buffer[i * 12 + 0x08] = U{ d.item2 }.c[0];
		buffer[i * 12 + 0x09] = U{ d.item2 }.c[1];
		buffer[i * 12 + 0x0A] = d.item2Amt;
		buffer[i * 12 + 0x0B] = d.empty2;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}

void RewardRand::process(FlagGroup flags)
{
	if (flags.hasFlag("r"))
	{
		randValue(flags);
	}
}

void RewardRand::randValue(FlagGroup flags)
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

	for (int i = 0; i < 512; i++)
	{
		int randNum = Helpers::randInt(0, 99);
		bool gilChance = true;
		if (flags.hasFlag("g"))
		{
			if (randNum < flags.getFlag("g").getValue())
			{
				if (flags.hasFlag("a"))
					rewardData[i].gil = Helpers::randNormControl(1, 1000000, 10000, 8000, flags.getFlag("a").getValue());
			}
			else
			{
				rewardData[i].gil = 0;
				gilChance = false;
			}
		}
		randNum = Helpers::randInt(0, 99);
		if (flags.hasFlag("m"))
		{
			if (!gilChance || randNum < flags.getFlag("m").getValue())
			{
				rewardData[i].item1 = data[Helpers::randInt(0, data.size() - 1)];
				rewardData[i].item1Amt = Helpers::randInt(1, 4);

				if (randNum < flags.getFlag("m").getValue() * flags.getFlag("m").getValue() / 100)
				{
					rewardData[i].item2 = data[Helpers::randInt(0, data.size() - 1)];
					rewardData[i].item2Amt = Helpers::randInt(1, 4);
				}
				else
				{
					if (flags.hasFlag("t") && Helpers::randInt(0, 99) < flags.getFlag("t").getValue())
					{
						rewardData[i].item2 = 8192;
						rewardData[i].item2Amt = Helpers::randInt(1, 4);
					}
					else
					{
						rewardData[i].item2 = 0xFFFF;
						rewardData[i].item2Amt = 0xFF;
					}
				}
			}
			else
			{
				if (flags.hasFlag("t") && Helpers::randInt(0, 99) < flags.getFlag("t").getValue())
				{
					rewardData[i].item1 = 8192;
					rewardData[i].item1Amt = Helpers::randInt(1, 4);
					rewardData[i].item2 = 0xFFFF;
					rewardData[i].item2Amt = 0xFF;
				}
				else
				{
					rewardData[i].item1 = 0xFFFF;
					rewardData[i].item1Amt = 0xFF;
					rewardData[i].item2 = 0xFFFF;
					rewardData[i].item2Amt = 0xFF;
				}
			}
		}
	}
}

void RewardRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
