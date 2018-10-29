#include "stdafx.h"
#include "Helpers.h"
#include <Windows.h>

string Helpers::language = "us";
string Helpers::mainPS2DataFolder = "";

Helpers::Helpers()
{
}


Helpers::~Helpers()
{
}

std::string Helpers::loadFile()
{

	std::string fileName = "";
	do
	{
		if (fileName != "")
			cout << "Sorry, that folder could not be accessed or caused an error" << endl;
		cout << "Drag folder: ";
		getline(cin, fileName);
		if (fileName != "")
		{
			if (fileName.substr(0, 1) == "\"")
				fileName.replace(0, 1, "");
			if (fileName.substr(fileName.length() - 1, 1) == "\"")
				fileName.replace(fileName.length() - 1, 1, "");
			cout << fileName << endl;
		}
	} while (!fileExists(fileName));
	return fileName;
}

bool Helpers::fileExists(std::string fileName)
{
	DWORD ftyp = GetFileAttributesA(fileName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return true;    // this is not a directory!
}

bool Helpers::getYesNo(string question)
{
	string answer = "";
	do
	{
		cout << question;
		getline(cin, answer);
	} while (answer != "y" && answer != "n");

	return answer == "y";
}

string Helpers::readFlags(string possibleFlags)
{
	string answer = "";
	bool containsInvalidFlags;
	do
	{
		containsInvalidFlags = false;
		cout << "Put all the flags you want to use (leave blank for all): ";
		getline(cin, answer);

		vector<char> chars(answer.begin(), answer.end());

		for (int i = 0; i < chars.size(); i++)
		{
			if (possibleFlags.find(chars[i]) == string::npos)
			{
				containsInvalidFlags = true;
				cout << "Sorry, you put in an invalid flag" << endl;
				break;
			}
		}

		if (chars.size() == 0)
			answer = possibleFlags;

	} while (containsInvalidFlags);
	return answer;
}
