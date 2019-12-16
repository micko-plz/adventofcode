#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

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

void computer(vector<int>& code, int input, int& output, bool& end_all, vsize& jk, vsize j, bool& phase_read) {
  int pMode1, pMode2;
  int hold_j;
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
        if (!phase_read) {
          code[code[j+1]] = input;
        }
        else {
          code[code[j+1]] = output;
        }
        phase_read = true;
        j+=2;
        break;
      case 4:
        output = code[code[j+1]];
        j+=2;
        hold_j = j;
        j = code.size();
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
        end_all = true;
        j = code.size();
        break;
      default:
        cout << "SWITCH ERROR!" << endl;
        exit(1);
    }  
  }
  jk = hold_j;
}

int main() {

  ifstream in;
  vector<int> code;
  vector<int> codeA;
  vector<int> codeB;
  vector<int> codeC;
  vector<int> codeD;
  vector<int> codeE;
  vector<int> combs;
  in.open("input.in");
  readinput(in, code);
  in.close();
  codeA = code;
  codeB = code;
  codeC = code;
  codeD = code;
  codeE = code;

  int myints[] = {5,6,7,8,9};
  vsize mypnts[] = {0, 0, 0, 0, 0};
  vector<int> codes[5] = {codeA, codeB, codeC, codeD, codeE};
  bool ph_read[] = {false, false, false, false, false};
  int output = 0;
  int maxout = 0;
  bool end_all = false;
  std::sort (myints,myints+5);
  do {
    while (!end_all) {
      for (int i = 0; i < 5; ++i) {
        computer(codes[i], myints[i], output, end_all, mypnts[i], mypnts[i], ph_read[i]);
        if (end_all) {
          break;
        }
      }
    }
    maxout = max(output, maxout);
    // reset all properties for next combination
    output = 0;
    fill(begin(mypnts), end(mypnts), 0);
    fill(begin(codes), end(codes), code);
    fill(begin(ph_read), end(ph_read), false);
    end_all = false;
  } while ( next_permutation(myints,myints+5) );

  cout << "max output: " << maxout << endl;
  return 0;
}

