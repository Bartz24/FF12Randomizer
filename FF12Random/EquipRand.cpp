#include "stdafx.h"
#include "EquipRand.h"

EquipData EquipRand::equipData[557] = {};
AttributeData EquipRand::attributeData[173] = {};

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
		file.seekg(int(EquipData::getDataIndex()));
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

		delete[] buffer;
		char * buffer2;
		size = 173 * 24; //Num attributes * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(AttributeData::getDataIndex()));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 173; i++)
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
		unsigned char c[2];
	}byte2;

	char * buffer;
	long size = 557 * 52; //Num equips * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(EquipData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 557; i++)
	{
		EquipData d = equipData[i];
		int index = 0;
		for (int i2 = 0; i2 < 52; i2++)
		{
			if (i2 >= 0x11 && i2 <= 0x13 || i2 == 0x1A || i2 >= 0x1E && i2 <= 0x23 || i2 == 0x07 || i2 >= 0x27 && i2 <= 0x2B)
				continue;
			buffer[i * 52 + i2] = d.unknown[index];
			index++;
		}
		buffer[i * 52 + 0x11] = d.equipRequirements;
		buffer[i * 52 + 0x12] = U{ d.cost }.c[0];
		buffer[i * 52 + 0x13] = U{ d.cost }.c[1];
		buffer[i * 52 + 0x1A] = d.power;
		buffer[i * 52 + 0x1E] = d.element;
		buffer[i * 52 + 0x1F] = d.hitChance;
		buffer[i * 52 + 0x20] = d.status1;
		buffer[i * 52 + 0x21] = d.status2;
		buffer[i * 52 + 0x22] = d.status3;
		buffer[i * 52 + 0x23] = d.status4;
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
	size = 173 * 24; //Num attributes * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(AttributeData::getDataIndex()));
	buffer2 = new char[size];

	for (int i = 0; i < 173; i++)
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
		buffer2[i * 24 + 8] = d.autoStatus1;
		buffer2[i * 24 + 9] = d.autoStatus2;
		buffer2[i * 24 + 10] = d.autoStatus3;
		buffer2[i * 24 + 11] = d.autoStatus4;
		buffer2[i * 24 + 12] = d.immuneStatus1;
		buffer2[i * 24 + 13] = d.immuneStatus2;
		buffer2[i * 24 + 14] = d.immuneStatus3;
		buffer2[i * 24 + 15] = d.immuneStatus4;
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

string EquipRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Equip Data Randomization Options (NOTE: AFFECTS SPECIAL ENEMY ATTACKS):" << endl;
		cout << "\t a: Randomize armor/accessory effects" << endl;
		cout << "\t c: Randomize gil cost (200-64000, more common around 4000 G)" << endl;
		cout << "\t e: Randomize equipment elements" << endl;
		cout << "\t s: Randomize equipment status effects" << endl;
		cout << "\t t: Randomize weapon charge time" << endl;
		flags = Helpers::readFlags("acestu");
	}
	if (flags.find('a') != string::npos)
	{
		randArmorEffects();
	}
	if (flags.find('c') != string::npos)
	{
		randCost();
	}
	if (flags.find('e') != string::npos)
	{
		randElements();
	}
	if (flags.find('s') != string::npos)
	{
		randStatusEffects();
	}
	if (flags.find('t') != string::npos)
	{
		randChargeTime();
	}
	return flags;
}

void EquipRand::randCost()
{
	for (int i = 0; i < 557; i++)
	{
		if (equipData[i].cost > 0)
			equipData[i].cost = unsigned short(350000.f / (1.f + exp(0.06f*float(rand() % 10000) / 100.f + 1.5f)));
	}
}

void EquipRand::randElements()
{
	for (int i = 0; i < 557; i++)
	{
		setElement(equipData[i].element, 22);
	}
	for (int i = 0; i < 173; i++)
	{	
		setElementMultiple(attributeData[i].absorbElement, 3);
		setElementMultiple(attributeData[i].immuneElement, 5);
		setElementMultiple(attributeData[i].halfElement, 6);
		setElementMultiple(attributeData[i].weakElement, 7);
		setElement(attributeData[i].boostElement, 6);
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

void EquipRand::randStatusEffects()
{
	for (int i = 0; i < 557; i++)
	{
		setStatus(equipData[i].status1, equipData[i].status2, equipData[i].status3, equipData[i].status4, 30);
		StatusValue status{ equipData[i].status1, equipData[i].status2, equipData[i].status3, equipData[i].status4 };
		if (status.status1.size() + status.status2.size() + status.status3.size() + status.status4.size() > 0)
			equipData[i].hitChance = rand() % 96 + 5;
		else
			equipData[i].hitChance = 0;
	}
	for (int i = 0; i < 173; i++)
	{
		setStatus(attributeData[i].autoStatus1, attributeData[i].autoStatus2, attributeData[i].autoStatus3, attributeData[i].autoStatus4, 30);
		setStatus(attributeData[i].immuneStatus1, attributeData[i].immuneStatus2, attributeData[i].immuneStatus3, attributeData[i].immuneStatus4, 30);
		StatusValue autoStatus{ attributeData[i].autoStatus1, attributeData[i].autoStatus2, attributeData[i].autoStatus3, attributeData[i].autoStatus4 };
		if (autoStatus.hasStatus(int(Status1::Death), 1))
			autoStatus.status1.erase(find(autoStatus.status1.begin(), autoStatus.status1.end(), Status1::Death));
		StatusValue immuneStatus{ attributeData[i].immuneStatus1, attributeData[i].immuneStatus2, attributeData[i].immuneStatus3, attributeData[i].immuneStatus4 };
		if (immuneStatus.hasStatus(int(Status1::Death), 1))
			immuneStatus.status1.erase(find(immuneStatus.status1.begin(), immuneStatus.status1.end(), Status1::Death));
		for (int i = 0; i < autoStatus.status1.size(); i++)
		{
			if (immuneStatus.hasStatus(int(autoStatus.status1[i]), 1))
				immuneStatus.status1.erase(find(immuneStatus.status1.begin(), immuneStatus.status1.end(), autoStatus.status1[i]));
		}
		for (int i = 0; i < autoStatus.status2.size(); i++)
		{
			if (immuneStatus.hasStatus(int(autoStatus.status2[i]), 2))
				immuneStatus.status2.erase(find(immuneStatus.status2.begin(), immuneStatus.status2.end(), autoStatus.status2[i]));
		}
		for (int i = 0; i < autoStatus.status3.size(); i++)
		{
			if (immuneStatus.hasStatus(int(autoStatus.status3[i]), 3))
				immuneStatus.status3.erase(find(immuneStatus.status3.begin(), immuneStatus.status3.end(), autoStatus.status3[i]));
		}
		for (int i = 0; i < autoStatus.status4.size(); i++)
		{
			if (immuneStatus.hasStatus(int(autoStatus.status4[i]), 4))
				immuneStatus.status4.erase(find(immuneStatus.status4.begin(), immuneStatus.status4.end(), autoStatus.status4[i]));
		}
		attributeData[i].autoStatus1 = autoStatus.getNumValue(1);
		attributeData[i].autoStatus2 = autoStatus.getNumValue(2);
		attributeData[i].autoStatus3 = autoStatus.getNumValue(3);
		attributeData[i].autoStatus4 = autoStatus.getNumValue(4);
		attributeData[i].immuneStatus1 = immuneStatus.getNumValue(1);
		attributeData[i].immuneStatus2 = immuneStatus.getNumValue(2);
		attributeData[i].immuneStatus3 = immuneStatus.getNumValue(3);
		attributeData[i].immuneStatus4 = immuneStatus.getNumValue(4);
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
	effects.push_back(0x72);	
	for (int i = 0; i < 556; i++)
	{
		if (equipData[i].itemFlag >= 0x40)
		{
			if (equipData[i].itemFlag >= 0x80 || rand() % 100 < 9)
				equipData[i].power = effects[rand() % effects.size()];
			else
				equipData[i].power = 0xFF;
		}
	}
}

void EquipRand::randChargeTime()
{
	for (int i = 0; i < 557; i++)
	{
		if (equipData[i].ct > 0)
			equipData[i].ct = unsigned char(90.f / (1.f + exp(0.02f*float(rand() % 10000) / 100.f - 0.5f)));
	}
}

void EquipRand::setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance)
{
	StatusValue status = StatusValue(0, 0, 0, 0);
	while (rand() % 100 < chance)
	{
		status.addRandomStatus();
	}
	num1 = status.getNumValue(1);
	num2 = status.getNumValue(2);
	num3 = status.getNumValue(3);
	num4 = status.getNumValue(4);
}

void EquipRand::setElement(unsigned char &num, int chance)
{
	ElementalValue element = ElementalValue(0);
	if (rand() % 100 < chance)
	{
		element.addRandomElement();
	}
	num = element.getNumValue();
}

void EquipRand::setElementMultiple(unsigned char &num, int chance)
{
	ElementalValue element = ElementalValue(0);
	while (rand() % 100 < chance)
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
