#include "stdafx.h"
#include "CharRename.h"


CharRename::CharRename()
{
}


CharRename::~CharRename()
{
}

void CharRename::load()
{
	string line;
	ifstream myfile("data\\menuNames.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 253; i++)
		{
			getline(myfile, line);
			data[i] = line;
		}
		myfile.close();
	}
}

void CharRename::save()
{
	ofstream myfile;
	myfile.open("menuNames.txt");
	for (int i = 0; i < 253; i++)
	{
		myfile << data[i];
		if (i < 252)
			myfile << endl;
	}
	myfile.close();
}

void CharRename::process(bool randEnemyNames)
{
	if (randEnemyNames)
		randomizeEnemyNames();

	string names[12] = { data[71], data[72], data[73], data[74], data[75], data[76], data[77], data[78], data[79], data[80],
	data[81], data[82] };
	for (int i = 0; i < 253; i++)
	{
		if (i >= 71 && i < 82)
		{
			switch (CharRand::names[i - 71])
			{
			case 0:
				data[i] = names[0];
				break;
			case 1:
				data[i] = names[4];
				break;
			case 2:
				data[i] = names[2];
				break;
			case 3:
				data[i] = names[1];
				break;
			case 4:
				data[i] = names[3];
				break;
			case 5:
				data[i] = names[5];
				break;
			case 6:
				data[i] = names[6] + "?";
				break;
			case 10:
				data[i] = names[7] + "?";
				break;
			case 11:
				data[i] = names[8] + "?";
				break;
			case 13:
				data[i] = names[9] + "?";
				break;
			case 16:
				data[i] = names[10] + "?";
				break;
			}
		}
		else if (i == 82)
		{
			switch (CharRand::names[4])
			{
			case 0:
				data[i] = names[0];
				break;
			case 2:
				data[i] = names[2];
				break;
			case 3:
				data[i] = names[1];
				break;
			case 4:
				data[i] = names[3];
				break;
			case 5:
				data[i] = names[5];
				break;
			}
		}
		else
			data[i] = ".IGNORE";
	}
	if (CharRand::names[0] != -1)
		fixGambitNames();
}
