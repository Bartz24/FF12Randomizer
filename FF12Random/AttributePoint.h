#pragma once

#include "Helpers.h"

enum class AttributeType {
	HP,
	MP,
	STR,
	VIT,
	MAG,
	SPD
};

class AttributePoint
{

private:
	const float hpMult = 75.f, mpMult = 13.f;

public:
	AttributeType type;
	float pointAmount;

	int getActualValue();

	AttributePoint();
	AttributePoint(AttributeType type, int value);
	~AttributePoint();
};

