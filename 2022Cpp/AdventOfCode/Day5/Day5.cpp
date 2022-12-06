// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <list>
#include "NobisTools.h" 

std::vector<std::vector<char>> buildCraneList(std::vector<std::string>& ccV) {
  auto it = ccV.begin();
  for (; it != ccV.end(); it++) {
    if ((*it).empty()) break;  
  }
  int indexSplit = std::distance(ccV.begin(), it);

  std::vector<std::vector<char>> craneStack(ccV[0].size());
  for (int n = indexSplit - 2; n >= 0; n--) {
    for (int i = 0; i < ccV[n].size(); i++) {
      if ( static_cast<int>(ccV[n][i]) >= static_cast<int>('A') && static_cast<int>(ccV[n][i]) <= static_cast<int>('Z')) {
        craneStack[i].push_back(ccV[n][i]);
      }
    }
  }
  for (int n = craneStack.size() - 1; n >= 0; n--) {
    if (craneStack[n].empty()) {
      craneStack.erase(craneStack.begin() + n);
    }
  }
  return craneStack;
}

void moveSingleCrane(std::vector<std::vector<char>>& craneList, int i_mo, int i_fr, int i_to) {
  int mo = i_mo, fr = i_fr -1, to = i_to -1;
  int start = craneList[fr].size() - mo;
  std::vector<char> subvector = { craneList[fr].begin() + start, craneList[fr].end() };
  craneList[to].insert(craneList[to].end(), subvector.rbegin(), subvector.rend());
  craneList[fr].erase(craneList[fr].begin() + start, craneList[fr].end());
}

void moveBlockCrane(std::vector<std::vector<char>>& craneList, int i_mo, int i_fr, int i_to) {
  int mo = i_mo, fr = i_fr - 1, to = i_to - 1;
  int start = craneList[fr].size() - mo;
  std::vector<char> subvector = { craneList[fr].begin() + start, craneList[fr].end() };
  craneList[to].insert(craneList[to].end(), subvector.begin(), subvector.end());
  craneList[fr].erase(craneList[fr].begin() + start, craneList[fr].end());
}

std::vector<std::vector<char>>  moveAllCrane(std::vector<std::string>& ccV, void(*move)(std::vector<std::vector<char>>&, int, int, int)) {
  std::vector<std::vector<char>> craneList = buildCraneList(ccV);
  int mo, fr, to;
  std::string tmp;
  for (int i = 0; i < ccV.size(); i++)
  {
    std::stringstream ss(ccV[i]);
    ss >> tmp >> mo >> tmp >> fr >> tmp >> to ;
    if (tmp == "to") {
      move(craneList, mo, fr, to);
    }
  }
  return craneList;
}

std::string result1(std::vector<std::string>& ccV) {
  std::string key;
  std::vector<std::vector<char>> craneList = moveAllCrane(ccV, moveSingleCrane);
  for (auto i : craneList) {
    key.push_back(i.back());
  }
  return key;
}
std::string result2(std::vector<std::string>& ccV) {
  std::string key;
  std::vector<std::vector<char>> craneList = moveAllCrane(ccV, moveBlockCrane);
  for (auto i : craneList) {
    key.push_back(i.back());
  }
  return key;
}

int main()
{
  using namespace std;

  auto lambda = [](const string& i_str, string& o_p) {
    o_p = i_str;
  };

  vector<string> ccV;
  nobistools::readAndSplitAllLines<string>(R"(.\Input\PartAB.txt)", ccV, lambda);
  cout << endl << "Result 1: " << result1(ccV);
  cout << endl << "Result 2: " << result2(ccV);
}