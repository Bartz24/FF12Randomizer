#include "stdafx.h"
#include "MagicRand.h"

MagicData MagicRand::magicData[105] = {};
ActionData MagicRand::actionData[497] = {};
string MagicRand::spellNames[81] = {};
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
			rData.status1 = stoi(data[12]);
			rData.status2 = stoi(data[13]);
			rData.status3 = stoi(data[14]);
			rData.status4 = stoi(data[15]);
			rData.element = stoi(data[16]);
			rData.mType2 = stoi(data[17]);
			rData.animation = stoi(data[18]);
			spells.push_back(rData);
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
		int index = 0;
		for (int i2 = 0; i2 < 60; i2++)
		{
			if (i2 == 0x06 || i2 == 0x08 || i2 == 0x09 || i2 == 0x0A || i2 == 0x0C || i2 >= 0x10 && i2 <= 0x14 || i2 >= 0x18 && i2 <= 0x1B || i2 == 0x24 || i2 == 0x25 || i2 == 0x2C || i2 == 0x2D)
				continue;
			buffer3[i * 60 + i2] = d.unknown[index];
			index++;
		}
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
		buffer3[i * 60 + 0x18] = d.status1;
		buffer3[i * 60 + 0x19] = d.status2;
		buffer3[i * 60 + 0x1A] = d.status3;
		buffer3[i * 60 + 0x1B] = d.status4;
		buffer3[i * 60 + 0x24] = U{ d.animation }.c[0];
		buffer3[i * 60 + 0x25] = U{ d.animation }.c[1];
		buffer3[i * 60 + 0x2C] = U{ d.mType }.c[0];
		buffer3[i * 60 + 0x2D] = U{ d.mType }.c[1];
	}

	file.write(buffer3, size);
	file.close();


	delete[] buffer3;
}

string MagicRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Magic Data Randomization Options:" << endl;
		cout << "\t a: Randomize AoE range (80%-no range, 20% 2-20, where 10 is normal for AoE abilities)" << endl;
		cout << "\t c: Randomize gil cost (20-62000, more common around 9000 G)" << endl;
		cout << "\t e: Randomize status effects on enemy attacks" << endl;
		cout << "\t m: Randomize MP cost (1-99, only affects abilites that had a MP cost)" << endl;
		cout << "\t s: Randomize gil costs in a smart way. Costs are based on how powerful they are. (Applies to c flag)" << endl;
		cout << "\t t: Randomize charge time (only affects abilities that had a charge time)" << endl;
		cout << "\t u: Randomize usable magick (Changes what spells are in the game by randomizing with new spells)" << endl;
		flags = Helpers::readFlags("acemstu");
	}
	if (flags.find('u') != string::npos)
	{
		randSpells();
	}
	if (flags.find('a') != string::npos)
	{
		randAoE();
	}
	if (flags.find('e') != string::npos)
	{
		randStatus();
	}
	if (flags.find('c') != string::npos)
	{
		if (flags.find('s') != string::npos)
		{
			randCostSmart();
		}
		else
			randCost();
	}
	if (flags.find('m') != string::npos)
	{
		randMPCost();
	}
	if (flags.find('t') != string::npos)
	{
		randCT();
	}
	return flags;
}

void MagicRand::randCost()
{
	for (int i = 0; i < 105; i++)
	{
		magicData[i].cost = unsigned short(350000.f / (1.f + exp(0.04f*float(rand() % 10000) / 100.f + 1.5f)) - 1400.f);
	}
}


void MagicRand::randCostSmart()
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
		StatusValue status = StatusValue{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 };
		if (status.getNumStatuses() > 0)
			baseCost *= pow(1.55f, status.getNumStatuses() + 3);

		float ran = float(rand() % 24000) / 24000.f + .60f;
		baseCost *= ran;
		baseCost = max(100.f, min(baseCost, 65535.f));
		magicData[i].cost = unsigned short(baseCost);
	}
	for (int i = 81; i < 105; i++)
	{
		magicData[i].cost = unsigned short(rand() % 19000 + 200);
	}
}

void MagicRand::randMPCost()
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].cost > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].cost = rand() % 99 + 1;
	}
}

void MagicRand::randCT()
{
	for (int i = 0; i < 497; i++)
	{
		if (actionData[i].ct > 0 && !(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].ct = unsigned char(45.f / (1.f + exp(0.02f*float(rand() % 10000) / 100.f - 0.5f)));
	}
}

void MagicRand::randAoE()
{
	for (int i = 0; i < 497; i++)
	{
		if (i >= 82 && i < 145)
			continue;
		if (didRandSpells && i < 81)
		{
			if (actionData[i].aoeRange == 255)
				actionData[i].aoeRange = rand() % 100 < 80 ? 0 : (rand() % 19 + 2);
		}
		else if (!(i >= 262 && i <= 274 || i >= 208 && i <= 225))
			actionData[i].aoeRange = rand() % 100 < 80 ? 0 : (rand() % 19 + 2);
	}
}

void MagicRand::randStatus()
{
	for (int i = 278; i < 497; i++)
	{
		StatusValue orig{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 };
		actionData[i].status1 = actionData[i].status2 = actionData[i].status3 = actionData[i].status4 = 0;
		while (StatusValue{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 }.getNumStatuses() < orig.getNumStatuses())
			addStatus(actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4);
		setStatus(actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4, 15);
		StatusValue status{ actionData[i].status1, actionData[i].status2, actionData[i].status3, actionData[i].status4 };
		if (status.getNumStatuses() > 0)
		{
			actionData[i].hitChance = rand() % 96 + 5;
			if (status.hasStatus(int(Status1::Death), 1))
				actionData[i].hitChance = (actionData[i].hitChance / 10) + 1;
		}
		else
			actionData[i].hitChance = 0;
	}
}


void MagicRand::setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance)
{
	StatusValue status = StatusValue(num1, num2, num3, num4);
	while (rand() % 100 < chance)
	{
		status.addRandomStatus();
	}
	num1 = status.getNumValue(1);
	num2 = status.getNumValue(2);
	num3 = status.getNumValue(3);
	num4 = status.getNumValue(4);
}

void MagicRand::addStatus(unsigned char & num1, unsigned char & num2, unsigned char & num3, unsigned char & num4)
{
	StatusValue status = StatusValue(num1, num2, num3, num4);
	status.addRandomStatus();
	num1 = status.getNumValue(1);
	num2 = status.getNumValue(2);
	num3 = status.getNumValue(3);
	num4 = status.getNumValue(4);
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

		randSpellsOfType(whiteIDs, 0);
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

		randSpellsOfType(blackIDs, 1);
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

		randSpellsOfType(timeIDs, 2);
	}
	{
		vector<int> greenIDs;
		greenIDs.push_back(58);
		greenIDs.push_back(66);
		greenIDs.push_back(70);
		greenIDs.push_back(73);
		greenIDs.push_back(75);
		greenIDs.push_back(74);

		randSpellsOfType(greenIDs, 3);
	}
	{
		vector<int> arcaneIDs;
		arcaneIDs.push_back(76);
		arcaneIDs.push_back(77);
		arcaneIDs.push_back(78);
		arcaneIDs.push_back(68);
		arcaneIDs.push_back(34);

		randSpellsOfType(arcaneIDs, 4);
	}
	didRandSpells = true;
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

vector<RandSpellData> MagicRand::getSpellsOfType(int type)
{
	vector<RandSpellData> tSpells;
	for (int i = 0; i < spells.size(); i++)
	{
		if (spells[i].magicType == type)
			tSpells.push_back(spells[i]);
	}
	return tSpells;
}

void MagicRand::randSpellsOfType(vector<int> idsReplace, int type)
{
	vector<RandSpellData> newSpells = getSpellsOfType(type);
	vector<int> weights = vector<int>();
	for (int i = 0; i < newSpells.size(); i++)
	{
		if (i > 0)
			weights.push_back(weights[i - 1] + newSpells[i].weight);
		else
			weights.push_back(newSpells[i].weight);
	}
	
	vector<int> newIDs = vector<int>();
	for (int i = 0; i < idsReplace.size(); i++)
	{
		int index = 0;
		do
		{
			index = 0;
			int chance = rand() % (weights[weights.size() - 1]);
			for (; chance > weights[index]; index++) {}
		} while (find(newIDs.begin(), newIDs.end(), index) != newIDs.end());
		newIDs.push_back(index);
	}
	sort(newIDs.begin(), newIDs.end());

	for (int i = 0; i < idsReplace.size(); i++)
	{
		int rep = idsReplace[i];
		int newID = newIDs[i];
		spellNames[rep] = newSpells[newID].name;
		spellDescs[rep] = newSpells[newID].description;
		actionData[rep].power = newSpells[newID].power;
		actionData[rep].ct = newSpells[newID].ct;
		actionData[rep].cost = newSpells[newID].mp;
		actionData[rep].accuracy = newSpells[newID].accuracy;
		actionData[rep].aoeRange = newSpells[newID].aoe;
		if (actionData[rep].aoeRange == 255)
			actionData[rep].aoeRange = (rand() % 100 < 80) ? 0 : 10;
		actionData[rep].hitChance = newSpells[newID].onHit;
		actionData[rep].target = newSpells[newID].target;
		actionData[rep].type = newSpells[newID].effect;
		actionData[rep].status1 = newSpells[newID].status1;
		actionData[rep].status2 = newSpells[newID].status2;
		actionData[rep].status3 = newSpells[newID].status3;
		actionData[rep].status4 = newSpells[newID].status4;
		actionData[rep].element = newSpells[newID].element;
		actionData[rep].mType = newSpells[newID].mType2;
		if (newSpells[newID].animation != 255)
			actionData[rep].animation = newSpells[newID].animation;
		else
			actionData[rep].animation = 179;

	}
}
