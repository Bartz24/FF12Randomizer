#include "stdafx.h"
#include "LicenseBoardRand.h"

LicenseBoardData LicenseBoardRand::boards[12] = {};

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
}

void LicenseBoardRand::process()
{
	cout << "License Board Randomization Options:" << endl;
	cout << "\t a: Require all accessory licenses (may not contain accessories) to appear" << endl;
	cout << "\t b: Randomize layout of the board" << endl;
	cout << "\t e: Require all esper licenses to appear" << endl;
	cout << "\t g: Require all 10 gambit licenses to appear" << endl;
	cout << "\t l: Randomize licenses used on the board" << endl;
	cout << "\t s: Generate a board that generally goes from low LP around Essentials to high LP" << endl;
	string flags = Helpers::readFlags("abegls");
	for (int i = 0; i < 12; i++)
	{
		vector<unsigned short> licensesToUse = getLicenses(boards[i]);
		if (flags.find('l') != string::npos)
		{
			setRandLicenses(licensesToUse, flags);
		}
		if (flags.find('s') != string::npos)
		{
			sortLicenses(licensesToUse);
		}
		bool layout[24][24];
		if (flags.find('b') != string::npos)
		{
			setRandLayout(layout, licensesToUse.size());
		}
		else
			getLayout(layout, boards[i]);
		do
		{
			if (flags.find('s') != string::npos)
				assignLoHiLicenses(boards[i], licensesToUse, *layout);
			else
				assignLicenses(boards[i], licensesToUse, *layout);
		} while (!pathToBelias(boards[i]));
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

void LicenseBoardRand::setRandLicenses(vector<unsigned short> &data, string flags)
{
	vector<unsigned short> newData = vector<unsigned short>();
	newData.push_back( 31); //Essentials
	newData.push_back( 360); //Second Board
	newData.push_back( 18); //Belias
	if (flags.find('g') != string::npos) //Gambits
	{
		for (int i = 266; i < 276; i++)
		{
			newData.push_back(i);
		}
	}
	if (flags.find('e') != string::npos) //Espers
	{
		for (int i = 19; i < 31; i++)
		{
			newData.push_back(i);
		}
	}
	if (flags.find('a') != string::npos) //Accessories
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
		int index = rand() % possible.size();
		newData.push_back( possible[index]);
		possible.erase(possible.begin() + index);
	}
	data = newData;
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
	int x = rand() % 8 + 8, y = rand() % 8 + 8;
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
	int index = rand() % possibleCells.size();
	x = possibleCells[index] % 24, y = possibleCells[index] / 24;
	layout[y][x] = true;
	possibleCells.erase(possibleCells.begin() + index);
	int added = 0;
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
			{
				if (added == 0 || rand() % 20 < 100)
				{
					possibleCells.push_back((y + yOff) * 24 + (x + xOff));
					added++;
				}
			}
		}
	}
}
}

void LicenseBoardRand::assignLicenses(LicenseBoardData &board, vector<unsigned short> data, bool * layout)
{
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			if (layout[y * 24 + x])
			{
				int index = rand() % data.size();
				board.board[y][x] = data[index];
				data.erase(data.begin() + index);
			}
			else
				board.board[y][x] = 0xFFFF;
		}
	}
}

void LicenseBoardRand::assignLoHiLicenses(LicenseBoardData &board, vector<unsigned short> data, bool * layout)
{
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
		xEssentials = rand() % 24;
		yEssentials = rand() % 24;
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

bool LicenseBoardRand::pathToBelias(LicenseBoardData & board)
{
	int pathBoard[24][24];
	int xBelias, yBelias;
	vector<int> posToCheck = vector<int>();
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			unsigned short type = board.board[y][x];
			if (type == 0xFFFF || (type <= 0x001E && type != 0x0012) || type == 0x0168)
				pathBoard[y][x] = -1;
			else if (type == 0x001F)
			{
				pathBoard[y][x] = 0;
				posToCheck.push_back(y * 24 + x);
			}
			else
				pathBoard[y][x] = 0;
			if (type == 0x0012)
			{
				xBelias = x;
				yBelias = y;
			}
		}
	}

	while (posToCheck.size() > 0)
	{
		int x = posToCheck[posToCheck.size() - 1] % 24;
		int y = posToCheck[posToCheck.size() - 1] / 24;

		pathBoard[y][x] = 1;
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

	return pathBoard[yBelias][xBelias] == 1;
}
