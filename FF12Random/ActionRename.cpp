#include "stdafx.h"
#include "ActionRename.h"


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


ActionRename::ActionRename()
{
}


ActionRename::~ActionRename()
{
}

void ActionRename::load()
{
	string line;
	ifstream myfile("abilityNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 545; i++)
		{
			getline(myfile, line);
			data[i] = line;
		}
		myfile.close();
	}
	for (int i = 0; i < 81; i++)
	{
		desc[i] = ".IGNORE";
	}
}

void ActionRename::save()
{
	ofstream myfile;
	myfile.open("abilityNames.txt");
	for (int i = 0; i < 545; i++)
	{
		myfile << data[i];
		if (i < 544)
			myfile << endl;
	}
	myfile.close();

	myfile.open("abilityDescriptions.txt");
	for (int i = 0; i < 81; i++)
	{
		myfile << desc[i];
		if (i < 80)
			myfile << endl;
	}
	if (MagicRand::didRandSpells)
	{
		myfile << endl;
		for (int i = 0; i < 6; i++)
		{
			myfile << ".IGNORE" << endl;
		}
		myfile << "Due to conflicts, item descriptions were removed.";
	}
	myfile.close();

	myfile.open("abilityDescriptions2.txt");
	myfile << endl;
	for (int i = 0; i < 81; i++)
	{
		myfile << desc[i];
		if (i < 80)
			myfile << endl;
	}
	if (MagicRand::didRandSpells)
	{
		for (int i = 0; i < 6; i++)
		{
			myfile << ".IGNORE" << endl;
		}
		myfile << "Due to conflicts, item descriptions were removed.";
	}
	myfile.close();
}

void ActionRename::process()
{
	if (MagicRand::didRandSpells)
	{
		for (int i = 0; i < 81; i++)
		{
			data[i] = MagicRand::spellNames[i];
			desc[i] = MagicRand::spellDescs[i];
			if (desc[i].find("%t") != string::npos)
			{
				string replace = (MagicRand::actionData[i].aoeRange > 0 ? (MagicRand::actionData[i].target >= 140 ? "all foes in range" : "all allies in range") : (MagicRand::actionData[i].target >= 140 ? "one foe" : "one ally"));
				desc[i] = desc[i].substr(0, desc[i].find("%t")) + replace + desc[i].substr(desc[i].find("%t") + 2, desc[i].length() - desc[i].find("%t") - 2);
			}
			while (desc[i].find("%c") != string::npos)
			{
				string replace = ",";
				desc[i] = desc[i].substr(0, desc[i].find("%c")) + replace + desc[i].substr(desc[i].find("%c") + 2, desc[i].length() - desc[i].find("%c") - 2);
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (MagicRand::trapNames[i] == "")
			data[i + 246] = ".IGNORE";
		else
			data[i + 246] = MagicRand::trapNames[i];
	}

	data[107] = "Sap Meteorite (A)";
	data[108] = "Disease Meteorite (B)";
	data[109] = "Attack Meteorite (C)";
	data[110] = "Attack Meteorite (D)";

	if (MagicRand::didRandElement)
	{

		data[283] = "Elementa I";
		data[284] = "Elementa II";
		data[285] = "Elementaga";
		data[286] = "Elementaja VI";
		data[287] = "Elementaja I";
		data[288] = "Elementaja II";
		data[289] = "Elementaja IV";
		data[290] = "Elementaja V";
		data[291] = "Elementaja VIII";
		data[292] = "Elementaja III";
		data[293] = "Elementaja VII";

		data[446] = "Piercing Elementaga I";
		data[447] = "Piercing Elementaga II";
		data[448] = "Piercing Elementaga III";
		data[449] = "Piercing Elementaga IV";
	}
	if (MagicRand::didRandStatus)
	{
		data[294] = "Effectaga";
		data[295] = "Effectaja";
		data[296] = "Effectaza";
		data[297] = "Effectara";
		data[299] = "Lv.2 Effect";
		data[300] = "Lv.3 Effect";
		data[301] = "Lv.4 Effect";
		data[302] = "Lv.5 Effect";
		data[303] = "Prime Lv. Effect";
	}
}
