#include "stdafx.h"
#include "BazaarRename.h"


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


BazaarRename::BazaarRename()
{
}


BazaarRename::~BazaarRename()
{
}

void BazaarRename::load()
{
	bpFileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";

	string line;
	ifstream myfile("data\\equipAbilityNames.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string id = line.substr(0, line.find(','));
			trim(id);
			int numID = stoi(id);
			string name = line.substr(line.find(',') + 1, line.length());
			name.erase(
				remove(name.begin(), name.end(), '\"'),
				name.end()
			);
			trim(name);
			names.insert(pair <int, string>(numID, name));
		}
		myfile.close();
	}
}

void BazaarRename::save()
{
	ofstream myfile;
	myfile.open("bazaarNames.txt");
	for (int i = 0; i < 128; i++)
	{
		myfile << data[i];
		if (i < 127)
			myfile << endl;
	}
	myfile.close();
}

void BazaarRename::process()
{
	for (int i = 0; i < 128; i++)
	{
		if (ShopRand::bazaarData[i].bazaarType != 0x02)
		{
			string name = getNameFromID(ShopRand::bazaarData[i].result1);
			if (ShopRand::bazaarData[i].result2Amt > 0)
				name += " & " + getNameFromID(ShopRand::bazaarData[i].result2);
			if (ShopRand::bazaarData[i].result3Amt > 0)
				name += " & " + getNameFromID(ShopRand::bazaarData[i].result3);
			data[i] = name;
		}
		else
			data[i] = ".IGNORE";
	}
}
