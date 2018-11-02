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
	string process(string preset);
	void randCost();
	string randAbilities(string preset);
	string randEquipment(string preset);
	void randAugments();
	void addRangeToVector(vector<int>& data, int low, int high);
	void replaceAbilitiesChance(int start, int end, std::vector<unsigned short> &abilities);
	void replaceAbilities(int start, int end, std::vector<unsigned short> &abilities);
	void extractAbilities(std::vector<unsigned short> &abilities, int start, int end, bool clear);
};

