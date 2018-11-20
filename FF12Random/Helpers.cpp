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

bool Helpers::fileExists(std::string fileName)
{
	DWORD ftyp = GetFileAttributesA(fileName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return true;    // this is not a directory!
}
