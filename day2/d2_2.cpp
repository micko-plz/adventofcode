#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <chrono>

int getOutput(vector<int> csv, const int& input1, const int& input2) {
  
  int num;
  int pos1;
  int pos2;
  int pos3;
  csv[1] = input1;
  csv[2] = input2;

  for (vector<int>::size_type j; j < csv.size(); j+=4) 
   {
      num = csv[j];
      pos1 = csv[j+1];
      pos2 = csv[j+2];
      pos3 = csv[j+3];

      if (num == 1) {
         csv[pos3] = csv[pos1] + csv[pos2]; 
      }
      else if (num == 2)
      {
         csv[pos3] = csv[pos1] * csv[pos2];
      }
      else if (num == 99)
      {
         break;
      }
   }
   return csv[0];
}

int main()
{
   auto start = chrono::high_resolution_clock::now();
   // read in values to vector of ints
   ifstream in;
   string number;
   vector<int> csvData;
   in.open("Intcode.txt");
   while( getline(in, number, ',') )
   {
      csvData.push_back(stoi(number));
   }
   in.close();
   for (int input1 = 0; input1 < 100; ++input1) {
     for (int input2 = 0; input2 < 100; ++input2) {
       if (getOutput(csvData, input1, input2) == 19690720) {
         auto stop = chrono::high_resolution_clock::now();
         cout << input1 << " " << input2 << endl;
         auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
         std::cout << "Solution took: " << duration.count() << " microseconds." << std::endl;
         return  0;
       }
     }
   }
}