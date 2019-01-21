#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <experimental/filesystem>

using namespace std;

class Helpers
{
	/*
	ITEM, 0
	EQUIP, 1
	ABILITY, 2
	AUGMENT, 3
	CHARACTER, 4
	ENEMY, 5
	SHOP, 6
	TREASURE, 7
	REWARD, 8
	LICENSE, 9
	LICENSEBOARD 10
	*/

public:
	static string version;
	static default_random_engine rng;
	static string language;
	static string mainPS2DataFolder;
	Helpers();
	~Helpers();
	static bool fileExists(std::string fileName);
	static int randInt(int low, int high);
	static int randInt(int low, int high, int minN, int maxN);
	static int randIntNorm(int low, int high, int center, int std);
	static int randIntControl(int low, int high, int norm, int ratio);
	static int randNormControl(int low, int high, int center, int std, int ratio);
	static unsigned int readInt(char bytes[], int index);
	static unsigned short readShort(char bytes[], int index);
	static void setInt(char *bytes, int index, unsigned int value);
	static void setShort(char *bytes, int index, unsigned short value);
	static int clamp(int value, int minN, int maxN);
	static vector<string> get_directories(const string& s);
};

