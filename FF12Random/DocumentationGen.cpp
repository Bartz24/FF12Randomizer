#include "stdafx.h"
#include "DocumentationGen.h"


void DocumentationGen::generateHTMLHead()
{
	document.push_back("<head>");

	document.push_back("<style>");

	document.push_back("table {");
	document.push_back("font-family: arial, sans-serif;");
	document.push_back("border-collapse: collapse;");
	document.push_back("width: 100%;");
	document.push_back("}");

	document.push_back("td, th {");
	document.push_back("border: 1px solid #dddddd;");
	document.push_back("text-align: left;");
	document.push_back("padding: 8px;");
	document.push_back("}");

	document.push_back("tr:nth-child(even) {");
	document.push_back("background-color: #dddddd;");
	document.push_back("}");

	document.push_back("</style>");

	document.push_back("</head>");
}

void DocumentationGen::addHeader1(string header)
{
	document.push_back("<h1>" + header + "</h1>");
}

void DocumentationGen::addHeader2(string header)
{
	document.push_back("<h2>" + header + "</h2>");
}

void DocumentationGen::addText(string text)
{
}

void DocumentationGen::addTable(vector<string> categories, vector<vector<string>> data)
{
	document.push_back("<table>");

	document.push_back("<tr>");
	for (int i = 0; i < categories.size(); i++)
	{
		document.push_back("<th>" + categories[i] + "</th>");
	}
	document.push_back("</tr>");

	for (int i = 0; i < data.size(); i++)
	{
		document.push_back("<tr>");
		for (int entry = 0; entry < data[i].size(); entry++)
		{
			document.push_back("<th>" + (data[i])[entry] + "</th>");
		}
		document.push_back("</tr>");
	}

	document.push_back("</table>");
}

void DocumentationGen::addBazaarRecipeData()
{
	addHeader1("Bazaar Recipes");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Gil");
	cats.push_back("Loot 1");
	cats.push_back("Loot 2");
	cats.push_back("Loot 3");

	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 0; i < 128; i++)
	{
		vector<string> entry = vector<string>();
		if (rename.bRename.data[i] == ".IGNORE")
			entry.push_back("Monograph");
		else if (i == 127)
			entry.push_back("Canopic Jar");
		else
			entry.push_back(rename.bRename.data[i]);
		entry.push_back(to_string(ShopRand::bazaarData[i].cost));
		if (ShopRand::bazaarData[i].loot1Amt > 0)
			entry.push_back(rename.bRename.getNameFromID(ShopRand::bazaarData[i].loot1) + " x" + to_string(ShopRand::bazaarData[i].loot1Amt));
		else
			entry.push_back("-");

		if (ShopRand::bazaarData[i].loot2Amt > 0)
			entry.push_back(rename.bRename.getNameFromID(ShopRand::bazaarData[i].loot2) + " x" + to_string(ShopRand::bazaarData[i].loot2Amt));
		else
			entry.push_back("-");

		if (ShopRand::bazaarData[i].loot3Amt > 0)
			entry.push_back(rename.bRename.getNameFromID(ShopRand::bazaarData[i].loot3) + " x" + to_string(ShopRand::bazaarData[i].loot3Amt));
		else
			entry.push_back("-");
		data.push_back(entry);
	}
	addTable(cats, data);
}

void DocumentationGen::addTreasureData()
{
	addHeader1("Treasures");
	for (int map = 0; map < 279; map++)
	{
		addHeader2(TreasureRand::mapData[map].mapName);
		vector<string> cats = vector<string>();
		cats.push_back("Spawn Chance");
		cats.push_back("Gil Chance");
		cats.push_back("Normal Gil Amount");
		cats.push_back("Normal Item 1 - 50 %");
		cats.push_back("Normal Item 2 - 50 %");
		cats.push_back("\"Diamond Armlet\" Gil Amount");
		cats.push_back("\"Diamond Armlet\" Item 1 - 90 %");
		cats.push_back("\"Diamond Armlet\" Item 2 - 10 %");

		vector<vector<string>> data = vector<vector<string>>();
		for (int i = 0; i < TreasureRand::mapData[map].count; i++)
		{
			vector<string> entry = vector<string>();
			entry.push_back(to_string(int(TreasureRand::mapData[map].treasure[i].spawnChance)) + "%");
			entry.push_back(to_string(int(TreasureRand::mapData[map].treasure[i].gilChance)) + "%");
			entry.push_back(to_string(TreasureRand::mapData[map].treasure[i].gil1));
			entry.push_back(rename.bRename.getNameFromID(TreasureRand::mapData[map].treasure[i].common1));
			entry.push_back(rename.bRename.getNameFromID(TreasureRand::mapData[map].treasure[i].common2));
			entry.push_back(to_string(TreasureRand::mapData[map].treasure[i].gil2));
			entry.push_back(rename.bRename.getNameFromID(TreasureRand::mapData[map].treasure[i].rare1));
			entry.push_back(rename.bRename.getNameFromID(TreasureRand::mapData[map].treasure[i].rare2));

			data.push_back(entry);
		}
		addTable(cats, data);
	}
}

DocumentationGen::DocumentationGen()
{
}

DocumentationGen::DocumentationGen(RenameMain rename)
{
	this->rename = rename;
}


DocumentationGen::~DocumentationGen()
{
}

void DocumentationGen::process()
{
	document.push_back("<!DOCTYPE html>");
	document.push_back("<html>");

	generateHTMLHead();

	document.push_back("<body>");

	addBazaarRecipeData();

	addTreasureData();

	document.push_back("</body>");

	document.push_back("</html>");
}

void DocumentationGen::save(string folder, long seed)
{
	ofstream myfile;
	myfile.open(folder + "\\documentation.html");
	for (int i = 0; i < document.size(); i++)
	{
		myfile << document[i];
		if (i < document.size() - 1)
			myfile << endl;
	}
	myfile.close();
}
