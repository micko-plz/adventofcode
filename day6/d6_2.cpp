// #include <iostream>
// #include <fstream>
// #include <sstream>
#include <vector>
#include <algorithm>
// #include <cmath>
// 
// using namespace std;

#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

void print_vector(const vector<string>& v) {
  for (vector<string>::size_type j = 0; j < v.size(); ++j) {
    cout << v[j] << endl;
  }
}


class orbital {
  public:

    orbital(string planet = " ", string orbiting = " ", int num_orbits = -1) : 
        planet_name(planet), dir_orbiting(orbiting), num_orbits(num_orbits), pathCOM{planet, orbiting} {}

    string planet() const {return planet_name; }
    string orbiting() const {return dir_orbiting; }
    vector<string> path() const {return pathCOM; }

    static bool found_parent(orbital o, string child) {
      if (o.planet() == child) {
        return true;
      }
      else {
        return false;
      }
    }

    int getDisttoCOM(vector<orbital>& orbits) {
      string temp_orb = dir_orbiting;
      num_orbits = 0;
      vector<orbital>::const_iterator start_it = orbits.begin();
      while (temp_orb != "COM") {
        start_it = find_if(orbits.begin(), orbits.end(), std::bind(found_parent,  std::placeholders::_1 , temp_orb) );
        if (start_it->num_orbits != -1) {
          num_orbits += start_it->num_orbits;
          copy(start_it->pathCOM.begin(), start_it->pathCOM.end(), back_inserter(pathCOM)); 
          temp_orb = "COM";  
        }
        else {
          temp_orb = start_it->orbiting();
          pathCOM.push_back(temp_orb);
          num_orbits++;
        }
      }
      num_orbits++;
      return num_orbits;
    }

  private:
    string planet_name;
    string dir_orbiting;
    int num_orbits;
    vector<string> pathCOM;

};



int main() {

    // Read In
    string x;
    ifstream inFile;
    
    inFile.open("input.in");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    char delim = ')'; 
    int i = 0;
    vector<orbital> orbits;
    typedef vector<orbital>::size_type vsize;
    typedef vector<orbital>::iterator vit;
    string planet;
    string orbiting;
    while (inFile >> x) {
      std::stringstream ss(x);
      std::string token;
      while (std::getline(ss, token, delim)){
        if (i == 0) {
          orbiting = token;
        }
        else if (i == 1)
        {
          planet = token;
          orbits.push_back(orbital(planet, orbiting));
        }
        i++;
      }
      i = 0;
    }
    
    inFile.close();
    
    // Algs
    int indme;
    int indsan;
    for (vsize i = 0; i < orbits.size(); ++i) {
      if (orbits[i].planet() == "YOU") {
        indme = i;
        orbits[i].getDisttoCOM(orbits);
      } 
      else if (orbits[i].planet() == "SAN") {
        indsan = i;
        orbits[i].getDisttoCOM(orbits);
      }
    }

    vector<string> san_path = orbits[indsan].path();
    vector<string>::iterator iter;
    vector<string>::iterator sanbeg = san_path.begin();
    vector<string>::iterator sanend = san_path.end();

    // find first intersection
    for (vector<string>::size_type j = 0; j < orbits[indme].path().size(); ++j){
      iter = find(sanbeg, sanend, orbits[indme].path()[j]);
      if (iter != sanend) {
        cout << "dist: " << j + (iter - sanbeg) - 2  << endl;
        return 0;
      }
    }
    cout << "Error";
    return 0;
}