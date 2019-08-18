#pragma once

#include <string>
#include <vector>
#include <experimental/filesystem>
#include "Helpers.h"
#include "MusicData.h"
#include "FlagGroup.h"

using namespace std;

class MusicRand
{
public:
	static vector<MusicData> data, newPaths;
	MusicRand();
	~MusicRand();
	void load(vector<string> musicFolders, FlagGroup flags);
	void process();
	void save(FlagGroup flags);
	string pickRandomThemeOfType(string type);
};

