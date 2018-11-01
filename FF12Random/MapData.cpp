#include "stdafx.h"
#include "MapData.h"


MapData::MapData()
{
}


MapData::~MapData()
{
}

string MapData::getFileName()
{
	return Helpers::mainPS2DataFolder + "\\plan_master\\us\\plan_map\\" + fileName.substr(0, 5) + "\\" + fileName + "\\global\\" + fileName + ".ebp";
}
