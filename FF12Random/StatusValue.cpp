#include "stdafx.h"
#include "StatusValue.h"


StatusValue::StatusValue()
{
}

StatusValue::StatusValue(unsigned int num)
{
	for (int i = 0; i < 32; i++)
	{
		unsigned int flag = (unsigned int)pow(2, i);
		if ((num & flag) == flag)
			statuses.push_back(Status(*(reinterpret_cast<int*>(&flag))));
	}
}


StatusValue::~StatusValue()
{
}

unsigned int StatusValue::getNumValue()
{
	unsigned int num = 0;
	for (int i = 0; i < statuses.size(); i++)
		num += unsigned int(statuses[i]);
	return num;
}

void StatusValue::addRandomStatus(initializer_list<Status> blacklist)
{
	vector<Status> blStatuses;
	for (auto &s : blacklist)
	{
		blStatuses.push_back(s);
	}
	if (statuses.size() == 32 - blacklist.size())
		return;
	Status status;
	do
	{
		status = Status(unsigned int(pow(2, Helpers::randInt(0, 32))));
	} while (hasStatus(status) || find(blacklist.begin(), blacklist.end(), status) != blacklist.end());
	statuses.push_back(status);
}


bool StatusValue::hasStatus(Status status)
{
	return find(statuses.begin(), statuses.end(), status) != statuses.end();
}