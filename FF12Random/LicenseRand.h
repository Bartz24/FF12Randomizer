#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Helpers.h"
#include "LicenseData.h"

class LicenseRand
{
private:
	string fileName;

public:
	static LicenseData licenseData[361];
	LicenseRand();
	~LicenseRand();
	void load();
	void save();
	void process();
	void randCost();
	void randAbilities();
	void randEquipment();
	void randAugments();
	void addRangeToVector(vector<int>& data, int low, int high);
	void replaceAbilitiesChance(int start, int end, std::vector<unsigned short> &abilities);
	void replaceAbilities(int start, int end, std::vector<unsigned short> &abilities);
	void extractAbilities(std::vector<unsigned short> &abilities, int start, int end, bool clear);
};

