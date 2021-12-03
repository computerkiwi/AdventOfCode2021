#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AdventUtil.h"


bool onesCommon(const std::vector<std::string>& binaryValues, int digit)
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

void Day3()
{
    std::vector<std::string> lines = GetLinesFromFile("input.txt");
    std::ofstream outFile("output.txt");

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
}
