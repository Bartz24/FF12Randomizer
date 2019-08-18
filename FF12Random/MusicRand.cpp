#include "stdafx.h"
#include "MusicRand.h"

vector<MusicData> MusicRand::data = vector<MusicData>();
vector<MusicData> MusicRand::newPaths = vector<MusicData>();

MusicRand::MusicRand()
{
}


MusicRand::~MusicRand()
{
}

void MusicRand::load(vector<string> musicFolders, FlagGroup flags)
{
	string line;
	ifstream myfile("data\\musicList.txt");
	if (myfile.is_open())
	{
		bool first = true;
		while (getline(myfile, line))
		{
			if (first)
			{
				first = false;
				continue;
			}

			vector<string> splitData = Helpers::split(line, ',');

			newPaths.push_back(MusicData("data\\FF12MusicBase\\ps2data\\sound\\music\\magi_data\\win\\" + splitData[0] + ".win.mab"));
			newPaths[newPaths.size() - 1].path = splitData[0] + ".win.mab";
			data.push_back(MusicData("data\\FF12MusicBase\\ps2data\\sound\\music\\magi_data\\win\\" + splitData[0] + ".win.mab"));
			data[data.size() - 1].setTypes(splitData[1]);
			newPaths[newPaths.size() - 1].setTypes(splitData[1]);
		}
		myfile.close();
	}

	for (string musicFolder : musicFolders)
	{
		if (musicFolder.find_first_not_of(' ') == std::string::npos)
			continue;
		vector<string> folders = Helpers::get_directories(musicFolder);
		for (string folder : folders)
		{
			vector<string> files = Helpers::get_files(folder);
			for (string file : files)
			{
				if (flags.hasFlag("n"))
					data.push_back(MusicData(file));
			}
		}
	}
	experimental::filesystem::create_directory(Helpers::mainPS2DataFolder + "\\sound");
	experimental::filesystem::create_directory(Helpers::mainPS2DataFolder + "\\sound\\music");
	experimental::filesystem::create_directory(Helpers::mainPS2DataFolder + "\\sound\\music\\magi_data");
	experimental::filesystem::create_directory(Helpers::mainPS2DataFolder + "\\sound\\music\\magi_data\\win");
}

void MusicRand::process()
{
}

void MusicRand::save(FlagGroup flags)
{
	vector<string> docData;
	vector<string> picked;
	for (MusicData &path : newPaths)
	{
		string from = "";
		do {
			if (flags.getFlag("m").isSmart())
				from = pickRandomThemeOfType(path.types[0]);
			else
				from = data[Helpers::randInt(0, data.size() - 1)].path;
		} while (find(picked.begin(), picked.end(), from) != picked.end());
		picked.push_back(from);
		string docPath = from.substr(from.find("\\music") + 1) + " -> " + path.path.substr(path.path.find("\\win") + 1);
		docData.push_back(docPath);
		experimental::filesystem::copy_file(from, Helpers::mainPS2DataFolder + "\\sound\\music\\magi_data\\win\\" + path.path);
	}

	{
		string folder = Helpers::mainPS2DataFolder.substr(0, Helpers::mainPS2DataFolder.find("\\ps2data"));
		ofstream oFile;
		oFile.open(folder + "\\musicChanges.txt");
		for (string s : docData)
		{
			oFile << s << endl;
		}
		oFile.close();
	}
}

string MusicRand::pickRandomThemeOfType(string type)
{
	vector<string> possible;
	for (MusicData d : data)
	{
		if (find(d.types.begin(), d.types.end(), type) != d.types.end())
			possible.push_back(d.path);
	}
	return possible[Helpers::randInt(0, possible.size() - 1)];
}
