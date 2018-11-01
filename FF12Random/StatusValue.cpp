#include "stdafx.h"
#include "StatusValue.h"


StatusValue::StatusValue()
{
}

StatusValue::StatusValue(int num1, int num2, int num3, int num4)
{
		if ((num1 & 0x01) == 0x01)
			status1.push_back(Status1(0x01)); 
		if ((num1 & 0x02) == 0x02)
			status1.push_back(Status1(0x02)); 
		if ((num1 & 0x04) == 0x04)
			status1.push_back(Status1(0x04));
		if ((num1 & 0x08) == 0x08)
			status1.push_back(Status1(0x08));
		if ((num1 & 0x10) == 0x10)
			status1.push_back(Status1(0x10));
		if ((num1 & 0x20) == 0x20)
			status1.push_back(Status1(0x20));
		if ((num1 & 0x40) == 0x40)
			status1.push_back(Status1(0x40));
		if ((num1 & 0x80) == 0x80)
			status1.push_back(Status1(0x80));

		if ((num2 & 0x01) == 0x01)
			status2.push_back(Status2(0x01));
		if ((num2 & 0x02) == 0x02)
			status2.push_back(Status2(0x02));
		if ((num2 & 0x04) == 0x04)
			status2.push_back(Status2(0x04));
		if ((num2 & 0x08) == 0x08)
			status2.push_back(Status2(0x08));
		if ((num2 & 0x10) == 0x10)
			status2.push_back(Status2(0x10));
		if ((num2 & 0x20) == 0x20)
			status2.push_back(Status2(0x20));
		if ((num2 & 0x40) == 0x40)
			status2.push_back(Status2(0x40));
		if ((num2 & 0x80) == 0x80)
			status2.push_back(Status2(0x80));

		if ((num3 & 0x01) == 0x01)
			status3.push_back(Status3(0x01));
		if ((num3 & 0x02) == 0x02)
			status3.push_back(Status3(0x02));
		if ((num3 & 0x04) == 0x04)
			status3.push_back(Status3(0x04));
		if ((num3 & 0x08) == 0x08)
			status3.push_back(Status3(0x08));
		if ((num3 & 0x10) == 0x10)
			status3.push_back(Status3(0x10));
		if ((num3 & 0x20) == 0x20)
			status3.push_back(Status3(0x20));
		if ((num3 & 0x40) == 0x40)
			status3.push_back(Status3(0x40));
		if ((num3 & 0x80) == 0x80)
			status3.push_back(Status3(0x80));

		if ((num4 & 0x01) == 0x01)
			status4.push_back(Status4(0x01));
		if ((num4 & 0x02) == 0x02)
			status4.push_back(Status4(0x02));
		if ((num4 & 0x04) == 0x04)
			status4.push_back(Status4(0x04));
		if ((num4 & 0x08) == 0x08)
			status4.push_back(Status4(0x08));
		if ((num4 & 0x10) == 0x10)
			status4.push_back(Status4(0x10));
		if ((num4 & 0x20) == 0x20)
			status4.push_back(Status4(0x20));
		if ((num4 & 0x40) == 0x40)
			status4.push_back(Status4(0x40));
		if ((num4 & 0x80) == 0x80)
			status4.push_back(Status4(0x80));
}


StatusValue::~StatusValue()
{
}

int StatusValue::getNumValue(int group)
{
	int num = 0;
	switch (group)
	{
	case 1:
		for (int i = 0; i < status1.size(); i++)
			num += int(status1[i]);
		return num;
	case 2:
		for (int i = 0; i < status2.size(); i++)
			num += int(status2[i]);
		return num;
	case 3:
		for (int i = 0; i < status3.size(); i++)
			num += int(status3[i]);
		return num;
	case 4:
		for (int i = 0; i < status4.size(); i++)
			num += int(status4[i]);
		return num;
	}
}

void StatusValue::addRandomStatus()
{
	if (status1.size() == 8 && status2.size() == 8 && status3.size() == 8 && status4.size() == 8)
		return;
	int status, group, chance;
	do
	{
		status = int(pow(2, rand() % 8));
		chance = rand() % 100;
		group = chance < 38 ? 1 : chance < 76 ? 2 : chance < 90 ? 3 : 4;
	} while (hasStatus(status, group));

	if (group == 4 && status == 0x20)
		group *= 1;

	switch (group)
	{
	case 1:
		status1.push_back(Status1(status));
		return;
	case 2:
		status2.push_back(Status2(status));
		return;
	case 3:
		status3.push_back(Status3(status));
		return;
	case 4:
		status4.push_back(Status4(status));
		return;
	}
}


bool StatusValue::hasStatus(int status, int group)
{
	if (status == 0x02 && group == 1 || status == 0x20 && group == 4)
		return true;
	switch (group)
	{
	case 1:
		return find(status1.begin(), status1.end(), Status1(status)) != status1.end();
	case 2:
		return find(status2.begin(), status2.end(), Status2(status)) != status2.end();
	case 3:
		return find(status3.begin(), status3.end(), Status3(status)) != status3.end();
	case 4:
		return find(status4.begin(), status4.end(), Status4(status)) != status4.end();
	}
}

int StatusValue::getNumStatuses()
{
	return status1.size() + status2.size() + status3.size() + status4.size();
}
