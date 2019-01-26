#pragma once
#include "Helpers.h"

enum class AttributeDataOffset
{
	us = 0x001218C
};

class AttributeData
{
public:
	static AttributeDataOffset getDataIndex();
	unsigned short hp; // 00-01
	unsigned short mp; // 02-03
	unsigned char str; // 04
	unsigned char mag; // 05
	unsigned char vit; // 06
	unsigned char spd; // 07
	unsigned int autoStatus; // 08-0B
	unsigned int immuneStatus; // 0C-0F
	unsigned char absorbElement; // 10
	unsigned char immuneElement; // 11
	unsigned char halfElement; // 12
	unsigned char weakElement; // 13
	unsigned char boostElement; // 14
	unsigned char empty1; // 15
	unsigned char empty2; // 16
	unsigned char empty3; // 17
	AttributeData();
	AttributeData(char data[24]);
	~AttributeData();
};