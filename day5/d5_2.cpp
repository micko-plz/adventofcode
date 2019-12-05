#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

typedef vector<int>::size_type vsize;


void printvec(const vector<int>& v) {
	for (vsize i = 0; i < v.size(); ++i) {
		cout << v[i] << " " ;
	}
	cout << "\n";
}

void readinput(ifstream& in, vector<int>& vec) {
  string number;
  while( getline(in, number, ',') )
  {
    vec.push_back(stoi(number));
  }
}

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

int deCode(int& z, int& pMode1, int& pMode2) {
  vector<int> vz = vecForm(z);
  vsize vsz = 5;
  int opCode = 10*vz[vsz-2] + vz[vsz-1];
  pMode1 = vz[vsz-3];
  pMode2 = vz[vsz-4];
  return opCode;
}
  
enum parameter_mode{position=0, immediate=1};

int getValue(const vector<int>& vec, int idx, int& pMode) {
  if (pMode == position) return vec[vec[idx]];
  else if (pMode == immediate) return vec[idx];
  else { 
    cout << "PMODE ERROR!" << endl;
    return 0;
  }
}

int main()
{
  
  auto start = std::chrono::high_resolution_clock::now();
  // read in values to vector of ints
  ifstream in;
  vector<int> code;
  in.open("input.in");
  readinput(in, code);
  in.close();


  int pMode1, pMode2;
  int input;
  vsize j = 0;
  int iters = 0;
  while (j < code.size()) 
  { 
    iters++;
    switch (deCode(code[j], pMode1, pMode2))
    {
      case 1:
        code[code[j+3]] = getValue(code, j+1, pMode1) + getValue(code, j+2, pMode2);
        j+=4;
        break;
      case 2:
        code[code[j+3]] = getValue(code, j+1, pMode1) * getValue(code, j+2, pMode2);
        j+=4;
        break;
      case 3:
        cout<<"Enter your number: ";
        cin>>input;
        start = std::chrono::high_resolution_clock::now();
        code[code[j+1]] = input;
        j+=2;
        break;
      case 4:
        cout << code[code[j+1]] << endl;
        j+=2;
        break;
      case 5:
        if (getValue(code, j+1, pMode1) != 0) j = getValue(code, j+2, pMode2);
        else j+=3;
        break;
      case 6:
        if (getValue(code, j+1, pMode1)  == 0) j = getValue(code, j+2, pMode2) ;
        else j+=3;
        break;
      case 7:
        if (getValue(code, j+1, pMode1)  < getValue(code, j+2, pMode2)) code[code[j+3]] = 1;
        else code[code[j+3]] = 0;
        j+=4;
        break;
      case 8:
        if (getValue(code, j+1, pMode1)  == getValue(code, j+2, pMode2)) code[code[j+3]] = 1;
        else code[code[j+3]] = 0;
        j+=4;
        break;
      case 99:
        j = code.size();
        break;
      default:
        cout << "SWITCH ERROR!" << endl;
        return 0;
    }  
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Solution took: " << duration.count() << " microseconds" << " for " << iters << " iterations." << std::endl;
  return 0;
}