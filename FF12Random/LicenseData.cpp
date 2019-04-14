#include "stdafx.h"
#include "LicenseData.h"

LicenseData::LicenseData(char byteNameA, char byteNameB, char licenseGroup, char unknown, char lpCost, char licenseSubgroup, char licenseMechanic, char startingCharacters, char* otherData)
{
	this->licenseName = byteNameB | byteNameA << 8;
	this->licenseGroup = licenseGroup;
	this->unknown = unknown;
	this->lpCost = lpCost;
	this->licenseSubgroup = licenseSubgroup;
	this->licenseMechanic = licenseMechanic;
	this->startingCharacters = startingCharacters;
	for (int i = 0; i < 8; i++)
	{
		char data[] = { otherData[i * 2] , otherData[i * 2 + 1] };
		this->otherData[i] = *reinterpret_cast<unsigned short*>(data);
	}
}

LicenseData::LicenseData()
{

}


LicenseData::~LicenseData()
{
}
