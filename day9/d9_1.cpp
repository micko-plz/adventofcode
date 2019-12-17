#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;

typedef vector<long long>::size_type vsize;


void printvec(const vector<long long>& v) {
	for (vsize i = 0; i < v.size(); ++i) {
		cout << v[i] << " " ;
	}
	cout << "\n";
}

void readinput(ifstream& in, vector<long long>& vec) {
  string number;
  while( getline(in, number, ',') )
  {
    vec.push_back(stoll(number));
  }
}

vector<long long> vecForm(long long z) {
	vector<long long> vec;
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

int deCode(long long& z, int& pMode1, int& pMode2, int& pMode3) {
  vector<long long> vz = vecForm(z);
  vsize vsz = 5;
  int opCode = 10*vz[vsz-2] + vz[vsz-1];
  pMode1 = vz[vsz-3];
  pMode2 = vz[vsz-4];
  pMode3 = vz[vsz-5];
  return opCode;
}
  
enum parameter_mode{position=0, immediate=1, relative=2};

long long getValue(const vector<long long>& vec, int idx, int& pMode, int relative_base) {
  if (pMode == position) return vec[vec[idx]];
  else if (pMode == immediate) return vec[idx];
  else if (pMode == relative) return vec[vec[idx] + relative_base];
  else { 
    cout << "PMODE ERROR!" << endl;
    return 0;
  }
}

long long giveValue(vector<long long>& vec, int idx, int& pMode, int relative_base, long long input) {
  if (pMode == position) vec[vec[idx]] = input;
  else if (pMode == immediate) vec[idx] = input;
  else if (pMode == relative) vec[vec[idx] + relative_base] = input;
  else { 
    cout << "PMODE ERROR!" << endl;
  }
}

void debug(vector<long long> code, int cas, int j, int pMode1, int pMode2, int pMode3, int relative_base) {
  // cout << "Case: " << cas << endl;
  // cout << "Pntr: " << j << endl;
  // cout << "Code here: " << code[j] << endl;
  // cout << "pMode1: " << pMode1 << endl;
  // cout << "pMode2: " << pMode2 << endl;
  // cout << "pMode3: " << pMode3 << endl;
  // cout << "val1: " << getValue(code, j+1, pMode1, relative_base) << endl;
  // cout << "val2: " << getValue(code, j+2, pMode2, relative_base) << endl;
  // cout << "relbase: " << relative_base << endl;
  // cout << "\n" << endl;
}

int main()
{
  // extra size
  long long int extra = 100000;
  vector<long long int> vextra(extra, 0);

  auto start = std::chrono::high_resolution_clock::now();
  // read in values to vector of ints
  ifstream in;
  vector<long long> code;
  in.open("input.in");
  readinput(in, code);
  in.close();
  copy(vextra.begin(),vextra.end(),back_inserter(code));
  long long code_sz = code.size();

  // printvec(code);
  int pMode1, pMode2, pMode3;
  long long input;
  vsize j = 0;
  int iters = 0;
  long long val;
  int relative_base = 0;
  while (j < code.size()) 
  { 
    iters++;
    switch (deCode(code[j], pMode1, pMode2, pMode3))
    {
      case 1:
        debug(code, 1, j, pMode1, pMode2, pMode3, relative_base);
        val = getValue(code, j+1, pMode1, relative_base) + getValue(code, j+2, pMode2, relative_base);
        giveValue(code, j+3, pMode3, relative_base, val);
        j+=4;
        break;
      case 2:
        debug(code, 2, j, pMode1, pMode2, pMode3, relative_base);
        val = getValue(code, j+1, pMode1, relative_base) * getValue(code, j+2, pMode2, relative_base);
        giveValue(code, j+3, pMode3, relative_base, val);
        j+=4;
        break;
      case 3:
        debug(code, 3, j, pMode1, pMode2, pMode3, relative_base);
        cout<<"Enter your number: ";
        cin>>input;
        start = std::chrono::high_resolution_clock::now();
        giveValue(code, j+1, pMode1, relative_base, input);
        j+=2;
        break;
      case 4:
        debug(code, 4, j, pMode1, pMode2, pMode3, relative_base);
        cout << getValue(code, j+1, pMode1, relative_base) << endl;
        j+=2;
        break;
      case 5:
        debug(code, 5, j, pMode1, pMode2, pMode3, relative_base);
        if (getValue(code, j+1, pMode1, relative_base) != 0) j = getValue(code, j+2, pMode2, relative_base);
        else j+=3;
        break;
      case 6:
        debug(code, 6, j, pMode1, pMode2, pMode3, relative_base);
        if (getValue(code, j+1, pMode1, relative_base)  == 0) j = getValue(code, j+2, pMode2, relative_base) ;
        else j+=3;
        break;
      case 7:
        debug(code, 7, j, pMode1, pMode2, pMode3, relative_base);
        if (getValue(code, j+1, pMode1, relative_base)  < getValue(code, j+2, pMode2, relative_base)) giveValue(code, j+3, pMode3, relative_base, 1);
        else giveValue(code, j+3, pMode3, relative_base, 0);
        j+=4;
        break;
      case 8:
        debug(code, 8, j, pMode1, pMode2, pMode3, relative_base);
        if (getValue(code, j+1, pMode1, relative_base)  == getValue(code, j+2, pMode2, relative_base)) giveValue(code, j+3, pMode3, relative_base, 1);
        else giveValue(code, j+3, pMode3, relative_base, 0);
        j+=4;
        break;
      case 9:
        debug(code, 9, j, pMode1, pMode2, pMode3, relative_base);
        relative_base += getValue(code, j+1, pMode1, relative_base);
        j+=2;
        break;
      case 99:
        debug(code, 99, j, pMode1, pMode2, pMode3, relative_base);
        j = code.size();
        break;
      default:
        cout << "SWITCH ERROR!" << endl;
        return 0;
    }
    if (j > code_sz) {
      cout << j;
      cout << "vec not big enough" << endl;
    }
  }
  cout << "\n";
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Solution took: " << duration.count() << " microseconds" << " for " << iters << " iterations." << std::endl;
  return 0;
}