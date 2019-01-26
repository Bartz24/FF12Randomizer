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

	myfile = ofstream();
	myfile.open("menu00.txt");
	for (int i = 0; i < 122; i++)
	{
		myfile << menu00[i];
		if (i < 121)
			myfile << endl;
	}
	myfile.close();
}

void BazaarRename::process()
{
	int curPackage = 1;
	for (int i = 0; i < 128; i++)
	{
		if (ShopRand::bazaarData[i].bazaarType != 0x02)
		{
			string name = to_string(int(ShopRand::bazaarData[i].result1Amt)) + "x " + getNameFromID(ShopRand::bazaarData[i].result1);
			if (ShopRand::bazaarData[i].result2Amt > 0)
				name += "{02}" + to_string(int(ShopRand::bazaarData[i].result2Amt)) + "x " + getNameFromID(ShopRand::bazaarData[i].result2);
			if (ShopRand::bazaarData[i].result3Amt > 0)
				name += "{02}" + to_string(int(ShopRand::bazaarData[i].result3Amt)) + "x " + getNameFromID(ShopRand::bazaarData[i].result3);
			menu00[curPackage >= 100 ? curPackage : (curPackage - 1)] = name;
			data[i] = "Bazaar Package " + to_string(curPackage);
			curPackage++;
		}
		else
		{
			data[i] = ".IGNORE";
		}
	}
	menu00[99] = ".IGNORE";
	menu00[121] = ".IGNORE";
}
