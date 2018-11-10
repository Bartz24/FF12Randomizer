#include "stdafx.h"
#include "TreasureRand.h"

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

MapData TreasureRand::mapData[279] = {};

TreasureRand::TreasureRand()
{
}


TreasureRand::~TreasureRand()
{
}

void TreasureRand::load()
{
	string line;
	ifstream myfile("data\\treasures.txt");
	if (myfile.is_open())
	{
		int index = 0;
		while (getline(myfile, line))
		{
			string fileName = line.substr(0, line.find(','));
			trim(fileName);
			mapData[index].fileName = fileName;
			string linePart2 = line.substr(line.find(',') + 1, line.length()-(line.find(',') + 1));
			string offset = linePart2.substr(0, linePart2.find(','));
			trim(offset);
			mapData[index].offset = stoi(offset);
			string linePart3 = linePart2.substr(linePart2.find(',') + 1, linePart2.length() - (linePart2.find(',') + 1));
			string count = linePart3.substr(0, linePart3.find(','));
			trim(count);
			mapData[index].count = stoi(count);
			string name = linePart3.substr(linePart3.find(',') + 1, linePart3.length() - (linePart3.find(',') + 1));
			mapData[index].mapName = name;
			index++;
		}
		myfile.close();
	}
	for (int i = 0; i < 279; i++)
	{
		fileName = mapData[i].getFileName();
		if (Helpers::fileExists(fileName))
		{
			char * buffer;
			long size = mapData[i].count * 24; //Num Treasure * data size
			ifstream file(fileName, ios::in | ios::binary | ios::ate);
			file.seekg(mapData[i].offset);
			buffer = new char[size];
			file.read(buffer, size);
			file.close();

			for (int t = 0; t < mapData[i].count; t++)
			{
				char data[24];
				for (int i2 = 0; i2 < 24; i2++)
				{
					data[i2] = buffer[t * 24 + i2];
				}
				mapData[i].treasure.push_back(TreasureData{ data });
			}

			delete[] buffer;
		}
	}
}

void TreasureRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;
	union U2 {
		unsigned int i;
		unsigned char c[2];
	}byte2;

	for (int i = 0; i < 279; i++)
	{
		fileName = mapData[i].getFileName();
		if (Helpers::fileExists(fileName))
		{
			char * buffer;
			long size = mapData[i].count * 24; //Num Treasure * data size
			fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
			file.seekp(mapData[i].offset);
			buffer = new char[size];

			for (int t = 0; t < mapData[i].count; t++)
			{
				TreasureData d = mapData[i].treasure[t];
				int index = 0;
				for (int i2 = 0; i2 < 24; i2++)
				{
					if (i2 >= 0x09 && i2 <= 0x17)
						continue;
					buffer[t * 24 + i2] = d.unknown[index];
					index++;
				}
				buffer[t * 24 + 0x09] = d.respawn;
				buffer[t * 24 + 0x0A] = d.spawnChance;
				buffer[t * 24 + 0x0B] = d.gilChance;
				buffer[t * 24 + 0x0C] = U{ d.common1 }.c[0];
				buffer[t * 24 + 0x0D] = U{ d.common1 }.c[1];
				buffer[t * 24 + 0x0E] = U{ d.common2 }.c[0];
				buffer[t * 24 + 0x0F] = U{ d.common2 }.c[1];
				buffer[t * 24 + 0x10] = U{ d.rare1 }.c[0];
				buffer[t * 24 + 0x11] = U{ d.rare1 }.c[1];
				buffer[t * 24 + 0x12] = U{ d.rare2 }.c[0];
				buffer[t * 24 + 0x13] = U{ d.rare2 }.c[1];
				buffer[t * 24 + 0x14] = U{ d.gil1 }.c[0];
				buffer[t * 24 + 0x15] = U{ d.gil1 }.c[1];
				buffer[t * 24 + 0x16] = U{ d.gil2 }.c[0];
				buffer[t * 24 + 0x17] = U{ d.gil2 }.c[1];
			}

			file.write(buffer, size);
			file.close();

			delete[] buffer;
		}
	}
}

string TreasureRand::process(string preset)
{
	string flags = preset;
	if (preset == "!")
	{
		cout << "Treasure Data Randomization Options:" << endl;
		cout << "\t t: Randomize all the treasures (spawn chance, gil, and items. Items of higher value can be found with the diamond armlet effect.)" << endl;
		flags = Helpers::readFlags("t");
	}
	if (flags.find('t') != string::npos)
	{
		randTreasures();
	}
	return flags;
}

//Usable Items:		0-28, 42-63
//Loot:				8192, 8224-8437 8448-8461 8468-8471
//Magic:			12288-12368
//Technicks:		16384-16407
//Gambits:			24576-24831
//Equipment:		4097-4255, 4258-4259, 4264, 4266-4274, 4288-4483

void TreasureRand::randTreasures()
{
	vector<int> data = vector<int>();
	addRangeToVector(data, 0, 28);
	addRangeToVector(data, 42, 63);
	addRangeToVector(data, 8192, 8192);
	addRangeToVector(data, 8224, 8437);
	addRangeToVector(data, 8448, 8461);
	addRangeToVector(data, 8468, 8471);
	addRangeToVector(data, 12288, 12368);
	addRangeToVector(data, 16384, 16407);
	addRangeToVector(data, 24576, 24831);
	addRangeToVector(data, 4097, 4255);
	addRangeToVector(data, 4258, 4259);
	addRangeToVector(data, 4264, 4264);
	addRangeToVector(data, 4266, 4274);
	addRangeToVector(data, 4288, 4483);

	for (int i = 0; i < 279; i++)
	{
		for (int t = 0; t < mapData[i].count; t++)
		{			
			int gilA, gilB;
			mapData[i].treasure[t].common1 = getItem(data, 0, 12000, gilA);
			mapData[i].treasure[t].common2 = getItem(data, 500, 15000, gilB);
			mapData[i].treasure[t].gil1 = (gilA + gilB) / 2 / 100;
			mapData[i].treasure[t].rare1 = getItem(data, 10000, 32000, gilA);
			mapData[i].treasure[t].rare2 = getItem(data, 30000, 70000, gilB);
			mapData[i].treasure[t].gil2 = (gilA * 9 + gilB) / 10 / 10;
			mapData[i].treasure[t].spawnChance = (4000 - (mapData[i].treasure[t].gil1 + mapData[i].treasure[t].gil2)) * 100 / 4000;
			mapData[i].treasure[t].gilChance = rand() % 90 + 5;
			mapData[i].treasure[t].respawn = 0xFF;
		}
	}
}

int TreasureRand::getItem(std::vector<int> &data, int minCost, int maxCost, int &cost)
{
	int itemID;
	cost = 99999;
	do
	{
		itemID = data[rand() % data.size()];
		if (itemID < 64)
			cost = ItemRand::itemData[itemID].cost;
		else if (itemID < 4600)
			cost = EquipRand::equipData[itemID - 4096].cost;
		else if (itemID < 9000)
		{
			cost = ItemRand::lootData[itemID - 8192].cost * 1000; //Make loot rarer in Treasures
		}
		else if (itemID < 13000)
			cost = MagicRand::magicData[itemID - 12288].cost;
		else if (itemID < 17000)
			cost = MagicRand::magicData[itemID - 16384 + 81].cost;
		else
			cost = ItemRand::gambitData[itemID - 24576].cost;

	} while (cost < minCost || cost > maxCost || rand() % 256 < int(sqrt(cost)));
	return itemID;
}

void TreasureRand::addRangeToVector(vector<int>& data, int low, int high)
{
	for (int i = low; i <= high; i++)
		data.push_back(i);
}
