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

void computer(vector<int> code, int input, int& output) {
  int pMode1, pMode2;
  bool input_read = false;
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
        if (!input_read) {
          cout << "input1: " << input << endl;
          code[code[j+1]] = input;
          input_read = true;
        }
        else {
          cout << "ouputRec: " << output << endl;
          code[code[j+1]] = output;
        }
        j+=2;
        break;
      case 4:
        output = code[code[j+1]];
        cout << "ouputEnd: " << output << endl;

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
        exit(1);
    }  
  }
}

int main() {

  ifstream in;
  vector<int> code;
  vector<int> combs;
  vector<vector<int>> all_combs;
  in.open("input.in");
  readinput(in, code);
  in.close();

  int myints[] = {0,1,2,3,4};
  int output = 0;
  int maxout = 0;
  std::sort (myints,myints+5);
  do {
    cout << "code: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << ' ' << myints[4] << "\n";
    for (int i = 0; i < 5; ++i) {
      computer(code, myints[i], output);

    }
    cout << "output after 5: " << output << endl;
    cout << "\n" << endl;
    maxout = max(output, maxout);
    output = 0;
  } while ( next_permutation(myints,myints+5) );

  cout << "max output: " << maxout << endl;
  return 0;
}

