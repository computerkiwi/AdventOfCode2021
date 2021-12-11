#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AdventUtil.h"

class Board5x5
{
public:
	int numbers[5][5];
	bool marked[5][5];

	bool won = false;

	template <typename Iter>
	Board5x5(Iter stringsIter)
	{
		for (int y = 0; y < 5; ++y)
		{
			std::stringstream stream(*stringsIter);

			for (int x = 0; x < 5; ++x)
			{
				stream >> numbers[x][y];
				marked[x][y] = false;
			}

			++stringsIter;
		}
	}

	bool CheckRow(int y)
	{
		for (int x = 0; x < 5; ++x)
		{
			if (!marked[x][y])
			{
				return false;
			}
		}

		return true;
	}

	bool CheckCol(int x)
	{
		for (int y = 0; y < 5; ++y)
		{
			if (!marked[x][y])
			{
				return false;
			}
		}

		return true;
	}

	bool MarkAndCheck(int number)
	{
		if (won)
		{
			return false;
		}

		for (int x = 0; x < 5; ++x)
		{
			for (int y = 0; y < 5; ++y)
			{
				if (numbers[x][y] == number)
				{
					// Assuming no duplicate numbers per board.
					marked[x][y] = true;
					won = CheckCol(x) || CheckRow(y);
					if (won)
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	int SumOfUnmarkedNumbers()
	{
		int sum = 0;

		for (int x = 0; x < 5; ++x)
		{
			for (int y = 0; y < 5; ++y)
			{
				if (!marked[x][y])
				{
					sum += numbers[x][y];
				}
			}
		}

		return sum;
	}
};

static std::vector<int> GetNumbersFromCallString(const std::string& str)
{
	auto values = SplitString(str, ',');

	std::vector<int> numbers;
	for (const std::string& str : values)
	{
		numbers.push_back(std::atoi(str.c_str()));
	}

	return numbers;
}

static void Day4()
{
	std::vector<std::string> lines = GetLinesFromFile("input.txt");

	auto iter = lines.begin() + 2;

	std::vector<Board5x5> boards;

	while (iter != lines.end())
	{
		boards.push_back(Board5x5(iter));
		if (lines.end() - iter > 6)
		{
			iter += 6;
		}
		else
		{
			iter = lines.end();
		}
	}

	std::vector<int> numbers = GetNumbersFromCallString(lines[0]);

	int firstAnswer = -1;
	int lastAnswer = -1;

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		int number = numbers[i];

		for (Board5x5& board : boards)
		{
			if (board.MarkAndCheck(number))
			{
				lastAnswer = board.SumOfUnmarkedNumbers() * number;

				if (firstAnswer == -1)
				{
					firstAnswer = lastAnswer;
				}
			}
		}
	}

	std::ofstream outFile("output.txt");
	std::cout << lastAnswer;
	outFile << lastAnswer;
}
