#include "stdafx.h"
#include "Helpers.h"
#include <Windows.h>

string Helpers::language = "us";
string Helpers::mainPS2DataFolder = "";
string Helpers::version = "1.5.0";

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
	int offset = 0;
	if (low < 0)
	{
		offset = -low;
		low = 0;
		high += offset;
	}
	uniform_int_distribution<mt19937::result_type> dist(low, high);
	return dist(rng) - offset;
}

int Helpers::randInt(int low, int high, int minN, int maxN)
{
	return randInt(max(low, minN), min(maxN, high));
}

int Helpers::randIntNorm(int low, int high, int center, int std)
{
	normal_distribution<double> dist(center, std);
	int num = dist(rng);
	return max(low, min(high, num));
}

int Helpers::randIntControl(int low, int high, int norm, int ratio)
{
	return float(ratio / 100.f) * Helpers::randInt(low, high) + float(1.f - (ratio / 100.f)) * norm;
}

int Helpers::randNormControl(int low, int high, int center, int std, int ratio)
{
	return randIntControl(low, high, Helpers::randIntNorm(low, high, center, std), ratio);
}

unsigned int Helpers::readInt(char bytes[], int index)
{
	char chars[] = { bytes[index] , bytes[index + 1], bytes[index + 2],bytes[index + 3] };
	return *reinterpret_cast<unsigned int*>(chars);
}

unsigned short Helpers::readShort(char bytes[], int index)
{
	char chars[] = { bytes[index] , bytes[index + 1] };
	return *reinterpret_cast<unsigned short*>(chars);
}

void Helpers::setInt(char *bytes, int index, unsigned int value)
{
	union U {
		unsigned int i;
		unsigned char c[4];
	}byte;
	bytes[index] = U{ value }.c[0];
	bytes[index + 1] = U{ value }.c[1];
	bytes[index + 2] = U{ value }.c[2];
	bytes[index + 3] = U{ value }.c[3];
}

void Helpers::setShort(char *bytes, int index, unsigned short value)
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	bytes[index] = U{ value }.c[0];
	bytes[index + 1] = U{ value }.c[1];
}

int Helpers::clamp(int value, int minN, int maxN)
{
	return max(minN, min(maxN, value));
}

vector<string> Helpers::get_directories(const string& s)
{
	vector<string> r;
	for (auto& p : std::experimental::filesystem::recursive_directory_iterator(s))
		if (p.status().type() == std::experimental::filesystem::file_type::directory)
			r.push_back(p.path().string());
	return r;
}
