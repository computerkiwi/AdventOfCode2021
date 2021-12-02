#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "AdventUtil.h"

void Day2()
{
    std::vector<std::string> lines = GetLinesFromFile("input.txt");
    std::ofstream outFile("output.txt");

    int hPos = 0;
    int depth = 0;

    for (const std::string& str : lines)
    {
        std::stringstream stream(str, std::stringstream::in);

        std::string command;
        int num;

        stream >> command;
        stream >> num;

        if (command == "forward")
        {
            hPos += num;
        }
        else if (command == "down")
        {
            depth += num;
        }
        else if (command == "up")
        {
            depth -= num;
        }
    }

    std::cout << (depth * hPos);
    outFile << (depth * hPos);
}
