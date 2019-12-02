#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <chrono>

int getOutput(vector<int> csv, const int& input1, const int& input2) {
  
  typedef vector<int>::iterator iter_t;
  iter_t pos1;
  iter_t pos2;
  iter_t pos3;
  iter_t begin = csv.begin();
  csv[1] = input1;
  csv[2] = input2;

  for (iter_t iter = csv.begin(); iter != csv.end(); iter+=4) 
   {
      if (*iter == 1) {
         *(begin+*(iter+3)) = *(begin+*(iter+1)) + *(begin+*(iter+2)); 
      }
      else if (*iter == 2)
      {
         *(begin+*(iter+3)) = *(begin+*(iter+1)) * *(begin+*(iter+2));
      }
      else if (*iter == 99)
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