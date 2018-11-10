#include "stdafx.h"
#include "CharRand.h"

CharData CharRand::charData[40] = {};

CharRand::CharRand()
{
}


CharRand::~CharRand()
{
}

void CharRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 40 * 128; //Num chars * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(CharData::getDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 40; i++)
		{
			char data[128];
			for (int i2 = 0; i2 < 128; i2++)
			{
				data[i2] = buffer[i * 128 + i2];
			}
			charData[i] = CharData{ data };
		}

		delete[] buffer;
	}
}

void CharRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	char * buffer;
	long size = 40 * 128; //Num chars * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(CharData::getDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 40; i++)
	{
		CharData d = charData[i];
		int index = 0;
		for (int i2 = 0; i2 < 128; i2++)
		{
			if (i2 >= 0x0A && i2 <= 0x13 || i2 == 0x16 || i2 == 0x17 || i2 == 0x19 || i2 == 0x1A || i2 == 0x1B || i2 == 0x1D || i2 == 0x1E || i2 == 0x1F
				|| i2 == 0x21 || i2 == 0x22 || i2 == 0x24 || i2 == 0x25 || i2 == 0x27 || i2 == 0x28 || i2 >= 0x34 && i2 <= 0x3D || i2 >= 0x58 && i2 <= 0x6B || i2 >= 0x48 && i2 <= 0x4B)
				continue;
			buffer[i * 128 + i2] = d.unknown[index];
			index++;
		}
		buffer[i * 128 + 0x0A] = U{ d.weapon }.c[0];
		buffer[i * 128 + 0x0B] = U{ d.weapon }.c[1];
		buffer[i * 128 + 0x0C] = U{ d.offHand }.c[0];
		buffer[i * 128 + 0x0D] = U{ d.offHand }.c[1];
		buffer[i * 128 + 0x0E] = U{ d.head }.c[0];
		buffer[i * 128 + 0x0F] = U{ d.head }.c[1];
		buffer[i * 128 + 0x10] = U{ d.body }.c[0];
		buffer[i * 128 + 0x11] = U{ d.body }.c[1];
		buffer[i * 128 + 0x12] = U{ d.accessory }.c[0];
		buffer[i * 128 + 0x13] = U{ d.accessory }.c[1];
		buffer[i * 128 + 0x16] = U{ d.hp }.c[0];
		buffer[i * 128 + 0x17] = U{ d.hp }.c[1];
		buffer[i * 128 + 0x19] = d.hpModifier;
		buffer[i * 128 + 0x1A] = U{ d.mp }.c[0];
		buffer[i * 128 + 0x1B] = U{ d.mp }.c[1];
		buffer[i * 128 + 0x1D] = d.mpModifier;
		buffer[i * 128 + 0x1E] = d.str;
		buffer[i * 128 + 0x1F] = d.strModifier;
		buffer[i * 128 + 0x21] = d.mag;
		buffer[i * 128 + 0x22] = d.magModifier;
		buffer[i * 128 + 0x24] = d.vit;
		buffer[i * 128 + 0x25] = d.vitModifier;
		buffer[i * 128 + 0x27] = d.spd;
		buffer[i * 128 + 0x28] = d.spdModifier;
		for (int item = 0; item < 10; item++)
		{
			buffer[i * 128 + 0x58 + item * 2] = U{ d.items[item] }.c[0];
			buffer[i * 128 + 0x59 + item * 2] = U{ d.items[item] }.c[1];
			buffer[i * 128 + 0x34 + item] = d.itemCount[item];
		}
		buffer[i * 128 + 0x4C] = d.immune1;
		buffer[i * 128 + 0x4D] = d.immune2;
		buffer[i * 128 + 0x4E] = d.immune3;
		buffer[i * 128 + 0x4F] = d.immune4;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;
}

string CharRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Char Data Options:" << endl;
		cout << "\t i: Update initial equipment/items/gambits/abilities" << endl;
		cout << "\t s: Randomize character stats" << endl;
		flags = Helpers::readFlags("is");
	}
	if (flags.find('i') != string::npos)
	{
		initialEquip();
	}
	if (flags.find('s') != string::npos)
	{
		randStats();
	}
	return flags;
}

void CharRand::initialEquip()
{
	for (int i = 0; i < 7; i++)
	{
		vector<unsigned short> weapons = vector<unsigned short>();
		vector<unsigned short> offHand = vector<unsigned short>();
		vector<unsigned short> head = vector<unsigned short>();
		vector<unsigned short> body = vector<unsigned short>();
		vector<unsigned short> accessory = vector<unsigned short>();
		vector<unsigned short> abilities = vector<unsigned short>();
		for (int data = 32; data < 359; data++)
		{
			if (data >= 300 && data <= 328 || data >= 219 && data <= 275)
				continue;
			if (LicenseRand::licenseData[data].startingCharacters & int(pow(2, i)))
			{
				for (int slot = 0; slot < 8; slot++)
				{
					unsigned short slotData = LicenseRand::licenseData[data].otherData[slot];
					if (slotData != 0xFFFF)
					{
						if (slotData < 100)
							abilities.push_back(slotData + 12288);
						else if (slotData < 0x1000)
							abilities.push_back(slotData + 16226);
						else if (slotData >= 0x1000 && slotData < 0x3000)
						{
							ItemFlagValue flag{ EquipRand::equipData[slotData - 4096].itemFlag };
							if (flag.hasItemFlag(ItemFlag::Accessory))
								accessory.push_back(slotData);
							else if (flag.hasItemFlag(ItemFlag::BodyArmor))
								body.push_back(slotData);
							else if (flag.hasItemFlag(ItemFlag::HeadArmor))
								head.push_back(slotData);
							else if (flag.hasItemFlag(ItemFlag::OffHand))
								offHand.push_back(slotData);
							else
								weapons.push_back(slotData);
						}
					}
				}
			}
		}
		if (i != 6)
		{
			if (weapons.size() > 0)
				charData[i].weapon = weapons[rand() % weapons.size()];
			else
				charData[i].weapon = 0xFFFF;
		}		
		else
		{
			charData[i].immune4 = 0x80;
			for (int slot = 0; slot < accessory.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[accessory[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status2::Sap), 2)
					|| status.hasStatus(int(Status2::Disable), 2) || status.hasStatus(int(Status2::Immobilize), 2) 
					|| status.hasStatus(int(Status1::Sleep), 1) || status.hasStatus(int(Status1::Stop), 1)
					|| status.hasStatus(int(Status1::Confuse), 1) || status.hasStatus(int(Status1::Doom), 1)
					|| status.hasStatus(int(Status4::Berserk), 4) || status.hasStatus(int(Status4::XZone), 4))
				{
					accessory.erase(accessory.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < head.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[head[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status2::Sap), 2)
					|| status.hasStatus(int(Status2::Disable), 2) || status.hasStatus(int(Status2::Immobilize), 2)
					|| status.hasStatus(int(Status1::Sleep), 1) || status.hasStatus(int(Status1::Stop), 1)
					|| status.hasStatus(int(Status1::Confuse), 1) || status.hasStatus(int(Status1::Doom), 1)
					|| status.hasStatus(int(Status4::Berserk), 4) || status.hasStatus(int(Status4::XZone), 4))
				{
					head.erase(head.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < body.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[body[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status2::Sap), 2)
					|| status.hasStatus(int(Status2::Disable), 2) || status.hasStatus(int(Status2::Immobilize), 2)
					|| status.hasStatus(int(Status1::Sleep), 1) || status.hasStatus(int(Status1::Stop), 1)
					|| status.hasStatus(int(Status1::Confuse), 1) || status.hasStatus(int(Status1::Doom), 1)
					|| status.hasStatus(int(Status4::Berserk), 4) || status.hasStatus(int(Status4::XZone), 4))
				{
					body.erase(body.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < offHand.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[offHand[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status2::Sap), 2)
					|| status.hasStatus(int(Status2::Disable), 2) || status.hasStatus(int(Status2::Immobilize), 2)
					|| status.hasStatus(int(Status1::Sleep), 1) || status.hasStatus(int(Status1::Stop), 1)
					|| status.hasStatus(int(Status1::Confuse), 1) || status.hasStatus(int(Status1::Doom), 1)
					|| status.hasStatus(int(Status4::Berserk), 4) || status.hasStatus(int(Status4::XZone), 4))
				{
					offHand.erase(offHand.begin() + slot);
					slot--;
				}
			}
		}
		if (i == 0)
		{
			for (int slot = 0; slot < accessory.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[accessory[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status4::XZone), 4))
				{
					accessory.erase(accessory.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < head.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[head[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status4::XZone), 4))
				{
					head.erase(head.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < body.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[body[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status4::XZone), 4))
				{
					body.erase(body.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < offHand.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[offHand[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status4::XZone), 4))
				{
					offHand.erase(offHand.begin() + slot);
					slot--;
				}
			}
		}
		if (charData[i].weapon != 0xFFFF && EquipRand::equipData[charData[i].weapon - 4096].equipRequirements >= 0x17)
		{
			if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x17)
				charData[i].offHand = rand() % 8 + 4484;
			else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x18)
				charData[i].offHand = rand() % 8 + 4492;
			else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x19)
				charData[i].offHand = rand() % 8 + 4500;
			else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x1A)
				charData[i].offHand = rand() % 8 + 4508;
			else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0xFF)
				charData[i].offHand = 0xFFFF;
		}
		else
		{
			if (offHand.size() > 0)
				charData[i].offHand = offHand[rand() % offHand.size()];
			else
				charData[i].offHand = 0xFFFF;
		}
		if (head.size() > 0)
			charData[i].head = head[rand() % head.size()];
		else
			charData[i].head = 0xFFFF;
		if (body.size() > 0)
			charData[i].body = body[rand() % body.size()];
		else
			charData[i].body = 0xFFFF;
		if (accessory.size() > 0)
			charData[i].accessory = accessory[rand() % accessory.size()];
		else
			charData[i].accessory = 0xFFFF;

		for (int item = 0; item < 10; item++)
		{
			charData[i].itemCount[item] = 0;
			charData[i].items[item] = 0xFFFF;
		}

		for (int item = 0; item < 2; item++)
		{
			int type;
			do {
				type = rand() % 64;
			} while (type >= 29 && type <= 41);
			charData[i].items[item] = type;
			charData[i].itemCount[item] = unsigned char(log2(float(rand() % 100) + 10.f) * 3.f - 8.f);
		}
		for (int ability = 0; ability < 2; ability++)
		{
			if (abilities.size() == 0)
				break;

			int index = rand() % abilities.size();

			charData[i].items[ability + 2] = abilities[index];
			abilities.erase(abilities.begin() + index);
			charData[i].itemCount[ability + 2] = 1;
		}
		if (i != 6)
		{
			for (int gambit = 0; gambit < 6; gambit++)
			{
				charData[i].items[gambit + 4] = rand() % 255 + 24576;
				charData[i].itemCount[gambit + 4] = 1;
			}
		}
		else
		{
			for (int item = 0; item < 6; item++)
			{
				int type;
				do {
					type = rand() % 64;
				} while (type >= 29 && type <= 41);
				charData[i].items[item + 4] = type;
				charData[i].itemCount[item + 4] = unsigned char(log2(float(rand() % 100) + 10.f) * 3.f - 8.f);
			}
		}
	}
}

void CharRand::randStats()
{
	for (int i = 0; i < 40; i++)
	{
		int totalStatPoints = 0;
		totalStatPoints += charData[i].hp / 3;
		totalStatPoints += charData[i].hpModifier / 8;
		totalStatPoints += charData[i].mp;
		totalStatPoints += charData[i].mpModifier / 8;
		totalStatPoints += charData[i].str;
		totalStatPoints += charData[i].strModifier / 4;
		totalStatPoints += charData[i].mag;
		totalStatPoints += charData[i].magModifier / 4;
		totalStatPoints += charData[i].vit;
		totalStatPoints += charData[i].vitModifier / 3;
		totalStatPoints += charData[i].spd;
		totalStatPoints += charData[i].spdModifier;

		charData[i].hp = 0;
		charData[i].hpModifier = 0;
		charData[i].mp = 0;
		charData[i].mpModifier = 0;
		charData[i].str = 0;
		charData[i].strModifier = 0;
		charData[i].mag = 0;
		charData[i].magModifier = 0;
		charData[i].vit = 0;
		charData[i].vitModifier = 0;
		charData[i].spd = 0;
		charData[i].spdModifier = 0;

		while (totalStatPoints > 0)
		{
			increaseStat(charData[i].hp, totalStatPoints);
			increaseStat(charData[i].hpModifier, totalStatPoints);
			increaseStat(charData[i].mp, totalStatPoints);
			increaseStat(charData[i].mpModifier, totalStatPoints);
			increaseStat(charData[i].str, totalStatPoints);
			increaseStat(charData[i].strModifier, totalStatPoints);
			increaseStat(charData[i].mag, totalStatPoints);
			increaseStat(charData[i].magModifier, totalStatPoints);
			increaseStat(charData[i].vit, totalStatPoints);
			increaseStat(charData[i].vitModifier, totalStatPoints);
			increaseStat(charData[i].spd, totalStatPoints);
			increaseStat(charData[i].spdModifier, totalStatPoints);
		}

		charData[i].hp = charData[i].hp * 3 + rand() % 4 - 2;
		charData[i].hpModifier = charData[i].hpModifier * 8 + rand() % 10 - 4;
		charData[i].mp = charData[i].mp + rand() % 2;
		charData[i].mpModifier = charData[i].mpModifier * 8 + rand() % 10 - 4;
		charData[i].str = charData[i].str + rand() % 2;
		charData[i].strModifier = charData[i].strModifier * 4 + rand() % 6 - 2;
		charData[i].mag = charData[i].mag + rand() % 2;
		charData[i].magModifier = charData[i].magModifier * 4 + rand() % 6 - 2;
		charData[i].vit = charData[i].vit + rand() % 2;
		charData[i].vitModifier = charData[i].vitModifier * 4 + rand() % 4 - 1;
		charData[i].spd = charData[i].spd + rand() % 2;
		charData[i].spdModifier = charData[i].spdModifier + rand() % 2;
	}
}

void CharRand::increaseStat(unsigned char & num, int &statPointsLeft)
{
	if (statPointsLeft <= 0)
		return;
	if (rand() % 100 < 40)
	{
		num++;
		statPointsLeft--;
	}
}

void CharRand::increaseStat(unsigned short & num, int &statPointsLeft)
{
	if (statPointsLeft <= 0)
		return;
	if (rand() % 100 < 40)
	{
		num++;
		statPointsLeft--;
	}
}
