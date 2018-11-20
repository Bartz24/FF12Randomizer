#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Helpers
{
public:
	static string language;
	static string mainPS2DataFolder;
	Helpers();
	~Helpers();
	static bool fileExists(std::string fileName);
};

