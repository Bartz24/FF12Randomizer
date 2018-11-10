#pragma once
#include <string>
#include <vector>

#include "RenameMain.h"
#include "TreasureRand.h"

using namespace std;

class DocumentationGen
{
private:
	RenameMain rename;
	vector<string> document = vector<string>();
	void generateHTMLHead();
	void addHeader1(string header);
	void addHeader2(string header);
	void addText(string text);
	void addTable(vector<string> categories, vector<vector<string>> data);
	void addBazaarRecipeData();
	void addTreasureData();
public:
	DocumentationGen();
	DocumentationGen(RenameMain rename);
	~DocumentationGen();
	void process();
	void save(string folder, long seed);
};

