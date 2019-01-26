#pragma once
#include "FlagGroup.h"
#include "MagicData.h"
#include "ActionData.h"
#include "StatusValue.h"
#include "ElementalValue.h"
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
	void process(FlagGroup flags);
	void randCost(int value);
	void randCostSmart(int value);
	void randMPCostSmart(int value);
	void randMPCost(int value);
	void randCT(int value);
	void randCTSmart(int value);
	void randAoE(int value);
	void randElements(int value);
	void randStatus(int value);
	void setStatus(unsigned int &num, int chance, initializer_list<Status> blacklist);
	void addStatus(unsigned int &num, initializer_list<Status> blacklist);
	void randSpells();
	void randSpellsFull();
	vector<string> split(const std::string &s, char delim);
	void addRangeToVector(vector<int>& data, int low, int high);
	vector<int> getSpellsOfType(int type, bool good);
	void randAllSpellsOfType(vector<int> idsReplace, int type, bool shuffle = false);
	void randSpellsOfType(vector<int> idsReplace, int type, bool good, bool shuffle, vector<int> &orderIDs);
	void randTraps();
};

