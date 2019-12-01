#include <fstream>
#include <vector>
#include <iostream>
#include <assert.h>
#include <chrono>

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    // Read in 100 masses
    std::ifstream in;
    in.open("ModuleMass.txt");
    std::vector<int> v;
    int element;

    if (in.is_open()) {
        while (in >> element) {
            v.push_back(element);
        }
    }
    in.close();

    // Check have correct dimension
    // assert (v.size() == 100);

    // perform algorithm : for each mass, divide by 3, round down, then subtract 2
    int sum = 0;
    for (std::vector<int>::size_type i = 0; i != v.size(); ++i) {
        sum += (v[i] / 3) - 2;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << sum << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Solution took: " << duration.count() << " microseconds." << std::endl;
    return 0;
}
