#pragma once
#include "EquipData.h"
#include "AttributeData.h"
#include "StatusValue.h"
#include "ElementalValue.h"

class EquipRand
{
private:
	string fileName;

public:
	static EquipData equipData[557];
	static AttributeData attributeData[173];
	EquipRand();
	~EquipRand();
	void load();
	void save();
	string process(string preset);
	void randCost();
	void randElements();
	void randStatusEffects();
	void randArmorEffects();
	void randChargeTime();
	void addRangeToVector(vector<int>& data, int low, int high);
	void setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance);
	void setElement(unsigned char &num, int chance);
	void setElementMultiple(unsigned char &num, int chance);
	void unsellable();
};

