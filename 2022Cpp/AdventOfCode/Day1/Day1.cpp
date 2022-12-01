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

#include "NobisTools.h" 

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

  auto lambda = [](const string& i_str, string& o_p) {
    o_p = i_str;
  };
  vector<string> calV;
  nobistools::readAndSplitAllLines<string>(R"(.\Input\PartAB.txt)", calV, lambda);
  vector<long long> vec = sumUpCalorie(calV);
  sort(vec.rbegin(), vec.rend());
  cout << endl << "Result1: " << vec.front();
  cout << endl << "Result2: " << vec.at(0) + vec.at(1) + vec.at(2);
  
}
