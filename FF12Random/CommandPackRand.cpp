#include "stdafx.h"
#include "CommandPackRand.h"
#include "MagicRand.h"
#include "EnemyRand.h"

CommandPack CommandPackRand::commandPackData[826] = {};

bool CommandPackRand::isBlackListedEnemyAbility(unsigned short i)
{
	return i == 81 || i >= 111 && i <= 123 || i >= 146 && i <= 149 || i >= 151 && i <= 157 || i == 183 || i == 185 || i == 187 || i == 189 || i == 191 || i == 193 
		|| i == 195 || i == 197 || i == 199 || i == 201 || i == 203 || i == 205 || i >= 207 && i <= 277 || i >= 286 && i <= 293 || i >= 450 || i == 162 || i == 169 || i >= 171 && i <= 174 || i == 178
		|| i == 411 || i == 412 || i == 416 || i == 417 || i == 439 || i == 323 || i == 325 || i == 436 || i == 326 || i == 327;
}

CommandPackRand::CommandPackRand()
{
}


CommandPackRand::~CommandPackRand()
{
}

void CommandPackRand::load()
{
	fileName = Helpers::mainPS2DataFolder + "\\image\\ff12\\test_battle\\" + Helpers::language + "\\binaryfile\\battle_pack.bin";
	if (Helpers::fileExists(fileName))
	{
		char * buffer;
		long size = (826+1+1) * 4; //(Num packs + num byte + end byte) * pointer size
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		file.seekg(Helpers::getPointer(fileName, 0x28, 0xF0));
		buffer = new char[size];
		file.read(buffer, size);
		file.close();

		for (int i = 0; i < 826; i++)
		{
			unsigned int pointer = Helpers::readInt(buffer, (i + 1) * 4);
			int count = (Helpers::readInt(buffer, (i + 2) * 4) - pointer) / 4;

			char * buffer2;
			size = count * 4; //Num abilities * size ability
			file = ifstream(fileName, ios::in | ios::binary | ios::ate);
			file.seekg(Helpers::getPointer(fileName, 0x28, 0xF0) + pointer);
			buffer2 = new char[size];
			file.read(buffer2, size);
			file.close();
			commandPackData[i] = CommandPack{ pointer, count, buffer2 };

			delete[] buffer2;
		}

		delete[] buffer;
	}
}

void CommandPackRand::save()
{
	for (int i = 0; i < 826; i++)
	{

		char * buffer;
		long size = commandPackData[i].abilityCount * 4; //Num abilities * size ability
		fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
		file.seekp(Helpers::getPointer(fileName, 0x28, 0xF0) + commandPackData[i].pointer);
		buffer = new char[size];
		for (int a = 0; a < commandPackData[i].abilityCount; a++)
		{
			Helpers::setShort(buffer, a * 4, commandPackData[i].abilities[a]);
			Helpers::setShort(buffer, a * 4+2, commandPackData[i].chances[a]);
		}

		file.write(buffer, size);
		file.close();

		delete[] buffer;
	}
}

void CommandPackRand::process(FlagGroup flags)
{
	if (flags.hasFlag("A"))
	{
		shuffle(flags.getFlag("A").getValue());
	}
}

void CommandPackRand::shuffle(int value)
{
	vector<unsigned short> abilities;
	for (int i = 0; i < 497; i++)
	{
		if (isBlackListedEnemyAbility(i))
			continue;
		abilities.push_back(i);
	}


	for (int i = 0; i < 826; i++)
	{
		for (int a = 0; a < commandPackData[i].abilityCount; a++)
		{
			if (commandPackData[i].abilities[a] < 0x8000 && !isBlackListedEnemyAbility(commandPackData[i].abilities[a]))
			{
				int rarity = MagicRand::actionData[commandPackData[i].abilities[a]].enemyRarity;
				vector<unsigned short> possible;
				for (int i = 0; i < abilities.size(); i++)
				{
					if (abs(MagicRand::actionData[abilities[i]].enemyRarity - rarity) <= ceil(double(value) / 100. * abs(double(rarity))))
						possible.push_back(abilities[i]);
				}
				commandPackData[i].abilities[a] = possible[Helpers::randInt(0, possible.size() - 1)];
			}
		}
	}
	
	for (int i = 0; i < EnemyRand::ardData.size(); i++)
	{
		for (int a = 0; a < EnemyRand::ardData[i].aiData.abilities.size(); a++)
		{
			if (EnemyRand::ardData[i].aiData.abilities[a].ability < 0x8000 && !isBlackListedEnemyAbility(EnemyRand::ardData[i].aiData.abilities[a].ability))
			{
				int rarity = MagicRand::actionData[EnemyRand::ardData[i].aiData.abilities[a].ability].enemyRarity;
				vector<unsigned short> possible;
				for (int i = 0; i < abilities.size(); i++)
				{
					if (abs(MagicRand::actionData[abilities[i]].enemyRarity - rarity) <= ceil(double(value) / 100. * abs(double(rarity))))
						possible.push_back(abilities[i]);
				}
				EnemyRand::ardData[i].aiData.abilities[a].ability = possible[Helpers::randInt(0, possible.size() - 1)];
			}
		}
	}
}