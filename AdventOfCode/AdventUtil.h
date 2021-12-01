#pragma once

#include <vector>
#include <string>
#include <fstream>
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

template <typename T>
std::vector<T> GetValuesFromFile(const std::string& filename)
{
    std::vector<std::string> lines = GetLinesFromFile("input.txt");

    std::vector<T> outVec;

    for (const std::string& line : lines)
    {
        T value;
        std::stringstream(line) >> value;
        outVec.push_back(value);
    }

    return outVec;
}
