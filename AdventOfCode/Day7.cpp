#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include "AdventUtil.h"

void Part1()
{
	std::string fileStr = GetFileAsString("input.txt");

	std::vector<std::string> numStrings = SplitString(fileStr, ',');

	std::vector<int> crabsAtCoords;
	crabsAtCoords.reserve(1500);

	for (const std::string& str : numStrings)
	{
		int xCoord;
		sscanf(str.c_str(), "%d", &xCoord);

		if (xCoord >= crabsAtCoords.size())
		{
			crabsAtCoords.resize(xCoord + 1);
		}
		++crabsAtCoords[xCoord];
	}

	std::vector<int> costsPerCoord(crabsAtCoords.size());

	int crabsSoFar = 0;
	int costSoFar = 0;
	// Scan from left to right, only considering the cost of crabs moving right.
	for (int i = 0; i < crabsAtCoords.size(); ++i)
	{
		costSoFar += crabsSoFar;
		costsPerCoord[i] = costSoFar;

		crabsSoFar += crabsAtCoords[i];
	}
	crabsSoFar = 0;
	costSoFar = 0;
	int bestFuel = costsPerCoord.back();
	int bestIndex = costsPerCoord.size() - 1;
	// Go right to left, adding the costs for crabs moving left.
	for (int i = crabsAtCoords.size() - 1; i >= 0; --i)
	{
		costSoFar += crabsSoFar;
		costsPerCoord[i] += costSoFar;

		if (costsPerCoord[i] < bestFuel)
		{
			bestFuel = costsPerCoord[i];
			bestIndex = i;
		}

		crabsSoFar += crabsAtCoords[i];
	}

	std::ofstream outFile("output.txt");
	std::cout << bestFuel;
	outFile << bestFuel;
}

void Day7()
{
	std::string fileStr = GetFileAsString("input.txt");

	std::vector<std::string> numStrings = SplitString(fileStr, ',');

	std::vector<int> crabsAtCoords;
	crabsAtCoords.reserve(1500);
	
	for (const std::string& str : numStrings)
	{
		int xCoord;
		sscanf(str.c_str(), "%d", &xCoord);

		if (xCoord >= crabsAtCoords.size())
		{
			crabsAtCoords.resize(xCoord + 1);
		}
		++crabsAtCoords[xCoord];
	}

	std::vector<int> costsPerCoord(crabsAtCoords.size());

	int bestFuel = INT_MAX;
	int bestIndex = -1;
	// Part 2 uses a slower N^2 method :(
	for (int i = 0; i < crabsAtCoords.size(); ++i)
	{
		for (int j = 0; j < crabsAtCoords.size(); ++j)
		{
			int dist = std::abs(i - j);
			costsPerCoord[i] += (dist * (dist + 1) / 2) * crabsAtCoords[j];
		}

		
		if (costsPerCoord[i] < bestFuel)
		{
			bestFuel = costsPerCoord[i];
			bestIndex = i;
		}
	}

	std::ofstream outFile("output.txt");
	std::cout << bestFuel;
	outFile << bestFuel;
}
