#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef vector<int>::size_type vsize;

vector<int> vecForm(int z) {
	vector<int> vec;
	int exp = 5;
	int rem;
	for (vsize i = 0; i < 6; ++i) {
		rem = int(z / pow (10, exp));
		vec.push_back(rem);
		z -= rem * pow(10,exp);
		exp--;
	}
	return vec;
}

bool notDecreasing(vector<int>& vec) {
	for (vsize i = 1; i < vec.size(); ++i) {
		if (vec[i-1] > vec[i]) return false;
	}
	return true;
}
bool has2repeat(vector<int> vec) {
  vector<int> vtemp;
  vtemp.push_back(vec[0]+1);
  vtemp.insert(vtemp.end(), vec.begin(), vec.end());
  vtemp.push_back(vec[vec.size()-1]+1);
  for (vsize i = 2; i < vec.size()+1; ++i) {
	  if (vtemp[i-2] != vtemp[i-1] && vtemp[i-1] == vtemp[i] && vtemp[i] != vtemp[i+1] ) return true;
	}
  return false;
}

int main()
{
	auto start = chrono::high_resolution_clock::now();
	int minp = 134792;
	int maxp = 675810;
	int numPass=0;
	vector<int> vec;
	for (int i = minp; i <= maxp; ++i) {
		vec = vecForm(i);
		// printvec(vec);
		if (notDecreasing(vec) && has2repeat(vec)) {
			numPass++;
		}
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << numPass << endl;
	cout << "Solution took: " << duration.count() << " milliseconds." << endl;
	return 0;
}
