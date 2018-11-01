#include "stdafx.h"
#include "AugmentRename.h"


// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
	trim(s);
	return s;
}


AugmentRename::AugmentRename()
{
}


AugmentRename::~AugmentRename()
{
}

void AugmentRename::load()
{
	bpFileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";

	string line;
	ifstream myfile("data\\augmentNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 129; i++)
		{
			getline(myfile, line);
			data[i] = line;
		}
		myfile.close();
	}
}

void AugmentRename::save()
{
	ofstream myfile;
	myfile.open("augmentNames.txt");
	for (int i = 0; i < 129; i++)
	{
		myfile << data[i];
		if (i < 128)
			myfile << endl;
	}
	myfile.close();
}

void AugmentRename::process()
{
	for (int i = 0; i < 129; i++)
	{
		if (data[i].find("%n") != string::npos)
		{
			data[i] = data[i].substr(0, data[i].find("%n")) + to_string(AugmentRand::augmentData[i].value) + data[i].substr(data[i].find("%n") + 2, data[i].size() - data[i].find("%n") + 2);
		}
	}
}
