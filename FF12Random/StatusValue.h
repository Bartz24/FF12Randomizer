#pragma once
#include <vector>

using namespace std;
enum class Status1
{
	Death = 0x01,
	Stone = 0x02,
	Petrify = 0x04,
	Stop = 0x08,
	Sleep = 0x10,
	Confuse = 0x20,
	Doom = 0x40,
	Blind = 0x80
};
enum class Status2
{
	Poison = 0x01,
	Silence = 0x02,
	Sap = 0x04,
	Oil = 0x08,
	Reverse = 0x10,
	Disable = 0x20,
	Immobilize = 0x40,
	Slow = 0x80
};
enum class Status3
{
	Disease = 0x01,
	Lure = 0x02,
	Protect = 0x04,
	Shell = 0x08,
	Haste = 0x10,
	Bravery = 0x20,
	Faith = 0x40,
	Reflect = 0x80
};
enum class Status4
{
	Vanish = 0x01,
	Regen = 0x02,
	Float = 0x04,
	Berserk = 0x08,
	Bubble = 0x10,
	CriticalHP = 0x20,
	Libra = 0x40,
	XZone = 0x80
};

class StatusValue
{
public:
	StatusValue();
	StatusValue(int num1, int num2, int num3, int num4);
	~StatusValue();
	vector<Status1> status1;
	vector<Status2> status2;
	vector<Status3> status3;
	vector<Status4> status4;
	int getNumValue(int group);
	void addRandomStatus();
	bool hasStatus(int status, int group);
};

