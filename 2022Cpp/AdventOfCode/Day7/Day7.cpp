// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "NobisTools.h" 

struct knot {
  std::string ppath, name;
  std::vector<std::string> dirs;
  long long dirSize = 0;
};

std::map<std::string, knot> dirmap;

std::string changeKnot(std::string i_cPath, std::string i_cr) {
  // up
  if (i_cr == "$ cd ..") {
    auto it = dirmap.find(i_cPath);
    return (*it).second.ppath;
  }
  if( i_cr == "$ cd /") { 
    return "/";
  }
  // down
  std::string pPath = i_cPath;
  std::string cDir = i_cr.substr(5);
  std::string key = pPath + cDir;

  auto it = dirmap.find(key);
  if (it == dirmap.end()) {
    knot tmp;
    tmp.ppath = pPath;
    tmp.name = cDir;
    dirmap[key] = tmp;
  }
  return key;
}

void addToKnot(std::string i_cPath, std::string i_fileDir) {
  std::string first, sec;
  std::stringstream ss(i_fileDir);
  ss >> first >> sec;

  auto it = dirmap.find(i_cPath);
  if (first[0] == 'd') {
      (*it).second.dirs.push_back(sec);
  }
  else {
    (*it).second.dirSize += stoi(first);
  }
}

void buildTree(std::vector<std::string> lines) {
  knot root;
  root.name = "/";
  dirmap[root.name] = root;

  std::string cPath;
  for (auto i : lines) {
    if (i == "$ ls") continue;
    if (i[0] == '$') {
      cPath = changeKnot(cPath, i);
    }
    else {
      addToKnot(cPath, i);
    }
  }
}

void calcSize(const std::string& i_path, long long& val) {
  auto it = dirmap.find(i_path);
  val += (*it).second.dirSize;
  for (const auto i : (*it).second.dirs) {
    calcSize(i_path + i, val);
  }
}

int result1() {
  long long total = 0;
  for (auto i : dirmap) {
    long long val = 0;
    calcSize(i.second.ppath + i.second.name, val);
    if( val <= 100000) {
      total += val;
    }
  }
  return total;
}

int result2() {
  long long sizeroot = 0;
  calcSize("/", sizeroot);
  long long needfree = 30000000 - 70000000 + sizeroot;
  std::vector<long long> wouldDo;
  for (auto i : dirmap) {
    long long val = 0;
    calcSize(i.second.ppath + i.second.name, val);
    if (val >= needfree) {
      wouldDo.push_back(val);
    }
  }
  std::sort(wouldDo.begin(), wouldDo.end()); 
  return wouldDo[0];
}

int main()
{
  using namespace std;

  auto lambda = [](const string& i_str, string& o_p) {
    o_p = i_str;
  };
  vector<string> lines;
  nobistools::readAndSplitAllLines<string>(R"(.\Input\PartAB.txt)", lines, lambda);
  buildTree(lines);

  cout << endl << "Result1: " << result1();
  cout << endl << "Result2: " << result2();
}
