#pragma once
#include "CharData.h"
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
	CharRand();
	~CharRand();
	void load();
	void save();
	string process(string preset);
	void initialEquip();
	void randStats();
	void increaseStat(unsigned short &num, int &statPointsLeft);
	void increaseStat(unsigned char &num, int &statPointsLeft);
};

