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
	static string type2Names[30][30];
public:
	static LicenseBoardData boards[12];
	static string newBoardNames[12];
	static int suggestedChars[12];
	static bool usingSingleBoard, type2;
	LicenseBoardRand();
	~LicenseBoardRand();
	void load();
	void process(FlagGroup flags);
	void save();
	void useSingleBoard();
	vector<unsigned short> getLicenses(LicenseBoardData board);
	void setRandLicenses(vector<unsigned short> &data, FlagGroup flags);
	void randomizeChars();
	void addForcedLicenses(int type, std::string &display, std::vector<unsigned short> &newData);
	void setForcedLicenseTypes(vector<unsigned short> &data, int type, int board, int type2 = -1);
	void getLayout(bool(&layout)[24][24], LicenseBoardData board);
	void setRandLayout(bool (&layout)[24][24], int size);
	void setMazeLayout(bool(&layout)[24][24], vector<int> &shortcutLocs, int size, int shortcutSpots);
	int surroundingSpots(bool(&layout)[24][24], int x, int y);
	void assignLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout, vector<int> shortcuts);
	void assignLoHiLicenses(LicenseBoardData &board, vector<unsigned short> data, bool* layout, vector<int> shortcuts);
	void sortLicenses(vector<unsigned short> &data);
	bool pathToLicense(LicenseBoardData &board, int id, int &numPathable);
};

