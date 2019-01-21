#pragma once

#include "Helpers.h"

enum MonographType
{
	Sage = 0x8065,
	Hunter = 0x8066,
	Knight = 0x8067,
	Dragoon = 0x8068,
	Mage = 0x8069,
	Warmage = 0x806A,
	Scholar = 0x806B,
	CanopicJar = 0x806C
};

class ARDData;

class ARDSec1
{
public:
	unsigned char unknown[84];
	unsigned int model; // 00-03
	unsigned short rangeDetect; // 22-23
	unsigned char absorbElement; // 29
	unsigned char halfElement; // 2A
	unsigned char immuneElement; // 2B
	unsigned char weakElement; // 2C
	unsigned char boostElement; // 2D
	unsigned short bestiaryNum; // 52-53
	ARDSec1();
	ARDSec1(char data[84]);
	~ARDSec1();
};

class ARDSec3
{
public:
	unsigned char unknown[56];
	unsigned short cp; // 00-01
	unsigned int hp; // 20-23
	unsigned short mp; // 24-25
	unsigned char str; // 26
	unsigned char mag; // 27
	unsigned char vit; // 28
	unsigned char spd; // 29
	unsigned char eva; // 2A
	unsigned char def; // 2B
	unsigned char mRes; // 2C
	unsigned char atk; // 2D
	unsigned char lp; // 2F
	unsigned int exp; // 34-37
	double sizeMult = 1;
	double expMult = 1;
	ARDSec3();
	ARDSec3(char data[56]);
	~ARDSec3();
};

class ARDSec4
{
public:
	unsigned char unknown[56];
	unsigned short cp; // 00-01
	unsigned int hp; // 20-23
	unsigned short mp; // 24-25
	unsigned char str; // 26
	unsigned char mag; // 27
	unsigned char vit; // 28
	unsigned char spd; // 29
	unsigned char eva; // 2A
	unsigned char def; // 2B
	unsigned char mRes; // 2C
	unsigned char atk; // 2D
	unsigned char lp; // 2F
	unsigned int exp; // 34-37
	double sizeMult = 1;
	double expMult = 1;
	ARDSec4();
	ARDSec4(char data[56]);
	~ARDSec4();
};

class ARDSec2
{
public:
	unsigned char unknown[88];
	unsigned char sec1Link; // 00
	unsigned short name; // 08-09
	unsigned short sizeX; // 0A-0B
	unsigned short sizeY; // 0C-0D
	unsigned short sizeZ; // 0E-0F
	unsigned short weapon; // 16-17
	unsigned int initHP; // 18-1B
	unsigned short offHand; // 1C-1D
	unsigned char sec3Link; // 22
	unsigned char sec4Link; // 24
	unsigned short drop40; // 28-29
	unsigned short drop25; // 2A-2B
	unsigned short drop05; // 2C-2D
	unsigned short drop01; // 2E-2F
	unsigned short drop100; // 30-31
	unsigned short steal55; // 32-33
	unsigned short steal10; // 34-35
	unsigned short steal03; // 36-37
	unsigned char monographDropRate; // 42
	unsigned char canopicJarDropRate; // 43
	unsigned short poach95; // 44-45
	unsigned short poach05; // 46-47
	unsigned short monographType; // 48-49
	unsigned short monographDrop; // 4A-4B
	unsigned short canopicJarType; // 4C-4D
	unsigned short canopicJarDrop; // 4E-4F
	unsigned char aiSet; // 50
	ARDSec2();
	ARDSec2(char data[88]);
	~ARDSec2();

	ARDSec1 getARDSec1(ARDData data);
	ARDSec3 getARDSec3(ARDData data);
	ARDSec4 getARDSec4(ARDData data);
};

class ARDData
{
public:

	string areaName;

	vector<ARDSec1> section1Data = vector<ARDSec1>();
	vector<ARDSec2> section2Data = vector<ARDSec2>();
	vector<ARDSec3> section3Data = vector<ARDSec3>();
	vector<ARDSec4> section4Data = vector<ARDSec4>();

	int section1Adrs;
	int section2Adrs;
	int section3Adrs;
	int section4Adrs;

	ARDData();
	ARDData(string areaName, char data[], int size);
	~ARDData();
};

