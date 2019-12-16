#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct image {

  vector<int> row;
  vector<vector<int>> im;

  int getNumVal(int val) {
    int numVal = 0;
    for (int i = 0; i < im.size(); ++i) {
      numVal += count(im[i].begin(), im[i].end(), val);
    }
    return numVal;
  }

  void printIm() {
    for (int i = 0; i < im.size(); ++i) {
      for (int j = 0; j < im[i].size(); ++j) {
        cout << im[i][j] << " ";
      }
      cout << "\n";
    }
  }
};

void printRow(vector<int> row) {
  for (int j = 0; j < row.size(); ++j) {
    cout << row[j] << " ";
  }
  cout << "\n";
}

int main() {

  string pixels;
  std::ifstream("input.in") >> pixels;

  vector<image> images;

  int row_lim = 6;
  int col_lim = 25;
  image t_im;
  for (int i = 0; i <= pixels.size(); ++i) {
    t_im.row.push_back(pixels[i] - '0');
    if (t_im.row.size() == col_lim) {
      t_im.im.push_back(t_im.row);
      t_im.row.clear();
    }
    if (t_im.im.size() == row_lim) {
      images.push_back(t_im);
      t_im = {};
    }
  }

  vector<int> numZeros;
  for (int j = 0; j < images.size(); ++j) {
    numZeros.push_back(images[j].getNumVal(0));
  }
  int minElementIndex = min_element(numZeros.begin(),numZeros.end()) - numZeros.begin();

  cout << "ans: " << images[minElementIndex].getNumVal(1)*images[minElementIndex].getNumVal(2) << endl;

  return 0;
}