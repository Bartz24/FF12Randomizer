#pragma once
#include <string>
#include "Helpers.h"

enum class LicenseDataOffset
{
	us = 0x00008E68,
	ch = 0x000089B8,
	cn = 0x000089C0,
	de = 0x000091B8,
	es = 0x00009110,
	fr = 0x00008E58,
	in = 0x000089A8,
	it = 0x00008ED8,
	kr = 0x00008E78
};

class LicenseData
{
public:
	static LicenseDataOffset getDataIndex();
	unsigned short licenseName;
	unsigned char licenseGroup;
	unsigned char unknown = 0x42;
	unsigned char lpCost;
	unsigned char licenseSubgroup;
	unsigned char licenseMechanic;
	unsigned char startingCharacters;
	unsigned short otherData[8];
	LicenseData();
	LicenseData(char byteNameA, char byteNameB, char licenseGroup, char unknown, char lpCost, char licenseSubgroup, char licenseMechanic, char startingCharacters, char* otherData);
	~LicenseData();
};

