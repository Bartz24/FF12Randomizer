#include "stdafx.h"
#include "AugmentRand.h"

AugmentData AugmentRand::augmentData[129] = {};

AugmentRand::AugmentRand()
{
}


AugmentRand::~AugmentRand()
{
}

void AugmentRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 129 * 8; //Num augments * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(AugmentData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 129; i++)
		{
			char data[8];
			for (int i2 = 0; i2 < 8; i2++)
			{
				data[i2] = buffer[i * 8 + i2];
			}
			augmentData[i] = AugmentData{ data };
		}

		delete[] buffer;
	}
}

void AugmentRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 129 * 8; //Num augments * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(AugmentData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 129; i++)
	{
		AugmentData d = augmentData[i];
		int index = 0;
		for (int i2 = 0; i2 < 8; i2++)
		{
			if (i2 == 0x04 || i2 == 0x05)
				continue;
			buffer[i * 8 + i2] = d.unknown[index];
			index++;
		}
		buffer[i * 8 + 0x04] = U{ d.value }.c[0];
		buffer[i * 8 + 0x05] = U{ d.value }.c[1];
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}

string AugmentRand::process(string preset)
{
	string flags = preset;
	if (flags.find('v') != string::npos)
	{
		randValue();
	}
	return flags;
}

void AugmentRand::randValue()
{
	vector<int> loreIds = vector<int>();
	loreIds.push_back(19);
	loreIds.push_back(22);
	loreIds.push_back(24);
	loreIds.push_back(26);
	loreIds.push_back(35);
	addRangeToVector(loreIds, 42, 47);
	addRangeToVector(loreIds, 60, 73);
	addRangeToVector(loreIds, 97, 102);
	vector<int> hpLores = vector<int>();
	addRangeToVector(hpLores, 74, 85);
	vector<int> percent = vector<int>();
	addRangeToVector(percent, 88, 96);
	addRangeToVector(percent, 119, 127);

	for (int i = 0; i < 129; i++)
	{
		if (find(loreIds.begin(), loreIds.end(), i) != loreIds.end())
			augmentData[i].value = Helpers::randInt(1, 4);
		else if (find(hpLores.begin(), hpLores.end(), i) != hpLores.end())
			augmentData[i].value = unsigned short(Helpers::randIntNorm(20, 1500, 400, 120));
		else if (find(percent.begin(), percent.end(), i) != percent.end())
			augmentData[i].value = Helpers::randInt(1, 30);
	}
}

void AugmentRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
