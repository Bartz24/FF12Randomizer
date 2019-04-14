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
	string bpFileName;
public:
	string data[129] = {};
	AugmentRename();
	~AugmentRename();
	void load();
	void save();
	void process();
};

