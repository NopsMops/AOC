// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <cassert>

std::vector<long long> sumUpCalorie(const std::vector<std::string> i_calV) {
  std::vector<long long> vec{ 0 };
  for (const auto i : i_calV) {
    if (!i.empty()) {
      vec.back() += std::stol(i);
    }
    else {
      vec.push_back(0);
    }
  }
  return vec;
}

int main()
{
  using namespace std;
  vector<std::string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  vector<long long> vec = sumUpCalorie(lines);
  sort(vec.rbegin(), vec.rend());
  cout << endl << "Result1: " << vec.front();
  cout << endl << "Result2: " << vec.at(0) + vec.at(1) + vec.at(2);
  
}
