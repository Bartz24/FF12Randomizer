#include "stdafx.h"
#include "LicenseBoardData.h"

LicenseBoardData::LicenseBoardData()
{
	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 24; y++)
		{
			board[y][x] = 0xFFFF;
		}
	}
	char header[8] = { 0x6C,0x69,0x63,0x64,0x18,0x00,0x18, 0x00 };

}


LicenseBoardData::~LicenseBoardData()
{
}
