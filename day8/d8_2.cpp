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
        if (im[i][j] != 0) {
        cout << im[i][j] << " ";
        }
        else if (im[i][j] == 0) {
          cout << " " << " ";
        }
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


int msum(int x, int y) {
  if (x == 0) {
    return 0;
  } 
  else if (x == 1 || y == 1)
  {
    return 1;
  }
  else if (x == 2)
  {
    return y;
  }
  else {
    cout << "fucked" << endl;
  }
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

  int t_sum = 2;
  image last_im;
  vector<int> blank_row(col_lim, 0);
  vector<vector<int>> blank_im(row_lim, blank_row);

  last_im.im = blank_im;
  last_im.printIm();
  cout << "\n";
  for (int i = 0; i < col_lim; ++i) {
    for (int j = 0; j < row_lim; ++j) {
      for (int k = 0; k < images.size(); ++k) {
        t_sum = msum(t_sum, images[k].im[j][i]);
      }
      last_im.im[j][i] = t_sum;
      t_sum = 2;
    }
  }

  last_im.printIm();

  return 0;
}