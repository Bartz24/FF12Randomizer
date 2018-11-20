#pragma once

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include "Helpers.h"

using namespace std;

enum class FileSizeTableOffset
{
	key_signal = 0x00009C44,
	battle_message = 0x00009C48,
	battle_pack = 0x00009C8C,
	menu_command = 0x00009C90,
	menu_message = 0x00009C94,
	help_menu = 0x00009C98,
	help_action = 0x00009C9C,
	listhelp_daijinamono = 0x00009CA0,
	questtitle = 0x00009CA4,
	menu_mapname = 0x00009CEC,
	penelosdiary = 0x00009CF0,
	help_penelosdiary = 0x00009CF4,
	listhelp_common = 0x00009CF8,
	listhelp_action = 0x00009CFC,
	listhelp_subcategory = 0x00009D00,
	listhelp_status = 0x00009D04,
	listhelp_ability = 0x00009D08,
	listhelp_eventitem = 0x00009D0C,
	listhelp_gambit = 0x00009D10,
	listhelp_targetchip = 0x00009D14,
	listhelp_license = 0x00009D18,
	menu_command_template = 0x00009D1C,
	menu_expansion = 0x00009D20,
	word = 0x00009D34,
	menu00 = 0x00009D38,
	menu01 = 0x00009D3C,
	menu02 = 0x00009D40,
	menu03 = 0x00009D44,
	menu04 = 0xFFFFFFFF //COULD NOT FIND
};

class FileSizeTableFix
{
private:
	string folder;
public:
	FileSizeTableFix();
	~FileSizeTableFix();
	void load(string path);
	void save();
	void process();
	void overwriteSize(FileSizeTableOffset position, unsigned long value);
	unsigned long getFileSize(string filePath);
};

