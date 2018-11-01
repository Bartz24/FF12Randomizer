#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "LicenseRand.h"
#include "LicenseBoardRand.h"

using namespace std;

class LicenseRename
{
private:
	map<string, int> nameCount;
	string data[362] = {};
	string suffix[362] = {};
	string augmentNames[129] = {};
	string bpFileName;
public:
	LicenseRename();
	~LicenseRename();
	void load();
	void save();
	string getNameFromID(int id);
	string getSameGroup(vector<int> nums);
	bool allMeetCondition(vector<int> nums, int type, int cond);
	string getGroup(int a);
	void process();
};

