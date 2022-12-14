// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

std::vector<std::string> crt;
int crtHSize = 40;
int crtVSize = 6;

void initCrt() {
  std::string str(crtHSize,'.');
  for (int i = 0; i < crtVSize; i++) {
    crt.push_back(str);
  }
}

void print() {
  for (int i = 0; i < crtVSize; i++) {
    std::cout << std::endl << crt[i];  
  }
  std::cout << std::endl;
}

void setX(long x) {
  for (int h = -1; h <= 1; h++) {
    if (x+h >= 0 && x+h < crtHSize) {
      for (auto& i : crt) {
        if (i[x+h] != '#') i[x+h] = 'x';
      }
    }
  }  
}
void resetX() {
  for (auto& i : crt) {
    for (auto& l : i) {
      if ( l == 'x') l = '.';
    }
  }
}

void drawCy(int i, int cyEnd) {

  for (int k = 0; k < i; k++) {
    int row = static_cast<int>((cyEnd+k) / crtHSize);
    int col = (cyEnd +k) - row * crtHSize;
    if (crt[row][col] == 'x') {
      crt[row][col] = '#';
    }
  }
}

void result2(const std::vector<std::string>& i_lines) {
  long x = 1, cyEnd = 0, val = 0;
  initCrt();
  setX(x);
  print();

  for (auto i : i_lines) {
    val = 0;
    if (i == "noop") {
      drawCy(1,cyEnd);
      cyEnd++;
    }
    else {
      drawCy(2, cyEnd);
      val = stoi(i.substr(5));
      x += val;
      cyEnd += 2;
    }
    resetX();
    setX(x);
    print();
  }
  resetX();
  print();
  return;
}

int result1(const std::vector<std::string>& i_lines) {
  std::vector<long> cylist = { 20,60,100,140,180,220 };

  long x = 1, sum = 0, cyEnd = 0, ix = 0, val = 0;
  for (auto i : i_lines) {
    val = 0;
    if (i == "noop") {
      cyEnd++;
    }
    else {
      val = stoi(i.substr(5));
      x += val;
      cyEnd += 2;
    }
    if (cyEnd >= cylist[ix]) {
      sum += (x - val) * cylist[ix];    
      ix++;
      if (ix == cylist.size()) break;
    }
  }
  return sum;
}

int main()
{
  using namespace std;

  vector<string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  cout << endl << "Result1: " << result1(lines);  
  result2(lines);
}
