// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <tuple>
#include <cassert>

#include "NobisTools.h" 

/*********
* star1
*/
unsigned star1(std::vector<std::tuple<char, int, bool>>& i_linesV, bool& o_loop)
{
  using namespace std;
  unsigned acc = 0;
  o_loop = false;
  auto it = i_linesV.begin();
  while ( it != i_linesV.end() && get<2>(*it) == false) {
    get<2>(*it) = true;
    if(get<0>(*it) == 'j') {
      it += get<1>(*it);
      continue;
    }
    else if (get<0>(*it) == 'a') {
      acc += get<1>(*it);      
    } 
    it++;
  }
  if (it != i_linesV.end()) {
    o_loop = true;
  }
  return acc;
}
/*********
* star2
*/
unsigned star2(std::vector<std::tuple<char, int, bool>>& i_linesV )
{
  using namespace std;
  unsigned acc = 0;
  bool loop = false;
  for (auto& c : i_linesV) {
    for (auto& b : i_linesV)   get<2>(b) = false;
    char oldVal = get<0>(c);
    if (get<0>(c) == 'n') get<0>(c) = 'j';  
    else if (get<0>(c) == 'j') get<0>(c) = 'n'; 
    acc = star1(i_linesV, loop);
    if (loop == false) break;
    get<0>(c) = oldVal;
  }
  return acc;
}

int main()
{
  using namespace std;

  vector<tuple<char, int, bool>> linesV;
  auto lambda = [](const string& i_str, tuple<char, int, bool>& o_command) {
    static std::regex regex(R"(([A-z]{3}) ([+-]\d+))");
    std::smatch matchResults;  //stands for “std::string match“
    if (std::regex_match(i_str, matchResults, regex)) {
      o_command = {};
      get<0>(o_command) =  matchResults[1].str().front();
      get<1>(o_command) = stoi(matchResults[2].str());
    }
    else {
      assert(false);
    }
  };

  nobistools::readAndSplitAllLines<tuple<char, int, bool>>(R"(.\Input\PartAB.txt)", linesV, lambda);
  bool loop = false;
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << star1(linesV, loop);
  cout << endl << "Result star2: " << star2(linesV);
  cout << endl << "----------------------------------------";

  return 0;
}
