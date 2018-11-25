#include "stdafx.h"
#include "Helpers.h"
#include <Windows.h>

string Helpers::language = "us";
string Helpers::mainPS2DataFolder = "";

default_random_engine Helpers::rng = default_random_engine();

Helpers::Helpers()
{
}


Helpers::~Helpers()
{
}

bool Helpers::fileExists(std::string fileName)
{
	DWORD ftyp = GetFileAttributesA(fileName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return true;    // this is not a directory!
}

int Helpers::randInt(int low, int high)
{
	uniform_int_distribution<mt19937::result_type> dist(low, high);
	return dist(rng);
}

int Helpers::randIntNorm(int low, int high, int center, int std)
{
	normal_distribution<double> dist(center, std);
	int num = dist(rng);
	return max(low, min(high, num));
}
