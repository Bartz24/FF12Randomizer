#pragma once
class LicenseBoardData
{
public:
	LicenseBoardData();
	~LicenseBoardData();
	char header[8];
	unsigned short board[24][24];
};

