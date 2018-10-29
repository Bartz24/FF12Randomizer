#include "stdafx.h"
#include "CharValue.h"


CharValue::CharValue()
{
}

CharValue::CharValue(int num)
{
	if (num & 0x01)
		characters.push_back(Character::Vaan);
	if (num & 0x02)
		characters.push_back(Character::Ashe);
	if (num & 0x04)
		characters.push_back(Character::Fran);
	if (num & 0x08)
		characters.push_back(Character::Balthier);
	if (num & 0x10)
		characters.push_back(Character::Basch);
	if (num & 0x20)
		characters.push_back(Character::Penelo);
	if (num & 0x40)
		characters.push_back(Character::Reks);
}


CharValue::~CharValue()
{
}

int CharValue::getNumValue()
{
	int num = 0;
	for (int i = 0; i < characters.size(); i++)
		num += int(characters[i]);
	return num;
}

bool CharValue::hasCharacter(Character character)
{
	return find(characters.begin(), characters.end(), character) != characters.end();
}
