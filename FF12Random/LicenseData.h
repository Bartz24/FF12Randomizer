#pragma once
#include <string>
#include "Helpers.h"

class LicenseData
{
public:
	unsigned short licenseName;
	unsigned char licenseGroup;
	unsigned char unknown = 0x42;
	unsigned char lpCost;
	unsigned char licenseSubgroup;
	unsigned char licenseMechanic;
	unsigned char startingCharacters;
	unsigned char esperLock;
	unsigned short otherData[8];
	LicenseData();
	LicenseData(char byteNameA, char byteNameB, char licenseGroup, char unknown, char lpCost, char licenseSubgroup, char licenseMechanic, char startingCharacters, char* otherData);
	~LicenseData();
};

