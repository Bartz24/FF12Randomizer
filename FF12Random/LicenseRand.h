#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Helpers.h"
#include "LicenseData.h"
#include "ItemRand.h"
#include "EquipRand.h"
#include "MagicRand.h"
#include "AugmentRand.h"


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
	void process(FlagGroup flags);
	void updateMagickLicenses();
	void updateLicenses(std::vector<std::vector<int>> &abilities, int type, std::vector<int> &licenses);
	void randCost(int value);
	void randCostSmart(int value);
	int augmentWorth(int index);
	void randAbilities(bool together, bool changeNum);
	void randEquipment(bool together, bool changeNum);
	void randAugments(bool includeBad);
	void addRangeToVector(vector<int>& data, int low, int high);
	void replaceAbilitiesChance(int start, int end, std::vector<unsigned short> &abilities);
	void replaceAbilities(int start, int end, std::vector<unsigned short> &abilities);
	void extractAbilities(std::vector<unsigned short> &abilities, int start, int end, bool clear);
};

