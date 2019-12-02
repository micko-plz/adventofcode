#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>


void readInput(std::fstream& in, std::vector<int>& v)
{
	int number = 0;
	char aux{};

	while (in >> number >> aux)
	{
		v.push_back(number);
	}

	in >> number;
	v.push_back(number);
}


int main()
{
   auto start = std::chrono::high_resolution_clock::now();
	std::fstream in("Intcode.txt", std::fstream::in);
	std::vector<int> v;

	readInput(in, v);
	std::vector<int> aux(v);

	for (int noun = 0; noun < 100; noun++)
	{
		for (int verb = 0; verb < 100; verb++)
		{
			v = aux;
			v[1] = noun;
			v[2] = verb;

			for (int currPos = 0; v[currPos] != 99; currPos += 4)
			{
				switch ((v[currPos]))
				{
				case 1:
					v[v[currPos + 3]] = v[v[currPos + 1]] + v[v[currPos + 2]];
					break;
				case 2:
					v[v[currPos + 3]] = v[v[currPos + 1]] * v[v[currPos + 2]];
					break;
				}
			}

			if (v[0] == 19690720)
			{
				std::cout << noun * 100 + verb;
				noun = 100;
				verb = 100;
			}
		}
	}
   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
   std::cout << "Solution took: " << duration.count() << " microseconds." << std::endl;

	in.close();
}