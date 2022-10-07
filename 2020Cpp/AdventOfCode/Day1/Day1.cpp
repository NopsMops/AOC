// PartAB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// 
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "NobisTools.h" 

/*******************************************
* star1
*/
int star1(const std::vector<int>& i_vecCoin)
{
  using namespace std;
  for (const auto& i : i_vecCoin) {
    for (const auto& k : i_vecCoin) {
      if (&i == &k || (i + k) != 2020) continue;
      return  i * k;
    }
  }
  return 0;
}

/*******************************************
* star2
*/
int star2(const std::vector<int>& i_vecCoin)
{
  using namespace std;
  for (const auto& i : i_vecCoin) {
    for (const auto& k : i_vecCoin) {
      for (const auto& c : i_vecCoin) {
        if (&i == &k || &i == &c || &k == &c || (i + k + c) != 2020) continue;
        return i * k * c;
      }
    }
  }
  return 0;
}

/*********
* main
*/
int main()
{
  using namespace std;

  auto lambda = [](const string& i_str, int& o_p) {
    o_p = stoi(i_str);
  };

  vector<int> vecCoin;
  if (nobistools::readAndSplitAllLines<int>(R"(.\Input\PartAB.txt)", vecCoin, lambda)) {
    cout << endl << "----------------------------------------";
    cout << endl << "Result star1: " << star1(vecCoin);
    cout << endl << "Result star2: " << star2(vecCoin);
    cout << endl << "----------------------------------------";
  }
  else {
    cout << endl << "Error: Something went wrong!";
    return 1;
  }

  return 0;
}





