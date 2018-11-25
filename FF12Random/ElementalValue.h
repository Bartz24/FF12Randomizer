#pragma once
#include <vector>
#include "Helpers.h"

using namespace std;
enum class Element
{
	Fire = 0x01,
	Lightning = 0x02,
	Ice = 0x04,
	Earth = 0x08,
	Water = 0x10,
	Wind = 0x20,
	Holy = 0x40,
	Dark = 0x80
};

class ElementalValue
{
public:
	ElementalValue();
	ElementalValue(int num);
	~ElementalValue();
	vector<Element> elements;
	int getNumValue();
	void addRandomElement();
	bool hasElement(Element element);
};

