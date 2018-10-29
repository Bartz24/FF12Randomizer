#include "stdafx.h"
#include "LicenseData.h"


LicenseDataOffset LicenseData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return LicenseDataOffset::us;
	if (language == "ch")
		return LicenseDataOffset::ch;
	if (language == "cn")
		return LicenseDataOffset::cn;
	if (language == "de")
		return LicenseDataOffset::de;
	if (language == "es")
		return LicenseDataOffset::es;
	if (language == "fr")
		return LicenseDataOffset::fr;
	if (language == "it")
		return LicenseDataOffset::it;
	if (language == "kr")
		return LicenseDataOffset::kr;
	return LicenseDataOffset::in;
}

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
