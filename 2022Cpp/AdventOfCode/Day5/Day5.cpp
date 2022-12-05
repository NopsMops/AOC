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

int findEmptyLine(const std::vector<std::string>& ccV) {
  int i = 0;
  std::vector<std::vector<char>> craneStack;
  for (i = 0; i < ccV.size(); i++) 
    if (ccV[i].empty())
      break;
  return i;
}

std::vector<int> getStackPos(const std::vector<std::string>& ccV) {
  int indexSplit = findEmptyLine(ccV);

  size_t start = 0, pos;
  std::string splitter = "123456789";
  std::vector<int> stackPos;
  do {
    pos = ccV[indexSplit - 1].find_first_of(splitter, start);
    if (pos == std::string::npos) break;
    stackPos.push_back(pos);
    start = pos + 1;
  } while (true);
  return stackPos;
}

std::vector<std::vector<char>> buildCraneList(const std::vector<std::string>& ccV) { 
  int indexSplit = findEmptyLine(ccV);
  std::vector<int> stackPos = getStackPos(ccV);
  std::vector<std::vector<char>> craneStack;

  for (auto i : stackPos) {
    std::vector<char> tmp;
    for (int n = indexSplit - 2; n >= 0; n--) {
      char cr = ccV[n][i];
      if (cr != ' ') {
        tmp.push_back(cr);
      }
    }
    craneStack.push_back(tmp);
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

std::vector<std::vector<char>>  moveAllCrane(const std::vector<std::string>& ccV, void(*move)(std::vector<std::vector<char>>& , int , int , int )) {
  std::vector<std::vector<char>> craneList = buildCraneList(ccV);
  int indexSplit = findEmptyLine(ccV);
  for (int i = indexSplit + 1; i < ccV.size(); i++)
  {
    std::vector<std::string> v;
    nobistools::split(ccV[i], " ", v);
    int mo = std::stoi(v[1]);
    int fr = std::stoi(v[3]);
    int to = std::stoi(v[5]);
    move(craneList, mo, fr, to);
  }
  return craneList;
}

std::string result1(const std::vector<std::string>& ccV) {
  std::string key;
  std::vector<std::vector<char>> craneList = moveAllCrane(ccV, moveSingleCrane);
  for (auto i : craneList) {
    key.push_back(i.back());
  }
  return key;
}
std::string result2(const std::vector<std::string>& ccV) {
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