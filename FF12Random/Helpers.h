#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <experimental/filesystem>
#include <algorithm>
#include <sstream>

using namespace std;

class Helpers
{
	/*
	ITEM, 0
	EQUIP, 1
	ABILITY, 2
	AUGMENT, 3
	CHARACTER, 4
	ENEMY, 5
	SHOP, 6
	TREASURE, 7
	REWARD, 8
	LICENSE, 9
	LICENSEBOARD 10
	*/

public:
	static string version;
	static default_random_engine rng;
	static string language;
	static string mainPS2DataFolder;
	Helpers();
	~Helpers();
	static bool fileExists(std::string fileName);
	static int getPointer(string fileName, int pointerLocation, int offset = 0x20);
	static int randInt(int low, int high);
	static int randInt(int low, int high, int minN, int maxN);
	static int randIntNorm(int low, int high, int center, int std);
	static int randIntWeibull(int low, int high, double center, double a);
	static int randIntControl(int low, int high, int norm, int ratio);
	static int randNormControl(int low, int high, int center, int std, int ratio);
	static int randWeibullControl(int low, int high, double center, double a, int ratio);
	static unsigned int readInt(char bytes[], int index);
	static unsigned short readShort(char bytes[], int index);
	static void setInt(char *bytes, int index, unsigned int value);
	static void setShort(char *bytes, int index, unsigned short value);
	static int clamp(int value, int minN, int maxN);
	static vector<string> get_directories(const string& s);
	static vector<string> get_files(const string& s);
	static void addRangeToVector(vector<int>& data, int low, int high);
	static void addRangeToVector(vector<unsigned short>& data, unsigned short low, unsigned short high);
	template <class T>
	static void shuffle(vector<T> &data, int factor=3);
	template <class T>
	static void shuffleWeighted(vector<T> &data, vector<int> &weights, int factor = 3);
	template <class T>
	static void sortWeighted(vector<T> &data, vector<float> &weights);
	static vector<string> split(const std::string &s, char delim);
	static string removeSpaces(string in);
};

template<class T>
inline void Helpers::shuffle(vector<T>& data, int factor)
{
	for (int i = 0; i < data.size() * 3; i++)
	{
		iter_swap(data.begin() + Helpers::randInt(0, data.size() - 1), data.begin() + Helpers::randInt(0, data.size() - 1));
	}
}

template<class T>
inline void Helpers::shuffleWeighted(vector<T>& data, vector<int> &weights, int factor)
{
	vector<T> newData;
	vector<int> newWeights;
	int weightTotal = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		weightTotal += weights[i];
	}
	
	for (int i = 0; i < data.size(); i++)
	{
		int rand = Helpers::randInt(0, weightTotal);
		int index = 0;
		for (; rand >= weights[index]; index++)
			rand -= weights[index];
		newData.push_back(data.erase(data.begin() + index));
		newWeights.push_back(weights.erase(weights.begin() + index));
	}
	data = newData;
	weights = newWeights;
	if (factor > 1)
		shuffleWeighted(data, weights, factor - 1);
}

template<class T>
inline void Helpers::sortWeighted(vector<T>& data, vector<float>& weights)
{
	vector<T> newData;
	vector<float> newWeights;
	newData.push_back(data[0]);
	data.erase(data.begin());
	newWeights.push_back(weights[0]);
	weights.erase(weights.begin());

	while (weights.size() > 0)
	{
		bool added = false;
		for (int w = 0; w < newWeights.size(); w++)
		{
			if (weights[0] > newWeights[w])
			{
				newWeights.insert(newWeights.begin() + w, weights[0]);
				weights.erase(weights.begin() + 0);
				newData.insert(newData.begin() + w, data[0]);
				data.erase(data.begin());
				added = true;
				break;
			}
			else if (weights[0] == newWeights[w])
			{
				if (Helpers::randInt(0, 99) < 50)
				{
					newWeights.insert(newWeights.begin() + w, weights[0]);
					weights.erase(weights.begin());
					newData.insert(newData.begin() + w, data[0]);
					data.erase(data.begin());
				}
				else
				{
					newWeights.insert(newWeights.begin() + w + 1, weights[0]);
					weights.erase(weights.begin());
					newData.insert(newData.begin() + w + 1, data[0]);
					data.erase(data.begin());
				}
				added = true;
				break;
			}
		}
		if (!added)
		{
			newWeights.push_back(weights[0]);
			weights.erase(weights.begin());
			newData.push_back(data[0]);
			data.erase(data.begin());
		}
	}

	data = newData;
	weights = newWeights;
}
