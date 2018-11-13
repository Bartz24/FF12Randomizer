// FF12Random.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <cstdio>
#include <sstream>
#include <experimental/filesystem>
#include "LicenseRand.h"
#include "LicenseBoardRand.h"
#include "MagicRand.h"
#include "ItemRand.h"
#include "EquipRand.h"
#include "ShopRand.h"
#include "CharRand.h"
#include "AugmentRand.h"
#include "RenameMain.h"
#include "FileSizeTableFix.h"
#include "TreasureRand.h"
#include "RewardRand.h"
#include "DocumentationGen.h"

using namespace std;

class Preset
{
public:
	string name, flags, description;
	Preset(string name, string flags, string description)
	{
		this->name = name;
		this->flags = flags;
		this->description = description;
	}
};

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

vector<string> split(const std::string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string str;
	while (getline(ss, str, delim)) {
		elems.push_back(str);
	}
	return elems;
}


int main(int argc, char* argv[])
{
	long seed = time(NULL);
	cout << "If you want to use a seed put that NUMBER here (Leave blank for random seed): ";
	std::string inputSeed;
	getline(std::cin, inputSeed);
	if (!inputSeed.empty())
		seed = stol(inputSeed);
	srand(seed);
	cout << "The seed being used is: " << seed << endl;

	vector<Preset> presets = vector<Preset>();

	cout << "Presets available listed below. You can use a custom preset that starts with $ too." << endl;

	string line;
	ifstream myfile("data\\presets.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> data = split(line, ',');
			string name = data[0], flags = data[1], desc = data[2];
			trim(name);
			trim(flags);
			trim(desc);
			presets.push_back(Preset{ name, flags, desc });
			cout << "\t" << name << ": " << desc << endl;
		}
		myfile.close();
	}


	cout << "If you want to use a flag preset put that here (Leave blank for new custom settings): ";
	std::string input;
	getline(std::cin, input);
	if (input.empty())
		input = "$!$!$!$!$!$!$!$!$!$!";
	else
	{
		if (input.substr(0, 1) != "$")
		{
			bool found = false;
			for (int i = 0; i < presets.size(); i++)
			{
				if (input == presets[i].name)
				{
					found = true;
					input = presets[i].flags;
				}
			}
			if (!found)
			{
				cout << "Invalid preset. The program will not use a preset now." << endl;
				input = "$!$!$!$!$!$!$!$!$!$!";
			}
		}
	}

	vector<string> inputFlags = split(input, '$');
	inputFlags.erase(inputFlags.begin());
	vector<string> outputFlags = vector<string>();
	for (int i = 0; i < inputFlags.size(); i++)
		outputFlags.push_back(".");

	string newFolder = "FF12Randomized" + to_string(seed);
	if (Helpers::fileExists(newFolder))
	{
		int num = 0;
		do
		{
			num++;
			newFolder = "FF12Randomized" + to_string(seed) + " (" + to_string(num) + ")";
		} while (Helpers::fileExists(newFolder));
	}
	if (Helpers::getYesNo("Use default mod template (Choose n for your own)? (y/n) "))
	{
		std::experimental::filesystem::copy("data\\FF12RandomizedBase", newFolder, std::experimental::filesystem::copy_options::recursive);
	}
	else
	{
		cout << "Select the folder that contains the ps2data folder (this folder will be copied to a new folder)" << endl;
		string folder = Helpers::loadFile();
		std::experimental::filesystem::copy(folder, newFolder, std::experimental::filesystem::copy_options::recursive);
	}
	Helpers::mainPS2DataFolder = newFolder + "\\ps2data\"";
	if (Helpers::mainPS2DataFolder.substr(0, 1) == "\"")
		Helpers::mainPS2DataFolder.replace(0, 1, "");
	if (Helpers::mainPS2DataFolder.substr(Helpers::mainPS2DataFolder.length() - 1, 1) == "\"")
		Helpers::mainPS2DataFolder.replace(Helpers::mainPS2DataFolder.length() - 1, 1, "");
	string bpFileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(bpFileName))
	{
		srand(seed);
		MagicRand mRand{};
		mRand.load();
		if (inputFlags[0] != "." && (inputFlags[0] != "!" || Helpers::getYesNo("Would you like to randomize the magic/technick/enemy ability data? (y/n) ")))
		{
			outputFlags[0] = mRand.process(inputFlags[0]);
			mRand.save();
		}

		srand(seed + 20);
		ItemRand iRand{};
		iRand.load();
		if (inputFlags[1] != "." && (inputFlags[1] != "!" || Helpers::getYesNo("Would you like to randomize the item, loot, or gambit gil values? (y/n) ")))
		{
			outputFlags[1] = iRand.process(inputFlags[1]);
			iRand.save();
		}

		srand(seed + 40);
		EquipRand eRand{};
		eRand.load();
		if (inputFlags[2] != "." && (inputFlags[2] != "!" || Helpers::getYesNo("Would you like to randomize the equipment data? (y/n) ")))
		{
			outputFlags[2] = eRand.process(inputFlags[2]);
			eRand.save();
		}

		srand(seed + 80);
		AugmentRand aRand{};
		aRand.load();
		if (inputFlags[3] != "." && (inputFlags[3] != "!" || Helpers::getYesNo("Would you like to randomize the augments? (y/n) ")))
		{
			outputFlags[3] = aRand.process(inputFlags[3]);
			aRand.save();
		}

		srand(seed + 160);
		LicenseRand lRand{};
		lRand.load();
		if (inputFlags[4] != "." && (inputFlags[4] != "!" || Helpers::getYesNo("Would you like to randomize the licenses (not the board layouts, that's later)? (y/n) ")))
		{
			outputFlags[4] = lRand.process(inputFlags[4]);
			lRand.save();
		}

		srand(seed + 320);
		ShopRand sRand{};
		sRand.load();
		if (inputFlags[5] != "." && (inputFlags[5] != "!" || Helpers::getYesNo("Would you like to randomize the shops and bazaars? (y/n) ")))
		{
			outputFlags[5] = sRand.process(inputFlags[5]);
			sRand.save();
		}

		srand(seed + 640);
		CharRand cRand{};
		cRand.load();
		if (inputFlags[6] != "." && (inputFlags[6] != "!" || Helpers::getYesNo("Would you like to randomize and update character data? (y/n) ")))
		{
			outputFlags[6] = cRand.process(inputFlags[6]);
			cRand.save();
		}

		srand(seed + 1280);
		RewardRand rRand{};
		rRand.load();
		if (inputFlags[7] != "." && (inputFlags[7] != "!" || Helpers::getYesNo("Would you like to randomize rewards for hunts and other events? (y/n) ")))
		{
			outputFlags[7] = rRand.process(inputFlags[7]);
			rRand.save();
		}
	}
	else
		cout << "Battle_pack.bin not found for the " + Helpers::language + " language!" << endl;
	srand(seed - 10);
	LicenseBoardRand bRand{};
	bool hasBoardData = true;
	for (int i = 1; i <= 12; i++)
	{
		if (!Helpers::fileExists(Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\in\\binaryfile\\board_" + to_string(i) + ".bin"))
		{
			hasBoardData = false;
			break;
		}
	}
	if (hasBoardData)
	{
		if (inputFlags[8] != "!" || Helpers::getYesNo("Would you like to randomize the license board layouts? (y/n) "))
		{
			bRand.load();
			outputFlags[8] = bRand.process(inputFlags[8]);
			bRand.save();
		}
	}
	else
		cout << "Board_X.bin files not found!" << endl;
	RenameMain rename = RenameMain();
	if (Helpers::fileExists(bpFileName))
	{
		srand(seed - 20);
		rename.load();
		rename.process();
		rename.save();
	}

	srand(seed - 40);
	TreasureRand tRand{};
	tRand.load();
	if (inputFlags[9] != "." && (inputFlags[9] != "!" || Helpers::getYesNo("Would you like to randomize the treasures? (y/n) ")))
	{
		outputFlags[9] = tRand.process(inputFlags[9]);
		tRand.save();
	}
	FileSizeTableFix fFix = FileSizeTableFix();
	fFix.load();
	fFix.process();
	fFix.save();


	if (Helpers::fileExists(bpFileName))
	{
		DocumentationGen dGen = DocumentationGen(rename);
		dGen.process();
		dGen.save(newFolder, seed);
	}

	string outputFlagStr = "";
	for (int i = 0; i < outputFlags.size(); i++)
		outputFlagStr += "$" + outputFlags[i];


	ofstream oFile;
	oFile.open(newFolder + "\\readme.txt");
	oFile << "The seed is: " + to_string(seed) << endl;
	oFile << "The flags used are: " + outputFlagStr << endl;
	oFile << "For info on the bazaars and treasures, check the documentation.html file!" << endl;
	oFile.close();

	cout << "Randomization Complete! The version of this randomizer is 1.3.3." << endl;
	cout << "The folder is called " + newFolder + " and can be found in the same folder as this program!" << endl;
	cout << "The flag string used for this is: " + outputFlagStr << endl;
	cout << "Remember to load the mod using DrakLab!" << endl;

	system("pause");

	return 0;
}

