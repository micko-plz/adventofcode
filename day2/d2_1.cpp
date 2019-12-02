#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
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

   int num;
   int pos1;
   int pos2;
   int pos3;
   // update so that runs with iterators
   for (vector<int>::size_type j; j < csvData.size(); j+=4) 
   {
      num = csvData[j];
      pos1 = csvData[j+1];
      pos2 = csvData[j+2];
      pos3 = csvData[j+3];

      if (num == 1) {
         csvData[pos3] = csvData[pos1] + csvData[pos2]; 
      }
      else if (num == 2)
      {
         csvData[pos3] = csvData[pos1] * csvData[pos2];
      }
      else if (num == 99)
      {
         break;
      }
   }

   cout << csvData[0] << endl;
   return 0;
}