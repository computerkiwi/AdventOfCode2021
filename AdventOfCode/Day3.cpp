#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AdventUtil.h"


bool OnesCommon(const std::vector<std::string>& binaryValues, int digit)
{
    int count = 0;
    for (const std::string& str : binaryValues)
    {
        if (str[digit] == '1')
        {
            ++count;
        }
    }

    return count >= (binaryValues.size() - count);
}

unsigned int BinaryStringToUint(const std::string& str)
{
    unsigned int value = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == '1')
        {
            value |= 1 << (str.size() - 1 - i);
        }
    }
    return value;
}

unsigned int OxygenGeneratorRating(const std::vector<std::string>& binaryValues)
{
    std::vector<std::string> current(binaryValues), next;

    for (int digit = 0; digit < binaryValues[0].size(); ++digit)
    {
        bool onesCommon = OnesCommon(current, digit);
        for (int i = 0; i < current.size(); ++i)
        {
            if (current[i][digit] == (onesCommon ? '1' : '0'))
            {
                next.push_back(current[i]);
            }
        }

        std::swap(current, next);
        next.clear();

        if (current.size() == 1)
        {
            return BinaryStringToUint(current[0]);
        }
    }

    // Shouldn't get here.
    throw "panic!";
}

unsigned int CO2GeneratorRating(const std::vector<std::string>& binaryValues)
{
    std::vector<std::string> current(binaryValues), next;

    for (int digit = 0; digit < binaryValues[0].size(); ++digit)
    {
        bool onesCommon = OnesCommon(current, digit);
        for (int i = 0; i < current.size(); ++i)
        {
            if (current[i][digit] == (onesCommon ? '0' : '1'))
            {
                next.push_back(current[i]);
            }
        }

        std::swap(current, next);
        next.clear();

        if (current.size() == 1)
        {
            return BinaryStringToUint(current[0]);
        }
    }

    // Shouldn't get here.
    throw "panic!";
}

void Day3()
{
    std::vector<std::string> lines = GetLinesFromFile("input.txt");
    std::ofstream outFile("output.txt");

    /*
    std::vector<int> oneCounts(lines[0].length());

    for (const std::string& str : lines)
    {
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] == '1')
            {
                ++oneCounts[i];
            }
        }
    }

    unsigned int gammaRate = 0;
    for (int i = 0; i < oneCounts.size(); ++i)
    {
        bool oneCommon = oneCounts[i] > lines.size() / 2;

        if (oneCommon)
        {
            gammaRate = gammaRate | (1 << (oneCounts.size() - 1 - i));
        }
    }

    unsigned int bitmask = 0;
    for (int i = 0; i < oneCounts.size(); ++i)
    {
        bitmask |= 1 << i;
    }

    unsigned int epsilonRate = (~gammaRate) & bitmask;

    std::cout << (gammaRate * epsilonRate);
    outFile << (gammaRate * epsilonRate);
    */

    unsigned int oxygenGeneratorRating = OxygenGeneratorRating(lines);
    unsigned int co2GeneratorRating = CO2GeneratorRating(lines);

    std::cout << oxygenGeneratorRating * co2GeneratorRating;
    outFile << oxygenGeneratorRating * co2GeneratorRating;
}
