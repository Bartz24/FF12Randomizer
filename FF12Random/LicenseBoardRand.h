#pragma once
#include <string>
#include <vector>
#include "LicenseData.h"
#include "LicenseBoardData.h"
#include "LicenseRand.h"

class LicenseBoardRand
{
private:
	string folderName;
public:
	static LicenseBoardData boards[12];
	LicenseBoardRand();
	~LicenseBoardRand();
	void load();
	string process(string preset);
	void save();
	vector<unsigned short> getLicenses(LicenseBoardData board);
	void setRandLicenses(vector<unsigned short> &data, string flags);
	void getLayout(bool(&layout)[24][24], LicenseBoardData board);
	void setRandLayout(bool (&layout)[24][24], int size);
	void assignLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout);
	void assignLoHiLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout);
	void sortLicenses(vector<unsigned short> &data);
	bool pathToBelias(LicenseBoardData &board);
};

