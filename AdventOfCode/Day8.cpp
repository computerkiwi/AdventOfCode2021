#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include "AdventUtil.h"

const int A = 0;
const int B = 1;
const int C = 2;
const int D = 3;
const int E = 4;
const int F = 5;
const int G = 6;

struct LetterCollection
{
	bool vals[7];

	LetterCollection() : LetterCollection(false)
	{
	}

	LetterCollection(bool a, bool b, bool c, bool d, bool e, bool f, bool g) : vals{ a,b,c,d,e,f,g }
	{}

	LetterCollection(bool enabled)
	{
		for (int i = 0; i < 7; ++i)
		{
			vals[i] = enabled;
		}
	}

	int LitCount() const
	{
		return std::accumulate(&vals[0], &vals[7], 0);
	}

	friend std::istream& operator>>(std::istream& in, LetterCollection& letterInput);
};

std::istream& operator>>(std::istream& in, LetterCollection& letterInput)
{
	std::string str;
	in >> str;

	letterInput = LetterCollection(false);

	for (char c : str)
	{
		switch (c)
		{
		case 'a':
			letterInput.vals[A] = true;
			break;
		case 'b':
			letterInput.vals[B] = true;
			break;
		case 'c':
			letterInput.vals[C] = true;
			break;
		case 'd':
			letterInput.vals[D] = true;
			break;
		case 'e':
			letterInput.vals[E] = true;
			break;
		case 'f':
			letterInput.vals[F] = true;
			break;
		case 'g':
			letterInput.vals[G] = true;
			break;
		}
	}

	return in;
}

struct Mapping
{
	int values[7];

	Mapping() : values{ -1, -1, -1, -1, -1, -1, -1 }
	{}
};

static void RecursivePopulateOptions(std::vector<Mapping>& output, Mapping& scratch, std::vector<bool>& remainingValues, int index)
{
	if (index >= 7)
	{
		output.push_back(scratch);
		return;
	}

	for (int i = 0; i < 7; ++i)
	{
		if (remainingValues[i])
		{
			remainingValues[i] = false;
			scratch.values[index] = i;
			RecursivePopulateOptions(output, scratch, remainingValues, index + 1);
			remainingValues[i] = true;
		}
	}
}

static std::vector<Mapping> PopulateOptions()
{
	std::vector<Mapping> output;
	Mapping scratch;
	std::vector<bool> remainingValues{ true, true, true, true, true, true, true };

	RecursivePopulateOptions(output, scratch, remainingValues, 0);
	return output;
}

static int GetDigit(const LetterCollection& inputDigit)
{
	const bool *v = inputDigit.vals;
	if ( v[A] &&  v[B] &&  v[C] && !v[D] &&  v[E] &&  v[F] &&  v[G]) {return 0;}
	if (!v[A] && !v[B] &&  v[C] && !v[D] && !v[E] &&  v[F] && !v[G]) {return 1;}
	if ( v[A] && !v[B] &&  v[C] &&  v[D] &&  v[E] && !v[F] &&  v[G]) {return 2;}
	if ( v[A] && !v[B] &&  v[C] &&  v[D] && !v[E] &&  v[F] &&  v[G]) {return 3;}
	if (!v[A] &&  v[B] &&  v[C] &&  v[D] && !v[E] &&  v[F] && !v[G]) {return 4;}
	if ( v[A] &&  v[B] && !v[C] &&  v[D] && !v[E] &&  v[F] &&  v[G]) {return 5;}
	if ( v[A] &&  v[B] && !v[C] &&  v[D] &&  v[E] &&  v[F] &&  v[G]) {return 6;}
	if ( v[A] && !v[B] &&  v[C] && !v[D] && !v[E] &&  v[F] && !v[G]) {return 7;}
	if ( v[A] &&  v[B] &&  v[C] &&  v[D] &&  v[E] &&  v[F] &&  v[G]) {return 8;}
	if ( v[A] &&  v[B] &&  v[C] &&  v[D] && !v[E] &&  v[F] &&  v[G]) {return 9;}

	return -1;
}

static LetterCollection MapDigit(const LetterCollection& inputDigit, const Mapping& mapping)
{
	LetterCollection mappedDigit;
	for (int i = 0; i < 7; ++i)
	{
		mappedDigit.vals[mapping.values[i]] = inputDigit.vals[i];
	}

	return mappedDigit;
}

static int GetDigitForMapping(const LetterCollection& inputDigit, const Mapping& mapping)
{
	LetterCollection mappedDigit = MapDigit(inputDigit, mapping);

	return GetDigit(mappedDigit);
}

void Day8()
{
	std::vector<std::string> inputLines = GetLinesFromFile("input.txt");

	int totalUniqueVals = 0;

	int sum = 0;

	for (const std::string& str : inputLines)
	{
		std::istringstream stream(str);

		std::vector<LetterCollection> infoDigits;
		infoDigits.reserve(14);
		std::vector<LetterCollection> outputDigits;
		outputDigits.reserve(4);

		for (int i = 0; i < 10; ++i)
		{
			LetterCollection letterInput;
			stream >> letterInput;
			infoDigits.push_back(letterInput);
		}
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '|');
		for (int i = 0; i < 4; ++i)
		{
			LetterCollection letterInput;
			stream >> letterInput;
			infoDigits.push_back(letterInput);
			outputDigits.push_back(letterInput);

			int litCount = letterInput.LitCount();
			if (litCount == 2 || litCount == 4 || litCount == 3 || litCount == 7)
			{
				++totalUniqueVals;
			}
		}

		std::vector<Mapping> mappings = PopulateOptions();

		Mapping correctMapping;
		for (const Mapping& mapping : mappings)
		{
			bool validMapping = true;
			for (const LetterCollection& digit : infoDigits)
			{
				if (GetDigitForMapping(digit, mapping) == -1)
				{
					validMapping = false;
					break;
				}
			}
			if (validMapping)
			{
				correctMapping = mapping;
				break;
			}
		}

		int value =
			GetDigitForMapping(outputDigits[0], correctMapping) * 1000 +
			GetDigitForMapping(outputDigits[1], correctMapping) * 100 +
			GetDigitForMapping(outputDigits[2], correctMapping) * 10 +
			GetDigitForMapping(outputDigits[3], correctMapping) * 1;

		sum += value;
	}

	std::ofstream outFile("output.txt");
	std::cout << sum;
	outFile << sum;
}
