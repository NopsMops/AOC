// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int calScore(const char& my, const char& opo) {
  
  if (my == 'X') {
    if (opo == 'C') return 1 + 6;
    else if (opo == 'A') return 1 + 3;
    return 1;
  }
  else if (my == 'Y') {
    if (opo == 'A') return 2 + 6;
    else if (opo == 'B') return 2 + 3;
    return 2;
  }
  if (opo == 'B') return 3 + 6;
  else if (opo == 'C') return 3 + 3;
  return 3;  
}
char useRockPapSci(const char& my, const char& opo) {
  if (my == 'X') {  // lose
    if (opo == 'A') return 'Z';
    else if (opo == 'B') return 'X';
    return 'Y';
  }
  else if (my == 'Y') { // draw
    if (opo == 'A') return 'X';
    else if (opo == 'B') return 'Y';
    return 'Z';
  }
  if (opo == 'A') return 'Y'; // win
  else if (opo == 'B') return 'Z';
  return 'X';
}

int main()
{
  using namespace std;

  auto lambda = [](const string& i_str, string& o_p) {
    o_p = i_str;
  };
  vector<string> stratV;
  nobistools::readAndSplitAllLines<string>(R"(.\Input\PartAB.txt)", stratV, lambda);
  int totalScoreStrategy1 = 0;
  int totalScoreStrategy2 = 0;
  for (auto i : stratV) {
    totalScoreStrategy1 += calScore(i.at(2), i.at(0));
    totalScoreStrategy2 += calScore(useRockPapSci(i.at(2), i.at(0)), i.at(0));
  }
  cout << endl << "Result1: " << totalScoreStrategy1;
  cout << endl << "Result2: " << totalScoreStrategy2;
}
