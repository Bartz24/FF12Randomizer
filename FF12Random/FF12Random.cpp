// FF12Random.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <time.h>
#include <windows.h>
#include <cstdio>
#include <functional>
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

	cout << "Processing..." << endl;
	system("pause");
	try {
		string inputs[4];

		//0-seed
		//1-flags
		//2-ps2data path
		//3-fst folder path

		string line;
		ifstream myfile("inputs.txt");
		if (myfile.is_open())
		{
			for (int i = 0; i < 4; i++)
			{
				getline(myfile, line);
				inputs[i] = line;
			}
			myfile.close();
		}

		size_t seed = time(NULL);
		if (!inputs[0].empty())
		{
			try
			{
				seed = stol(inputs[0]);
			}
			catch (const exception &e)
			{
				seed = hash<string>{}(inputs[0]);
			}
		}
		srand(seed);

		Helpers::rng.seed(seed);

		vector<string> inputFlags = split(inputs[1], '$');
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
		if (inputs[2].empty())
		{
			std::experimental::filesystem::copy("data\\FF12RandomizedBase", newFolder, std::experimental::filesystem::copy_options::recursive);
		}
		else
		{
			std::experimental::filesystem::copy(inputs[2], newFolder, std::experimental::filesystem::copy_options::recursive);
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
			if (inputFlags[0] != ".")
			{
				outputFlags[0] = mRand.process(inputFlags[0]);
			}

			srand(seed + 20);
			ItemRand iRand{};
			iRand.load();
			if (inputFlags[1] != ".")
			{
				outputFlags[1] = iRand.process(inputFlags[1]);
			}

			srand(seed + 40);
			EquipRand eRand{};
			eRand.load();
			if (inputFlags[2] != ".")
			{
				outputFlags[2] = eRand.process(inputFlags[2]);
			}

			srand(seed + 80);
			AugmentRand aRand{};
			aRand.load();
			if (inputFlags[3] != ".")
			{
				outputFlags[3] = aRand.process(inputFlags[3]);
			}

			srand(seed + 160);
			LicenseRand lRand{};
			lRand.load();
			if (inputFlags[4] != ".")
			{
				outputFlags[4] = lRand.process(inputFlags[4]);
			}

			srand(seed + 320);
			ShopRand sRand{};
			sRand.load();
			if (inputFlags[5] != ".")
			{
				outputFlags[5] = sRand.process(inputFlags[5]);
			}

			srand(seed + 640);
			CharRand cRand{};
			cRand.load();
			if (inputFlags[6] != ".")
			{
				outputFlags[6] = cRand.process(inputFlags[6]);
			}

			srand(seed + 1280);
			RewardRand rRand{};
			rRand.load();
			if (inputFlags[7] != ".")
			{
				outputFlags[7] = rRand.process(inputFlags[7]);
			}
			mRand.save();
			iRand.save();
			eRand.save();
			aRand.save();
			lRand.save();
			sRand.save();
			cRand.save();
			rRand.save();
		}
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
			bRand.load();
			if (inputFlags[8] != ".")
			{
				outputFlags[8] = bRand.process(inputFlags[8]);
				bRand.save();
			}
		}
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
		if (inputFlags[9] != ".")
		{
			outputFlags[9] = tRand.process(inputFlags[9]);
			tRand.save();
		}

		FileSizeTableFix fFix = FileSizeTableFix();
		fFix.load(inputs[3]);
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
		if (!inputs[0].empty())
			oFile << "The seed is: " + inputs[0] << endl;
		else
			oFile << "The seed is: " + to_string(seed) << endl;
		oFile << "The flags used are: " + outputFlagStr << endl;
		oFile << "For info on the bazaars and treasures, check the documentation.html file!" << endl;
		oFile.close();
	}
	catch (const exception &e)
	{
		cerr << e.what();
		system("pause");
	}

	return 0;
}

