#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "ElementalValue.h"
#include "StatusValue.h"

using namespace std;

class HTMLDocument
{
private:
	vector<string> document;
public:
	HTMLDocument(bool main=false);
	~HTMLDocument();
	void generateHTMLHead(bool main=false);
	void addHeader1(string header);
	void addHeader2(string header);
	void add(string text);
	void addParagraph(string text);
	void addMainHeader(string path = "header.html");
	void addTable(vector<string> categories, vector<vector<string>> data);
	void addLinks(vector<string> paths, vector<string> displays);
	static string addElement(Element element);
	static string addStatus(Status status);
	void save(string path);
};