#pragma once

#include "ARDData.h"
#include "FlagGroup.h"
#include "ItemRand.h"
#include "MagicRand.h"
#include "EquipRand.h"

class EnemyRand
{
public:
	static vector<ARDData> ardData;
	vector<int> itemIDs = vector<int>();
	EnemyRand();
	~EnemyRand();
	void load();
	void save();
	void process(FlagGroup flags);
	void modifyValue(int value, unsigned int &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue = false);
	void modifyValue(int value, unsigned short &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue = false);
	void modifyValue(int value, unsigned char &dataVal, bool inverse, double &sizeMult, double &expMult, int minN, int maxN, bool lvValue = false);
	void randDrops(ARDSec2 &sec2Data, ARDData aData, int value);
	void randSteal(ARDSec2 &sec2Data, ARDData aData, int value);
	void randPoach(ARDSec2 &sec2Data, ARDData aData, int value);
	void randMonographRate(ARDSec2 &sec2Data, int value);
	void randMonographType(ARDSec2 &sec2Data);
	void randMonographItem(ARDSec2 &sec2Data, ARDData aData, int value);
	void randCanopicJarRate(ARDSec2 &sec2Data, int value);
	void randCanopicJarType(ARDSec2 &sec2Data);
	void randCanopicJarItem(ARDSec2 &sec2Data, ARDData aData, int value);
	void buffTrialMode(ARDSec3 &sec3Data, ARDData aData, int value);
	int getItem(std::vector<int> &data, int center, int std, int value, bool remove);
	int getCost(int itemID);
	bool canAddItem(int actualCost, int center, int std, int value);
	void addRangeToVector(vector<int> &data, int low, int high);
	void randElements(ARDSec1 &sec1Data, int value);
	void setElement(unsigned char &num);
	void setElementMultiple(unsigned char &num, int chance);
};

