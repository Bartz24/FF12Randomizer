#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include "Helpers.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "MagicRand.h"

using namespace std;

class ActionRename
{
private:
	string bpFileName;
public:
	string data[545] = {};
	string desc[81] = {};
	ActionRename();
	~ActionRename();
	string getNameFromID(int id);
	void load();
	void save();
	void process();
};

