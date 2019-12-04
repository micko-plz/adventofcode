#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

typedef vector<int>::size_type vsize;


void printvec(const vector<int>& v) {
	for (vsize i = 0; i < v.size(); ++i) {
		cout << v[i] << " " ;
	}
	cout << "\n";
}

int intForm(const vector<int>& vec) {
	assert(vec.size() == 6);
	int num = 0;
	int exp = 5;
	for (vsize i = 0; i < vec.size(); ++i) {
		num += vec[i]*pow(10,exp);
		exp--;
	}
	return num;
}

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

bool hasAdjacent(vector<int>& vec){
	for (vsize i = 1; i < vec.size(); ++i) {
		if (vec[i-1] == vec[i]) {
			return true;
		}
	}
	return false;
}

bool notDecreasing(vector<int>& vec) {
	for (vsize i = 1; i < vec.size(); ++i) {
		if (vec[i-1] > vec[i]) return false;
	}
	return true;
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
		if (hasAdjacent(vec) && notDecreasing(vec)) {
			numPass++;
		}
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << numPass << endl;
	cout << "Solution took: " << duration.count() << " microseconds." << endl;
	return 0;
}
