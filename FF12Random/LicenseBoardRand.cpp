#include "stdafx.h"
#include "LicenseBoardRand.h"

LicenseBoardData LicenseBoardRand::boards[12] = {};
string LicenseBoardRand::boardDescriptions[12] = {};
vector<string> LicenseBoardRand::boardNames = vector<string>();
string LicenseBoardRand::type2Names[30][30] = {};
int LicenseBoardRand::suggestedChars[12] = {};
bool LicenseBoardRand::usingSingleBoard = false;
bool LicenseBoardRand::usingForcedBoards = false;

LicenseBoardRand::LicenseBoardRand()
{
}


LicenseBoardRand::~LicenseBoardRand()
{
}

void LicenseBoardRand::load()
{
	folderName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\in\\binaryfile";

	for (int i = 0; i < 12; i++)
	{
		char * buffer;
		long size = 24 * 24 * 2 + 8; //Board X * Y * size of data + header size
		ifstream file(folderName + "\\board_" + to_string(i + 1)+".bin", ios::in | ios::binary | ios::ate);
		file.seekg(0);
		buffer = new char[size];
		file.read(buffer, size);
		file.close();		

		for (int i2 = 0; i2 < 8; i2++)
			boards[i].header[i2] = buffer[i2];

		for (int x = 0; x < 24; x++)
		{
			for (int y = 0; y < 24; y++)
			{
				char data[] = { buffer[y * 24 * 2 + x * 2 + 8] , buffer[y * 24 * 2 + x * 2 + 9] };
				boards[i].board[y][x] = *reinterpret_cast<unsigned short*>(data);
			}
		}

		delete[] buffer;
	}

	{
		string line;
		ifstream myfile("data\\type2Classes.csv");
		if (myfile.is_open())
		{
			bool first = true;
			int row = 0;
			while (getline(myfile, line) && row < 30)
			{
				if (first)
				{
					first = false;
					continue;
				}

				vector<string> data = Helpers::split(line, ',');
				for (int c = 1; c < data.size(); c++)
					type2Names[row][c - 1] = data[c];
				row++;
			}
			myfile.close();
		}
	}
}

void LicenseBoardRand::process(FlagGroup flags)
{

	if (!flags.hasFlag("s") && flags.hasFlag("C"))
	{
		randomizeChars();
	}
	else
		suggestedChars[0] = 0;

	for (int i = 0; i < 12; i++)
	{
		if (usingSingleBoard && i > 0)
		{
			boards[i] = boards[0];
			continue;
		}
		if (flags.hasFlag("s"))
		{
			useSingleBoard();
		}
		vector<unsigned short> licensesToUse = getLicenses(boards[i]);
		if (flags.hasFlag("l") && !usingSingleBoard)
		{
			setRandLicenses(licensesToUse, flags);
		}
		if (flags.hasFlag("L") && !usingSingleBoard)
		{
			int type1, type2;
			do {
				type1 = Helpers::randInt(0, 29);
				type2 = Helpers::randInt(0, 29);
			} while (type2 == type1 || find(boardNames.begin(), boardNames.end(), getBoardName(type1, type2)) != boardNames.end());

			usingForcedBoards = true;
			if (flags.getFlag("L").isSmart())
			{
				setForcedLicenseTypes(licensesToUse, type1, i, type2, true, flags);
			}
			else
			{
				setForcedLicenseTypes(licensesToUse, type1, i, type2, false, flags);
			}
			boardNames.push_back(getBoardName(type1, type2));
		}
		if (flags.hasFlag("h"))
		{
			sortLicenses(licensesToUse);
		}
		bool layout[24][24];
		getLayout(layout, boards[i]);
		if (flags.hasFlag("l") || flags.hasFlag("L") || flags.hasFlag("h") || flags.hasFlag("b"))
		{
			int numPathable = 0;
			int attempts = 0;
			do
			{
				attempts++;
				vector<int> shortcutLocs = vector<int>();
				if (flags.hasFlag("b") || flags.hasFlag("L"))
				{
					if (flags.hasFlag("m"))
					{
						int shortcuts = 0;
						if (!flags.hasFlag("L"))
						{
							for (int i = 0; i < licensesToUse.size(); i++)
							{
								if (licensesToUse[i] <= 0x001E || licensesToUse[i] == 0x0168)
									shortcuts++;
							}
						}
						setMazeLayout(layout, shortcutLocs, licensesToUse.size()-shortcuts, shortcuts);
					}
					else
						setRandLayout(layout, licensesToUse.size());
				}
				if (flags.hasFlag("h"))
					assignLoHiLicenses(boards[i], licensesToUse, *layout, shortcutLocs);
				else
					assignLicenses(boards[i], licensesToUse, *layout, shortcutLocs);
			} while (attempts < 100 && (!pathToLicense(boards[i], 18, numPathable) || numPathable < 20 || !pathToLicense(boards[i], 360, numPathable) || numPathable < 20));
		}
	}
}

void LicenseBoardRand::save()
{
	union U {
		unsigned short s;
		unsigned char c[2];
	}byte;

	for (int i = 0; i < 12; i++)
	{
		char * buffer;
		long size = 24 * 24 * 2 + 8; //Board X * Y * size of data + header size
		ofstream file(folderName + "\\board_" + to_string(i + 1) + ".bin", ios::out | ios::binary | ios::ate);
		file.seekp(0);
		buffer = new char[size];

		for (int i2 = 0; i2 < 8; i2++)
			buffer[i2] = boards[i].header[i2];

		for (int x = 0; x < 24; x++)
		{
			for (int y = 0; y < 24; y++)
			{
				buffer[y * 24 * 2 + x * 2 + 8] = U{ boards[i].board[y][x] }.c[0];
				buffer[y * 24 * 2 + x * 2 + 9] = U{ boards[i].board[y][x] }.c[1];
			}
		}

		file.write(buffer, size);
		file.close();


		delete[] buffer;
	}
}

void LicenseBoardRand::useSingleBoard()
{
	for (int i = 0; i < 12; i++)
	{
		char * buffer;
		long size = 24 * 24 * 2 + 8; //Board X * Y * size of data + header size
		ifstream file("data\\ps2Board.bin", ios::in | ios::binary | ios::ate);
		file.seekg(0);
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i2 = 0; i2 < 8; i2++)
			boards[i].header[i2] = buffer[i2];

		for (int x = 0; x < 24; x++)
		{
			for (int y = 0; y < 24; y++)
			{
				char data[] = { buffer[y * 24 * 2 + x * 2 + 8] , buffer[y * 24 * 2 + x * 2 + 9] };
				boards[i].board[y][x] = *reinterpret_cast<unsigned short*>(data);
			}
		}

		delete[] buffer;
	}

	usingSingleBoard = true;
}

vector<unsigned short> LicenseBoardRand::getLicenses(LicenseBoardData board)
{
	vector<unsigned short> data = vector<unsigned short>();

	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			if (board.board[y][x] != 0xFFFF)
				data.push_back(board.board[y][x]);
		}
	}

	return data;
}

void LicenseBoardRand::setRandLicenses(vector<unsigned short> &data, FlagGroup flags)
{
	vector<unsigned short> newData = vector<unsigned short>();
	newData.push_back( 31); //Essentials
	newData.push_back( 360); //Second Board
	newData.push_back( 18); //Belias
	if (flags.hasFlag("g")) //Gambits
	{
		for (int i = 266; i < 276; i++)
		{
			newData.push_back(i);
		}
	}
	if (flags.hasFlag("e")) //Espers
	{
		for (int i = 19; i < 31; i++)
		{
			newData.push_back(i);
		}
	}
	if (flags.hasFlag("a")) //Accessories
	{
		for (int i = 161; i < 182; i++)
		{
			newData.push_back(i);
		}
		newData.push_back(353);
		newData.push_back(354);
	}
	vector<unsigned short> possible = vector<unsigned short>();
	for (int i = 0; i < 361; i++)
	{
		if (find(newData.begin(), newData.end(), i) == newData.end())
			possible.push_back( i);
	}
	while (newData.size() < data.size())
	{		
		int index = Helpers::randInt(0, possible.size() - 1);
		newData.push_back( possible[index]);
		possible.erase(possible.begin() + index);
	}
	data = newData;
}

void LicenseBoardRand::randomizeChars()
{
	vector<int> chars;
	for (int i = 1; i < 7; i++)
	{
		chars.push_back(i);
		chars.push_back(-i);
	}
	Helpers::shuffle(chars);
	for (int i = 0; i < 12; i++)
		suggestedChars[i] = chars[i];
}

void LicenseBoardRand::addForcedLicenses(int type, std::string &display, std::vector<unsigned short> &newData)
{
	switch (type)
	{
	case 0:
		display += "White Magicks";
		Helpers::addRangeToVector(newData, 182, 189);
		newData.push_back(355);
		Helpers::addRangeToVector(newData, 208, 211);
		break;
	case 1:
		display += "Black Magicks";
		Helpers::addRangeToVector(newData, 190, 197);
		newData.push_back(356);
		newData.push_back(358);
		Helpers::addRangeToVector(newData, 215, 217);
		break;
	case 2:
		display += "Time Magicks";
		Helpers::addRangeToVector(newData, 198, 204);
		newData.push_back(357);
		newData.push_back(359);
		newData.push_back(218);
		break;
	case 3:
		display += "Green Magicks";
		Helpers::addRangeToVector(newData, 205, 207);
		break;
	case 4:
		display += "Arcane Magicks";
		Helpers::addRangeToVector(newData, 212, 214);
		break;
	case 5:
		display += "Technicks";
		Helpers::addRangeToVector(newData, 276, 299);
		break;
	case 6:
		display += "Swords";
		Helpers::addRangeToVector(newData, 32, 39);
		Helpers::addRangeToVector(newData, 329, 331);
		break;
	case 7:
		display += "Greatswords";
		Helpers::addRangeToVector(newData, 40, 44);
		Helpers::addRangeToVector(newData, 332, 333);
		break;
	case 8:
		display += "Katanas";
		Helpers::addRangeToVector(newData, 45, 49);
		Helpers::addRangeToVector(newData, 334, 335);
		break;
	case 9:
		display += "Ninja Swords";
		Helpers::addRangeToVector(newData, 50, 52);
		newData.push_back(336);
		break;
	case 10:
		display += "Spears";
		Helpers::addRangeToVector(newData, 53, 59);
		newData.push_back(337);
		break;
	case 11:
		display += "Poles";
		Helpers::addRangeToVector(newData, 60, 65);
		Helpers::addRangeToVector(newData, 338, 339);
		break;
	case 12:
		display += "Bows";
		Helpers::addRangeToVector(newData, 66, 72);
		Helpers::addRangeToVector(newData, 340, 341);
		break;
	case 13:
		display += "Crossbows";
		Helpers::addRangeToVector(newData, 73, 76);
		break;
	case 14:
		display += "Guns";
		Helpers::addRangeToVector(newData, 77, 82);
		newData.push_back(342);
		break;
	case 15:
		display += "Axes & Hammers";
		Helpers::addRangeToVector(newData, 83, 89);
		newData.push_back(343);
		break;
	case 16:
		display += "Daggers";
		Helpers::addRangeToVector(newData, 90, 95);
		newData.push_back(344);
		break;
	case 17:
		display += "Rods";
		Helpers::addRangeToVector(newData, 96, 100);
		break;
	case 18:
		display += "Staves";
		Helpers::addRangeToVector(newData, 101, 105);
		newData.push_back(345);
		break;
	case 19:
		display += "Maces";
		Helpers::addRangeToVector(newData, 106, 110);
		break;
	case 20:
		display += "Measures";
		Helpers::addRangeToVector(newData, 111, 113);
		newData.push_back(346);
		break;
	case 21:
		display += "Hand-bombs";
		Helpers::addRangeToVector(newData, 114, 116);
		newData.push_back(347);
		break;
	case 22:
		display += "Shields";
		Helpers::addRangeToVector(newData, 117, 125);
		newData.push_back(348);
		break;
	case 23:
		display += "Heavy Armors";
		Helpers::addRangeToVector(newData, 126, 136);
		Helpers::addRangeToVector(newData, 349, 350);
		break;
	case 24:
		display += "Light Armors";
		Helpers::addRangeToVector(newData, 137, 148);
		newData.push_back(351);
		break;
	case 25:
		display += "Mystic Armors";
		Helpers::addRangeToVector(newData, 149, 160);
		newData.push_back(352);
		break;
	case 26:
		display += "Accessories";
		Helpers::addRangeToVector(newData, 161, 181);
		Helpers::addRangeToVector(newData, 353, 354);
		break;
	case 27:
		display += "Gambits";
		Helpers::addRangeToVector(newData, 266, 275);
		break;
	case 28:
		display += "Espers";
		Helpers::addRangeToVector(newData, 19, 30);
		break;
	case 29:
		display += "Augments";
		Helpers::addRangeToVector(newData, 219, 265);
		Helpers::addRangeToVector(newData, 300, 328);
		break;
	}
}

void LicenseBoardRand::setForcedLicenseTypes(vector<unsigned short>& data, int type, int board, int type2, bool useType2, FlagGroup flags)
{
	vector<unsigned short> newData = vector<unsigned short>();
	newData.push_back(31); //Essentials
	newData.push_back(360); //Second Board
	newData.push_back(18); //Belias

	string display = "";
	addForcedLicenses(type, display, newData);
	display += "/";
	addForcedLicenses(type2, display, newData);

	if (flags.hasFlag("g")) //Gambits
	{
		for (int i = 266; i < 276; i++)
		{
			if (find(newData.begin(), newData.end(), i) == newData.end())
				newData.push_back(i);
		}
	}
	if (flags.hasFlag("e")) //Espers
	{
		for (int i = 19; i < 31; i++)
		{
			if (find(newData.begin(), newData.end(), i) == newData.end())
				newData.push_back(i);
		}
	}
	if (flags.hasFlag("a")) //Accessories
	{
		for (int i = 161; i < 182; i++)
		{
			if (find(newData.begin(), newData.end(), i) == newData.end())
				newData.push_back(i);
		}
		if (find(newData.begin(), newData.end(), 353) == newData.end())
			newData.push_back(353);
		if (find(newData.begin(), newData.end(), 354) == newData.end())
			newData.push_back(354);
	}
	if (!useType2) {
		vector<unsigned short> possible = vector<unsigned short>();
		for (int i = 0; i < 361; i++)
		{
			if (find(newData.begin(), newData.end(), i) == newData.end())
				possible.push_back(i);
		}
		while (newData.size() < data.size())
		{
			int index = Helpers::randInt(0, possible.size() - 1);
			newData.push_back(possible[index]);
			possible.erase(possible.begin() + index);
		}
	}
	boardDescriptions[board] = display;
	data = newData;
}

string LicenseBoardRand::getBoardName(int type, int type2)
{
	if (type < type2)
		return type2Names[29 - type2][type];
	else
		return type2Names[29 - type][type2];
}

void LicenseBoardRand::getLayout(bool(&layout)[24][24], LicenseBoardData board)
{
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			layout[y][x] = board.board[y][x] != 0xFFFF;
		}
	}
}

void LicenseBoardRand::setRandLayout(bool(&layout)[24][24], int size)
{
	vector<unsigned short> possibleCells = vector<unsigned short>();
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			layout[y][x] = false;
		}
	}
	int x = Helpers::randInt(8, 16), y = Helpers::randInt(8, 16);
	layout[y][x] = true;

	for (int xOff = -1; xOff <= 1; xOff++)
	{
		for (int yOff = -1; yOff <= 1; yOff++)
		{
			if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
				continue;
			if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
				continue;
			possibleCells.push_back((y + yOff) * 24 + (x + xOff));
		}
	}

	for (int count = 1; count < size; count++)
	{
		int index = 0;
		do
		{
			index = Helpers::randInt(0, possibleCells.size() - 1);
			x = possibleCells[index] % 24, y = possibleCells[index] / 24;
		} while (Helpers::randInt(0, 99) < 100 - 20 * surroundingSpots(layout, x, y));
		layout[y][x] = true;
		possibleCells.erase(possibleCells.begin() + index);
		for (int xOff = -1; xOff <= 1; xOff++)
		{
			for (int yOff = -1; yOff <= 1; yOff++)
			{
				if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
					continue;
				if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
					continue;
				if (layout[y + yOff][x + xOff])
					continue;
				if (find(possibleCells.begin(), possibleCells.end(), (y + yOff) * 24 + (x + xOff)) == possibleCells.end())
					possibleCells.push_back((y + yOff) * 24 + (x + xOff));
			}
		}
	}
}

void LicenseBoardRand::setMazeLayout(bool(&layout)[24][24], vector<int> &shortcutLocs, int size, int shortcutSpots)
{
	vector<unsigned short> possibleCells = vector<unsigned short>();
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			layout[y][x] = false;
		}
	}
	int x = Helpers::randInt(8, 16), y = Helpers::randInt(8, 16);
	layout[y][x] = true;

	for (int xOff = -1; xOff <= 1; xOff++)
	{
		for (int yOff = -1; yOff <= 1; yOff++)
		{
			if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
				continue;
			if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
				continue;
			possibleCells.push_back((y + yOff) * 24 + (x + xOff));
		}
	}

	for (int count = 1; count < size; count++)
	{
		int index = 0, tries = 0, spots;
		while (true)
		{
			index = Helpers::randInt(0, possibleCells.size() - 1);
			x = possibleCells[index] % 24, y = possibleCells[index] / 24;
			spots = surroundingSpots(layout, x, y);
			tries++;
			if (spots == 1 || tries >= 100 && spots == 2 || tries >= 200 && spots >= 3)
				break;
		}
		layout[y][x] = true;
		possibleCells.erase(possibleCells.begin() + index);
		for (int xOff = -1; xOff <= 1; xOff++)
		{
			for (int yOff = -1; yOff <= 1; yOff++)
			{
				if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
					continue;
				if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
					continue;
				if (layout[y + yOff][x + xOff])
					continue;
				if (find(possibleCells.begin(), possibleCells.end(), (y + yOff) * 24 + (x + xOff)) == possibleCells.end())
					possibleCells.push_back((y + yOff) * 24 + (x + xOff));
			}
		}
	}

	int spots;
	while (shortcutLocs.size() < shortcutSpots)
	{
		x = Helpers::randInt(0, 23), y = Helpers::randInt(0, 23);
		if (layout[y][x])
			continue;
		spots = surroundingSpots(layout, x, y);
		if (spots > 1 && find(shortcutLocs.begin(), shortcutLocs.end(), (y) * 24 + (x)) == shortcutLocs.end())
			shortcutLocs.push_back(y * 24 + x);
	}
}

int LicenseBoardRand::surroundingSpots(bool(&layout)[24][24], int x, int y)
{
	int surroundingSpots = 0;

	for (int xOff = -1; xOff <= 1; xOff++)
	{
		for (int yOff = -1; yOff <= 1; yOff++)
		{
			if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
				continue;
			if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
				continue;
			if (layout[y + yOff][x + xOff])
				surroundingSpots++;
		}
	}

	return surroundingSpots;
}

void LicenseBoardRand::assignLicenses(LicenseBoardData &board, vector<unsigned short> data, bool * layout, vector<int> shortcuts)
{

	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			if (layout[y * 24 + x])
			{
				int index;
				do
				{
					index = Helpers::randInt(0, data.size() - 1);
				} while (shortcuts.size() > 0 && (data[index] <= 0x001E || data[index] == 0x0168));
				board.board[y][x] = data[index];
				data.erase(data.begin() + index);
			}
			else
				board.board[y][x] = 0xFFFF;
		}
	}
	for (int i = 0; i < shortcuts.size(); i++)
	{
		int x = shortcuts[i] % 24, y = shortcuts[i] / 24;
		int index = Helpers::randInt(0, data.size() - 1);
		board.board[y][x] = data[index];
		data.erase(data.begin() + index);
	}
}

void LicenseBoardRand::assignLoHiLicenses(LicenseBoardData &board, vector<unsigned short> data, bool * layout, vector<int> shortcuts)
{
	vector<unsigned short> shortcutLicenses = vector<unsigned short>();
	if (shortcuts.size() > 0)
	{
		for (int i = data.size() - 1; i >= 0; i--)
		{
			if (data[i] <= 0x001E || data[i] == 0x0168)
			{
				shortcutLicenses.push_back(data[i]);
				data.erase(data.begin() + i);
			}
		}
	}
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			board.board[y][x] = 0xFFFF;
		}
	}
	int pathBoard[24][24];
	int xEssentials, yEssentials;
	do
	{
		xEssentials = Helpers::randInt(0, 23);
		yEssentials = Helpers::randInt(0, 23);
	} while (!layout[yEssentials * 24 + xEssentials]);
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			if (x == xEssentials && y == yEssentials)
				pathBoard[y][x] = 0;
			else
				pathBoard[y][x] = (layout[y * 24 + x] ? 9999 : -1);
		}
	}
	vector<int> posToCheck = vector<int>();
	posToCheck.push_back(yEssentials * 24 + xEssentials);
	board.board[yEssentials][xEssentials] = 31;
	ptrdiff_t posEssentials = find(data.begin(), data.end(), 31) - data.begin();
	data.erase(data.begin() + posEssentials);
	while (posToCheck.size() > 0)
	{
		int x = posToCheck[posToCheck.size() - 1] % 24;
		int y = posToCheck[posToCheck.size() - 1] / 24;

		posToCheck.erase(posToCheck.end() - 1);

		for (int xOff = -1; xOff <= 1; xOff++)
		{
			for (int yOff = -1; yOff <= 1; yOff++)
			{
				if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
					continue;
				if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0) || (x + xOff == xEssentials && y + yOff == yEssentials))
					continue;
				if (pathBoard[y + yOff][x + xOff] > pathBoard[y][x] + 1 && find(posToCheck.begin(), posToCheck.end(), (y + yOff) * 24 + (x + xOff)) == posToCheck.end())
				{
					posToCheck.push_back((y + yOff) * 24 + x + xOff);
					pathBoard[y + yOff][x + xOff] = pathBoard[y][x] + 1;
				}
			}
		}
	}

	int distIndex = 1;
	while(data.size() > 0)
	{
		for (int x = 0; x < 24; x++)
		{
			bool end = false;
			for (int y = 0; y < 24; y++)
			{
				if (pathBoard[y][x] == distIndex)
				{
					board.board[y][x] = data[0];
					data.erase(data.begin());
					if (data.size() == 0)
					{
						end = true;
						break;
					}
				}
			}
			if (end)
				break;
		}
		distIndex++;
	}
	for (int i = 0; i < shortcuts.size(); i++)
	{
		int x = shortcuts[i] % 24, y = shortcuts[i] / 24;
		int index = Helpers::randInt(0, shortcutLicenses.size() - 1);
		board.board[y][x] = shortcutLicenses[index];
		shortcutLicenses.erase(shortcutLicenses.begin() + index);
	}
}

void LicenseBoardRand::sortLicenses(vector<unsigned short>& data)
{
	if (LicenseRand::licenseData[0].unknown == 0x42)
	{
		bool swapped = true;
		while (swapped)
		{
			swapped = false;
			for (int i = 0; i < data.size() - 1; i++)
			{
				if (LicenseRand::licenseData[data[i + 1]].lpCost < LicenseRand::licenseData[data[i]].lpCost)
				{
					swapped = true;
					swap(data[i], data[i + 1]);
				}
			}
		}
	}
}

bool LicenseBoardRand::pathToLicense(LicenseBoardData & board, int id, int &numPathable)
{
	int pathBoard[24][24];
	int xBelias = -1, yBelias = -1;
	vector<int> posToCheck = vector<int>();
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			unsigned short type = board.board[y][x];
			if (type == 0xFFFF || (type <= 0x001E && type != id) || (id != 0x0168 && type == 0x0168))
				pathBoard[y][x] = -1;
			else if (type == 0x001F)
			{
				pathBoard[y][x] = 0;
				posToCheck.push_back(y * 24 + x);
			}
			else
				pathBoard[y][x] = 0;
			if (type == id)
			{
				xBelias = x;
				yBelias = y;
			}
		}
	}

	if (xBelias == -1 && yBelias == -1)
		return true;
	numPathable = 0;

	while (posToCheck.size() > 0)
	{
		int x = posToCheck[posToCheck.size() - 1] % 24;
		int y = posToCheck[posToCheck.size() - 1] / 24;

		pathBoard[y][x] = 1;
		numPathable++;
		posToCheck.erase(posToCheck.end() - 1);

		for (int xOff = -1; xOff <= 1; xOff++)
		{
			for (int yOff = -1; yOff <= 1; yOff++)
			{
				if (x + xOff < 0 || x + xOff >= 24 || y + yOff < 0 || y + yOff >= 24)
					continue;
				if ((abs(xOff) == 1 && yOff != 0) || (abs(yOff) == 1 && xOff != 0) || (xOff == 0 && yOff == 0))
					continue;
				if (pathBoard[y + yOff][x + xOff] == 0)
					posToCheck.push_back((y + yOff) * 24 + x + xOff);
			}
		}
	}	
	bool valid = pathBoard[yBelias][xBelias] == 1;
	return valid;
}
