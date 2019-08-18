#include "stdafx.h"
#include "RenameMain.h"

string RenameMain::lootNames[280] = {};
string RenameMain::equipNames[420] = {};
string RenameMain::abilityNames[545] = {};
string RenameMain::gambitNames[284] = {};
string RenameMain::helpMenu[200] = {};
string RenameMain::menuCmd[210] = {};
string RenameMain::menuMsg[130] = {};
string RenameMain::charNames[629] = {};

RenameMain::RenameMain()
{
}


RenameMain::~RenameMain()
{
}

void RenameMain::load()
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	wstring ws(path);
	string strPath(ws.begin(), ws.end());
	strPath = strPath.substr(0, strPath.find_last_of("\\/"));
	string s = "\"" + Helpers::mainPS2DataFolder + "\" .EXTRACT";
	system(("FF12TextPatcher.exe " + s).c_str());

	string line;
	ifstream myfile("lootNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 280; i++)
		{
			getline(myfile, line);
			lootNames[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("equipmentNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 420; i++)
		{
			getline(myfile, line);
			equipNames[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("gambitNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 284; i++)
		{
			getline(myfile, line);
			gambitNames[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("charNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 629; i++)
		{
			getline(myfile, line);
			charNames[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("data\\help_menu.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 200; i++)
		{
			getline(myfile, line);
			helpMenu[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("menu_command.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 210; i++)
		{
			getline(myfile, line);
			menuCmd[i] = line;
		}
		myfile.close();
	}

	myfile = ifstream("data\\menu_message.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 130; i++)
		{
			getline(myfile, line);
			menuMsg[i] = line;
		}
		myfile.close();
	}

	actRename.load();
	lRename.load();
	bRename.load();
	aRename.load();
	cRename.load();
	for (int i = 0; i < 545; i++)
		abilityNames[i] = actRename.data[i];

	if (Helpers::fileExists("text"))
		std::experimental::filesystem::remove_all("text");
	std::experimental::filesystem::copy("data\\text", "text", std::experimental::filesystem::copy_options::recursive);
}

void RenameMain::save()
{
	actRename.save();
	lRename.save();
	bRename.save();
	aRename.save();
	cRename.save();

	ofstream myfile;
	myfile.open("gambitNames.txt");
	for (int i = 0; i < 284; i++)
	{
		myfile << gambitNames[i];
		if (i < 283)
			myfile << endl;
	}
	myfile.close();

	myfile = ofstream();
	myfile.open("charNames.txt");
	for (int i = 0; i < 629; i++)
	{
		myfile << charNames[i];
		if (i < 628)
			myfile << endl;
	}
	myfile.close();

	myfile = ofstream();
	myfile.open("equipmentNames.txt");
	for (int i = 0; i < 420; i++)
	{
		myfile << equipNames[i];
		if (i < 419)
			myfile << endl;
	}
	myfile.close();

	myfile = ofstream();
	myfile.open("help_menu.txt");
	for (int i = 0; i < 200; i++)
	{
		myfile << helpMenu[i];
		if (i < 199)
			myfile << endl;
	}
	myfile.close();

	myfile = ofstream();
	myfile.open("menu_command.txt");
	for (int i = 0; i < 210; i++)
	{
		myfile << menuCmd[i];
		if (i < 209)
			myfile << endl;
	}
	myfile.close();


	myfile = ofstream();
	myfile.open("menu_message.txt");
	for (int i = 0; i < 130; i++)
	{
		myfile << menuMsg[i];
		if (i < 129)
			myfile << endl;
	}
	myfile.close();

	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	wstring ws(path);
	string strPath(ws.begin(), ws.end());
	strPath = strPath.substr(0, strPath.find_last_of("\\/"));
	string s = "\"" + Helpers::mainPS2DataFolder + "\"";
	system(("FF12TextPatcher.exe " + s).c_str());

	remove("licenseNames.txt");
	remove("bazaarNames.txt");
	remove("augmentNames.txt");

	remove("abilityNames.txt");
	remove("abilityDescriptions.txt");
	remove("abilityDescriptions2.txt");
	remove("charNames.txt");
	remove("equipmentNames.txt");
	remove("menuNames.txt");
	remove("lootNames.txt");
	remove("gambitNames.txt");
	remove("help_menu.txt");
	remove("menu_command.txt");
	remove("menu_message.txt");
	remove("penelosdiary.txt");
	remove("menu00.txt");

	std::experimental::filesystem::remove_all("text");
}

void RenameMain::process(string seed, string flags, bool randomizeEnemyNames, bool updateBoardNames)
{
	menuCmd[70] = "Rando Primer";

	if (LicenseBoardRand::usingSingleBoard)
	{
		for (int i = 4; i < 16; i++)
		{
			menuCmd[i] = "";
		}
	}

	if (LicenseBoardRand::usingForcedBoards)
	{
		for (int i = 39; i < 51; i++)
		{
			menuMsg[i] = LicenseBoardRand::boardDescriptions[i - 39] + "{02}" + menuMsg[i];
		}
	}

	if (updateBoardNames && (!LicenseBoardRand::usingSingleBoard || LicenseBoardRand::usingForcedBoards))
	{
		for (int board = 0; board < 12; board++)
		{
			string name;
			if (LicenseBoardRand::usingForcedBoards)
			{
				name = LicenseBoardRand::boardNames[board];
			}
			else
			{
				vector<int> types;
				Helpers::addRangeToVector(types, 0, 29);
				vector<float> percents;
				for (int i = 0; i < 30; i++)
					percents.push_back(getPercentOfLicenses(i, board));
				Helpers::sortWeighted(types, percents);
				do {
					int type1 = Helpers::randInt(0, 7);
					int type2;
					do {
						type2 = Helpers::randInt(4, 11);
					} while (type1 == type2);
					name = LicenseBoardRand::getBoardName(type1, type2);
				} while (find(menuCmd + 4, menuCmd + 16, name) != menuCmd + 16);
			}
			menuCmd[board + 4] = name + "(" + char(int('A') + board) + ")";
		}
	}


	if (LicenseBoardRand::suggestedChars[0] != 0)
	{
		for (int i = 39; i < 51; i++)
		{
			int c = LicenseBoardRand::suggestedChars[i - 39];
			if (c < 0)
				menuMsg[i] = "This is " + cRename.data[abs(c) - 1 + 71] + "'s first board.{02}" + menuMsg[i];
			else
				menuMsg[i] = "This is " + cRename.data[abs(c) - 1 + 71] + "'s second board.{02}" + menuMsg[i];
		}
	}

	actRename.process();
	for (int i = 0; i < 545; i++)
		abilityNames[i] = actRename.data[i];
	string jobNames[12];
	for (int i = 0; i < 12; i++)
	{
		jobNames[i] = char(int('A') + i);
	}
	lRename.process(jobNames);
	cRename.process(randomizeEnemyNames);
	bRename.process();
	aRename.process();

	helpMenu[99].replace(helpMenu[99].find("%s"), 2, seed);
	helpMenu[99].replace(helpMenu[99].find("%f"), 2, flags);
	helpMenu[99].replace(helpMenu[99].find("%v"), 2, Helpers::version);

	for (int i = 0; i < 420; i++)
	{
		EquipData eData = EquipRand::equipData[i];
		AttributeData data = EquipRand::attributeData[eData.attribute / 24];
		if (data.boostElement > 0)
		{
			ElementalValue elements(data.boostElement);
			string elementDisplay = "";
			if (elements.hasElement(Element::Fire))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8A}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Lightning))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8B}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Ice))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8C}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Earth))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8D}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Water))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8E}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Wind))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{8F}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Holy))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{90}{0F}{3C}{81}{80}";
			if (elements.hasElement(Element::Dark))
				elementDisplay += "{0F}{3C}{C1}{FE}{0F}{3F}{81}{91}{0F}{3C}{81}{80}";
			equipNames[i] = elementDisplay + equipNames[i];
		}
	}
}

float RenameMain::getPercentOfLicenses(int type, int board)
{
	vector<int> licenses;
	string display = "";
	switch (type)
	{
	case 0:
		display += "White Magicks";
		Helpers::addRangeToVector(licenses, 182, 189);
		licenses.push_back(355);
		Helpers::addRangeToVector(licenses, 208, 211);
		break;
	case 1:
		display += "Black Magicks";
		Helpers::addRangeToVector(licenses, 190, 197);
		licenses.push_back(356);
		licenses.push_back(358);
		Helpers::addRangeToVector(licenses, 215, 217);
		break;
	case 2:
		display += "Time Magicks";
		Helpers::addRangeToVector(licenses, 198, 204);
		licenses.push_back(357);
		licenses.push_back(359);
		licenses.push_back(218);
		break;
	case 3:
		display += "Green Magicks";
		Helpers::addRangeToVector(licenses, 205, 207);
		break;
	case 4:
		display += "Arcane Magicks";
		Helpers::addRangeToVector(licenses, 212, 214);
		break;
	case 5:
		display += "Technicks";
		Helpers::addRangeToVector(licenses, 276, 299);
		break;
	case 6:
		display += "Swords";
		Helpers::addRangeToVector(licenses, 32, 39);
		Helpers::addRangeToVector(licenses, 329, 331);
		break;
	case 7:
		display += "Greatswords";
		Helpers::addRangeToVector(licenses, 40, 44);
		Helpers::addRangeToVector(licenses, 332, 333);
		break;
	case 8:
		display += "Katanas";
		Helpers::addRangeToVector(licenses, 45, 49);
		Helpers::addRangeToVector(licenses, 334, 335);
		break;
	case 9:
		display += "Ninja Swords";
		Helpers::addRangeToVector(licenses, 50, 52);
		licenses.push_back(336);
		break;
	case 10:
		display += "Spears";
		Helpers::addRangeToVector(licenses, 53, 59);
		licenses.push_back(337);
		break;
	case 11:
		display += "Poles";
		Helpers::addRangeToVector(licenses, 60, 65);
		Helpers::addRangeToVector(licenses, 338, 339);
		break;
	case 12:
		display += "Bows";
		Helpers::addRangeToVector(licenses, 66, 72);
		Helpers::addRangeToVector(licenses, 340, 341);
		break;
	case 13:
		display += "Crossbows";
		Helpers::addRangeToVector(licenses, 73, 76);
		break;
	case 14:
		display += "Guns";
		Helpers::addRangeToVector(licenses, 77, 82);
		licenses.push_back(342);
		break;
	case 15:
		display += "Axes & Hammers";
		Helpers::addRangeToVector(licenses, 83, 89);
		licenses.push_back(343);
		break;
	case 16:
		display += "Daggers";
		Helpers::addRangeToVector(licenses, 90, 95);
		licenses.push_back(344);
		break;
	case 17:
		display += "Rods";
		Helpers::addRangeToVector(licenses, 96, 100);
		break;
	case 18:
		display += "Staves";
		Helpers::addRangeToVector(licenses, 101, 105);
		licenses.push_back(345);
		break;
	case 19:
		display += "Maces";
		Helpers::addRangeToVector(licenses, 106, 110);
		break;
	case 20:
		display += "Measures";
		Helpers::addRangeToVector(licenses, 111, 113);
		licenses.push_back(346);
		break;
	case 21:
		display += "Hand-bombs";
		Helpers::addRangeToVector(licenses, 114, 116);
		licenses.push_back(347);
		break;
	case 22:
		display += "Shields";
		Helpers::addRangeToVector(licenses, 117, 125);
		licenses.push_back(348);
		break;
	case 23:
		display += "Heavy Armors";
		Helpers::addRangeToVector(licenses, 126, 136);
		Helpers::addRangeToVector(licenses, 349, 350);
		break;
	case 24:
		display += "Light Armors";
		Helpers::addRangeToVector(licenses, 137, 148);
		licenses.push_back(351);
		break;
	case 25:
		display += "Mystic Armors";
		Helpers::addRangeToVector(licenses, 149, 160);
		licenses.push_back(352);
		break;
	case 26:
		display += "Accessories";
		Helpers::addRangeToVector(licenses, 161, 181);
		Helpers::addRangeToVector(licenses, 353, 354);
		break;
	case 27:
		display += "Gambits";
		Helpers::addRangeToVector(licenses, 266, 275);
		break;
	case 28:
		display += "Espers";
		Helpers::addRangeToVector(licenses, 18, 30);
		break;
	case 29:
		display += "Augments";
		Helpers::addRangeToVector(licenses, 219, 265);
		Helpers::addRangeToVector(licenses, 300, 328);
		break;
	}
	int found = 0;
	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			if (find(licenses.begin(), licenses.end(), LicenseBoardRand::boards[board].board[y][x]) != licenses.end())
				found++;
		}
	}
	return float(found) / float(licenses.size());
}

string LicenseRename::getNameFromID(int id)
{
	if (id < 4000)
		return RenameMain::abilityNames[MagicRand::actionData[id].name];
	else return RenameMain::equipNames[EquipRand::equipData[id - 4096].id - 2048];
}

string BazaarRename::getNameFromID(int id)
{
	if (id < 64)
		return RenameMain::abilityNames[MagicRand::actionData[id + 82].name];
	else if (id < 4600)
		return RenameMain::equipNames[EquipRand::equipData[id - 4096].id - 2048];
	else if (id < 9000)
		return RenameMain::lootNames[id - 8192];
	else if (id < 13000)
		return RenameMain::abilityNames[id - 12288];
	else if (id < 17000)
		return RenameMain::abilityNames[id - 16384 + 158];
	else if (id < 17000)
		return RenameMain::abilityNames[id - 16384 + 158];
	else if (id < 25000)
	{
		string name = RenameMain::gambitNames[ItemRand::gambitData[id - 24576].name - 12288];
		if (name.find("{B2}") != string::npos)
			name = name.replace(name.find("{B2}"), 4, "<");
		if (name.find("{C4}") != string::npos)
			name = name.replace(name.find("{C4}"), 4, ">=");
		return name;
	}
	return "";
}

void CharRename::fixGambitNames()
{	
	for (int i = 0; i < 6; i++)
	{
		RenameMain::gambitNames[i + 163] = "Ally: " + data[i + 71];
		RenameMain::gambitNames[i + 224] = "Foe: targeting " + data[i + 71];
	}
}

void CharRename::randomizeEnemyNames()
{
	vector<char> vowels = { 'a','e','i','o','u','y' };
	vector<int> vowelWeights = { 14810,21912,13318,14003,5246,3853 };
	int vowelTotal = 0;
	for (int i = 0; i < vowelWeights.size(); i++)
		vowelTotal += vowelWeights[i];
	vector<char> consanants = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z' };
	vector<int> consanantWeights = { 2715, 4943, 7874, 4200, 3693, 10795, 188, 1257, 7253, 4761, 12666, 3316, 205, 10977, 11450, 16587, 2019, 3819, 315, 128 };
	int consanantTotal = 0;
	for (int i = 0; i < consanantWeights.size(); i++)
		consanantTotal += consanantWeights[i];

	for (int i = 18; i < 629; i++)
	{
		if (RenameMain::charNames[i].find("No name") != string::npos)
			continue;

		string newName="";

		for (int c = 0; c < RenameMain::charNames[i].length(); c++)
		{
			char ch = RenameMain::charNames[i][c];

			char newCh;
			if (find(vowels.begin(), vowels.end(), tolower(ch)) != vowels.end())
			{
				int pick = Helpers::randInt(0, vowelTotal - 1);
				int p = 0;
				for (;pick >= vowelWeights[p]; p++)
					pick -= vowelWeights[p];
				newCh = vowels[p];
			}
			else if (find(consanants.begin(), consanants.end(), tolower(ch)) != consanants.end())
			{
				int pick = Helpers::randInt(0, consanantTotal - 1);
				int p = 0;
				for (; pick >= consanantWeights[p]; p++)
					pick -= consanantWeights[p];
				newCh = consanants[p];
			}
			else
			{
				newName += ch;
				continue;
			}
			if (isupper(ch))
				newCh = toupper(newCh);
			newName += newCh;
		}
		RenameMain::charNames[i] = newName;
	}
}
