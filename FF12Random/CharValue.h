#pragma once
#include <vector>

using namespace std;

enum class Character
{
	Vaan = 0x01,
	Ashe = 0x02,
	Fran = 0x04,
	Balthier = 0x08,
	Basch = 0x10,
	Penelo = 0x20,
	Reks = 0x40

};

class CharValue
{
public:
	CharValue();
	CharValue(int num);
	~CharValue();
	vector<Character> characters;
	int getNumValue();
	bool hasCharacter(Character character);
};

