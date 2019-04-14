#include "stdafx.h"
#include "HTMLDocument.h"


HTMLDocument::HTMLDocument(bool main)
{
	document.push_back("<!DOCTYPE html>");
	document.push_back("<html>");

	generateHTMLHead(main);

	document.push_back("<body>");
}


HTMLDocument::~HTMLDocument()
{
}

void HTMLDocument::generateHTMLHead(bool main)
{
	document.push_back("<head>");

	document.push_back("<meta charset=\"utf - 8\"/>");

	document.push_back("<title>FF12 Randomizer Documentation</title>");
	if (main)
		document.push_back("<link rel=\"stylesheet\" type=\"text/css\" href=\"../data/docs/css/main.css\">");
	else
		document.push_back("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/main.css\">");
	document.push_back("<link href=\"https://fonts.googleapis.com/css?family=Roboto:300\" rel=\"stylesheet\">");

	document.push_back("</head>");
}

void HTMLDocument::addHeader1(string header)
{
	document.push_back("<h1>" + header + "</h1>");
}

void HTMLDocument::addHeader2(string header)
{
	document.push_back("<h2>" + header + "</h2>");
}

void HTMLDocument::add(string text)
{
	document.push_back(text);
}

void HTMLDocument::addParagraph(string text)
{
	document.push_back("<p>" + text + "</p>");
}

void HTMLDocument::addMainHeader(string path)
{
	document.push_back("<embed class=\"tm-embedHeader\" src=\"" + path + "\"></embed>");
}

void HTMLDocument::addTable(vector<string> categories, vector<vector<string>> data)
{
	document.push_back("<table>");

	document.push_back("<tr>");
	for (int i = 0; i < categories.size(); i++)
	{
		document.push_back("<th>" + categories[i] + "</th>");
	}
	document.push_back("</tr>");

	for (int i = 0; i < data.size(); i++)
	{
		document.push_back("<tr>");
		for (int entry = 0; entry < data[i].size(); entry++)
		{
			document.push_back("<td>" + (data[i])[entry] + "</td>");
		}
		document.push_back("</tr>");
	}

	document.push_back("</table>");
}

void HTMLDocument::addLinks(vector<string> paths, vector<string> displays)
{
	document.push_back("<header class=\"tm-header\">");
	document.push_back("<div class=\"tm-container\">");
	document.push_back("<p class=\"tm-name\">FF12 Randomizer</p>");
	document.push_back("<nav class=\"tm-nav\">");
	document.push_back("<ul>");
	
	for (int i = 0; i < paths.size(); i++)
	{
		document.push_back("<li><a href = \"" + paths[i] + "\", target = \"_top\">" + displays[i] + "</a></li>");
	}

	document.push_back("</ul>");
	document.push_back("</nav>");	
	document.push_back("</div>");
	document.push_back("</header>");
}

string HTMLDocument::addElement(Element element)
{
	string elem;
	switch (element)
	{
	case Element::Fire:
		elem = "fire";
		break;
	case Element::Ice:
		elem = "ice";
		break;
	case Element::Lightning:
		elem = "thunder";
		break;
	case Element::Water:
		elem = "water";
		break;
	case Element::Wind:
		elem = "wind";
		break;
	case Element::Earth:
		elem = "earth";
		break;
	case Element::Holy:
		elem = "holy";
		break;
	case Element::Dark:
		elem = "dark";
		break;
	}
	return "<img style=\"width:20px;height:20px;\" src=\"../common/" + elem + ".png\"/>";
}

string HTMLDocument::addStatus(Status status)
{
	string stat;
	switch (status)
	{
	case Status::Death:
		stat = "death";
		break;
	case Status::Stone:
		stat = "stone";
		break;
	case Status::Petrify:
		stat = "petrify";
		break;
	case Status::Stop:
		stat = "stop";
		break;
	case Status::Sleep:
		stat = "sleep";
		break;
	case Status::Confuse:
		stat = "confuse";
		break;
	case Status::Doom:
		stat = "doom";
		break;
	case Status::Blind:
		stat = "blind";
		break;
	case Status::Reverse:
		stat = "reverse";
		break;
	case Status::Disable:
		stat = "disable";
		break;
	case Status::Immobilize:
		stat = "immobilize";
		break;
	case Status::Slow:
		stat = "slow";
		break;
	case Status::Poison:
		stat = "poison";
		break;
	case Status::Silence:
		stat = "silence";
		break;
	case Status::Sap:
		stat = "sap";
		break;
	case Status::Oil:
		stat = "oil";
		break;
	case Status::Disease:
		stat = "disease";
		break;
	case Status::Lure:
		stat = "lure";
		break;
	case Status::Protect:
		stat = "protect";
		break;
	case Status::Shell:
		stat = "shell";
		break;
	case Status::Haste:
		stat = "haste";
		break;
	case Status::Bravery:
		stat = "bravery";
		break;
	case Status::Faith:
		stat = "faith";
		break;
	case Status::Reflect:
		stat = "reflect";
		break;
	case Status::Vanish:
		stat = "vanish";
		break;
	case Status::Regen:
		stat = "regen";
		break;
	case Status::Float:
		stat = "float";
		break;
	case Status::Berserk:
		stat = "berserk";
		break;
	case Status::Bubble:
		stat = "bubble";
		break;
	case Status::Libra:
		stat = "libra";
		break;
	case Status::XZone:
		stat = "xzone";
		break;
	}
	return "<img style=\"width:20px;height:20px;\" src=\"../common/" + stat + ".png\"/>";
}

void HTMLDocument::save(string path)
{
	document.push_back("</body>");

	document.push_back("</html>");

	ofstream myfile(path);
	for (int i = 0; i < document.size(); i++)
	{
		myfile << document[i];
		if (i < document.size() - 1)
			myfile << endl;
	}
	myfile.close();
}
