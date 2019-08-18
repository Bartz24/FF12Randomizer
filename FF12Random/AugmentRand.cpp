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
		file.seekg(Helpers::getPointer(fileName, 0xEC));
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
	file.seekp(Helpers::getPointer(fileName, 0xEC));
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

void AugmentRand::process(FlagGroup flags)
{
	if (flags.hasFlag("h"))
	{
		randHPLores(flags.getFlag("h").getValue());
	}
	if (flags.hasFlag("b"))
	{
		randBattleLores(flags.getFlag("b").getValue());
	}
	if (flags.hasFlag("m"))
	{
		randMagickLores(flags.getFlag("m").getValue());
	}
	if (flags.hasFlag("c"))
	{
		randChannelling(flags.getFlag("c").getValue());
	}
	if (flags.hasFlag("s"))
	{
		randSwiftness(flags.getFlag("s").getValue());
	}
	if (flags.hasFlag("l"))
	{
		randShieldBlock(flags.getFlag("l").getValue());
	}
	if (flags.hasFlag("p"))
	{
		randPotionLores(flags.getFlag("p").getValue());
	}
	if (flags.hasFlag("e"))
	{
		randEtherLores(flags.getFlag("e").getValue());
	}
	if (flags.hasFlag("x"))
	{
		randPhoenixLores(flags.getFlag("x").getValue());
	}
}

void AugmentRand::randHPLores(int value)
{
	for (int i = 74; i <= 85; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(20, 2000, 160, 1.2, value));
	}
}

void AugmentRand::randBattleLores(int value)
{
	for (int i = 0; i < 129; i++)
	{
		if (i == 35 || i >= 42 && i <= 47 || i >= 60 && i <= 68)
			augmentData[i].value = unsigned short(Helpers::randWeibullControl(1, 8, 1, 1.2, value));
	}
}

void AugmentRand::randMagickLores(int value)
{
	for (int i = 0; i < 129; i++)
	{
		if (i == 19 || i == 22 || i == 24 || i == 26 || i >= 69 && i <= 73 || i == 87 || i >= 97 && i <= 102)
			augmentData[i].value = unsigned short(Helpers::randWeibullControl(1, 8, 1, 1.2, value));
	}
}

void AugmentRand::randChannelling(int value)
{
	for (int i = 91; i <= 93; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 10, 1.2, value));
	}
}

void AugmentRand::randSwiftness(int value)
{
	for (int i = 94; i <= 96; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 10, 1.2, value));
	}
}

void AugmentRand::randShieldBlock(int value)
{
	for (int i = 88; i <= 90; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 10, 1.2, value));
	}
}

void AugmentRand::randPotionLores(int value)
{
	for (int i = 119; i <= 121; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 15, 1.2, value));
	}
}

void AugmentRand::randEtherLores(int value)
{
	for (int i = 122; i <= 124; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 15, 1.2, value));
	}
}

void AugmentRand::randPhoenixLores(int value)
{
	for (int i = 125; i <= 127; i++)
	{
		augmentData[i].value = unsigned short(Helpers::randWeibullControl(5, 30, 15, 1.2, value));
	}
}
