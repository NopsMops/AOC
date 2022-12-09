// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "NobisTools.h" 

bool visTree(const std::vector<std::string>& i_lines, const int n, const int i) {
  int high = i_lines[n][i];

  int dir = 0;
  for (int x = i - 1; x >= 0; x--) {
    if (i_lines[n][x] >= high) {
      dir++;
      break;
    }
  }

  for (int x = i +1; x < i_lines[0].size(); x++) {
    if (i_lines[n][x] >= high) {
      dir++;
      break;
    }
  }

  for (int x = n - 1; x >= 0; x--) {
    if (i_lines[x][i] >= high) {
      dir++;
      break;
    }
  }

  for (int x = n + 1; x < i_lines.size(); x++) {
    if (i_lines[x][i] >= high) {
      dir++;
      break;
    }
  }

  return dir == 4 ? false : true;
}

int eval2(std::vector<int> forEval) {
  int res = 0;
  for (auto i : forEval) {
    res += i;
  }
  if (res > 0) {
    res = 1;
    for (auto i : forEval) {
      if (i > 0) {
        res *= i;
      }
    }
  }
  return res;
}

int houseTree(const std::vector<std::string>& i_lines, const int n, const int i) {
  int high = i_lines[n][i];

  int dir1 = 0, dir2 = 0, dir3 = 0, dir4 = 0;
  for (int x = i - 1; x >= 0; x--) {
    if (i_lines[n][x] >= high) {
      dir1++;
      break;
    }
    dir1++;
  }
  
  for (int x = i + 1; x < i_lines[0].size(); x++) {
    if (i_lines[n][x] >= high) {
      dir2++;
      break;
    }
    dir2++;
  }
  
  for (int x = n - 1; x >= 0; x--) {
    if (i_lines[x][i] >= high) {
      dir3++;
      break;
    }
    dir3++;
  }
  
  for (int x = n + 1; x < i_lines.size(); x++) {
    if (i_lines[x][i] >= high) {
      dir4++;
      break;
    }
    dir4++;
  }
  std::vector<int> forEval;
  forEval.push_back(dir1);
  forEval.push_back(dir2);
  forEval.push_back(dir3);
  forEval.push_back(dir4);
  
  return eval2(forEval);
}

int result2(const std::vector<std::string>& i_lines) {
  std::vector<int> house;
  for (int i = 1; i < i_lines[0].size() - 1; i++) {
    for (int n = 1; n < i_lines.size() - 1; n++) {
      int trees = houseTree(i_lines, n, i);
      house.push_back(trees);
    }
  }
  std::sort(house.rbegin(), house.rend());
  return house[0];
}

int result1( const std::vector<std::string>& i_lines) {
  int trees = 0;
  for (int i = 1; i < i_lines[0].size() -1; i++) {
    for (int n = 1; n < i_lines.size() - 1; n++) {
      if (visTree(i_lines, n, i)) {
        trees++;
      }
    }
  }
  return i_lines[0].size() * 2 + (i_lines.size() - 2) * 2 + trees;
}


int main()
{
  using namespace std;

  auto lambda = [](const string& i_str, string& o_p) {
    o_p = i_str;
  };
  vector<string> lines;
  nobistools::readAndSplitAllLines<string>(R"(.\Input\PartAB.txt)", lines, lambda);
  
  cout << endl << "Result1: " << result1(lines);
  cout << endl << "Result1: " << result2(lines);
  
}

