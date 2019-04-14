#include "stdafx.h"
#include "ARDData.h"

ARDSec1::ARDSec1()
{
}

ARDSec1::ARDSec1(char data[84])
{
	for (int i = 0; i < 84; i++)
	{
		this->unknown[i] = data[i];
	}

	this->model = Helpers::readInt(data, 0x00);
	this->rangeDetect = Helpers::readShort(data, 0x22);
	this->absorbElement = data[0x29];
	this->halfElement = data[0x2A];
	this->immuneElement = data[0x2B];
	this->weakElement = data[0x2C];
	this->boostElement = data[0x2D];
	this->bestiaryNum = Helpers::readShort(data, 0x52);
}

ARDSec1::~ARDSec1()
{
}

ARDSec3::ARDSec3()
{
}

ARDSec3::ARDSec3(char data[56])
{
	for (int i = 0; i < 56; i++)
	{
		this->unknown[i] = data[i];
	}

	this->cp = Helpers::readShort(data, 0x00);
	this->hp = Helpers::readInt(data, 0x20);
	this->mp = Helpers::readShort(data, 0x24);
	this->str = data[0x26];
	this->mag = data[0x27];
	this->vit = data[0x28];
	this->spd = data[0x29];
	this->eva = data[0x2A];
	this->def = data[0x2B];
	this->mRes = data[0x2C];
	this->atk = data[0x2D];
	this->lp = data[0x2F];
	this->exp = Helpers::readInt(data, 0x34);
}

ARDSec3::~ARDSec3()
{
}

ARDSec4::ARDSec4()
{
}

ARDSec4::ARDSec4(char data[56])
{
	for (int i = 0; i < 56; i++)
	{
		this->unknown[i] = data[i];
	}

	this->cp = Helpers::readShort(data, 0x00);
	this->hp = Helpers::readInt(data, 0x20);
	this->mp = Helpers::readShort(data, 0x24);
	this->str = data[0x26];
	this->mag = data[0x27];
	this->vit = data[0x28];
	this->spd = data[0x29];
	this->eva = data[0x2A];
	this->def = data[0x2B];
	this->mRes = data[0x2C];
	this->atk = data[0x2D];
	this->lp = data[0x2F];
	this->exp = Helpers::readInt(data, 0x34);
}

ARDSec4::~ARDSec4()
{
}

ARDSec2::ARDSec2()
{
}

ARDSec2::ARDSec2(char data[88])
{
	for (int i = 0; i < 88; i++)
	{
		this->unknown[i] = data[i];
	}

	this->sec1Link = data[0x00];
	this->name = Helpers::readShort(data, 0x08);
	this->sizeX = Helpers::readShort(data, 0x0A);
	this->sizeY = Helpers::readShort(data, 0x0C);
	this->sizeZ = Helpers::readShort(data, 0x0E);
	this->weapon = Helpers::readShort(data, 0x16);
	this->initHP = Helpers::readInt(data, 0x18);
	this->offHand = Helpers::readShort(data, 0x1C);
	this->sec3Link = data[0x22];
	this->sec4Link = data[0x24];
	this->drop40 = Helpers::readShort(data, 0x28);
	this->drop25 = Helpers::readShort(data, 0x2A);
	this->drop05 = Helpers::readShort(data, 0x2C);
	this->drop01 = Helpers::readShort(data, 0x2E);
	this->drop100 = Helpers::readShort(data, 0x30);
	this->steal55 = Helpers::readShort(data, 0x32);
	this->steal10 = Helpers::readShort(data, 0x34);
	this->steal03 = Helpers::readShort(data, 0x36);
	this->monographDropRate = data[0x42];
	this->canopicJarDropRate = data[0x43];
	this->poach95 = Helpers::readShort(data, 0x44);
	this->poach05 = Helpers::readShort(data, 0x46);
	this->monographType = Helpers::readShort(data, 0x48);
	this->monographDrop = Helpers::readShort(data, 0x4A);
	this->canopicJarType = Helpers::readShort(data, 0x4C);
	this->canopicJarDrop = Helpers::readShort(data, 0x4E);
	this->aiSet = data[0x50];
}

ARDSec2::~ARDSec2()
{
}

ARDSec1 ARDSec2::getARDSec1(ARDData data)
{
	return data.section1Data[sec1Link];
}

ARDSec3 ARDSec2::getARDSec3(ARDData data)
{
	return data.section3Data[sec3Link];
}

ARDSec4 ARDSec2::getARDSec4(ARDData data)
{
	return data.section4Data[sec4Link];
}

ARDData::ARDData()
{

}

ARDData::ARDData(string areaName, char data[], int size)
{
	this->areaName = areaName;

	this->section1Adrs = Helpers::readInt(data, 0x10);
	this->aiAdrs = Helpers::readInt(data, 0x14);
	this->section2Adrs = Helpers::readInt(data, 0x18);
	this->section3Adrs = Helpers::readInt(data, 0x24);
	this->section4Adrs = Helpers::readInt(data, 0x28);

	int sec1Count = data[section1Adrs + 4];
	for (int i = 0; i < sec1Count; i++)
	{
		char sec1Data[84];
		for (int s = 0; s < 84; s++)
		{
			sec1Data[s] = data[section1Adrs + 0x20 + i * 84 + s];
		}
		section1Data.push_back(ARDSec1(sec1Data));
	}

	int sec2Count = data[section2Adrs + 4];
	for (int i = 0; i < sec2Count; i++)
	{
		char sec2Data[88];
		for (int s = 0; s < 88; s++)
		{
			sec2Data[s] = data[section2Adrs + 0x20 + i * 88 + s];
		}
		section2Data.push_back(ARDSec2(sec2Data));
	}

	int sec3Count = data[section3Adrs + 4];
	for (int i = 0; i < sec3Count; i++)
	{
		char sec3Data[56];
		for (int s = 0; s < 56; s++)
		{
			sec3Data[s] = data[section3Adrs + 0x20 + i * 56 + s];
		}
		section3Data.push_back(ARDSec3(sec3Data));
	}

	int sec4Count = data[section4Adrs + 4];
	for (int i = 0; i < sec4Count; i++)
	{
		char sec4Data[56];
		for (int s = 0; s < 56; s++)
		{
			sec4Data[s] = data[section4Adrs + 0x20 + i * 56 + s];
		}
		section4Data.push_back(ARDSec4(sec4Data));
	}
	
	int aiSize = section2Adrs - aiAdrs;
	char *aiDataArray = new char[aiSize];
	for (int i = 0; i < aiSize; i++)
	{
		aiDataArray[i] = data[aiAdrs + i];
	}
	aiData = AIData{ aiDataArray, aiSize };

	delete[] aiDataArray;
}

ARDData::~ARDData()
{
}
