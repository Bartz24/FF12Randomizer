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

//Swords		License IDs: 32-39, 329-331
//				Equip IDs:	 4097-4113, 4256-4257, 4260-4264, 4273, 4288, 4290
//Greatswords	License IDs: 40-44, 332-333
//				Equip IDs:	 4114-4120, 4258-4259, 4262, 4265, 4269, 4289
//Katanas		License IDs: 45-49, 334-335
//				Equip IDs:	 4121-4130, 4266
//Ninja Swords	License IDs: 50-52, 336
//				Equip IDs:	 4131-4137, 4267
//Spears		License IDs: 53-59, 337
//				Equip IDs:	 4138-4149, 4270
//Poles			License IDs: 60-65, 338-339
//				Equip IDs:	 4150-4161, 4294
//Bows			License IDs: 66-72, 340-341
//				Equip IDs:	 4162-4175, 4274, 4295
//Crossbows		License IDs: 73-76
//				Equip IDs:	 4177-4182, 4272
//Guns			License IDs: 77-82, 342
//				Equip IDs:	 4183-4193, 4293
//Axes&Hammers	License IDs: 83-89, 343
//				Equip IDs:	 4194-4205, 4292
//Daggers		License IDs: 90-95, 344
//				Equip IDs:	 4206-4216, 4268
//Rods			License IDs: 96-100
//				Equip IDs:	 4217-4224
//Staves		License IDs: 101-105, 345
//				Equip IDs:	 4225-4234
//Maces			License IDs: 106-110
//				Equip IDs:	 4235-4243, 4255, 4271
//Measures		License IDs: 111-113, 346
//				Equip IDs:	 4244-4249
//Hand-bombs	License IDs: 114-116, 347
//				Equip IDs:	 4250-4254, 4291
//Shields		License IDs: 117-125, 348
//				Equip IDs:	 4297-4315
//Heavy Armor	License IDs: 126-136, 349-350
//				Equip IDs:	 4358-4375, 4418-4435
//Light Armor	License IDs: 137-148, 351
//				Equip IDs:	 4316-4336, 4376-4396
//Mystic Armor	License IDs: 149-160, 352
//				Equip IDs:	 4337-4357, 4397-4417
//Accessories	License IDs: 161-181, 353-354
//				Equip IDs:	 4436-4483
//All			License IDs: 32-181, 329-354
//				Equip IDs:	 4097-4255, 4258-4259, 4264, 4266-4274, 4288-4483

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
	void setStatus(unsigned int &num, int chance, int* weights);
	bool addStatus(unsigned int & num, int* weights);
	void setElement(unsigned char &num);
	void setElementSingle(unsigned char &num, int chance);
	void setElementMultiple(unsigned char &num, int chance);
	void unsellable();
};

