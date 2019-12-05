#include <vector> 
#include <iostream>
#include <cmath>

using namespace std;

typedef vector<int>::size_type vsize;

vector<int> vecForm(int z) {
	vector<int> vec;
	int exp = 4;
	int rem;
	for (vsize i = 0; i < 5; ++i) {
		rem = int(z / pow (10, exp));
		vec.push_back(rem);
		z -= rem * pow(10,exp);
		exp--;
	}
	return vec;
}
void printvec(const vector<int>& v) {
	for (vsize i = 0; i < v.size(); ++i) {
		cout << v[i] << " " ;
	}
	cout << "\n";
}

int deCode(int& z, int& pMode1, int& pMode2) {
  vector<int> vz = vecForm(z);
  printvec(vz);
  vsize vsz = 5;
  int opCode = 10*vz[vsz-2] + vz[vsz-1];
  pMode1 = vz[vsz-3];
  pMode2 = vz[vsz-4];
  return opCode;
}

int main() {
  int num = 1002;
  int pMode1, pMode2, code;

  code = deCode(num, pMode1, pMode2);
  cout << code << " " << pMode1 << " " << pMode2 << endl;
  return 0;
}