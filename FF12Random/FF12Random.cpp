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

using namespace std;

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
	cout << "If you want to use a flag preset put that here (Leave blank for custom settings): ";
	std::string input;
	getline(std::cin, input);
	if (input.empty())
		input = "$!$!$!$!$!$!$!$!$!$!";

	vector<string> inputFlags = split(input, '$');
	inputFlags.erase(inputFlags.begin());
	vector<string> outputFlags = vector<string>();
	for (int i = 0; i < inputFlags.size(); i++)
		outputFlags.push_back(".");

	if (Helpers::getYesNo("Use default mod template (Choose n for your own)? (y/n) "))
	{
		std::experimental::filesystem::copy("data\\FF12RandomizedBase", "FF12Randomized" + to_string(seed), std::experimental::filesystem::copy_options::recursive);
		Helpers::mainPS2DataFolder = "\"FF12Randomized" + to_string(seed) + "\\ps2data\"";
		if (Helpers::mainPS2DataFolder.substr(0, 1) == "\"")
			Helpers::mainPS2DataFolder.replace(0, 1, "");
		if (Helpers::mainPS2DataFolder.substr(Helpers::mainPS2DataFolder.length() - 1, 1) == "\"")
			Helpers::mainPS2DataFolder.replace(Helpers::mainPS2DataFolder.length() - 1, 1, "");
	}
	else
	{
		cout << "Select the folder that contains the ps2data folder (this folder will be copied to a new folder)" << endl;
		string folder = Helpers::loadFile();
		std::experimental::filesystem::copy(folder, "FF12Randomized" + to_string(seed), std::experimental::filesystem::copy_options::recursive);
		Helpers::mainPS2DataFolder = "\"FF12Randomized" + to_string(seed) + "\\ps2data\"";
		if (Helpers::mainPS2DataFolder.substr(0, 1) == "\"")
			Helpers::mainPS2DataFolder.replace(0, 1, "");
		if (Helpers::mainPS2DataFolder.substr(Helpers::mainPS2DataFolder.length() - 1, 1) == "\"")
			Helpers::mainPS2DataFolder.replace(Helpers::mainPS2DataFolder.length() - 1, 1, "");
	}
	string bpFileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(bpFileName))
	{
		srand(seed);
		ItemRand iRand{};
		iRand.load();
		if (inputFlags[0] != "." && (inputFlags[0] != "!" || Helpers::getYesNo("Would you like to randomize the item, loot, or gambit gil values? (y/n) ")))
		{
			outputFlags[0] = iRand.process(inputFlags[0]);
			iRand.save();
		}

		srand(seed + 20);
		EquipRand eRand{};
		eRand.load();
		if (inputFlags[1] != "." && (inputFlags[1] != "!" || Helpers::getYesNo("Would you like to randomize the equipment data? (y/n) ")))
		{
			outputFlags[1] = eRand.process(inputFlags[1]);
			eRand.save();
		}

		srand(seed + 40);
		MagicRand mRand{};
		mRand.load();
		if (inputFlags[2] != "." && (inputFlags[2] != "!" || Helpers::getYesNo("Would you like to randomize the magic/technick/enemy ability data? (y/n) ")))
		{
			outputFlags[2] = mRand.process(inputFlags[2]);
			mRand.save();
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
	if (Helpers::fileExists(bpFileName))
	{
		srand(seed - 20);
		RenameMain rename = RenameMain();
		rename.load();
		if (Helpers::getYesNo("Would you like the text to be changed to match better? (y/n) "))
		{
			rename.process();
			rename.save();
		}
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

	string outputFlagStr = "";
	for (int i = 0; i < outputFlags.size(); i++)
		outputFlagStr += "$" + outputFlags[i];


	ofstream myfile;
	myfile.open("FF12Randomized" + to_string(seed) + "\\readme.txt");
	myfile << "The seed is: " + to_string(seed) << endl;
	myfile << "The flags used are: " + outputFlagStr << endl;
	myfile.close();

	cout << "Randomization Complete! The version of this randomizer is 1.2.2." << endl;
	cout << "The folder is called FF12Randomized" + to_string(seed) + " and can be found in the same folder as this program!" << endl;
	cout << "The flag string used for this is: " + outputFlagStr << endl;
	cout << "Remember to load the mod using DrakLab!" << endl;

	system("pause");

	return 0;
}

