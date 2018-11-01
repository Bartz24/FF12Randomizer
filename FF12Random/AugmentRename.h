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
#include "AugmentRand.h"

using namespace std;

class AugmentRename
{
private:
	string data[129] = {};
	string bpFileName;
public:
	AugmentRename();
	~AugmentRename();
	void load();
	void save();
	void process();
};

