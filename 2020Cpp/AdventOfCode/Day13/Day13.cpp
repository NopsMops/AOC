// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <valarray>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>
#include <tuple>
#include "NobisTools.h"




int result1(const std::string& i_time, const std::vector<std::string>& i_bus) {
  long long time = stol(i_time);
  for (std::string b : i_bus) {
    if (b != "x") {
      int val = stoi(b);
      
    }
  }
  return 0;
}

int result2(const std::string& i_time, const std::vector<std::string>& i_bus) {
  long long time = stol(i_time);
  return 0;
}

int main()
{
  using namespace std;
  ifstream in(R"(.\Input\PartAB.txt)");
  string line1, line2;
  getline(in, line1);
  getline(in, line2);
  std::vector<std::string> strSpl;
  nobistools::split(line2, ",", strSpl);
  
  cout << endl << "Result1: " << result1(line1, strSpl);
  cout << endl << "Result2: " << result2(line1, strSpl);

}

