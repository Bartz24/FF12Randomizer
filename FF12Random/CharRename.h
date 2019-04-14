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
#include "CharRand.h"

class CharRename
{
public:
	string data[253] = {};
	CharRename();
	~CharRename();
	void load();
	void save();
	void process(bool randEnemyNames);
	void fixGambitNames();
	void randomizeEnemyNames();
};

