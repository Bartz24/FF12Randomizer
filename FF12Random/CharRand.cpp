#include "stdafx.h"
#include "CharRand.h"

enum CharacterID
{
	vaan,
	ashe,
	fran,
	balthier,
	basch,
	penelo,
	reks,
	amalia,
	baschGuest1,
	baschGuest2,
	lamont,
	vossler1,
	vossler2,
	larsa,
	reddas = 16
};

CharData CharRand::charData[40] = {};
StartGambitData CharRand::gambitData[7] = {};
int CharRand::names[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

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

		char * buffer2;
		size = 7 * 64; //Num gambits * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(StartGambitData::getDataIndex()));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 7; i++)
		{
			char data[64];
			for (int i2 = 0; i2 < 64; i2++)
			{
				data[i2] = buffer2[i * 64 + i2];
			}
			gambitData[i] = StartGambitData{ data };
		}

		delete[] buffer2;
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
			buffer[i * 128 + i2] = d.unknown[i2];
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
		buffer[i * 128 + 0x2C] = d.gambits;
		for (int item = 0; item < 10; item++)
		{
			buffer[i * 128 + 0x58 + item * 2] = U{ d.items[item] }.c[0];
			buffer[i * 128 + 0x59 + item * 2] = U{ d.items[item] }.c[1];
			buffer[i * 128 + 0x34 + item] = d.itemCount[item];
		}
		buffer[i * 128 + 0x48] = d.auto1;
		buffer[i * 128 + 0x49] = d.auto2;
		buffer[i * 128 + 0x4A] = d.auto3;
		buffer[i * 128 + 0x4B] = d.auto4;
		buffer[i * 128 + 0x4C] = d.immune1;
		buffer[i * 128 + 0x4D] = d.immune2;
		buffer[i * 128 + 0x4E] = d.immune3;
		buffer[i * 128 + 0x4F] = d.immune4;
		buffer[i * 128 + 0x70] = d.model;
	}
	file.write(buffer, size);
	file.close();


	delete[] buffer;


	char * buffer2;
	size = 7 * 64; //Num loots * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(StartGambitData::getDataIndex()));
	buffer2 = new char[size];

	for (int i = 0; i < 7; i++)
	{
		StartGambitData d = gambitData[i];
		int index = 0;
		for (int i2 = 0; i2 < 64; i2++)
		{
			buffer2[i * 64 + i2] = d.unknown[i2];
		}
		for (int i2 = 0; i2 < 12; i2++)
		{
			buffer2[i * 64 + i2 * 2] = U{ d.gambits[i2] }.c[0];
			buffer2[i * 64 + i2 * 2 + 1] = U{ d.gambits[i2] }.c[1];
			buffer2[i * 64 + 0x20 + i2 * 2] = U{ d.actions[i2] }.c[0];
			buffer2[i * 64 + 0x21 + i2 * 2] = U{ d.actions[i2] }.c[1];
		}
	}

	file.write(buffer2, size);
	file.close();

	delete[] buffer2;
}

void CharRand::process(FlagGroup flags)
{
	if (flags.hasFlag("s"))
	{
		swapCharas();
	}
	if (flags.hasFlag("i"))
	{
		initialEquip();
	}
	if (flags.hasFlag("c"))
	{
		randStats();
	}
	if (flags.hasFlag("o"))
	{
		soloChara();
	}

	charData[6].immune4 = 0x80;

	checkDangerousEquip(charData[0].accessory);
	checkDangerousEquip(charData[0].head);
	checkDangerousEquip(charData[0].body);
	checkDangerousEquip(charData[0].offHand);

	checkDangerousEquip(charData[6].accessory);
	checkDangerousEquip(charData[6].head);
	checkDangerousEquip(charData[6].body);
	checkDangerousEquip(charData[6].offHand);
}

void CharRand::checkDangerousEquip(int itemID)
{
	if (itemID != 0xFFFF)
	{
		ItemFlagValue iFlag{ EquipRand::equipData[itemID - 4096].itemFlag };
		if (iFlag.hasItemFlag(ItemFlag::OffHand) && EquipRand::equipData[itemID - 4096].equipRequirements >= 0x17)
			return;

		AttributeData data = EquipRand::attributeData[EquipRand::equipData[itemID - 4096].attribute / 24];
		StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
		if (statusDangerous(status))
			itemID == 0xFFFF;
	}
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
				charData[i].weapon = weapons[Helpers::randInt(0, weapons.size() - 1)];
			else
				charData[i].weapon = 0xFFFF;
		}		
		if (i == 0 || i == 6)
		{
			for (int slot = 0; slot < accessory.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[accessory[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 };
				if (statusDangerous(status))
				{
					accessory.erase(accessory.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < head.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[head[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (statusDangerous(status))
				{
					head.erase(head.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < body.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[body[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (statusDangerous(status))
				{
					body.erase(body.begin() + slot);
					slot--;
				}
			}
			for (int slot = 0; slot < offHand.size(); slot++)
			{
				AttributeData data = EquipRand::attributeData[EquipRand::equipData[offHand[slot] - 4096].attribute / 24 - 3];
				StatusValue status{ data.autoStatus1, data.autoStatus2, data.autoStatus3, data.autoStatus4 }; 
				if (statusDangerous(status))
				{
					offHand.erase(offHand.begin() + slot);
					slot--;
				}
			}
		}
		if (i != 6)
		{
			if (charData[i].weapon != 0xFFFF && EquipRand::equipData[charData[i].weapon - 4096].equipRequirements >= 0x17)
			{
				if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x17)
					charData[i].offHand = Helpers::randInt(4484, 4491);
				else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x18)
					charData[i].offHand = Helpers::randInt(4492, 4499);
				else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x19)
					charData[i].offHand = Helpers::randInt(4500, 4507);
				else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0x1A)
					charData[i].offHand = Helpers::randInt(4508, 4515);
				else if (EquipRand::equipData[charData[i].weapon - 4096].equipRequirements == 0xFF)
					charData[i].offHand = 0xFFFF;
			}
			else
			{
				if (offHand.size() > 0)
					charData[i].offHand = offHand[Helpers::randInt(0, offHand.size() - 1)];
				else
					charData[i].offHand = 0xFFFF;
			}
		}
		if (head.size() > 0)
			charData[i].head = head[Helpers::randInt(0, head.size() - 1)];
		else
			charData[i].head = 0xFFFF;
		if (body.size() > 0)
			charData[i].body = body[Helpers::randInt(0, body.size() - 1)];
		else
			charData[i].body = 0xFFFF;
		if (accessory.size() > 0)
			charData[i].accessory = accessory[Helpers::randInt(0, accessory.size() - 1)];
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
				type = Helpers::randInt(0, 63);
			} while (type >= 29 && type <= 41);
			charData[i].items[item] = type;
			charData[i].itemCount[item] = unsigned char(log2(float(Helpers::randInt(0,99)) + 10.f) * 3.f - 8.f);
		}
		for (int ability = 0; ability < 2; ability++)
		{
			if (abilities.size() == 0)
				break;

			int index = Helpers::randInt(0, abilities.size() - 1);

			charData[i].items[ability + 2] = abilities[index];
			abilities.erase(abilities.begin() + index);
			charData[i].itemCount[ability + 2] = 1;
		}
		if (i != 6)
		{
			for (int gambit = 0; gambit < 6; gambit++)
			{
				charData[i].items[gambit + 4] = Helpers::randInt(24576, 24830);
				charData[i].itemCount[gambit + 4] = 1;
			}
		}
		else
		{
			for (int item = 0; item < 6; item++)
			{
				int type;
				do {
					type = Helpers::randInt(0, 63);
				} while (type >= 29 && type <= 41);
				charData[i].items[item + 4] = type;
				charData[i].itemCount[item + 4] = unsigned char(log2(float(Helpers::randInt(0, 99)) + 10.f) * 3.f - 8.f);
			}
		}
	}
}

bool CharRand::statusDangerous(StatusValue &status)
{
	return status.hasStatus(int(Status1::Petrify), 1) || status.hasStatus(int(Status1::Death), 1) || status.hasStatus(int(Status2::Sap), 2)
		|| status.hasStatus(int(Status2::Disable), 2) || status.hasStatus(int(Status2::Immobilize), 2)
		|| status.hasStatus(int(Status1::Sleep), 1) || status.hasStatus(int(Status1::Stop), 1)
		|| status.hasStatus(int(Status1::Confuse), 1) || status.hasStatus(int(Status1::Doom), 1)
		|| status.hasStatus(int(Status4::Berserk), 4) || status.hasStatus(int(Status4::XZone), 4);
}

void CharRand::soloChara()
{
	for (int i = 0; i < 27; i++)
	{
		if (i == 0 || i == 6)
			continue;
		charData[i].auto1 = 0x10;
		charData[i].auto2 = 0x01;
		charData[i].head = charData[i].weapon = charData[i].offHand = charData[i].body = charData[i].accessory = 0xFFFF;
		charData[i].hp = 1;
		charData[i].hpModifier = charData[i].mpModifier = charData[i].strModifier = charData[i].magModifier = charData[i].spdModifier = charData[i].vitModifier = 0;
		charData[i].mp = charData[i].str = charData[i].mag = charData[i].spd = charData[i].vit = 0;
		for (int item = 0; item < 10; item++)
		{
			charData[i].items[item] = 0xFFFF;
			charData[i].itemCount[item] = 0;
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

		charData[i].hp = charData[i].hp * 3 + Helpers::randInt(-2, 2);
		charData[i].hpModifier = charData[i].hpModifier * 8 + Helpers::randInt(-6, 6);
		charData[i].mp = charData[i].mp + Helpers::randInt(-2, 2);
		charData[i].mpModifier = charData[i].mpModifier * 8 + Helpers::randInt(-6, 6);
		charData[i].str = charData[i].str + Helpers::randInt(-1, 1);
		charData[i].strModifier = charData[i].strModifier * 4 + Helpers::randInt(-3, 3);
		charData[i].mag = charData[i].mag + Helpers::randInt(-1, 1);
		charData[i].magModifier = charData[i].magModifier * 4 + Helpers::randInt(-3, 3);
		charData[i].vit = charData[i].vit + Helpers::randInt(-1, 1);
		charData[i].vitModifier = charData[i].vitModifier * 4 + Helpers::randInt(-3, 3);
		charData[i].spd = charData[i].spd + Helpers::randInt(-2, 2);
		charData[i].spdModifier = charData[i].spdModifier + Helpers::randInt(-2, 2);
	}
}

void CharRand::swapCharas()
{
	int ids[] = { 0,1,2,3,4,5 };
	shuffle(begin(ids), end(ids), Helpers::rng);
	vector<CharData> data = vector<CharData>();
	for (int i = 0; i < 6; i++)
		data.push_back(charData[i]);
	for (int i = 0; i < 6; i++)
	{	
		charData[i] = data[ids[i]];
		charData[i].items[8] = 0x60A5 + i;
		charData[i].items[9] = 0x60E2 + i;
		charData[i].gambits = 0x48;
	}
	charData[0].gambits = 0x00;
	names[0] = ids[0];
	names[1] = ids[3];
	names[2] = ids[2];
	names[3] = ids[4];
	names[4] = ids[1];
	names[5] = ids[5];

	fixLicenses(ids);
	fixGambits(ids);

	if (ids[1] != 1)
	{
		charData[CharacterID::amalia] = charData[CharacterID::ashe];
		charData[CharacterID::amalia].items[5] = 0x60AB;
	}
	if (ids[4] != 4)
	{
		charData[CharacterID::baschGuest1] = charData[CharacterID::basch];
		charData[CharacterID::baschGuest1].weapon = 0xFFFF;
		charData[CharacterID::baschGuest1].offHand = 0xFFFF;
		charData[CharacterID::baschGuest1].head = 0xFFFF;
		charData[CharacterID::baschGuest1].body = 0xFFFF;
		charData[CharacterID::baschGuest1].accessory = 0xFFFF;

		charData[CharacterID::baschGuest2] = charData[CharacterID::basch];
	}
	int gids[] = { int(CharacterID::reks), int(CharacterID::vossler1), int(CharacterID::larsa), int(CharacterID::reddas) };
	shuffle(begin(gids), end(gids), Helpers::rng);

	vector<CharData> gdata = vector<CharData>();
	for (int i = 6; i < 17; i++)
	{
		gdata.push_back(charData[i]);
	}
	int index = 0;
	for (int i = 6; i < 17; i++)
	{
		if (i >= 7 && i < 11 || i == 12 || i == 14 || i == 15)
			continue;
		charData[i] = gdata[gids[index]-6];
		charData[i].gambits = 0x48;
		index++;
	}
	if (gids[2] != CharacterID::larsa)
		charData[10] = charData[13];

	if (gids[1] != CharacterID::vossler1)
		charData[12] = charData[11];

	charData[6].gambits = 0x00;

	names[6] = gids[0];

	if (gids[1] != CharacterID::larsa)
		names[7] = gids[2];
	else
		names[7] = CharacterID::lamont;

	names[8] = gids[1];
	names[9] = gids[2];
	names[10] = gids[3];
}

void CharRand::fixLicenses(int charIds[6])
{
	for (int i = 0; i < 361; i++)
	{
		if (i >= 32 && i <= 218 || i >= 276 && i <= 299 || i >= 329 && i <= 359)
		{
			int charas = LicenseRand::licenseData[i].startingCharacters;
			bool hasLicenses[] = { (charas & 0x01) == 0x01, (charas & 0x02) == 0x02, (charas & 0x04) == 0x04,
				(charas & 0x08) == 0x08, (charas & 0x10) == 0x10, (charas & 0x20) == 0x20 };

			bool newLicenses[] = { hasLicenses[charIds[0]], hasLicenses[charIds[1]] , hasLicenses[charIds[2]] ,
				hasLicenses[charIds[3]] , hasLicenses[charIds[4]] ,hasLicenses[charIds[5]] };
			charas = 0;
			for (int i = 0; i < 6; i++)
				if (newLicenses[i])
					charas += pow(2, i);
			charas += 64;
			LicenseRand::licenseData[i].startingCharacters = charas;
		}
	}
}

void CharRand::fixGambits(int charIds[6])
{
	StartGambitData start = gambitData[0];
	StartGambitData other = gambitData[2];

	gambitData[charIds[0]] = start;
	gambitData[charIds[5]] = start;
	gambitData[charIds[1]] = other;
	gambitData[charIds[2]] = other;
	gambitData[charIds[3]] = other;
	gambitData[charIds[4]] = other;
	gambitData[6] = other;
}

void CharRand::increaseStat(unsigned char & num, int &statPointsLeft)
{
	if (statPointsLeft <= 0)
		return;
	if (Helpers::randInt(0, 99) < 40)
	{
		num++;
		statPointsLeft--;
	}
}

void CharRand::increaseStat(unsigned short & num, int &statPointsLeft)
{
	if (statPointsLeft <= 0)
		return;
	if (Helpers::randInt(0, 99) < 40)
	{
		num++;
		statPointsLeft--;
	}
}
