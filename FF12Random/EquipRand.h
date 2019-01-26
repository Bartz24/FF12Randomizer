#pragma once
#include <algorithm>
#include "EquipData.h"
#include "AttributeData.h"
#include "StatusValue.h"
#include "ElementalValue.h"
#include "ItemFlagValue.h"
#include "FlagGroup.h"
#include "AttributePoint.h"

using namespace std;

//White		License IDs:	182-189, 355, 208-211
//			Magic IDs:		0-17,51-56,69
//Black		License IDs:	190-197, 356, 358, 215-217
//			Magic IDs:		18-33,35,57,59-65
//Time		License IDs:	198-204, 357, 359, 218
//			Magic IDs:		36-50,67,71-72,79-80
//Green		License IDs:	205-207
//			Magic IDs:		58,66,70,73-75
//Arcane	License IDs:	212-214
//			Magic IDs:		76-78,68,34
//Technick	License IDs:	276-299
//			Magic IDs:		158-181
//All		License IDs:	182-218, 276-299, 355-359

class EquipRand
{
private:
	string fileName;

public:
	static EquipData equipData[557];
	static AttributeData attributeData[176];
	EquipRand();
	~EquipRand();
	void load();
	void save();
	void process(FlagGroup flags);
	void randCost(int value);
	void randCostSmart(int value);
	void randElements(int value);
	void randStatusEffects(int value);
	void randArmorEffects();
	void randChargeTime(int value);
	void randChargeTimeSmart(int value);
	void randWeaponPower(int value);
	void randWeaponPowerSmart(int value);
	void randArmorDef(int value);
	void randArmorDefSmart(int value);
	void randShieldEva(int value);
	void randShieldEvaSmart(int value);
	void randAmmoPower(int value);
	void randAmmoPowerSmart(int value);
	void shuffleAttributes();
	void randAttributeValues(int value);
	void modifyValue(int value, unsigned short &dataVal, int minN, int maxN);
	void modifyValue(int value, unsigned char &dataVal, int minN, int maxN);
	void addRangeToVector(vector<int>& data, int low, int high);
	void setStatus(unsigned int &num, int chance, initializer_list<Status> blacklist);
	void addStatus(unsigned int & num, initializer_list<Status> blacklist);
	void setElement(unsigned char &num);
	void setElementSingle(unsigned char &num, int chance);
	void setElementMultiple(unsigned char &num, int chance);
	void unsellable();
};

