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
	static bool usingSingleBoard;
	LicenseBoardRand();
	~LicenseBoardRand();
	void load();
	void process(FlagGroup flags);
	void save();
	void useSingleBoard();
	vector<unsigned short> getLicenses(LicenseBoardData board);
	void setRandLicenses(vector<unsigned short> &data, FlagGroup flags);
	void getLayout(bool(&layout)[24][24], LicenseBoardData board);
	void setRandLayout(bool (&layout)[24][24], int size);
	void setMazeLayout(bool(&layout)[24][24], vector<int> &shortcutLocs, int size, int shortcutSpots);
	int surroundingSpots(bool(&layout)[24][24], int x, int y);
	void assignLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout, vector<int> shortcuts);
	void assignLoHiLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout, vector<int> shortcuts);
	void sortLicenses(vector<unsigned short> &data);
	bool pathToLicense(LicenseBoardData &board, int id, int &numPathable);
};

