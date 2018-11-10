#include "stdafx.h"
#include "RenameMain.h"

string RenameMain::lootNames[280] = {};
string RenameMain::equipNames[420] = {};
string RenameMain::abilityNames[545] = {};
string RenameMain::gambitNames[284] = {};

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

	actRename.load();
	lRename.load();
	bRename.load();
	aRename.load();
}

void RenameMain::save()
{
	actRename.save();
	lRename.save();
	bRename.save();
	aRename.save();

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
	remove("equipmentNames.txt");
	remove("lootNames.txt");
	remove("gambitNames.txt");
}

void RenameMain::process()
{
	actRename.process();
	for (int i = 0; i < 545; i++)
		abilityNames[i] = actRename.data[i];
	lRename.process();
	bRename.process();
	aRename.process();
}

string LicenseRename::getNameFromID(int id)
{
	if (id < 4000)
		return RenameMain::abilityNames[id];
	else return RenameMain::equipNames[id - 4096];
}

string BazaarRename::getNameFromID(int id)
{
	if (id < 64)
		return RenameMain::abilityNames[id + 82];
	else if (id < 4600)
		return RenameMain::equipNames[id - 4096];
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
