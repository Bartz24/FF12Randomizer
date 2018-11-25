#include "stdafx.h"
#include "StartGambitData.h"


StartGambitDataOffset StartGambitData::getDataIndex()
{
	string language = Helpers::language;
	if (language == "us")
		return StartGambitDataOffset::us;
	return StartGambitDataOffset::us;
}

StartGambitData::StartGambitData(char data[64])
{
	for (int i = 0; i < 64; i++)
	{
		this->unknown[i] = data[i];
	}
	for (int i = 0; i < 12; i++)
	{
		char gambit[] = { data[i * 2] , data[0x01 + i * 2] };
		this->gambits[i] = *reinterpret_cast<unsigned short*>(gambit);
		char act[] = { data[0x20 + i * 2] , data[0x21 + i * 2] };
		this->actions[i] = *reinterpret_cast<unsigned short*>(act);
	}
}

StartGambitData::StartGambitData()
{
}


StartGambitData::~StartGambitData()
{
}
