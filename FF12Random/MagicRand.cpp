#include "stdafx.h"
#include "MagicRand.h"

MagicData MagicRand::magicData[105] = {};
ActionData MagicRand::actionData[497] = {};
string MagicRand::spellNames[81] = {};
string MagicRand::trapNames[16] = {};
string MagicRand::spellDescs[81] = {};
bool MagicRand::didRandSpells = false;

MagicRand::MagicRand()
{
}


MagicRand::~MagicRand()
{
}

void MagicRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = 81 * 8; //Num magic * data size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(MagicData::getMagDataIndex()));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 81; i++)
		{
			magicData[i] = MagicData{ buffer[i * 8], buffer[i * 8 + 1], buffer[i * 8 + 2], buffer[i * 8 + 3],
				buffer[i * 8 + 4], buffer[i * 8 + 5], buffer[i * 8 + 6],	buffer[i * 8 + 7]};
		}

		delete[] buffer;

		char * buffer2;
		size = 24 * 8; //Num tech * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(MagicData::getTechDataIndex()));
		buffer2 = new char[size];
		file.read(buffer2, size);
		file.close();

		for (int i = 0; i < 24; i++)
		{
			magicData[i + 81] = MagicData{ buffer2[i * 8], buffer2[i * 8 + 1], buffer2[i * 8 + 2], buffer2[i * 8 + 3],
				buffer2[i * 8 + 4], buffer2[i * 8 + 5], buffer2[i * 8 + 6],	buffer2[i * 8 + 7] };
		}

		delete[] buffer2;

		char * buffer3;
		size = 497 * 60; //Num action * data size
		file = ifstream(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(int(ActionData::getDataIndex()));
		buffer3 = new char[size];
		file.read(buffer3, size);
		file.close();

		for (int i = 0; i < 497; i++)
		{
			char data[60];
			for (int i2 = 0; i2 < 60; i2++)
			{
				data[i2] = buffer3[i * 60 + i2];
			}
			actionData[i] = ActionData{ data };
		}

		delete[] buffer3;
	}

	string line;
	ifstream myfile("data\\abilities.csv");
	if (myfile.is_open())
	{
		bool first = true;
		while (getline(myfile, line))
		{
			if (first)
			{
				first = false;
				continue;
			}

			vector<string> data = split(line, ',');
			RandSpellData rData = RandSpellData();
			rData.name = data[0];
			rData.description = data[1];
			rData.weight = stoi(data[2]);
			rData.magicType = stoi(data[3]);
			rData.power = stoi(data[4]);
			rData.ct = stoi(data[5]);
			rData.mp = stoi(data[6]);
			rData.accuracy = stoi(data[7]);
			rData.aoe = stoi(data[8]);
			rData.onHit = stoi(data[9]);
			rData.target = stoi(data[10]);
			rData.effect = stoi(data[11]);
			char stat[] = { stoi(data[12]), stoi(data[13]), stoi(data[14]), stoi(data[15]) };
			rData.status = *reinterpret_cast<unsigned int*>(stat);
			rData.element = stoi(data[16]);
			rData.mType2 = stoi(data[17]);
			rData.animation = stoi(data[18]);
			rData.specialType = stoi(data[19]);
			rData.icon = stoi(data[20]);
			rData.castAnimation = stoi(data[21]);
			spells.push_back(rData);
		}
		myfile.close();
	}

	myfile = ifstream("data\\traps.csv");
	if (myfile.is_open())
	{
		bool first = true;
		while (getline(myfile, line))
		{
			if (first)
			{
				first = false;
				continue;
			}

			vector<string> data = split(line, ',');
			TrapData tData = TrapData();
			tData.name = data[0];
			tData.description = data[1];
			tData.power = stoi(data[2]);
			tData.aoe = stoi(data[3]);
			tData.effect = stoi(data[4]);
			char stat[] = { stoi(data[5]), stoi(data[6]), stoi(data[7]), stoi(data[8]) };
			tData.status = *reinterpret_cast<unsigned int*>(stat);
			traps.push_back(tData);
		}
		myfile.close();
	}
}


void MagicRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	union U2 {
		unsigned int s;
		unsigned char c[4];
	}byte2;

	char * buffer;
	long size = 81 * 8; //Num magic * data size
	fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(MagicData::getMagDataIndex()));
	buffer = new char[size];

	for (int i = 0; i < 81; i++)
	{
		MagicData d = magicData[i];
		buffer[i * 8] = U{ d.cost }.c[0];
		buffer[i * 8 + 1] = U{ d.cost }.c[1];
		buffer[i * 8 + 2] = d.id1;
		buffer[i * 8 + 3] = d.icon;
		buffer[i * 8 + 4] = d.id2;
		buffer[i * 8 + 5] = d.unknown1;
		buffer[i * 8 + 6] = d.order;
		buffer[i * 8 + 7] = d.unknown2;
	}

	file.write(buffer, size);
	file.close();


	delete[] buffer;

	char * buffer2;
	size = 24 * 8; //Num tech * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(MagicData::getTechDataIndex()));
	buffer2 = new char[size];

	for (int i = 0; i < 24; i++)
	{
		MagicData d = magicData[i + 81];
		buffer2[i * 8] = U{ d.cost }.c[0];
		buffer2[i * 8 + 1] = U{ d.cost }.c[1];
		buffer2[i * 8 + 2] = d.id1;
		buffer2[i * 8 + 3] = d.icon;
		buffer2[i * 8 + 4] = d.id2;
		buffer2[i * 8 + 5] = d.unknown1;
		buffer2[i * 8 + 6] = d.order;
		buffer2[i * 8 + 7] = d.unknown2;
	}

	file.write(buffer2, size);
	file.close();


	delete[] buffer2;

	char * buffer3;
	size = 497 * 60; //Num actions * data size
	file = fstream(fileName, ios::out | ios::in | ios::binary | ios::ate);
	file.seekp(int(ActionData::getDataIndex()));
	buffer3 = new char[size];

	for (int i = 0; i < 497; i++)
	{
		ActionData d = actionData[i];
		for (int i2 = 0; i2 < 60; i2++)
		{
			buffer3[i * 60 + i2] = d.unknown[i2];
		}
		buffer3[i * 60 + 0x00] = U{ d.description }.c[0];
		buffer3[i * 60 + 0x01] = U{ d.description }.c[1];
		buffer3[i * 60 + 0x06] = d.aoeRange;
		buffer3[i * 60 + 0x08] = d.type;
		buffer3[i * 60 + 0x09] = d.ct;
		buffer3[i * 60 + 0x0A] = d.cost;
		buffer3[i * 60 + 0x0C] = d.target;
		buffer3[i * 60 + 0x10] = d.power;
		buffer3[i * 60 + 0x11] = d.powerMult;
		buffer3[i * 60 + 0x12] = d.accuracy;
		buffer3[i * 60 + 0x13] = d.element;
		buffer3[i * 60 + 0x14] = d.hitChance;
		buffer3[i * 60 + 0x18] = U2{ d.status }.c[0];
		buffer3[i * 60 + 0x19] = U2{ d.status }.c[1];
		buffer3[i * 60 + 0x1A] = U2{ d.status }.c[2];
		buffer3[i * 60 + 0x1B] = U2{ d.status }.c[3];
		buffer3[i * 60 + 0x21] = d.castAnimation;
		buffer3[i * 60 + 0x24] = U{ d.animation }.c[0];
		buffer3[i * 60 + 0x25] = U{ d.animation }.c[1];
		buffer3[i * 60 + 0x2C] = U{ d.mType }.c[0];
		buffer3[i * 60 + 0x2D] = U{ d.mType }.c[1];
		buffer3[i * 60 + 0x36] = d.specialType;
		buffer3[i * 60 + 0x38] = d.gambitPage;
		buffer3[i * 60 + 0x39] = d.gambitPageOrder;
	}

	file.write(buffer3, size);
	file.close();


	delete[] buffer3;
}

void MagicRand::process(FlagGroup flags)
{
	if (flags.hasFlag("u"))
	{
		if (flags.getFlag("u").isSmart())
			randSpells();
		else
			randSpellsFull();
	}
	if (flags.hasFlag("a"))
	{
		randAoE(flags.getFlag("a").getValue());
	}
	if (flags.hasFlag("s"))
	{
		randStatus(flags.getFlag("s").getValue());
	}
	if (flags.hasFlag("e"))
	{
		randElements(flags.getFlag("e").getValue());
	}
	if (flags.hasFlag("c"))
	{
		if (flags.getFlag("c").isSmart())
			randCostSmart(flags.getFlag("c").getValue());
		else
			randCost(flags.getFlag("c").getValue());
	}
	if (flags.hasFlag("m"))
	{
		if (flags.getFlag("m").isSmart())
			randMPCostSmart(flags.getFlag("m").getValue());
		else
			randMPCost(flags.getFlag("m").getValue());
	}
	if (flags.hasFlag("t"))
	{
		if (flags.getFlag("t").isSmart())
			randCTSmart(flags.getFlag("t").getValue());
		else
			randCT(flags.getFlag("t").getValue());
	}
	if (flags.hasFlag("r"))
	{
		randTraps();
	}
}

void MagicRand::randCost(int value)
{
	for (int i = 0; i < 105; i++)
	{
		magicData[i].cost = unsigned short(Helpers::randNormControl(2, 65535, 9000, 4000, value));
	}
}


void MagicRand::randCostSmart(int value)
{
	for (int i = 0; i < 81; i++)
	{
		float baseCost = pow(float(actionData[i].cost), 1.6f) + 80.f;
		if (actionData[i].power > 0)
			baseCost *= pow(actionData[i].power / 13.f, 1.94f);
		if (actionData[i].powerMult > 0)
			baseCost *= actionData[i].powerMult;
		if (actionData[i].aoeRange > 0)
			baseCost *= pow(1.25f, actionData[i].aoeRange + 1);
		if (actionData[i].accuracy > 0)
			baseCost *= float(actionData[i].accuracy) / 20.f;
		StatusValue status = StatusValue{ actionData[i].status };
		if (status.statuses.size() > 0)
			baseCost *= pow(1.55f, status.statuses.size() + 3);

		baseCost = max(100.f, min(baseCost, 65535.f));
		magicData[i].cost = unsigned short(Helpers::randIntControl(2, 65535, baseCost, value));
	}
	for (int i = 81; i < 105; i++)
	{
		magicData[i].cost = unsigned short(Helpers::randNormControl(2, 65535, 14000, 6000, value));
	}
}

void MagicRand::randMPCostSmart(int value)
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].cost > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].cost = Helpers::randInt(actionData[i].cost - value, actionData[i].cost + value, 1, 99);
	}
}

void MagicRand::randMPCost(int value)
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].cost > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].cost = Helpers::randNormControl(1, 99, 30, 10, value);
	}
}

void MagicRand::randCT(int value)
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].ct > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].ct = unsigned char(Helpers::randInt(20 - value, 20 + value, 1, 255));
	}
}

void MagicRand::randCTSmart(int value)
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].ct > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].ct = unsigned char(Helpers::randInt(actionData[i].ct - value, actionData[i].ct + value, 1, 255));
	}
}

void MagicRand::randAoE(int value)
{
	for (int i = 0; i < 497; i++)
	{
		if (i >= 82 && i < 145 || i >= 262 && i <= 274 || i >= 208 && i <= 225)
			continue;
		if(actionData[i].aoeRange > 0 || Helpers::randInt(0, 99) < value && actionData[i].aoeRange == 0)
		actionData[i].aoeRange = Helpers::randInt(1, 20);
	}
}

void MagicRand::randElements(int value)
{
	for (int i = 278; i < 497; i++)
	{
		ElementalValue orig{ actionData[i].element };
		actionData[i].element = 0;
		ElementalValue newElem{ actionData[i].element };
		while (newElem.elements.size() < orig.elements.size())
			newElem.addRandomElement();
		while (Helpers::randInt(0, 99) < value)
			newElem.addRandomElement();
		actionData[i].element = newElem.getNumValue();
	}
}

void MagicRand::randStatus(int value)
{
	for (int i = 278; i < 497; i++)
	{
		StatusValue orig{ actionData[i].status };
		actionData[i].status = 0;
		while (StatusValue{ actionData[i].status }.statuses.size() < orig.statuses.size())
			addStatus(actionData[i].status, { Status::Stone, Status::XZone });
		setStatus(actionData[i].status, value, { Status::Stone, Status::XZone });
		StatusValue status{ actionData[i].status };
		if (status.statuses.size() > 0 && actionData[i].hitChance < 100)
		{
			actionData[i].hitChance = Helpers::randInt(5, 50);
		}
		else
			actionData[i].hitChance = 0;
	}
}


void MagicRand::setStatus(unsigned int &num, int chance, initializer_list<Status> blacklist)
{
	StatusValue status = StatusValue(num);
	while (Helpers::randInt(0, 99) < chance)
	{
		status.addRandomStatus(blacklist);
	}
	num = status.getNumValue();
}

void MagicRand::addStatus(unsigned int & num, initializer_list<Status> blacklist)
{
	StatusValue status = StatusValue(num);
	status.addRandomStatus(blacklist);
	num = status.getNumValue();
}

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

void MagicRand::randSpells()
{
	{
		vector<int> whiteIDs;
		whiteIDs.push_back(0);
		whiteIDs.push_back(4);
		whiteIDs.push_back(6);
		whiteIDs.push_back(11);
		whiteIDs.push_back(14);
		whiteIDs.push_back(5);
		whiteIDs.push_back(15);
		whiteIDs.push_back(10);
		whiteIDs.push_back(16);
		whiteIDs.push_back(1);
		whiteIDs.push_back(2);
		whiteIDs.push_back(3);
		whiteIDs.push_back(7);
		whiteIDs.push_back(9);
		whiteIDs.push_back(12);
		whiteIDs.push_back(13);
		whiteIDs.push_back(51);
		whiteIDs.push_back(55);
		whiteIDs.push_back(52);
		whiteIDs.push_back(56);
		whiteIDs.push_back(53);
		whiteIDs.push_back(54);
		whiteIDs.push_back(8);
		whiteIDs.push_back(69);
		whiteIDs.push_back(17);

		randAllSpellsOfType(whiteIDs, 0);
	}
	{
		vector<int> blackIDs;
		blackIDs.push_back(18);
		blackIDs.push_back(23);
		blackIDs.push_back(28);
		blackIDs.push_back(19);
		blackIDs.push_back(24);
		blackIDs.push_back(29);
		blackIDs.push_back(20);
		blackIDs.push_back(25);
		blackIDs.push_back(30);
		blackIDs.push_back(22);
		blackIDs.push_back(27);
		blackIDs.push_back(21);
		blackIDs.push_back(26);
		blackIDs.push_back(31);
		blackIDs.push_back(32);
		blackIDs.push_back(33);
		blackIDs.push_back(35);
		blackIDs.push_back(57);
		blackIDs.push_back(62);
		blackIDs.push_back(60);
		blackIDs.push_back(64);
		blackIDs.push_back(61);
		blackIDs.push_back(65);
		blackIDs.push_back(59);
		blackIDs.push_back(63);

		randAllSpellsOfType(blackIDs, 1);
	}
	{
		vector<int> timeIDs;
		timeIDs.push_back(36);
		timeIDs.push_back(38);
		timeIDs.push_back(39);
		timeIDs.push_back(45);
		timeIDs.push_back(44);
		timeIDs.push_back(40);
		timeIDs.push_back(41);
		timeIDs.push_back(42);
		timeIDs.push_back(43);
		timeIDs.push_back(46);
		timeIDs.push_back(67);
		timeIDs.push_back(37);
		timeIDs.push_back(71);
		timeIDs.push_back(72);
		timeIDs.push_back(47);
		timeIDs.push_back(48);
		timeIDs.push_back(49);
		timeIDs.push_back(50);
		timeIDs.push_back(79);
		timeIDs.push_back(80);

		randAllSpellsOfType(timeIDs, 2);
	}
	{
		vector<int> greenIDs;
		greenIDs.push_back(58);
		greenIDs.push_back(66);
		greenIDs.push_back(70);
		greenIDs.push_back(73);
		greenIDs.push_back(75);
		greenIDs.push_back(74);

		randAllSpellsOfType(greenIDs, 3);
	}
	{
		vector<int> arcaneIDs;
		arcaneIDs.push_back(76);
		arcaneIDs.push_back(77);
		arcaneIDs.push_back(78);
		arcaneIDs.push_back(68);
		arcaneIDs.push_back(34);

		randAllSpellsOfType(arcaneIDs, 4);
	}
	didRandSpells = true;
	for (int i = 82; i < 146; i++)
	{
		actionData[i].description = 0x0FFE;
	}
}

void MagicRand::randSpellsFull()
{
	vector<int> ids;
	addRangeToVector(ids, 0, 80);
	randAllSpellsOfType(ids, -1, true);
	didRandSpells = true;
	for (int i = 82; i < 146; i++)
	{
		actionData[i].description = 0x0FFE;
	}
}

vector<string> MagicRand::split(const std::string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string str;
	while (getline(ss, str, delim)) {
		elems.push_back(str);
	}
	return elems;
}

void MagicRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}

vector<int> MagicRand::getSpellsOfType(int type, bool good)
{
	vector<int> tSpells;
	for (int i = 0; i < spells.size(); i++)
	{
		if ((type == -1 || spells[i].magicType == type) && (good ? spells[i].target <= 76 : spells[i].target > 76))
			tSpells.push_back(i);
	}
	return tSpells;
}

void MagicRand::randAllSpellsOfType(vector<int> idsReplace, int type, bool shuffle)
{
	vector<int> goodSpells = vector<int>();
	vector<int> badSpells = vector<int>();

	vector<int> orderIDs = vector<int>();
	if (shuffle)
		addRangeToVector(orderIDs, 0, idsReplace.size() - 1);

	for (int i = 0; i < idsReplace.size(); i++)
	{
		if (actionData[idsReplace[i]].target <= 76)
			goodSpells.push_back(idsReplace[i]);
		else
			badSpells.push_back(idsReplace[i]);
	}

	if (goodSpells.size() > 0)
		randSpellsOfType(goodSpells, type, true, shuffle, orderIDs);
	if (badSpells.size() > 0)
		randSpellsOfType(badSpells, type, false, shuffle, orderIDs);

	if (shuffle)
	{
		int order = 0;
		for (int i = 0; i < spells.size(); i++)
		{
			int index = find(orderIDs.begin(), orderIDs.end(), i)-orderIDs.begin();
			if (index + orderIDs.begin() != orderIDs.end())
			{
				magicData[index].order = order;
				actionData[index].gambitPage = order / 17 + 1;
				actionData[index].gambitPageOrder = order % 17;
				order++;
			}
		}
	}
}

void MagicRand::randSpellsOfType(vector<int> idsReplace, int type, bool good, bool shuffle, vector<int> &orderIDs)
{
	vector<int> newSpells = getSpellsOfType(type, good);
	vector<int> weights = vector<int>();
	for (int i = 0; i < newSpells.size(); i++)
	{
		if (i > 0)
			weights.push_back(weights[i - 1] + spells[newSpells[i]].weight);
		else
			weights.push_back(spells[newSpells[i]].weight);
	}
	
	vector<int> newIDs = vector<int>();
	for (int i = 0; i < idsReplace.size(); i++)
	{
		int index = 0;
		do
		{
			index = 0;
			int chance = Helpers::randInt(0, weights[weights.size() - 1]);
			for (; chance > weights[index]; index++) {}
		} while (find(newIDs.begin(), newIDs.end(), index) != newIDs.end());
		newIDs.push_back(index);
	}

	if (shuffle)
		random_shuffle(idsReplace.begin(), idsReplace.end());
	sort(newIDs.begin(), newIDs.end());

	for (int i = 0; i < idsReplace.size(); i++)
	{
		int rep = idsReplace[i];
		int newID = newIDs[i];
		RandSpellData spell = spells[newSpells[newID]];
		spellNames[rep] = spell.name;
		spellDescs[rep] = spell.description;
		actionData[rep].power = spell.power;
		actionData[rep].ct = spell.ct;
		actionData[rep].cost = spell.mp;
		actionData[rep].accuracy = spell.accuracy;
		actionData[rep].aoeRange = spell.aoe;
		if (actionData[rep].aoeRange == 255)
			actionData[rep].aoeRange = (Helpers::randInt(0, 99) < 80) ? 0 : 10;
		actionData[rep].hitChance = spell.onHit;
		actionData[rep].target = spell.target;
		actionData[rep].type = spell.effect;
		actionData[rep].status = spell.status;
		actionData[rep].element = spell.element;
		actionData[rep].mType = spell.mType2;
		actionData[rep].animation = spell.animation;
		actionData[rep].specialType = spell.specialType;
		magicData[rep].icon = spell.icon;
		actionData[rep].castAnimation = spell.castAnimation;

		if (shuffle)
		{
			orderIDs[rep] = newSpells[newIDs[i]];
		}
	}
}


void MagicRand::randTraps()
{
	for (int i = 246; i < 262; i++)
	{
		int index = Helpers::randInt(0, traps.size() - 1);
		trapNames[i - 246] = traps[index].name;
		actionData[i].power = traps[index].power;
		actionData[i].aoeRange = traps[index].aoe;
		actionData[i].type = traps[index].effect;
		actionData[i].status = traps[index].status;
	}
}
