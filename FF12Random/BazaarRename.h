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
#include "ShopRand.h"

using namespace std;

class BazaarRename
{
private:
	string bpFileName;
public:
	string data[128] = {};
	BazaarRename();
	~BazaarRename();
	string getNameFromID(int id);
	void load();
	void save();
	void process();
};

