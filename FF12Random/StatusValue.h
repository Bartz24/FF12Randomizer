#pragma once
#include <vector>
#include "Helpers.h"

using namespace std;
enum class Status
{
	Death = 0x01000000,
	Stone = 0x02000000,
	Petrify = 0x04000000,
	Stop = 0x08000000,
	Sleep = 0x10000000,
	Confuse = 0x20000000,
	Doom = 0x40000000,
	Blind = 0x80000000,
	Poison = 0x00010000,
	Silence = 0x00020000,
	Sap = 0x00040000,
	Oil = 0x00080000,
	Reverse = 0x00100000,
	Disable = 0x00200000,
	Immobilize = 0x00400000,
	Slow = 0x00800000,
	Disease = 0x00000100,
	Lure = 0x00000200,
	Protect = 0x00000400,
	Shell = 0x00000800,
	Haste = 0x00001000,
	Bravery = 0x00002000,
	Faith = 0x00004000,
	Reflect = 0x00008000,
	Vanish = 0x00000001,
	Regen = 0x00000002,
	Float = 0x00000004,
	Berserk = 0x00000008,
	Bubble = 0x00000010,
	CriticalHP = 0x00000020,
	Libra = 0x00000040,
	XZone = 0x00000080
};

class StatusValue
{
public:
	StatusValue();
	StatusValue(unsigned int num);
	~StatusValue();
	vector<Status> statuses;
	unsigned int getNumValue();
	void addRandomStatus(initializer_list<Status> blacklist);
	bool hasStatus(Status status);
};

