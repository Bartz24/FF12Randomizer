#include "stdafx.h"
#include "MusicData.h"


MusicData::MusicData()
{
}

MusicData::MusicData(string p)
{
	path = p;
	types = Helpers::split(p, '.');
	types.erase(types.begin());
}


MusicData::~MusicData()
{
}

void MusicData::setTypes(string typesString)
{
	types = Helpers::split(typesString, '.');
}
