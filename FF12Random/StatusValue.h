#pragma once
#include <vector>
#include "Helpers.h"
#include "FlagGroup.h"

using namespace std;
enum class Status
{
	/*Death = 0x01000000,
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
	XZone = 0x00000080*/
	Death = 0x00000001,
	Stone = 0x00000002,
	Petrify = 0x00000004,
	Stop = 0x00000008,
	Sleep = 0x00000010,
	Confuse = 0x00000020,
	Doom = 0x00000040,
	Blind = 0x00000080,
	Poison = 0x00000100,
	Silence = 0x00000200,
	Sap = 0x00000400,
	Oil = 0x00000800,
	Reverse = 0x00001000,
	Disable = 0x00002000,
	Immobilize = 0x00004000,
	Slow = 0x00008000,
	Disease = 0x00010000,
	Lure = 0x00020000,
	Protect = 0x00040000,
	Shell = 0x00080000,
	Haste = 0x00100000,
	Bravery = 0x00200000,
	Faith = 0x00400000,
	Reflect = 0x00800000,
	Vanish = 0x01000000,
	Regen = 0x02000000,
	Float = 0x04000000,
	Berserk = 0x08000000,
	Bubble = 0x10000000,
	CriticalHP = 0x20000000,
	Libra = 0x40000000,
	XZone = 0x80000000
};

class StatusValue
{
private:
	static char flagMappings[32];
public:
	static int onEquipWeights[32];
	static int onHitWeights[32];
	static int immuneWeights[32];
	StatusValue();
	StatusValue(unsigned int num);
	~StatusValue();
	vector<Status> statuses;
	unsigned int getNumValue();
	void addRandomStatus(int* weights);
	bool hasStatus(Status status);
	void removeStatus(Status status);
	static void readFlags(static int* weights, FlagGroup flags);
};

