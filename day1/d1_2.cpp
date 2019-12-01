#include <fstream>
#include <vector>
#include <iostream>
#include <assert.h>
#include <chrono>

int fuel_alg(int mass) {
  return (mass / 3) - 2;
}

int fuel4fuel(int most_recent_fuel_calc, int sum_fuel) {

  assert(most_recent_fuel_calc > 0);
  sum_fuel += most_recent_fuel_calc;

  if (fuel_alg(most_recent_fuel_calc) <= 0) {
    return sum_fuel;
  }
  else
  {
    fuel4fuel(fuel_alg(most_recent_fuel_calc), sum_fuel);
  }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // Read in 100 masses
    std::vector<int> mass_vec;
    int element;

    std::ifstream in;
    in.open("ModuleMass.txt");

    if (in.is_open()) {
        while (in >> element) {
            mass_vec.push_back(element);
        }
    }
    in.close();

    // Check have correct dimension
    assert (mass_vec.size() == 100);

    int sum_fuel;
    int sum_all_modules = 0;
    double avg_time = 0.0;
    for (std::vector<int>::size_type i = 0; i != mass_vec.size(); ++i) {
        sum_fuel = 0;
        sum_all_modules += fuel4fuel(fuel_alg(mass_vec[i]), sum_fuel);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << sum_all_modules << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Solution took: " << duration.count() << " microseconds." << std::endl;
    return 0;
}

