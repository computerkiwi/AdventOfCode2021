#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AdventUtil.h"

template<typename T>
class Grid
{
private:
	std::vector<T> m_data;
	int m_w;
	int m_h;
public:
	Grid(int w, int h) :
		m_w(w),
		m_h(h),
		m_data(w * h)
	{
	}

	T& At(int x, int y)
	{
		return m_data[x + y * m_w];
	}

	int Width() const
	{
		return m_w;
	}

	int Height() const
	{
		return m_h;
	}

	typename std::vector<T>::iterator begin()
	{
		return m_data.begin();
	}
	typename std::vector<T>::iterator end()
	{
		return m_data.end();
	}
};

struct Vec2
{
	int x;
	int y;

	Vec2 operator+(const Vec2& other) const
	{
		Vec2 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		return vec;
	}

	bool operator==(const Vec2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vec2& other) const
	{
		return !(*this == other);
	}
};

static int Sign(int x)
{
	return (x > 0) - (x < 0);
}

struct Line2D
{
	Vec2 a;
	Vec2 b;

	static Line2D FromInputLine(const std::string& input)
	{
		Line2D line;

		sscanf(input.c_str(), "%d,%d -> %d,%d", &line.a.x, &line.a.y, &line.b.x, &line.b.y);

		return line;
	}

	int MaxX() const
	{
		return std::max(a.x, b.x);
	}
	int MaxY() const
	{
		return std::max(a.y, b.y);
	}

	Vec2 Direction() const
	{
		Vec2 vec;
		// Can just use sign, assuming 8 cardinal directions
		vec.x = Sign(b.x - a.x);
		vec.y = Sign(b.y - a.y);
		return vec;
	}

	// How many steps of length Direction() do we have to make to reach the end.
	int DirectionSteps() const
	{
		return std::max(std::abs(b.x - a.x), std::abs(b.y - a.y));
	}
};

void Day5()
{
	std::vector<std::string> inputLines = GetLinesFromFile("input.txt");

	std::vector<Line2D> lines;
	int maxX = 0;
	int maxY = 0;
	for(const std::string& input : inputLines)
	{
		Line2D line = Line2D::FromInputLine(input);
		/*
		// Remove diagonals for part 1
		Vec2 dir = line.Direction();
		if (dir.x != 0 && dir.y != 0)
		{
			continue;
		}
		*/

		maxX = std::max(maxX, line.MaxX());
		maxY = std::max(maxY, line.MaxY());
		lines.push_back(line);
	}

	Grid<int> grid(maxX + 1, maxY + 1);

	for (const Line2D& line : lines)
	{
		Vec2 point = line.a;
		Vec2 dir = line.Direction();
		while (true)
		{
			++grid.At(point.x, point.y);

			if (point == line.b)
			{
				break;
			}
			point = point + dir;
		}
	}

	int overlapCount = std::count_if(grid.begin(), grid.end(), [](int val) { return val >= 2; });

	std::ofstream outFile("output.txt");
	std::cout << overlapCount;
	outFile << overlapCount;
}
