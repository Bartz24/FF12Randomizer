#pragma once
#include <algorithm>
#include "CharData.h"
#include "StartGambitData.h"
#include "CharValue.h"
#include "ItemFlagValue.h"
#include "LicenseRand.h"
#include "EquipRand.h"

class CharRand
{
private:
	string fileName;

public:
	static CharData charData[40];
	static StartGambitData gambitData[7];
	static int names[12];
	CharRand();
	~CharRand();
	void load();
	void save();
	string process(string preset);
	void initialEquip();
	void randStats();
	void swapCharas();
	void fixLicenses(int charIds[6]);
	void fixGambits(int charIds[6]);
	void increaseStat(unsigned short &num, int &statPointsLeft);
	void increaseStat(unsigned char &num, int &statPointsLeft);
};

