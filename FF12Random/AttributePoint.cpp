#include "stdafx.h"
#include "AttributePoint.h"


int AttributePoint::getActualValue()
{
	switch (type)
	{
	case AttributeType::HP:
		return round(pointAmount * hpMult);
	case AttributeType::MP:
		return round(pointAmount * mpMult);
	case AttributeType::STR:
	case AttributeType::VIT:
	case AttributeType::MAG:
	case AttributeType::SPD:
		return round(pointAmount);
	}
	return 0;
}

AttributePoint::AttributePoint()
{
}

AttributePoint::AttributePoint(AttributeType type, int value)
{
	this->type = type;
	switch (type)
	{
	case AttributeType::HP:
		pointAmount = float(value) / hpMult;
		break;
	case AttributeType::MP:
		pointAmount = float(value) / mpMult;
		break;
	case AttributeType::STR:
	case AttributeType::VIT:
	case AttributeType::MAG:
	case AttributeType::SPD:
		pointAmount = float(value);
		break;
	}
}


AttributePoint::~AttributePoint()
{
}
