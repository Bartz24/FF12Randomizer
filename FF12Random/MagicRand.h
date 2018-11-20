#pragma once
#include "MagicData.h"
#include "ActionData.h"
#include "StatusValue.h"
#include "RandSpellData.h"
#include "TrapData.h"
#include <vector>
#include <sstream>
#include <algorithm>

class MagicRand
{
private:
	string fileName;
	vector<RandSpellData> spells = vector<RandSpellData>();
	vector<TrapData> traps = vector<TrapData>();

public:
	static ActionData actionData[497];
	static MagicData magicData[105];
	static string spellNames[81];
	static string spellDescs[81];
	static string trapNames[16];
	static bool didRandSpells;
	MagicRand();
	~MagicRand();
	void load();
	void save();
	string process(string preset);
	void randCost();
	void randCostSmart();
	void randMPCost();
	void randCT();
	void randAoE();
	void randStatus();
	void setStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4, int chance);
	void addStatus(unsigned char &num1, unsigned char &num2, unsigned char &num3, unsigned char &num4);
	void randSpells();
	vector<string> split(const std::string &s, char delim);
	void addRangeToVector(vector<int>& data, int low, int high);
	vector<RandSpellData> getSpellsOfType(int type);
	void randSpellsOfType(vector<int> idsReplace, int type);
	void randTraps();
};

