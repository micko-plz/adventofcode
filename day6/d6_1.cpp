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
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

class orbital {
  public:

    orbital(string planet = " ", string orbiting = " ", int num_orbits = -1) : planet_name(planet), dir_orbiting(orbiting), num_orbits(num_orbits) {}

    string planet() const {return planet_name; }
    string orbiting() const {return dir_orbiting; }

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
          temp_orb = "COM";  
        }
        else if (start_it == orbits.end())
        {
          cout << "fucked iteration" << endl;
          return 0;
        }
        else {
          temp_orb = start_it->orbiting();
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

};



int main() {
    string x;
    ifstream inFile;
    
    inFile.open("input.in");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    char delim = ')'; 
    int o = 0;
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
        else
        {
          cout << "Youre fucked" << endl;
        }
        i++;
      }
      i = 0;
    }
    
    inFile.close();
    
    int numOrbits = 0;
    for (vsize i = 0; i < orbits.size(); ++i) {
      numOrbits += orbits[i].getDisttoCOM(orbits);
    }
    cout << numOrbits << endl;
    return 0;
}