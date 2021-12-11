#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

static std::vector<std::string> SplitString(const std::string& str, char delim)
{
    std::vector<std::string> result;

    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

static std::vector<std::string> GetLinesFromFile(const std::string& filename, bool clearTrailingWhitespace = true)
{

    std::ifstream file("input.txt", std::ifstream::in);

    std::stringbuf buffer; 
    file.get(buffer, EOF);

    std::vector<std::string> outVec = SplitString(buffer.str(), '\n');

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
