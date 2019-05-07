#include "stdafx.h"
#include "DocumentationGen.h"




void DocumentationGen::addHeaderData()
{
	

	vector<string> paths;
	vector<string> disps;

	paths.push_back("../../../" + folderName + "/documentation.html");
	disps.push_back("Home");

	paths.push_back("equip.html");
	disps.push_back("Equipment");

	//paths.push_back("abilities.html");
	paths.push_back("#");
	disps.push_back("Abilities (WIP)");

	//paths.push_back("shops.html");
	paths.push_back("#");
	disps.push_back("Shops (WIP)");

	paths.push_back("bazaar.html");
	disps.push_back("Bazaar Recipes");

	paths.push_back("treasures.html");
	disps.push_back("Treasures");

	paths.push_back("enemy.html");
	disps.push_back("Enemies");

	paths.push_back("tips.html");
	disps.push_back("Tips");

	headerData.addLinks(paths, disps);
}

void DocumentationGen::addBazaarRecipeData()
{
	bazaarPage.addMainHeader();

	bazaarPage.add("<div class=\"tm-content\">");

	bazaarPage.addHeader1("Bazaar Recipes");
	vector<string> cats = vector<string>();
	cats.push_back("Result 1");
	cats.push_back("Result 2");
	cats.push_back("Result 3");
	cats.push_back("Cost");
	cats.push_back("Loot 1");
	cats.push_back("Loot 2");
	cats.push_back("Loot 3");

	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 0; i < 128; i++)
	{
		vector<string> entry = vector<string>();
		if (rename.bRename.data[i] == ".IGNORE")
		{
			entry.push_back("Monograph");
			entry.push_back("-");
			entry.push_back("-");
		}
		else if (i == 127)
		{
			entry.push_back("Canopic Jar");
			entry.push_back("-");
			entry.push_back("-");
		}
		else
		{
			if (ShopRand::bazaarData[i].result1Amt > 0)
				entry.push_back(getNameFromID(ShopRand::bazaarData[i].result1) + " x" + to_string(ShopRand::bazaarData[i].result1Amt));
			else
				entry.push_back("-");

			if (ShopRand::bazaarData[i].result2Amt > 0)
				entry.push_back(getNameFromID(ShopRand::bazaarData[i].result2) + " x" + to_string(ShopRand::bazaarData[i].result2Amt));
			else
				entry.push_back("-");

			if (ShopRand::bazaarData[i].result3Amt > 0)
				entry.push_back(getNameFromID(ShopRand::bazaarData[i].result3) + " x" + to_string(ShopRand::bazaarData[i].result3Amt));
			else
				entry.push_back("-");
		}
		entry.push_back(to_string(ShopRand::bazaarData[i].cost));
		if (ShopRand::bazaarData[i].loot1Amt > 0)
			entry.push_back(getNameFromID(ShopRand::bazaarData[i].loot1) + " x" + to_string(ShopRand::bazaarData[i].loot1Amt));
		else
			entry.push_back("-");

		if (ShopRand::bazaarData[i].loot2Amt > 0)
			entry.push_back(getNameFromID(ShopRand::bazaarData[i].loot2) + " x" + to_string(ShopRand::bazaarData[i].loot2Amt));
		else
			entry.push_back("-");

		if (ShopRand::bazaarData[i].loot3Amt > 0)
			entry.push_back(getNameFromID(ShopRand::bazaarData[i].loot3) + " x" + to_string(ShopRand::bazaarData[i].loot3Amt));
		else
			entry.push_back("-");
		data.push_back(entry);
	}
	bazaarPage.addTable(cats, data);

	bazaarPage.add("</div>");
}

void DocumentationGen::addTreasureData()
{
	treasurePage.addMainHeader();

	treasurePage.add("<div class=\"tm-content\">");

	treasurePage.addHeader1("Treasures");
	for (int map = 0; map < 279; map++)
	{
		treasurePage.addHeader2(TreasureRand::mapData[map].mapName);
		vector<string> cats = vector<string>();
		cats.push_back("Spawn Chance");
		cats.push_back("Gil Chance");
		cats.push_back("Normal Gil Amount");
		cats.push_back("Normal Item 1 - 50%");
		cats.push_back("Normal Item 2 - 50%");
		cats.push_back("\"Diamond Armlet\" Gil Amount");
		cats.push_back("\"Diamond Armlet\" Item 1 - 95%");
		cats.push_back("\"Diamond Armlet\" Item 2 - 5%");

		vector<vector<string>> data = vector<vector<string>>();
		for (int i = 0; i < TreasureRand::mapData[map].count; i++)
		{
			vector<string> entry = vector<string>();
			entry.push_back(to_string(int(TreasureRand::mapData[map].treasure[i].spawnChance)) + "%");
			entry.push_back(to_string(int(TreasureRand::mapData[map].treasure[i].gilChance)) + "%");
			entry.push_back(to_string(TreasureRand::mapData[map].treasure[i].gil1));
			entry.push_back(getNameFromID(TreasureRand::mapData[map].treasure[i].common1));
			entry.push_back(getNameFromID(TreasureRand::mapData[map].treasure[i].common2));
			entry.push_back(to_string(TreasureRand::mapData[map].treasure[i].gil2));
			entry.push_back(getNameFromID(TreasureRand::mapData[map].treasure[i].rare1));
			entry.push_back(getNameFromID(TreasureRand::mapData[map].treasure[i].rare2));

			data.push_back(entry);
		}
		treasurePage.addTable(cats, data);
	}

	treasurePage.add("</div>");
}

void DocumentationGen::addEquipData()
{
	equipPage.addMainHeader();

	equipPage.add("<div class=\"tm-content\">");

	addWeaponData();

	addShieldData();

	addArmorData();

	addAccessoryData();

	addAmmoData();

	equipPage.add("</div>");
}

void DocumentationGen::addAccessoryData()
{
	equipPage.addHeader1("Accessories");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Cost");
	cats.push_back("Defense");
	cats.push_back("Magick Resistance");
	cats.push_back("Element-Absorb");
	cats.push_back("Element-Immune");
	cats.push_back("Element-Half");
	cats.push_back("Element-Weak");
	cats.push_back("Element-Boost");
	cats.push_back("Status-On Equip");
	cats.push_back("Status-Immune");
	cats.push_back("Max HP Bonus");
	cats.push_back("Max MP Bonus");
	cats.push_back("Strength Bonus");
	cats.push_back("Magick Power Bonus");
	cats.push_back("Vitality Bonus");
	cats.push_back("Speed Bonus");
	cats.push_back("Special Effect");
	cats.push_back("License Needed");
	cats.push_back("LP Cost");
	cats.push_back("Possible Jobs");
	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 0; i < 420; i++)
	{
		ItemFlagValue iFlag{ EquipRand::equipData[i].itemFlag };
		if (iFlag.hasItemFlag(ItemFlag::Accessory))
		{
			AttributeData attr = EquipRand::attributeData[EquipRand::equipData[i].attribute / 24];
			vector<string> entry = vector<string>();
			entry.push_back(getNameFromID(i + 4096));
			entry.push_back(to_string(int(EquipRand::equipData[i].cost)));
			entry.push_back(to_string(int(EquipRand::equipData[i].def)));
			entry.push_back(to_string(int(EquipRand::equipData[i].mRes)));
			{
				string elements = "";
				ElementalValue elem(attr.absorbElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.immuneElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.halfElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.weakElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.boostElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string statuses = "";
				StatusValue stat(attr.autoStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			{
				string statuses = "";
				StatusValue stat(attr.immuneStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			entry.push_back(attr.hp == 0 ? "-" : to_string(attr.hp));
			entry.push_back(attr.mp == 0 ? "-" : to_string(attr.mp));
			entry.push_back(attr.str == 0 ? "-" : to_string(attr.str));
			entry.push_back(attr.mag == 0 ? "-" : to_string(attr.mag));
			entry.push_back(attr.vit == 0 ? "-" : to_string(attr.vit));
			entry.push_back(attr.spd == 0 ? "-" : to_string(attr.spd));

			string effect = getArmorEffectDesc(EquipRand::equipData[i].power);
			entry.push_back(effect);

			string licenseName, lpCost, jobs;

			tie(licenseName, lpCost, jobs) = getLicenseData(i + 4096);

			entry.push_back(licenseName);
			entry.push_back(lpCost);
			entry.push_back(jobs);

			data.push_back(entry);
		}
	}
	equipPage.addTable(cats, data);
}

void DocumentationGen::addAmmoData()
{
	equipPage.addHeader1("Ammunition");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Cost");
	cats.push_back("Attack Power");
	cats.push_back("Element-On Hit");
	cats.push_back("Status-On Hit");
	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 388; i < 420; i++)
	{
		ItemFlagValue iFlag{ EquipRand::equipData[i].itemFlag };
		AttributeData attr = EquipRand::attributeData[EquipRand::equipData[i].attribute / 24];
		vector<string> entry = vector<string>();
		entry.push_back(getNameFromID(i + 4096));
		entry.push_back(to_string(int(EquipRand::equipData[i].cost)));
		entry.push_back(to_string(int(EquipRand::equipData[i].power)));
		{
			string elements = "";
			ElementalValue elem(EquipRand::equipData[i].element);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string statuses = "";
			StatusValue stat(EquipRand::equipData[i].status);
			for (int e = 0; e < stat.statuses.size(); e++)
			{
				statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
			}
			if (statuses == "")
				statuses = "-";
			else
				statuses = to_string(EquipRand::equipData[i].hitChance) + "% " + statuses;
			entry.push_back(statuses);
		}

		data.push_back(entry);

	}
	equipPage.addTable(cats, data);
}

void DocumentationGen::addArmorData()
{
	equipPage.addHeader1("Armor");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Cost");
	cats.push_back("Defense");
	cats.push_back("Magick Resistance");
	cats.push_back("Element-Absorb");
	cats.push_back("Element-Immune");
	cats.push_back("Element-Half");
	cats.push_back("Element-Weak");
	cats.push_back("Element-Boost");
	cats.push_back("Status-On Equip");
	cats.push_back("Status-Immune");
	cats.push_back("Max HP Bonus");
	cats.push_back("Max MP Bonus");
	cats.push_back("Strength Bonus");
	cats.push_back("Magick Power Bonus");
	cats.push_back("Vitality Bonus");
	cats.push_back("Speed Bonus");
	cats.push_back("Special Effect");
	cats.push_back("License Needed");
	cats.push_back("LP Cost");
	cats.push_back("Possible Jobs");
	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 0; i < 420; i++)
	{
		ItemFlagValue iFlag{ EquipRand::equipData[i].itemFlag };
		if (iFlag.hasItemFlag(ItemFlag::BodyArmor) || iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			AttributeData attr = EquipRand::attributeData[EquipRand::equipData[i].attribute / 24];
			vector<string> entry = vector<string>();
			entry.push_back(getNameFromID(i + 4096));
			entry.push_back(to_string(int(EquipRand::equipData[i].cost)));
			entry.push_back(to_string(int(EquipRand::equipData[i].def)));
			entry.push_back(to_string(int(EquipRand::equipData[i].mRes)));
			{
				string elements = "";
				ElementalValue elem(attr.absorbElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.immuneElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.halfElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.weakElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.boostElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string statuses = "";
				StatusValue stat(attr.autoStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			{
				string statuses = "";
				StatusValue stat(attr.immuneStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			entry.push_back(attr.hp == 0 ? "-" : to_string(attr.hp));
			entry.push_back(attr.mp == 0 ? "-" : to_string(attr.mp));
			entry.push_back(attr.str == 0 ? "-" : to_string(attr.str));
			entry.push_back(attr.mag == 0 ? "-" : to_string(attr.mag));
			entry.push_back(attr.vit == 0 ? "-" : to_string(attr.vit));
			entry.push_back(attr.spd == 0 ? "-" : to_string(attr.spd));

			string effect = getArmorEffectDesc(EquipRand::equipData[i].power);
			entry.push_back(effect);

			string licenseName, lpCost, jobs;

			tie(licenseName, lpCost, jobs) = getLicenseData(i + 4096);

			entry.push_back(licenseName);
			entry.push_back(lpCost);
			entry.push_back(jobs);

			data.push_back(entry);
		}
	}
	equipPage.addTable(cats, data);
}

void DocumentationGen::addShieldData()
{
	equipPage.addHeader1("Shields");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Cost");
	cats.push_back("Evasion");
	cats.push_back("Magick Evasion");
	cats.push_back("Element-Absorb");
	cats.push_back("Element-Immune");
	cats.push_back("Element-Half");
	cats.push_back("Element-Weak");
	cats.push_back("Element-Boost");
	cats.push_back("Status-On Equip");
	cats.push_back("Status-Immune");
	cats.push_back("Max HP Bonus");
	cats.push_back("Max MP Bonus");
	cats.push_back("Strength Bonus");
	cats.push_back("Magick Power Bonus");
	cats.push_back("Vitality Bonus");
	cats.push_back("Speed Bonus");
	cats.push_back("License Needed");
	cats.push_back("LP Cost");
	cats.push_back("Possible Jobs");
	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 200; i < 220; i++)
	{
		ItemFlagValue iFlag{ EquipRand::equipData[i].itemFlag };
		AttributeData attr = EquipRand::attributeData[EquipRand::equipData[i].attribute / 24];
		vector<string> entry = vector<string>();
		entry.push_back(getNameFromID(i + 4096));
		entry.push_back(to_string(int(EquipRand::equipData[i].cost)));
		entry.push_back(to_string(int(EquipRand::equipData[i].def)));
		entry.push_back(to_string(int(EquipRand::equipData[i].mRes)));
		{
			string elements = "";
			ElementalValue elem(attr.absorbElement);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string elements = "";
			ElementalValue elem(attr.immuneElement);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string elements = "";
			ElementalValue elem(attr.halfElement);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string elements = "";
			ElementalValue elem(attr.weakElement);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string elements = "";
			ElementalValue elem(attr.boostElement);
			for (int e = 0; e < elem.elements.size(); e++)
			{
				elements = elements + HTMLDocument::addElement(elem.elements[e]);
			}
			if (elements == "")
				elements = "-";
			entry.push_back(elements);
		}
		{
			string statuses = "";
			StatusValue stat(attr.autoStatus);
			for (int e = 0; e < stat.statuses.size(); e++)
			{
				statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
			}
			if (statuses == "")
				statuses = "-";
			entry.push_back(statuses);
		}
		{
			string statuses = "";
			StatusValue stat(attr.immuneStatus);
			for (int e = 0; e < stat.statuses.size(); e++)
			{
				statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
			}
			if (statuses == "")
				statuses = "-";
			entry.push_back(statuses);
		}
		entry.push_back(attr.hp == 0 ? "-" : to_string(attr.hp));
		entry.push_back(attr.mp == 0 ? "-" : to_string(attr.mp));
		entry.push_back(attr.str == 0 ? "-" : to_string(attr.str));
		entry.push_back(attr.mag == 0 ? "-" : to_string(attr.mag));
		entry.push_back(attr.vit == 0 ? "-" : to_string(attr.vit));
		entry.push_back(attr.spd == 0 ? "-" : to_string(attr.spd));

		string licenseName, lpCost, jobs;

		tie(licenseName, lpCost, jobs) = getLicenseData(i + 4096);

		entry.push_back(licenseName);
		entry.push_back(lpCost);
		entry.push_back(jobs);

		data.push_back(entry);

	}
	equipPage.addTable(cats, data);
}

void DocumentationGen::addWeaponData()
{
	equipPage.addHeader1("Weapons");
	vector<string> cats = vector<string>();
	cats.push_back("Name");
	cats.push_back("Cost");
	cats.push_back("Attack Power");
	cats.push_back("Charge Time (CT)");
	cats.push_back("Weapon Evasion");
	cats.push_back("Weapon Range");
	cats.push_back("Crit Chance (%)/Combo Rate");
	cats.push_back("Knockback");
	cats.push_back("Element-On Hit");
	cats.push_back("Element-Boost");
	cats.push_back("Status-On Hit");
	cats.push_back("Status-On Equip");
	cats.push_back("Status-Immune");
	cats.push_back("Max HP Bonus");
	cats.push_back("Max MP Bonus");
	cats.push_back("Strength Bonus");
	cats.push_back("Magick Power Bonus");
	cats.push_back("Vitality Bonus");
	cats.push_back("Speed Bonus");
	cats.push_back("License Needed");
	cats.push_back("LP Cost");
	cats.push_back("Possible Jobs");
	vector<vector<string>> data = vector<vector<string>>();
	for (int i = 0; i < 420; i++)
	{
		if (i >= 179 && i <= 191)
			continue;
		ItemFlagValue iFlag{ EquipRand::equipData[i].itemFlag };
		if (!iFlag.hasItemFlag(ItemFlag::OffHand) && !iFlag.hasItemFlag(ItemFlag::Accessory) && !iFlag.hasItemFlag(ItemFlag::BodyArmor)
			&& !iFlag.hasItemFlag(ItemFlag::HeadArmor))
		{
			AttributeData attr = EquipRand::attributeData[EquipRand::equipData[i].attribute / 24];
			vector<string> entry = vector<string>();
			entry.push_back(getNameFromID(i + 4096));
			entry.push_back(to_string(int(EquipRand::equipData[i].cost)));
			entry.push_back(to_string(int(EquipRand::equipData[i].power)));
			entry.push_back(to_string(int(EquipRand::equipData[i].ct)));
			entry.push_back(to_string(int(EquipRand::equipData[i].evasion)));
			entry.push_back(to_string(int(EquipRand::equipData[i].def)));
			entry.push_back(to_string(int(EquipRand::equipData[i].critChance)));
			entry.push_back(to_string(int(EquipRand::equipData[i].knockback)));
			{
				string elements = "";
				ElementalValue elem(EquipRand::equipData[i].element);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string elements = "";
				ElementalValue elem(attr.boostElement);
				for (int e = 0; e < elem.elements.size(); e++)
				{
					elements = elements + HTMLDocument::addElement(elem.elements[e]);
				}
				if (elements == "")
					elements = "-";
				entry.push_back(elements);
			}
			{
				string statuses = "";
				StatusValue stat(EquipRand::equipData[i].status);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				else
					statuses = to_string(EquipRand::equipData[i].hitChance) + "% " + statuses;
				entry.push_back(statuses);
			}
			{
				string statuses = "";
				StatusValue stat(attr.autoStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			{
				string statuses = "";
				StatusValue stat(attr.immuneStatus);
				for (int e = 0; e < stat.statuses.size(); e++)
				{
					statuses = statuses + HTMLDocument::addStatus(stat.statuses[e]);
				}
				if (statuses == "")
					statuses = "-";
				entry.push_back(statuses);
			}
			entry.push_back(attr.hp == 0 ? "-" : to_string(attr.hp));
			entry.push_back(attr.mp == 0 ? "-" : to_string(attr.mp));
			entry.push_back(attr.str == 0 ? "-" : to_string(attr.str));
			entry.push_back(attr.mag== 0 ? "-" : to_string(attr.mag));
			entry.push_back(attr.vit == 0 ? "-" : to_string(attr.vit));
			entry.push_back(attr.spd == 0 ? "-" : to_string(attr.spd));

			string licenseName, lpCost, jobs;
			tie(licenseName, lpCost, jobs) = getLicenseData(i + 4096);

			entry.push_back(licenseName);
			entry.push_back(lpCost);
			entry.push_back(jobs);

			data.push_back(entry);
		}

	}
	equipPage.addTable(cats, data);
}

void DocumentationGen::addMainData()
{
	mainPage.addMainHeader("../data/docs/" + folderName + "/header.html");

	mainPage.add("<div class=\"tm-content\">");

	mainPage.addHeader1("Mod Information");
	mainPage.addParagraph("Author: Bartz24");
	mainPage.addParagraph("Version: "+Helpers::version);
	mainPage.addParagraph("Seed: " + seed);
	mainPage.addParagraph("Flags: " + flags);

	mainPage.add("</div>");
}

void DocumentationGen::addEnemyData()
{
	enemyPage.addMainHeader();

	enemyPage.add("<div class=\"tm-content\">");

	for (int i = 0; i < EnemyRand::ardData.size(); i++)
	{
		ARDData ard = EnemyRand::ardData[i];
		if (ard.section2Data.size() > 0)
		{
			enemyPage.addHeader1(getAreaName(ard.areaName));

			vector<string> cats = vector<string>();
			cats.push_back("Name");
			cats.push_back("Max HP");
			cats.push_back("Max MP");
			cats.push_back("Strength");
			cats.push_back("Magick Power");
			cats.push_back("Vitality");
			cats.push_back("Speed");
			cats.push_back("Attack Power");
			cats.push_back("Defense");
			cats.push_back("Evade");
			cats.push_back("Magick Resistance");
			cats.push_back("Element-Absorb");
			cats.push_back("Element-Immune");
			cats.push_back("Element-Half");
			cats.push_back("Element-Weak");
			cats.push_back("Element-Boost");
			cats.push_back("EXP");
			cats.push_back("LP");
			cats.push_back("Clan Points");
			cats.push_back("Drops");
			cats.push_back("Steals");
			cats.push_back("Poaches");
			cats.push_back("Monograph Drop");
			cats.push_back("Canopic Jar Drop");
			vector<vector<string>> data = vector<vector<string>>();
			for (int e = 0; e < ard.section2Data.size(); e++)
			{
				ARDSec2 sec2 = ard.section2Data[e];
				ARDSec1 sec1 = sec2.getARDSec1(ard);
				ARDSec3 sec3 = sec2.getARDSec3(ard);

				vector<string> entry = vector<string>();
				string name = rename.charNames[sec2.name - 0x4000];
				replace(name.begin(), name.end(), 'ú', 'u');
				entry.push_back(name);
				entry.push_back(to_string(sec3.hp));
				entry.push_back(to_string(sec3.mp));
				entry.push_back(to_string(sec3.str));
				entry.push_back(to_string(sec3.mag));
				entry.push_back(to_string(sec3.vit));
				entry.push_back(to_string(sec3.spd));
				entry.push_back(to_string(sec3.atk));
				entry.push_back(to_string(sec3.def));
				entry.push_back(to_string(sec3.eva));
				entry.push_back(to_string(sec3.mRes));
				{
					string elements = "";
					ElementalValue elem(sec1.absorbElement);
					for (int e = 0; e < elem.elements.size(); e++)
					{
						elements = elements + HTMLDocument::addElement(elem.elements[e]);
					}
					if (elements == "")
						elements = "-";
					entry.push_back(elements);
				}
				{
					string elements = "";
					ElementalValue elem(sec1.immuneElement);
					for (int e = 0; e < elem.elements.size(); e++)
					{
						elements = elements + HTMLDocument::addElement(elem.elements[e]);
					}
					if (elements == "")
						elements = "-";
					entry.push_back(elements);
				}
				{
					string elements = "";
					ElementalValue elem(sec1.halfElement);
					for (int e = 0; e < elem.elements.size(); e++)
					{
						elements = elements + HTMLDocument::addElement(elem.elements[e]);
					}
					if (elements == "")
						elements = "-";
					entry.push_back(elements);
				}
				{
					string elements = "";
					ElementalValue elem(sec1.weakElement);
					for (int e = 0; e < elem.elements.size(); e++)
					{
						elements = elements + HTMLDocument::addElement(elem.elements[e]);
					}
					if (elements == "")
						elements = "-";
					entry.push_back(elements);
				}
				{
					string elements = "";
					ElementalValue elem(sec1.boostElement);
					for (int e = 0; e < elem.elements.size(); e++)
					{
						elements = elements + HTMLDocument::addElement(elem.elements[e]);
					}
					if (elements == "")
						elements = "-";
					entry.push_back(elements);
				}
				entry.push_back(to_string(sec3.exp));
				entry.push_back(to_string(sec3.lp));
				entry.push_back(to_string(sec3.cp));

				{
					string drops = "";
					if (sec2.drop100 != 0xFFFF)
						drops += "100% " + getNameFromID(sec2.drop100) + ",<br>";
					if (sec2.drop40 != 0xFFFF)
						drops += "40% " + getNameFromID(sec2.drop40) + ",<br>";
					if (sec2.drop25 != 0xFFFF)
						drops += "25% " + getNameFromID(sec2.drop25) + ",<br>";
					if (sec2.drop05 != 0xFFFF)
						drops += "5% " + getNameFromID(sec2.drop05) + ",<br>";
					if (sec2.drop01 != 0xFFFF)
						drops += "1% " + getNameFromID(sec2.drop01) + ",<br>";
					if (drops.length() > 0)
						drops = drops.substr(0, drops.length() - 5);
					else
						drops = "-";
					entry.push_back(drops);
				}
				{
					string steals = "";
					if (sec2.steal55 != 0xFFFF)
						steals += "55% " + getNameFromID(sec2.steal55) + ",<br>";
					if (sec2.steal10 != 0xFFFF)
						steals += "10% " + getNameFromID(sec2.steal10) + ",<br>";
					if (sec2.steal03 != 0xFFFF)
						steals += "3% " + getNameFromID(sec2.steal03) + ",<br>";
					if (steals.length() > 0)
						steals = steals.substr(0, steals.length() - 5);
					else
						steals = "-";
					entry.push_back(steals);
				}
				{
					string poach = "";
					if (sec2.poach95 != 0xFFFF)
						poach += "95% " + getNameFromID(sec2.poach95) + ",<br>";
					if (sec2.poach05 != 0xFFFF)
						poach += "5% " + getNameFromID(sec2.poach05) + ",<br>";
					if (poach.length() > 0)
						poach = poach.substr(0, poach.length() - 5);
					else
						poach = "-";
					entry.push_back(poach);
				}
				{
					string mono = "-";
					if (sec2.monographType != 0xFFFF)
					{
						mono = "(" + getMonographName(sec2.monographType) + ")";
						mono += " " + to_string(sec2.monographDropRate) + "%";
						mono += " " + getNameFromID(sec2.monographDrop);
					}
					entry.push_back(mono);
				}
				{
					string mono = "-";
					if (sec2.canopicJarType != 0xFFFF)
					{
						mono = "(" + getMonographName(sec2.canopicJarType) + ")";
						mono += " " + to_string(sec2.canopicJarDropRate) + "%";
						mono += " " + getNameFromID(sec2.canopicJarDrop);
					}
					entry.push_back(mono);
				}
				data.push_back(entry);
			}
		enemyPage.addTable(cats, data);
		}
	}

	enemyPage.add("</div>");
}

string DocumentationGen::getAreaName(string area)
{
	string type = area.substr(0, 3);

	string name = "Unknown";

	if (type == "asp")
		name = "Skyferry";
	else if (type == "bds")
		name = "Necrohol of Nabudis";
	else if (type == "bhm")
		name = "Sky Fortress Bahamut";
	else if (type == "bog")
		name = "Nabreus Deadlands";
	else if (type == "bul")
		name = "Mt. Bur-Omisace";
	else if (type == "dgl")
		name = "Pharos at Ridorana (Bosses)";
	else if (type == "dor")
		name = "Draklor Laboratory";
	else if (type == "dst")
		name = "Dalmasca Estersand";
	else if (type == "ene")
		name = "Ogir-Yensa Sandsea";
	else if (type == "enw")
		name = "Nam-Yensa Sandsea";
	else if (type == "fon")
		name = "Phon Coast";
	else if (type == "frs")
		name = "Salikawood";
	else if (type == "gil")
		name = "Giruvegan & Great Crystal";
	else if (type == "gol")
		name = "Golmore Jungle";
	else if (type == "grm")
		name = "Garamsythe Waterway";
	else if (type == "hne")
		name = "Henne Mines";
	else if (type == "lus")
		name = "Lhusu Mines";
	else if (type == "mfr")
		name = "The Feywood";
	else if (type == "mic")
		name = "Barheim Passage";
	else if (type == "mnt")
		name = "Mosphoran Highwaste";
	else if (type == "mrm")
		name = "Stilshrine of Miriam";
	else if (type == "naf")
		name = "Nalbina Fortress";
	else if (type == "nal")
		name = "Nalbina Dungeon";
	else if (type == "ozm")
		name = "Ozmone Plains";
	else if (type == "pbc")
		name = "Paramina Rift";
	else if (type == "pla")
		name = "Tchita Uplands";
	else if (type == "rbl")
		name = "Pharos at Ridorana";
	else if (type == "rsn")
		name = "Dreadnought Leviathan";
	else if (type == "rui")
		name = "Sochen Cave Palace";
	else if (type == "rwf")
		name = "Ridorana Cataract";
	else if (type == "rwg")
		name = "Tomb of Raithwall";
	else if (type == "sav")
		name = "Giza Plains";
	else if (type == "srb")
		name = "Cerobi Steppe";
	else if (type == "tri")
		name = "Trial Mode";
	else if (type == "wdl")
		name = "Dalmasca Westersand";
	else if (type == "ztc")
		name = "Zertinan Caverns";

	return name + " " + char(toupper(area[4]));
}

tuple<string, string, string> DocumentationGen::getLicenseData(int id)
{
	for (int i = 32; i < 360; i++)
	{
		if (i >= 300 && i <= 328 || i >= 219 && i <= 275)
			continue;
		for (int a = 0; a < 8; a++)
		{
			if (LicenseRand::licenseData[i].otherData[a] == id)
			{
				string jobNames[12];
				for (int i = 0; i < 12; i++)
				{
					jobNames[i] = rename.menuCmd[4 + i] + ", ";
					for (int j = 0; j < i; j++)
					{
						if (jobNames[j] == jobNames[i] && jobNames[j] != "")
							jobNames[i] = "";
					}
				}

				string jobs = rename.lRename.getPossibleJobs(i, jobNames);

				if (jobs != "All" && jobs != "None")
				{
					jobs = jobs.substr(0, jobs.length() - 2);
				}

				regex pattern = regex("(.*) \\((\\d+) LP\\) \\((.*)\\)");
				smatch matches;
				if (regex_search(rename.lRename.data[i], matches, pattern))
				{
					return { matches[1].str(), to_string(LicenseRand::licenseData[i].lpCost), jobs };
				}
				else
					return { rename.lRename.data[i], to_string(LicenseRand::licenseData[i].lpCost), jobs };
			}
		}
	}
		
	return { "-", "-", "-" };
}

string DocumentationGen::getNameFromID(int id)
{
	string text = rename.bRename.getNameFromID(id);
	while (text.find("{0F}{3C}") == 0)
	{
		text = text.substr(48);
	}
	return text;
}

string DocumentationGen::getMonographName(int id)
{
	switch (id)
	{
	case MonographType::Sage:
		return "Sage";
	case MonographType::Hunter:
		return "Hunter";
	case MonographType::Knight:
		return "Knight";
	case MonographType::Dragoon:
		return "Dragoon";
	case MonographType::Mage:
		return "Mage";
	case MonographType::Warmage:
		return "Warmage";
	case MonographType::Scholar:
		return "Scholar";
	case MonographType::CanopicJar:
		return "Canopic Jar";
	}
}

string DocumentationGen::getArmorEffectDesc(int id)
{
	switch (id)
	{
	case 0x02:
		return "Improves chance to hit.";
	case 0x04:
		return "Improves chance of avoiding attacks.";
	case 0x05:
		return "Half Damage when HP Critical.";
	case 0x06:
		return "Counter normal attacks.";
	case 0x07:
		return "Improves chance to counter.";
	case 0x08:
		return "Increase magick power when HP Critical.";
	case 0x09:
		return "Increase damage while empty-handed.";
	case 0x0A:
		return "Increase strength when HP Critical.";
	case 0x0B:
		return "Increase strength when HP is full.";
	case 0x0C:
		return "Obtained LP becomes gil.";
	case 0x0D:
		return "Improves chance of scoring multiple hits.";
	case 0x0E:
		return "Doubles potency of restorative items.";
	case 0x0F:
		return "Reverse effects of restorative items.";
	case 0x10:
		return "Ignore weather effects and terrain.";
	case 0x11:
		return "Steal superior and rare items.";
	case 0x12:
		return "Improve magick accuracy.";
	case 0x19:
		return "Obtain superior items from chests.";
	case 0x1B:
		return "Double EXP earned.";
	case 0x1C:
		return "Double LP earned.";
	case 0x1D:
		return "Reduce EXP earned to 0.";
	case 0x1F:
		return "Magicks casted bypass Reflect.";
	case 0x20:
		return "Replace MP cost with gil.";
	case 0x24:
		return "Half MP Cost.";
	case 0x25:
		return "Move safely past traps.";
	case 0x27:
		return "Reduce MP to 0.";
	case 0x67:
		return "Increase magick power when HP is full.";
	default:
		return "-";
	}
}

DocumentationGen::DocumentationGen()
{
}

DocumentationGen::DocumentationGen(RenameMain rename, string modSeedFolderName, string seed, string flags)
{
	this->rename = rename;
	folderName = modSeedFolderName;
	mainPage = HTMLDocument(true);
	this->seed = seed;
	this->flags = flags;
}


DocumentationGen::~DocumentationGen()
{
}

void DocumentationGen::process()
{
	addHeaderData();

	addMainData();

	addBazaarRecipeData();

	addTreasureData();

	addEquipData();

	addEnemyData();
}

void DocumentationGen::save()
{
	std::experimental::filesystem::create_directory("data\\docs\\"+folderName);
	std::experimental::filesystem::copy("data\\docs\\common\\tips.html", "data\\docs\\" + folderName + "\\tips.html");
	mainPage.save(folderName + "\\documentation.html");
	headerData.save("data\\docs\\" + folderName + "\\header.html");
	treasurePage.save("data\\docs\\"+ folderName + "\\treasures.html");
	bazaarPage.save("data\\docs\\" + folderName + "\\bazaar.html");
	equipPage.save("data\\docs\\" + folderName + "\\equip.html");
	enemyPage.save("data\\docs\\" + folderName + "\\enemy.html");
}
