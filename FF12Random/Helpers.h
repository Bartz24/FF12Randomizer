#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

class Helpers
{
public:
	static default_random_engine rng;
	static string language;
	static string mainPS2DataFolder;
	Helpers();
	~Helpers();
	static bool fileExists(std::string fileName);
	static int randInt(int low, int high);
	static int randIntNorm(int low, int high, int center, int std);
};

