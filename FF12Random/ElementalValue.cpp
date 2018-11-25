#include "stdafx.h"
#include "ElementalValue.h"


ElementalValue::ElementalValue()
{
}

ElementalValue::ElementalValue(int num)
{	
	if (num >= 0x80)
	{
		elements.push_back(Element::Dark);
		num -= 0x80;
	}
	if (num >= 0x40)
	{
		elements.push_back(Element::Holy);
		num -= 0x40;
	}
	if (num >= 0x20)
	{
		elements.push_back(Element::Wind);
		num -= 0x20;
	}
	if (num >= 0x10)
	{
		elements.push_back(Element::Water);
		num -= 0x10;
	}
	if (num >= 0x08)
	{
		elements.push_back(Element::Earth);
		num -= 0x08;
	}
	if (num >= 0x04)
	{
		elements.push_back(Element::Ice);
		num -= 0x04;
	}
	if (num >= 0x02)
	{
		elements.push_back(Element::Lightning);
		num -= 0x02;
	}
	if (num >= 0x01)
	{
		elements.push_back(Element::Fire);
		num -= 0x01;
	}
}


ElementalValue::~ElementalValue()
{
}

int ElementalValue::getNumValue()
{
	int num = 0;
	for (int i = 0; i < elements.size(); i++)
		num += int(elements[i]);
	return num;
}

void ElementalValue::addRandomElement()
{
	if (elements.size() == 8)
		return;
	Element ele;
	do
	{
		ele = Element(int(pow(2, Helpers::randInt(0, 7))));
	} while (hasElement(ele));
	elements.push_back(ele);
}

bool ElementalValue::hasElement(Element element)
{
	return find(elements.begin(), elements.end(), element) != elements.end();
}
