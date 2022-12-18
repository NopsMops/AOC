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
#include <map>

std::map<char, std::string> mRPS{ {'X', "Rock"},{'A', "Rock"}, {'Y', "Paper"},{'B', "Paper"}, {'Z', "Scissor"},{'C', "Scissor"} };
std::map<char, int> mPoint{ {'X', 1},{'Y', 2}, {'Z', 3}};

int calScore(const std::string& my, const std::string& opo) {
  if (my == opo) return 3;
  else if (my == "Rock" && opo == "Scissor") return 6;
  else if (my == "Paper" && opo == "Rock") return 6;
  else if (my == "Scissor" && opo == "Paper") return 6;
  return 0;
}

char winLoseDraw(const char& my, const char& opo) {
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
  vector<std::string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  int totalScoreStrategy1 = 0;
  int totalScoreStrategy2 = 0;
  for (auto i : lines) {
    totalScoreStrategy1 += calScore(mRPS.find(i.at(2))->second, mRPS.find(i.at(0))->second) + mPoint.find(i.at(2))->second;
    totalScoreStrategy2 += calScore(mRPS.find(winLoseDraw(i.at(2), i.at(0)))->second, mRPS.find(i.at(0))->second) +
                                    mPoint.find(winLoseDraw(i.at(2), i.at(0)))->second;
  }
  cout << endl << "Result1: " << totalScoreStrategy1;
  cout << endl << "Result2: " << totalScoreStrategy2;
  return 0;
}