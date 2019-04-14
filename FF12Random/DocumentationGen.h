#pragma once
#include <string>
#include <vector>
#include <regex>
#include <tuple>

#include "HTMLDocument.h"
#include "RenameMain.h"
#include "TreasureRand.h"
#include "EnemyRand.h"

using namespace std;

class DocumentationGen
{
private:
	RenameMain rename;
	string folderName, seed, flags;
	HTMLDocument bazaarPage;
	HTMLDocument treasurePage;
	HTMLDocument equipPage;
	HTMLDocument enemyPage;
	HTMLDocument headerData;
	HTMLDocument mainPage;
	void addHeaderData();
	void addBazaarRecipeData();
	void addTreasureData();
	void addEquipData();
	void addAccessoryData();
	void addAmmoData();
	void addArmorData();
	void addShieldData();
	void addWeaponData();
	void addMainData();
	void addEnemyData();
	string getAreaName(string area);
	tuple<string, string, string> getLicenseData(int id);
	string getNameFromID(int id);
	string getMonographName(int id);
	string getArmorEffectDesc(int id);
public:
	DocumentationGen();
	DocumentationGen(RenameMain rename, string folderName, string seed,string flags);
	~DocumentationGen();
	void process();
	void save();
};

