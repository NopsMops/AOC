// Day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <utility>
#include <functional>
#include <limits>
#include <array>
#include <queue>
#include <deque>
#include <numeric>

void print(std::vector<int> v, std::vector<int> vix) {
  std::cout << std::endl;
  for (auto i : vix) {
    std::cout << " " << v[i];
  }
}

int mix(std::vector<int>& v, const long long& decryp = 1, const int& loop = 1) {
  std::vector<int> vix(v.size());
  iota(vix.begin(), vix.end(), 0);

  //print(v, vix);
  for (int n = 0; n < loop; n++) {
    for (int i = 0; i < v.size(); i++) {
      int val = v[i];

      // wo ist index in index liste
      auto it = std::find(vix.begin(), vix.end(), i);
      int num = (*it);
      int ixnum = std::distance(vix.begin(), it);

      if (val == 0) continue;
      vix.erase(vix.begin() + ixnum);
      int vixSize = vix.size();
      int steps = (abs(val) * decryp) % vixSize;
      /*int steps = abs(val);
      steps = steps % vixSize;*/
      if (val < 0) {
        //left
        rotate(vix.begin(), vix.begin() + vixSize - steps, vix.end());
      }
      else {
        //right
        rotate(vix.begin(), vix.begin() + steps, vix.end());
      }
      vix.insert(vix.begin() + ixnum, num);
    }
  }

  auto it = find(v.begin(), v.end(), 0);
  int ixZero = std::distance(v.begin(), it);

  auto itvix = find(vix.begin(), vix.end(), ixZero);
  int ixvZero = std::distance(vix.begin(), itvix);

  int sum = 0;
  for (auto i : { 1000,2000,3000 }) {
    sum += v[vix[(ixvZero + i) % v.size()]];
  }
  return sum;
}


void main()
{
  using namespace std;
  vector<std::string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  vector<int> v;
  for (auto i : lines) {
    v.push_back(stoi(i));
  }

  long long  decryp = 811589153;
  cout << endl << "Result1: " << mix(v) << endl;
  cout << endl << "Result2: " << decryp* mix(v, decryp, 10) << endl;
}


