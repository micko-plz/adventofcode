#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class coord
{
public:
	coord(int x = 0, int y = 0) : x(x), y(y) {}

	static int manhattanDistance(const coord& c1, const coord& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y);
	}

	bool operator==(const coord& c)
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
};



void readInput(fstream& in, list<coord>& wire1path)
{
	coord currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				wire1path.push_back(coord(currPos.x, currPos.y));
			}
			break;
		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				wire1path.push_back(coord(currPos.x, currPos.y));
			}
			break;
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				wire1path.push_back(coord(currPos.x, currPos.y));
			}
			break;
		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				wire1path.push_back(coord(currPos.x, currPos.y));
			}
		default:
			break;
		}
		in >> aux;
	}
}


void readInput2(fstream& in, list<coord>& wire1path, vector<coord>& intersections)
{
	list<coord>::iterator it = wire1path.end();
	coord currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				if ((it = find(wire1path.begin(), wire1path.end(), currPos)) != wire1path.end())
				{
					intersections.push_back(coord(currPos.x, currPos.y));
				}
			}
			break;
		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				if ((it = find(wire1path.begin(), wire1path.end(), currPos)) != wire1path.end())
				{
					intersections.push_back(coord(currPos.x, currPos.y));
				}
			}
			break;
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				if ((it = find(wire1path.begin(), wire1path.end(), currPos)) != wire1path.end())
				{
					intersections.push_back(coord(currPos.x, currPos.y));
				}
			}
			break;
		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				if ((it = find(wire1path.begin(), wire1path.end(), currPos)) != wire1path.end())
				{
					intersections.push_back(coord(currPos.x, currPos.y));
				}
			}
		default:
			break;
		}
		in >> aux;
	}
}


int main()
{
   auto start = chrono::high_resolution_clock::now();
	fstream in("input.in", fstream::in);
	fstream in2("input2.in", fstream::in);
	vector<coord> intersections;
	list<coord> wire1path;

	readInput(in, wire1path);
	readInput2(in2, wire1path, intersections);

	int minDist = coord::manhattanDistance(coord(0, 0), (*(intersections.begin())));
	for (auto it = intersections.begin() + 1; it != intersections.end(); it++)
	{
		if (coord::manhattanDistance(coord(0, 0), (*it)) < minDist)
		{
			minDist = coord::manhattanDistance(coord(0, 0), (*it));
		}
	}

   auto stop = chrono::high_resolution_clock::now();
   auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
   cout << "Solution took: " << duration.count() << " seconds." << endl;
	 cout << "answer: " << minDist << endl;

	in.close();
}
