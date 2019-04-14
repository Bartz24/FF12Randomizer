#include "stdafx.h"
#include "EquipRand.h"

EquipData EquipRand::equipData[557] = {};
AttributeData EquipRand::attributeData[176] = {};

EquipRand::EquipRand()
{
}


EquipRand::~EquipRand()
{
}

void EquipRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 557 * 52; //Num equips * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(Helpers::getPointer(fileName, 0x38));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 557; i++)
		{
			char data[52];
			for (int i2 = 0; i2 < 52; i2++)
			{
				data[i2] = buffer[i * 52 + i2];
			}
			equipData[i] = EquipData{ data };
		}

		system("pause");

		delete[] buffer;
		char * buffer2;
		size = 176 * 24; //Num attributes * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(Helpers::getPointer(fileName, 0x38, 0x7144));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 176; i++)
		{
			char data[24];
			for (int i2 = 0; i2 < 24; i2++)
			{
				data[i2] = buffer2[i * 24 + i2];
			}
			attributeData[i] = AttributeData{ data };
		}

		delete[] buffer2;
	}
}

void EquipRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	union U2 {
		unsigned int i;
		unsigned char c[4];
	}byte2;

	char * buffer;
	long size = 557 * 52; //Num equips * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(Helpers::getPointer(fileName, 0x38));
	buffer = new char[size];

	for (int i = 0; i < 557; i++)
	{
		EquipData d = equipData[i];
		for (int i2 = 0; i2 < 52; i2++)
		{
			buffer[i * 52 + i2] = d.unknown[i2];
		}
		Helpers::setShort(buffer, i * 52 + 0x02, d.id);
		buffer[i * 52 + 0x11] = d.equipRequirements;
		buffer[i * 52 + 0x12] = U{ d.cost }.c[0];
		buffer[i * 52 + 0x13] = U{ d.cost }.c[1];
		buffer[i * 52 + 0x18] = d.def;
		buffer[i * 52 + 0x19] = d.mRes;
		buffer[i * 52 + 0x1A] = d.power;
		buffer[i * 52 + 0x1B] = d.knockback;
		buffer[i * 52 + 0x1C] = d.critChance;
		buffer[i * 52 + 0x1D] = d.evasion;
		buffer[i * 52 + 0x1E] = d.element;
		buffer[i * 52 + 0x1F] = d.hitChance;
		buffer[i * 52 + 0x20] = U2{ d.status }.c[0];
		buffer[i * 52 + 0x21] = U2{ d.status }.c[1];
		buffer[i * 52 + 0x22] = U2{ d.status }.c[2];
		buffer[i * 52 + 0x23] = U2{ d.status }.c[3];
		buffer[i * 52 + 0x27] = d.ct;
		buffer[i * 52 + 0x28] = U2{ d.attribute }.c[0];
		buffer[i * 52 + 0x29] = U2{ d.attribute }.c[1];
		buffer[i * 52 + 0x2A] = U2{ d.attribute }.c[2];
		buffer[i * 52 + 0x2B] = U2{ d.attribute }.c[3];
		buffer[i * 52 + 0x07] = d.itemFlag;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;

	char * buffer2;
	size = 176 * 24; //Num attributes * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(Helpers::getPointer(fileName, 0x38, 0x7144));
	buffer2 = new char[size];

	for (int i = 0; i < 176; i++)
	{
		AttributeData d = attributeData[i];
		buffer2[i * 24] = U{ d.hp }.c[0];
		buffer2[i * 24 + 1] = U{ d.hp }.c[1];
		buffer2[i * 24 + 2] = U{ d.mp }.c[0];
		buffer2[i * 24 + 3] = U{ d.mp }.c[1];
		buffer2[i * 24 + 4] = d.str;
		buffer2[i * 24 + 5] = d.mag;
		buffer2[i * 24 + 6] = d.vit;
		buffer2[i * 24 + 7] = d.spd;
		buffer2[i * 24 + 8] = U2{ d.autoStatus }.c[0];
		buffer2[i * 24 + 9] = U2{ d.autoStatus }.c[1];
		buffer2[i * 24 + 10] = U2{ d.autoStatus }.c[2];
		buffer2[i * 24 + 11] = U2{ d.autoStatus }.c[3];
		buffer2[i * 24 + 12] = U2{ d.immuneStatus }.c[0];
		buffer2[i * 24 + 13] = U2{ d.immuneStatus }.c[1];
		buffer2[i * 24 + 14] = U2{ d.immuneStatus }.c[2];
		buffer2[i * 24 + 15] = U2{ d.immuneStatus }.c[3];
		buffer2[i * 24 + 16] = d.absorbElement;
		buffer2[i * 24 + 17] = d.immuneElement;
		buffer2[i * 24 + 18] = d.halfElement;
		buffer2[i * 24 + 19] = d.weakElement;
		buffer2[i * 24 + 20] = d.boostElement;
		buffer2[i * 24 + 21] = d.empty1;
		buffer2[i * 24 + 22] = d.empty2;
		buffer2[i * 24 + 23] = d.empty3;
	}

	file.write(buffer2, size);
	file.close();


	delete[] buffer2;
}

void EquipRand::process(FlagGroup flags)
{
	if (flags.hasFlag("a"))
	{
		randArmorEffects();
	}
	if (flags.hasFlag("e"))
	{
		randElements(flags.getFlag("e").getValue());
	}
	if (flags.hasFlag("s"))
	{
		randStatusEffects(flags.getFlag("s").getValue());
	}
	if (flags.hasFlag("t"))
	{
		if (flags.getFlag("t").isSmart())
		{
			randChargeTimeSmart(flags.getFlag("t").getValue());
		}
		else
			randChargeTime(flags.getFlag("t").getValue());
	}
	if (flags.hasFlag("w"))
	{
		if (flags.getFlag("w").isSmart())
		{
			randWeaponPowerSmart(flags.getFlag("w").getValue());
		}
		else
			randWeaponPower(flags.getFlag("w").getValue());
	}
	if (flags.hasFlag("d"))
	{
		if (flags.getFlag("d").isSmart())
		{
			randArmorDefSmart(flags.getFlag("d").getValue());
		}
		else
			randArmorDef(flags.getFlag("d").getValue());
	}
	if (flags.hasFlag("v"))
	{
		if (flags.getFlag("v").isSmart())
		{
			randShieldEvaSmart(flags.getFlag("v").getValue());
		}
		else
			randShieldEva(flags.getFlag("v").getValue());
	}
	if (flags.hasFlag("o"))
	{
		if (flags.getFlag("o").isSmart())
		{
			randAmmoPowerSmart(flags.getFlag("o").getValue());
		}
		else
			randAmmoPower(flags.getFlag("o").getValue());
	}
	if (flags.hasFlag("h"))
	{
		shuffleAttributes();
	}
	if (flags.hasFlag("u"))
	{
		randAttributeValues(flags.getFlag("u").getValue());
	}
	if (flags.hasFlag("c"))
	{
		if (flags.getFlag("c").isSmart())
		{
			randCostSmart(flags.getFlag("c").getValue());
		}
		else
			randCost(flags.getFlag("c").getValue());
	}
}

void EquipRand::randCost(int value)
{
	for (int i = 0; i < 557; i++)
	{
		if (equipData[i].cost > 0)
			equipData[i].cost = unsigned short(float(value / 100.f) * Helpers::randInt(2, 65535) + float(1.f - (value / 100.f)) * Helpers::randIntNorm(200, 65535, 4000, 1800));
	}
}

void EquipRand::randCostSmart(int value)
{
	for (int i = 0; i < 557; i++)
	{
		float baseCost = 5;
		if (i >= 388 && i < 420)
		{
			baseCost *= 55.f * pow(1.9f, equipData[i].power + 1);
		}
		else if (ItemFlagValue{ equipData[i].itemFlag }.hasItemFlag(ItemFlag::Accessory))
		{
			baseCost *= 500;
		}
		else if (ItemFlagValue{ equipData[i].itemFlag }.hasItemFlag(ItemFlag::BodyArmor) || ItemFlagValue{ equipData[i].itemFlag }.hasItemFlag(ItemFlag::HeadArmor))
		{
			baseCost *= 3.2f*pow((equipData[i].def + equipData[i].mRes), 1.96f);
		}
		else if (ItemFlagValue{ equipData[i].itemFlag }.hasItemFlag(ItemFlag::OffHand))
		{
			baseCost *= 4.6f*pow((equipData[i].def + equipData[i].mRes), 1.7f);
		}
		else
		{
			baseCost *= 0.9f * pow(equipData[i].power, 1.98f);
		}
		StatusValue status{ equipData[i].status };
		baseCost *= pow(1.11f, status.statuses.size());

		ElementalValue elem{ equipData[i].element };
		baseCost *= pow(1.03f, elem.elements.size());


		baseCost = max(10.f, min(baseCost, 65535.f));
		equipData[i].cost = unsigned short(float(value / 100.f) * Helpers::randInt(2, 65535) + float(1.f - (value / 100.f)) * baseCost);
	}
}

void EquipRand::randElements(int value)
{
	for (int i = 0; i < 557; i++)
	{
		setElement(equipData[i].element);
		setElementMultiple(equipData[i].element, value);
	}
	for (int i = 1; i < 176; i++)
	{
		setElement(attributeData[i].absorbElement);
		setElementMultiple(attributeData[i].absorbElement, value);
		setElement(attributeData[i].immuneElement);
		setElementMultiple(attributeData[i].immuneElement, value);
		setElement(attributeData[i].halfElement);
		setElementMultiple(attributeData[i].halfElement, value);
		setElement(attributeData[i].weakElement);
		setElementMultiple(attributeData[i].weakElement, value);
		setElement(attributeData[i].boostElement);
		setElementMultiple(attributeData[i].boostElement, value);
		ElementalValue absorb{ attributeData[i].absorbElement };
		ElementalValue immune{ attributeData[i].immuneElement };
		ElementalValue half{ attributeData[i].halfElement };
		ElementalValue weak{ attributeData[i].weakElement };
		for (int i = 0; i < absorb.elements.size(); i++)
		{
			if (immune.hasElement(absorb.elements[i]))
				immune.elements.erase(find(immune.elements.begin(), immune.elements.end(), absorb.elements[i]));
			if (half.hasElement(absorb.elements[i]))
				half.elements.erase(find(half.elements.begin(), half.elements.end(), absorb.elements[i]));
			if (weak.hasElement(absorb.elements[i]))
				weak.elements.erase(find(weak.elements.begin(), weak.elements.end(), absorb.elements[i]));
		}
		for (int i = 0; i < immune.elements.size(); i++)
		{
			if (half.hasElement(immune.elements[i]))
				half.elements.erase(find(half.elements.begin(), half.elements.end(), immune.elements[i]));
			if (weak.hasElement(immune.elements[i]))
				weak.elements.erase(find(weak.elements.begin(), weak.elements.end(), immune.elements[i]));
		}
		for (int i = 0; i < half.elements.size(); i++)
		{
			if (weak.hasElement(half.elements[i]))
				weak.elements.erase(find(weak.elements.begin(), weak.elements.end(), half.elements[i]));
		}
		attributeData[i].absorbElement = absorb.getNumValue();
		attributeData[i].immuneElement = immune.getNumValue();
		attributeData[i].halfElement = half.getNumValue();
		attributeData[i].weakElement = weak.getNumValue();
	}
}

void EquipRand::randStatusEffects(int value)
{
	for (int i = 0; i < 557; i++)
	{
		StatusValue orig{ equipData[i].status };
		equipData[i].status = 0;
		bool full = false;
		while (!full && StatusValue{ equipData[i].status }.statuses.size() < orig.statuses.size())
			full = addStatus(equipData[i].status, StatusValue::onHitWeights);
		setStatus(equipData[i].status, value, StatusValue::onHitWeights);
		StatusValue status{ equipData[i].status };
		if (status.statuses.size() > 0)
		{
			equipData[i].hitChance = Helpers::randInt(5, 50);
		}
		else
			equipData[i].hitChance = 0;
	}
	for (int i = 1; i < 176; i++)
	{
		attributeData[i].autoStatus = 0;
		setStatus(attributeData[i].autoStatus, value, StatusValue::onEquipWeights);

		attributeData[i].immuneStatus = 0;
		setStatus(attributeData[i].immuneStatus, value, StatusValue::immuneWeights);
		StatusValue autoStatus{ attributeData[i].autoStatus };
		StatusValue immuneStatus{ attributeData[i].immuneStatus };
		for (int i = 0; i < autoStatus.statuses.size(); i++)
		{
			if (immuneStatus.hasStatus(autoStatus.statuses[i]))
				immuneStatus.statuses.erase(find(immuneStatus.statuses.begin(), immuneStatus.statuses.end(), autoStatus.statuses[i]));
		}
		attributeData[i].autoStatus = autoStatus.getNumValue();
		attributeData[i].immuneStatus = immuneStatus.getNumValue();
	}
}

void EquipRand::randArmorEffects()
{
	vector<int> effects = vector<int>();
	effects.push_back(0xFF);	
	effects.push_back(0x02);
	addRangeToVector(effects, 0x04, 0x12);
	effects.push_back(0x19);
	addRangeToVector(effects, 0x1B, 0x1D);
	effects.push_back(0x1D);
	addRangeToVector(effects, 0x1F, 0x20);
	addRangeToVector(effects, 0x24, 0x25);
	effects.push_back(0x27);
	effects.push_back(0x67);
	for (int i = 0; i < 556; i++)
	{
		if (equipData[i].itemFlag >= 0x40)
		{
			if (equipData[i].itemFlag >= 0x80 || Helpers::randInt(0, 99) < 9)
				equipData[i].power = effects[Helpers::randInt(0, effects.size() - 1)];
			else
				equipData[i].power = 0xFF;
		}
	}
}

void EquipRand::randChargeTime(int value)
{
	for (int i = 0; i < 557; i++)
	{
		if (equipData[i].ct > 0)
			equipData[i].ct = unsigned char(Helpers::randInt(20 - value, 20 + value, 1, 255));
	}
}

void EquipRand::randChargeTimeSmart(int value)
{
	for (int i = 0; i < 557; i++)
	{
		if (equipData[i].ct > 0)
			equipData[i].ct = unsigned char(Helpers::randInt(equipData[i].ct - value, equipData[i].ct + value, 1, 255));
	}
}

void EquipRand::randWeaponPower(int value)
{
	for (int i = 0; i < 557; i++)
	{
		ItemFlagValue iFlag{ equipData[i].itemFlag };
		if (!iFlag.hasItemFlag(ItemFlag::OffHand) && !iFlag.hasItemFlag(ItemFlag::Accessory) && !iFlag.hasItemFlag(ItemFlag::BodyArmor)
			&& !iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			equipData[i].power = Helpers::randNormControl(10, 255, 60, 20, value);
			if (i >= 87 && i <= 97 || i == 197 || i >= 148 && i <= 150) // If gun or measure, nerf
			{
				equipData[i].power = pow(equipData[i].power, 0.8);
			}
		}
	}
}

void EquipRand::randWeaponPowerSmart(int value)
{
	for (int i = 0; i < 557; i++)
	{
		ItemFlagValue iFlag{ equipData[i].itemFlag };
		if (!iFlag.hasItemFlag(ItemFlag::OffHand) && !iFlag.hasItemFlag(ItemFlag::Accessory) && !iFlag.hasItemFlag(ItemFlag::BodyArmor)
			&& !iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			equipData[i].power = Helpers::randInt(equipData[i].power - value, equipData[i].power + value, 10, 255);
			if (i >= 87 && i <= 97 || i == 197 || i >= 148 && i <= 150) // If gun or measure, nerf
			{
				equipData[i].power *= 0.95;
			}
		}
	}
}

void EquipRand::randArmorDef(int value)
{
	for (int i = 0; i < 557; i++)
	{
		ItemFlagValue iFlag{ equipData[i].itemFlag };
		if (iFlag.hasItemFlag(ItemFlag::BodyArmor) || iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			if (equipData[i].def > 0)
				equipData[i].def = Helpers::randNormControl(0, 255, 22, 12, value);
			if (equipData[i].mRes > 0)
				equipData[i].mRes = Helpers::randNormControl(0, 255, 22, 12, value);
		}
	}
}

void EquipRand::randArmorDefSmart(int value)
{
	for (int i = 0; i < 557; i++)
	{
		ItemFlagValue iFlag{ equipData[i].itemFlag };
		if (iFlag.hasItemFlag(ItemFlag::BodyArmor) || iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			if (equipData[i].def > 0)
				equipData[i].def = Helpers::randInt(equipData[i].def - value, equipData[i].def + value, 0, 255);
			if (equipData[i].mRes > 0)
				equipData[i].mRes = Helpers::randInt(equipData[i].mRes - value, equipData[i].mRes + value, 0, 255);
		}
	}
}

void EquipRand::randShieldEva(int value)
{
	for (int i = 200; i < 220; i++)
	{
		if (equipData[i].def > 0)
			equipData[i].def = Helpers::randNormControl(0, 99, 14, 12, value);
		if (equipData[i].mRes > 0)
			equipData[i].mRes = Helpers::randNormControl(0, 99, 14, 12, value);
	}
}

void EquipRand::randShieldEvaSmart(int value)
{
	for (int i = 200; i < 220; i++)
	{
		if (equipData[i].def > 0)
			equipData[i].def = Helpers::randInt(equipData[i].def - value, equipData[i].def + value, 0, 99);
		if (equipData[i].mRes > 0)
			equipData[i].mRes = Helpers::randInt(equipData[i].mRes - value, equipData[i].mRes + value, 0, 99);
	}
}

void EquipRand::randAmmoPower(int value)
{
	for (int i = 388; i < 420; i++)
	{
		equipData[i].power = Helpers::randNormControl(1, 99, 1, 3, value);
	}
}

void EquipRand::randAmmoPowerSmart(int value)
{
	for (int i = 388; i < 420; i++)
	{
		equipData[i].power = Helpers::randInt(equipData[i].power - value, equipData[i].power + value, 1, 99);
	}
}

void EquipRand::shuffleAttributes()
{
	for (int i = 1; i < 176; i++)
	{
		vector<AttributePoint> ap = vector<AttributePoint>();

		if (attributeData[i].hp > 0)
			ap.push_back(AttributePoint(AttributeType::HP, attributeData[i].hp));
		if (attributeData[i].mp > 0)
			ap.push_back(AttributePoint(AttributeType::MP, attributeData[i].mp));
		if (attributeData[i].str > 0)
			ap.push_back(AttributePoint(AttributeType::STR, attributeData[i].str));
		if (attributeData[i].vit > 0)
			ap.push_back(AttributePoint(AttributeType::VIT, attributeData[i].vit));
		if (attributeData[i].mag > 0)
			ap.push_back(AttributePoint(AttributeType::MAG, attributeData[i].mag));
		if (attributeData[i].spd > 0)
			ap.push_back(AttributePoint(AttributeType::SPD, attributeData[i].spd));

		attributeData[i].hp = attributeData[i].mp = attributeData[i].str = attributeData[i].vit = attributeData[i].mag = attributeData[i].spd = 0;

		vector<AttributeType> types = vector<AttributeType>();
		types.push_back(AttributeType::HP);
		types.push_back(AttributeType::MP);
		types.push_back(AttributeType::STR);
		types.push_back(AttributeType::VIT);
		types.push_back(AttributeType::MAG);
		types.push_back(AttributeType::SPD);

		for (int a = 0; a < ap.size(); a++)
		{
			int index = Helpers::randInt(0, types.size() - 1);
			ap[a].type = types[index];
			types.erase(types.begin() + index);
		}
		for (int a = 0; a < ap.size(); a++)
		{
			switch (ap[a].type)
			{
			case AttributeType::HP:
				attributeData[i].hp = ap[a].getActualValue();
				break;
			case AttributeType::MP:
				attributeData[i].mp = ap[a].getActualValue();
				break;
			case AttributeType::STR:
				attributeData[i].str = ap[a].getActualValue();
				break;
			case AttributeType::VIT:
				attributeData[i].vit = ap[a].getActualValue();
				break;
			case AttributeType::MAG:
				attributeData[i].mag = ap[a].getActualValue();
				break;
			case AttributeType::SPD:
				attributeData[i].spd = ap[a].getActualValue();
				break;

			}
		}
	}
}

void EquipRand::randAttributeValues(int value)
{
	for (int i = 1; i < 176; i++)
	{
		if (attributeData[i].hp > 0)
			modifyValue(value, attributeData[i].hp, 1, 4000);
		if (attributeData[i].mp > 0)
			modifyValue(value, attributeData[i].mp, 1, 400);
		if (attributeData[i].str > 0)
			modifyValue(value, attributeData[i].str, 1, 99);
		if (attributeData[i].vit > 0)
			modifyValue(value, attributeData[i].vit, 1, 99);
		if (attributeData[i].mag > 0)
			modifyValue(value, attributeData[i].mag, 1, 99);
		if (attributeData[i].spd > 0)
			modifyValue(value, attributeData[i].spd, 1, 99);
	}
}

void EquipRand::modifyValue(int value, unsigned short &dataVal, int minN, int maxN)
{
	double mult = double(Helpers::randInt(100, value)) / double(100);
	bool doMult = Helpers::randInt(0, 99) < 50; // false = divide

	if (doMult)
	{
		dataVal = Helpers::clamp(round(double(dataVal)*mult), minN, maxN);
	}
	else
	{
		dataVal = Helpers::clamp(round(double(dataVal) / mult), minN, maxN);
	}
}

void EquipRand::modifyValue(int value, unsigned char &dataVal, int minN, int maxN)
{
	double mult = double(Helpers::randInt(100, value)) / double(100);
	bool doMult = Helpers::randInt(0, 99) < 50; // false = divide

	if (doMult)
	{
		dataVal = Helpers::clamp(round(double(dataVal)*mult), minN, maxN);
	}
	else
	{
		dataVal = Helpers::clamp(round(double(dataVal) / mult), minN, maxN);
	}
}

void EquipRand::setStatus(unsigned int &num, int chance, int* weights)
{
	StatusValue status = StatusValue(num);
	while (Helpers::randInt(0, 99) < chance)
	{
		status.addRandomStatus(weights);
	}
	num = status.getNumValue();
}

bool EquipRand::addStatus(unsigned int & num, int* weights)
{
	StatusValue status = StatusValue(num);
	int size = status.statuses.size();
	status.addRandomStatus(weights);
	num = status.getNumValue();
	return status.statuses.size() == size;
}

void EquipRand::setElement(unsigned char &num)
{
	ElementalValue orig{ num };
	num = 0;
	ElementalValue element{ num };
	while (element.elements.size() < orig.elements.size())
		element.addRandomElement();
	num = element.getNumValue();
}

void EquipRand::setElementSingle(unsigned char &num, int chance)
{
	ElementalValue element = ElementalValue(num);
	if (Helpers::randInt(0, 99) < chance)
	{
		element.addRandomElement();
	}
	num = element.getNumValue();
}

void EquipRand::setElementMultiple(unsigned char &num, int chance)
{
	ElementalValue element = ElementalValue(num);
	while (Helpers::randInt(0, 99) < chance)
	{
		element.addRandomElement();
	}
	num = element.getNumValue();
}

void EquipRand::unsellable()
{
	for (int i = 0; i < 557; i++)
	{
		bool hasCannotSell = false;
		int num = equipData[i].itemFlag;
		if (num >= 0x80)
			num -= 0x80;
		if (num >= 0x60)
			num -= 0x60;
		if (num >= 0x40)
			num -= 0x40;
		if (num >= 0x20)
			num -= 0x20;
		if (num >= 0x04)
			num -= 0x04;
		if (num >= 0x02)
		{
			hasCannotSell = true;
			num -= 0x02;
		}
		if (!hasCannotSell)
			equipData[i].itemFlag += 0x02;
	}
}

void EquipRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
