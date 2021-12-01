// AdventOfCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>

std::vector<std::string> GetLinesFromFile(const std::string& filename, bool clearTrailingWhitespace = true)
{
    std::vector<std::string> outVec;

    std::ifstream file("input.txt", std::ifstream::in);

    std::stringbuf buffer;
    while (file.get(buffer, '\n'))
    {
        outVec.push_back(buffer.str());
        buffer.str(std::string());
        // Clear out the delimiter.
        file.get();
    }

    while (clearTrailingWhitespace && outVec.size() > 0 && outVec.back().empty())
    {
        outVec.pop_back();
    }

    return outVec;
}

int main()
{
    std::vector<std::string> lines = GetLinesFromFile("input.txt");
    std::ofstream outFile("output.txt");

    int prev = INT_MAX;
    int count = 0;

    std::vector<int> nums;

    for (const std::string& line : lines)
    {
        int num;
        std::stringstream(line) >> num;
        nums.push_back(num);
    }


    for (int i = 0; i < nums.size() - 2; ++i)
    {
        int sum = nums[i] + nums[i + 1] + nums[i + 2];

        if (sum > prev)
        {
            ++count;
        }

        prev = sum;
    }

    outFile << count;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
