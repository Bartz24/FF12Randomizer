#pragma once
#include <string>
#include <vector>
#include "Helpers.h"

using namespace std;

class MusicData
{
public:
	string path;
	vector<string> types;
	MusicData();
	MusicData(string p);
	~MusicData();
	void setTypes(string typesString);
};

