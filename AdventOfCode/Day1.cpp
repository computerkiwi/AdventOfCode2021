#include <iostream>
#include <string>
#include <vector>
#include "AdventUtil.h"

int GetNumberOfIncreasingWindows(const std::vector<int>& nums, int windowSize)
{
    int prev = INT_MAX;
    int count = 0;

    for (int i = 0; i < nums.size() - (windowSize - 1); ++i)
    {
        int sum = 0;
        for (int j = 0; j < windowSize; ++j)
        {
            sum += nums[i + j];
        }

        if (sum > prev)
        {
            ++count;
        }
        prev = sum;
    }

    return count;
}

void Day1()
{
    std::vector<int> nums = GetValuesFromFile<int>("input.txt");
    std::ofstream outFile("output.txt");

    int countSize1 = GetNumberOfIncreasingWindows(nums, 1);
    int countSize3 = GetNumberOfIncreasingWindows(nums, 3);

    outFile << "Part 1 count:\n" << countSize1 << '\n' << "Part 2 count:\n" << countSize3;
    std::cout << "Part 1 count:\n" << countSize1 << '\n' << "Part 2 count:\n" << countSize3;
}
