#include "stdafx.h"
#include "EnemyRand.h"

vector<ARDData> EnemyRand::ardData = vector<ARDData>();

EnemyRand::EnemyRand()
{
}


EnemyRand::~EnemyRand()
{
}

void EnemyRand::load()
{
	vector<string> folders = Helpers::get_directories(Helpers::mainPS2DataFolder + "\\plan_master\\in\\plan_map");
	for (string folder : folders)
	{
		string areaName = folder.substr(folder.size() - 5, 5);
		if (!Helpers::fileExists(folder+"\\area") || areaName == "\\area")
			continue;
		string fileName = folder + "\\area\\" + areaName + ".ard";
		
		char *buffer;

		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		int size = file.tellg();
		file.seekg(0, ios::beg);
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		ardData.push_back(ARDData(areaName, buffer, size));

		delete[] buffer;
	}

	addRangeToVector(itemIDs, 0, 28);
	addRangeToVector(itemIDs, 42, 63);
	addRangeToVector(itemIDs, 8192, 8192);
	addRangeToVector(itemIDs, 8224, 8437);
	addRangeToVector(itemIDs, 8448, 8461);
	addRangeToVector(itemIDs, 8468, 8471);
	addRangeToVector(itemIDs, 12288, 12368);
	addRangeToVector(itemIDs, 16384, 16407);
	addRangeToVector(itemIDs, 24576, 24831);
	addRangeToVector(itemIDs, 4097, 4255);
	addRangeToVector(itemIDs, 4258, 4259);
	addRangeToVector(itemIDs, 4264, 4264);
	addRangeToVector(itemIDs, 4266, 4274);
	addRangeToVector(itemIDs, 4288, 4483);
}

void EnemyRand::save()
{
	for (int i = 0; i < ardData.size(); i++)
	{
		string areaFolder = Helpers::mainPS2DataFolder + "\\plan_master\\in\\plan_map\\" + ardData[i].areaName + "\\area";
		string fileName = areaFolder + "\\" + ardData[i].areaName + ".ard";
		if (Helpers::fileExists(areaFolder) && Helpers::fileExists(fileName))
		{
			{
				char * buffer;
				long size = ardData[i].section1Data.size() * 84; //Num Sec1 * data size
				fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
				file.seekp(ardData[i].section1Adrs + 0x20);
				buffer = new char[size];

				for (int s = 0; s < ardData[i].section1Data.size(); s++)
				{
					ARDSec1 d = ardData[i].section1Data[s];
					int index = 0;
					for (int i2 = 0; i2 < 84; i2++)
					{
						buffer[s * 84 + i2] = d.unknown[index];
						index++;
					}
					Helpers::setInt(buffer, s * 84 + 0x00, d.model);
					Helpers::setShort(buffer, s * 84 + 0x22, d.rangeDetect);
					buffer[s * 84 + 0x29] = d.absorbElement;
					buffer[s * 84 + 0x2A] = d.halfElement;
					buffer[s * 84 + 0x2B] = d.immuneElement;
					buffer[s * 84 + 0x2C] = d.weakElement;
					buffer[s * 84 + 0x2D] = d.boostElement;
					Helpers::setShort(buffer, s * 84 + 0x52, d.bestiaryNum);
				}

				file.write(buffer, size);
				file.close();

				delete[] buffer;
			}

			{
				char * buffer;
				long size = ardData[i].section2Data.size() * 88; //Num Sec2 * data size
				fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
				file.seekp(ardData[i].section2Adrs + 0x20);
				buffer = new char[size];

				for (int s = 0; s < ardData[i].section2Data.size(); s++)
				{
					ARDSec2 d = ardData[i].section2Data[s];
					int index = 0;
					for (int i2 = 0; i2 < 88; i2++)
					{
						buffer[s * 88 + i2] = d.unknown[index];
						index++;
					}
					buffer[s * 88 + 0x00] = d.sec1Link;
					Helpers::setShort(buffer, s * 88 + 0x08, d.name);
					Helpers::setShort(buffer, s * 88 + 0x0A, d.sizeX);
					Helpers::setShort(buffer, s * 88 + 0x0C, d.sizeY);
					Helpers::setShort(buffer, s * 88 + 0x0E, d.sizeZ);
					Helpers::setShort(buffer, s * 88 + 0x16, d.weapon);
					Helpers::setInt(buffer, s * 88 + 0x18, d.initHP);
					Helpers::setShort(buffer, s * 88 + 0x1C, d.offHand);
					buffer[s * 88 + 0x22] = d.sec3Link;
					buffer[s * 88 + 0x24] = d.sec4Link;
					Helpers::setShort(buffer, s * 88 + 0x28, d.drop40);
					Helpers::setShort(buffer, s * 88 + 0x2A, d.drop25);
					Helpers::setShort(buffer, s * 88 + 0x2C, d.drop05);
					Helpers::setShort(buffer, s * 88 + 0x2E, d.drop01);
					Helpers::setShort(buffer, s * 88 + 0x30, d.drop100);
					Helpers::setShort(buffer, s * 88 + 0x32, d.steal55);
					Helpers::setShort(buffer, s * 88 + 0x34, d.steal10);
					Helpers::setShort(buffer, s * 88 + 0x36, d.steal03);
					buffer[s * 88 + 0x42] = d.monographDropRate;
					buffer[s * 88 + 0x43] = d.canopicJarDropRate;
					Helpers::setShort(buffer, s * 88 + 0x44, d.poach95);
					Helpers::setShort(buffer, s * 88 + 0x46, d.poach05);
					Helpers::setShort(buffer, s * 88 + 0x48, d.monographType);
					Helpers::setShort(buffer, s * 88 + 0x4A, d.monographDrop);
					Helpers::setShort(buffer, s * 88 + 0x4C, d.canopicJarType);
					Helpers::setShort(buffer, s * 88 + 0x4E, d.canopicJarDrop);
					buffer[s * 88 + 0x50] = d.aiSet;
				}

				file.write(buffer, size);
				file.close();

				delete[] buffer;
			}

			{
				char * buffer;
				long size = ardData[i].section3Data.size() * 56; //Num Sec3 * data size
				fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
				file.seekp(ardData[i].section3Adrs + 0x20);
				buffer = new char[size];

				for (int s = 0; s < ardData[i].section3Data.size(); s++)
				{
					ARDSec3 d = ardData[i].section3Data[s];
					int index = 0;
					for (int i2 = 0; i2 < 56; i2++)
					{
						buffer[s * 56 + i2] = d.unknown[index];
						index++;
					}
					Helpers::setShort(buffer, s * 56 + 0x00, d.cp);
					Helpers::setInt(buffer, s * 56 + 0x20, d.hp);
					Helpers::setShort(buffer, s * 56 + 0x24, d.mp);
					buffer[s * 56 + 0x26] = d.str;
					buffer[s * 56 + 0x27] = d.mag;
					buffer[s * 56 + 0x28] = d.vit;
					buffer[s * 56 + 0x29] = d.spd;
					buffer[s * 56 + 0x2A] = d.eva;
					buffer[s * 56 + 0x2B] = d.def;
					buffer[s * 56 + 0x2C] = d.mRes;
					buffer[s * 56 + 0x2D] = d.atk;
					buffer[s * 56 + 0x2F] = d.lp;
					Helpers::setInt(buffer, s * 56 + 0x34, d.exp);
				}

				file.write(buffer, size);
				file.close();

				delete[] buffer;
			}

			{
				char * buffer;
				long size = ardData[i].section4Data.size() * 56; //Num Sec4 * data size
				fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
				file.seekp(ardData[i].section4Adrs + 0x20);
				buffer = new char[size];

				for (int s = 0; s < ardData[i].section4Data.size(); s++)
				{
					ARDSec4 d = ardData[i].section4Data[s];
					int index = 0;
					for (int i2 = 0; i2 < 56; i2++)
					{
						buffer[s * 56 + i2] = d.unknown[index];
						index++;
					}
					Helpers::setShort(buffer, s * 56 + 0x00, d.cp);
					Helpers::setInt(buffer, s * 56 + 0x20, d.hp);
					Helpers::setShort(buffer, s * 56 + 0x24, d.mp);
					buffer[s * 56 + 0x26] = d.str;
					buffer[s * 56 + 0x27] = d.mag;
					buffer[s * 56 + 0x28] = d.vit;
					buffer[s * 56 + 0x29] = d.spd;
					buffer[s * 56 + 0x2A] = d.eva;
					buffer[s * 56 + 0x2B] = d.def;
					buffer[s * 56 + 0x2C] = d.mRes;
					buffer[s * 56 + 0x2D] = d.atk;
					buffer[s * 56 + 0x2F] = d.lp;
					Helpers::setInt(buffer, s * 56 + 0x34, d.exp);
				}

				file.write(buffer, size);
				file.close();

				delete[] buffer;
			}

			{
				char * buffer;
				long size = ardData[i].aiData.unknownByteSize; // data size
				fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
				file.seekp(ardData[i].aiAdrs);
				buffer = new char[size];

				for (int i2 = 0; i2 < size; i2++)
				{
					buffer[i2] = ardData[i].aiData.unknown[i2];
				}

				for (int a = 0; a < ardData[i].aiData.abilities.size(); a++)
				{
					Helpers::setShort(buffer, ardData[i].aiData.abilities[a].pointer, ardData[i].aiData.abilities[a].ability);
					Helpers::setShort(buffer, ardData[i].aiData.abilities[a].pointer + 5, ardData[i].aiData.abilities[a].targetType);
				}

				file.write(buffer, size);
				file.close();

				delete[] buffer;

				delete[] ardData[i].aiData.unknown;
			}
		}
	}
}

void EnemyRand::process(FlagGroup flags)
{
	for (int a = 0;a < ardData.size();a++)
	{
		ARDData &aData = ardData[a];
		for (int s = 0; s < aData.section3Data.size(); s++)
		{
			ARDSec3 &sec3 = aData.section3Data[s];
			if (flags.hasFlag("h"))
				modifyValue(flags.getFlag("h").getValue(), sec3.hp, false, sec3.sizeMult, sec3.expMult, 1, 1e9);
			if (flags.hasFlag("m"))
				modifyValue(flags.getFlag("m").getValue(), sec3.mp, true, sec3.sizeMult, sec3.expMult, 0, 9999);
			if (flags.hasFlag("r"))
				modifyValue(flags.getFlag("r").getValue(), sec3.str, false, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("g"))
				modifyValue(flags.getFlag("g").getValue(), sec3.mag, true, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("v"))
				modifyValue(flags.getFlag("v").getValue(), sec3.vit, false, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("s"))
				modifyValue(flags.getFlag("s").getValue(), sec3.spd, true, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("e"))
				modifyValue(flags.getFlag("e").getValue(), sec3.eva, true, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("d"))
				modifyValue(flags.getFlag("d").getValue(), sec3.def, false, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("i"))
				modifyValue(flags.getFlag("i").getValue(), sec3.mRes, false, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("a"))
				modifyValue(flags.getFlag("a").getValue(), sec3.atk, false, sec3.sizeMult, sec3.expMult, 0, 255);
			if (flags.hasFlag("l"))
			{
				if (flags.getFlag("l").isSmart())
					sec3.lp = Helpers::clamp(round(double(sec3.lp) * sqrt(sec3.expMult)), 0, 255);
				else
				{
					double dummyS = 1, doubleE = 1;
					modifyValue(flags.getFlag("l").getValue(), sec3.lp, false, dummyS, doubleE, 0, 255);
				}
			}
			if (flags.hasFlag("x"))
			{
				if (flags.getFlag("x").isSmart())
					sec3.exp = Helpers::clamp(round(double(sec3.exp) * sqrt(sec3.expMult)), 0, 999999);
				else
				{
					double dummyS = 1, doubleE = 1;
					modifyValue(flags.getFlag("x").getValue(), sec3.exp, false, dummyS, doubleE, 0, 999999);
				}
			}
			if (flags.hasFlag("T"))
				buffTrialMode(sec3, aData, flags.getFlag("T").getValue());
			if (flags.hasFlag("C"))
				sec3.cp = 1;
		}
		for (int s = 0; s < aData.section4Data.size(); s++)
		{
			ARDSec4 &sec4 = aData.section4Data[s];
			if (flags.hasFlag("h"))
				modifyValue(flags.getFlag("h").getValue(), sec4.hp, false, sec4.sizeMult, sec4.expMult, 0, 1e9, true);
			if (flags.hasFlag("m"))
				modifyValue(flags.getFlag("m").getValue(), sec4.mp, true, sec4.sizeMult, sec4.expMult, 0, 9999, true);
			if (flags.hasFlag("r"))
				modifyValue(flags.getFlag("r").getValue(), sec4.str, false, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("g"))
				modifyValue(flags.getFlag("g").getValue(), sec4.mag, true, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("v"))
				modifyValue(flags.getFlag("v").getValue(), sec4.vit, false, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("s"))
				modifyValue(flags.getFlag("s").getValue(), sec4.spd, true, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("e"))
				modifyValue(flags.getFlag("e").getValue(), sec4.eva, true, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("d"))
				modifyValue(flags.getFlag("d").getValue(), sec4.def, false, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("i"))
				modifyValue(flags.getFlag("i").getValue(), sec4.mRes, false, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("a"))
				modifyValue(flags.getFlag("a").getValue(), sec4.atk, false, sec4.sizeMult, sec4.expMult, 0, 255, true);
			if (flags.hasFlag("x"))
			{
				if (flags.getFlag("x").isSmart())
					sec4.exp = Helpers::clamp(round(double(sec4.exp) * sqrt(sec4.expMult)), 0, 999999);
				else
				{
					double dummyS = 1, doubleE = 1;
					modifyValue(flags.getFlag("x").getValue(), sec4.exp, false, dummyS, doubleE, 0, 999999, true);
				}
			}
		}
		
		for (int s = 0; s < aData.section2Data.size(); s++)
		{
			ARDSec2 &sec2 = aData.section2Data[s];
			if (flags.hasFlag("z"))
			{
				double sizeMult = pow(sec2.getARDSec3(aData).sizeMult, 0.125) * pow(sec2.getARDSec4(aData).sizeMult, 0.08);
				sec2.sizeX = Helpers::clamp(sec2.sizeX*sizeMult, 1, 300);
				sec2.sizeY = Helpers::clamp(sec2.sizeY*sizeMult, 1, 300);
				sec2.sizeZ = Helpers::clamp(sec2.sizeZ*sizeMult, 1, 300);
			}

			if (flags.hasFlag("p"))
				randDrops(sec2, aData, flags.getFlag("p").getValue());
			if (flags.hasFlag("t"))
				randSteal(sec2, aData, flags.getFlag("t").getValue());
			if (flags.hasFlag("o"))
				randPoach(sec2, aData, flags.getFlag("o").getValue());
			if (flags.hasFlag("n"))
				randMonographRate(sec2, flags.getFlag("n").getValue());
			if (flags.hasFlag("y"))
				randMonographType(sec2);
			if (flags.hasFlag("w"))
				randMonographItem(sec2, aData, flags.getFlag("w").getValue());
			if (flags.hasFlag("b"))
				randCanopicJarRate(sec2, flags.getFlag("b").getValue());
			if (flags.hasFlag("j"))
				randCanopicJarType(sec2);
			if (flags.hasFlag("q"))
				randCanopicJarItem(sec2, aData, flags.getFlag("q").getValue());
		}
	}
}

void EnemyRand::modifyValue(int value, unsigned int &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue)
{
	double mult = double(Helpers::randInt(100, value)) / double(100);
	bool doMult = Helpers::randInt(0, 99) < 50; // false = divide

	if (lvValue && dataVal == 0)
		dataVal = 1;
	if (doMult)
	{
		dataVal = Helpers::clamp(round(double(dataVal)*mult), minN, maxN);
		expMult *= mult;
		if (!inverse)
			sizeMult *= mult;
		else
			sizeMult /= mult;
	}
	else
	{
		dataVal = Helpers::clamp(round(double(dataVal) / mult), minN, maxN);
		expMult /= mult;
		if (!inverse)
			sizeMult /= mult;
		else
			sizeMult *= mult;
	}
}

void EnemyRand::modifyValue(int value, unsigned short &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue)
{
	double mult = double(Helpers::randInt(100, value)) / double(100);
	bool doMult = Helpers::randInt(0, 99) < 50; // false = divide

	if (lvValue && dataVal == 0)
		dataVal = 1;
	if (doMult)
	{
		dataVal = Helpers::clamp(round(double(dataVal)*mult), minN, maxN);
		expMult *= mult;
		if (!inverse)
			sizeMult *= mult;
		else
			sizeMult /= mult;
	}
	else
	{
		dataVal = Helpers::clamp(round(double(dataVal) / mult), minN, maxN);
		expMult /= mult;
		if (!inverse)
			sizeMult /= mult;
		else
			sizeMult *= mult;
	}
}

void EnemyRand::modifyValue(int value, unsigned char &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue)
{
	double mult = double(Helpers::randInt(100, value)) / double(100);
	bool doMult = Helpers::randInt(0, 99) < 50; // false = divide

	if (lvValue && dataVal == 0)
		dataVal = 1;
	if (doMult)
	{
		dataVal = Helpers::clamp(round(double(dataVal)*mult), minN, maxN);
		expMult *= mult;
		if (!inverse)
			sizeMult *= mult;
		else
			sizeMult /= mult;
	}
	else
	{
		dataVal = Helpers::clamp(round(double(dataVal) / mult), minN, maxN);
		expMult /= mult;
		if (!inverse)
			sizeMult /= mult;
		else
			sizeMult *= mult;
	}
}

void EnemyRand::randDrops(ARDSec2 &sec2Data, ARDData aData, int value)
{
	if (sec2Data.drop40 != 0xFFFF)
		sec2Data.drop40 = getItem(itemIDs, Helpers::clamp(.12 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 200, value, false);
	if (sec2Data.drop25 != 0xFFFF)
		sec2Data.drop25 = getItem(itemIDs, Helpers::clamp(.18 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 1000, value, false);
	if (sec2Data.drop05 != 0xFFFF)
		sec2Data.drop05 = getItem(itemIDs, Helpers::clamp(.3 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 6000, value, false);
	if (sec2Data.drop01 != 0xFFFF)
		sec2Data.drop01 = getItem(itemIDs, Helpers::clamp(sec2Data.getARDSec3(aData).hp, 0, 65535), 8000, value, false);
	if (sec2Data.drop100 != 0xFFFF)
		sec2Data.drop100 = getItem(itemIDs, Helpers::clamp(sec2Data.getARDSec3(aData).hp, 0, 65535), 2000, value, false);
}

void EnemyRand::randSteal(ARDSec2 &sec2Data, ARDData aData, int value)
{
	if (sec2Data.steal55 != 0xFFFF)
		sec2Data.steal55 = getItem(itemIDs, Helpers::clamp(.14 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 200, value, false);
	if (sec2Data.steal10 != 0xFFFF)
		sec2Data.steal10 = getItem(itemIDs, Helpers::clamp(.36 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 1800, value, false);
	if (sec2Data.steal03 != 0xFFFF)
		sec2Data.steal03 = getItem(itemIDs, Helpers::clamp(sec2Data.getARDSec3(aData).hp, 0, 65535), 6000, value, false);
}

void EnemyRand::randPoach(ARDSec2 &sec2Data, ARDData aData, int value)
{
	if (sec2Data.poach95 != 0xFFFF)
		sec2Data.poach95 = getItem(itemIDs, Helpers::clamp(.6 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 1000, value, false);
	if (sec2Data.poach05 != 0xFFFF)
		sec2Data.poach05 = getItem(itemIDs, Helpers::clamp(sec2Data.getARDSec3(aData).hp, 0, 65535), 3200, value, false);
}

void EnemyRand::randMonographRate(ARDSec2 & sec2Data, int value)
{
	if (sec2Data.monographDropRate != 0xFFFF)
	sec2Data.monographDropRate = Helpers::randNormControl(1, 100, 30, 10, value);
}

void EnemyRand::randMonographType(ARDSec2 & sec2Data)
{
	if (sec2Data.monographType != 0xFFFF)
		sec2Data.monographType = Helpers::randInt(0x8065, 0x806C);
}

void EnemyRand::randMonographItem(ARDSec2 & sec2Data, ARDData aData, int value)
{
	if (sec2Data.monographDrop != 0xFFFF)
		sec2Data.monographDrop = getItem(itemIDs, Helpers::clamp(.5 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 1400, value, false);
}

void EnemyRand::randCanopicJarRate(ARDSec2 & sec2Data, int value)
{
	sec2Data.canopicJarDropRate = Helpers::randNormControl(1, 100, 5, 5, value);
}

void EnemyRand::randCanopicJarType(ARDSec2 & sec2Data)
{
	if (sec2Data.canopicJarType != 0xFFFF)
		sec2Data.canopicJarType = Helpers::randInt(0x8065, 0x806C);
}

void EnemyRand::randCanopicJarItem(ARDSec2 & sec2Data, ARDData aData, int value)
{
	if (sec2Data.canopicJarDrop != 0xFFFF)
		sec2Data.canopicJarDrop = getItem(itemIDs, Helpers::clamp(.9 * double(sec2Data.getARDSec3(aData).hp), 0, 65535), 4400, value, false);
}

void EnemyRand::buffTrialMode(ARDSec3 &sec3Data, ARDData aData, int value)
{
	if (aData.areaName.find("tri") != string::npos)
	{
		double mult = double(Helpers::randInt(100, value)) / double(100);
		sec3Data.atk = Helpers::clamp(sec3Data.atk * mult, 0, 255);
		sec3Data.mag = Helpers::clamp(sec3Data.mag * mult, 0, 255);
		sec3Data.def = Helpers::clamp(sec3Data.def * mult, 0, 255);
		sec3Data.str = Helpers::clamp(sec3Data.str * mult, 0, 255);
		sec3Data.vit = Helpers::clamp(sec3Data.vit * mult, 0, 255);
		sec3Data.eva = Helpers::clamp(sec3Data.eva * mult, 0, 255);
		sec3Data.spd = Helpers::clamp(sec3Data.spd * mult, 0, 255);
		sec3Data.mRes = Helpers::clamp(sec3Data.mRes * mult, 0, 255);
		sec3Data.hp = Helpers::clamp(sec3Data.hp * mult, 0, 1e9);
		sec3Data.mp = Helpers::clamp(sec3Data.mp * mult, 0, 9999);
	}
}

int EnemyRand::getItem(std::vector<int> &data, int center, int std, int value, bool remove)
{
	int itemID;
	int cost = 99999;
	int index;
	int tries = 0;
	do
	{
		index = Helpers::randInt(0, data.size() - 1);
		itemID = data[index];
		cost = getCost(itemID);
		tries++;
	} while (tries < 100 && !canAddItem(cost, center, std, value) && (itemID > 8000 && itemID < 9000 ? false : Helpers::randInt(0,99) < 80));
	if (remove)
		data.erase(data.begin() + index);
	return itemID;
}

int EnemyRand::getCost(int itemID)
{
	if (itemID < 64)
		return ItemRand::itemData[itemID].cost;
	else if (itemID < 4600)
		return EquipRand::equipData[itemID - 4096].cost;
	else if (itemID < 9000)
	{
		return ItemRand::lootData[itemID - 8192].cost;
	}
	else if (itemID < 13000)
		return MagicRand::magicData[itemID - 12288].cost;
	else if (itemID < 17000)
		return MagicRand::magicData[itemID - 16384 + 81].cost;
	else
		return ItemRand::gambitData[itemID - 24576].cost;
}

bool EnemyRand::canAddItem(int actualCost, int center, int std, int value)
{
	float zScoreAbs = float(abs(actualCost - center)) / float(std);
	int chance = int(exp(-zScoreAbs) * 10000.f); //chance in terms of % * 100

	int actualChance = Helpers::randIntControl(0, 9999, chance, value);

	return Helpers::randInt(0, 9999) < actualChance;
}

void EnemyRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
