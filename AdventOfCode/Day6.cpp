#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include "AdventUtil.h"

/*
using ullong = unsigned long long;

struct big
{
	ullong lower = 0;
	ullong upper = 0;

	big() = default;
	big(const big& other) = default;

	big(ullong val) : lower(val)
	{}

	big operator+(const big& other) const
	{
		big newBig;

		newBig.lower = lower + other.lower;
		newBig.upper = upper + other.upper;
		if (newBig.lower < lower)
		{
			++newBig.upper;
		}

		return newBig;
	}

	big& operator+=(const big& other)
	{
		*this = *this + other;
		return *this;
	}

	big operator++()
	{
		*this = *this + 1;
	}

	std::string ToString()
	{

	}
};
*/

using big = unsigned long long;

void Day6()
{
	std::string fileStr = GetFileAsString("input.txt");
	
	std::vector<std::string> numStrings = SplitString(fileStr, ',');

	const int AGE_CAP = 9;

	big countsPerAge[AGE_CAP] = { 0 };

	for (const std::string& str : numStrings)
	{
		int val;
		sscanf(str.c_str(), "%d", &val);

		// Assume everything is in [0,AGE_CAP) and can fit in the array.
		++countsPerAge[val];
	}

	const int days = 256;
	for (int i = 0; i < days; ++i)
	{
		big resettingCount = countsPerAge[0];

		for (int j = 0; j < AGE_CAP - 1; ++j)
		{
			countsPerAge[j] = countsPerAge[j + 1];
		}
		countsPerAge[AGE_CAP - 1] = 0;

		countsPerAge[6] += resettingCount;
		countsPerAge[8] += resettingCount;
	}

	big total = std::accumulate(&countsPerAge[0], &countsPerAge[0] + 9, (big)0);

	std::ofstream outFile("output.txt");
	std::cout << total;
	outFile << total;
}
