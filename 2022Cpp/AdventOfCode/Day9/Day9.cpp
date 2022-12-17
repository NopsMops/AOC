// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

std::set<std::pair<int, int>> posT;
std::vector< std::pair<int, int>> knots;

bool touch(std::pair<int, int>& t, std::pair<int, int>& h) {
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (t.first == h.first + x && t.second == h.second + y) {
        return true;
      }
    }
  }
  return false;
}

void pulltbehind(int k) {

  std::pair<int, int>& t = knots[k];
  std::pair<int, int>& h = knots[k-1];

  if (h.first == t.first || h.second == t.second) {
    if (h.first + 2 == t.first) {
      t.first--;
    }
    else if (h.first - 2 == t.first) {
      t.first++;
    }
    else if (h.second + 2 == t.second) {
      t.second--;
    }
    else if (h.second - 2 == t.second) {
      t.second++;
    }
  }
  else {
    std::pair<int, int> tmp = t;
    bool att = false;
    for (int i = -1; i <= 1; i += 2) {
      for (int n = -1; n <= 1; n += 2) {
        t = tmp;
        t.first += i;
        t.second += n;
        if (touch(t, knots[k - 1])) {
          att = true;
          break;
        }
      }
      if (att) break;
    }
  }
  posT.insert(knots[knots.size() - 1]);
}

void moveT() {
  for (int k = 1; k < knots.size(); k++) {
    if (touch(knots[k],knots[k - 1])) continue;
    pulltbehind(k);
  }
}

void moveH(const std::string i_com) {
  std::string first, sec;
  std::stringstream ss(i_com);
  ss >> first >> sec;
  int steps = stoi(sec);
  
  if (first == "D") {
    for (int i = 0; i < steps; i++) {
      knots[0].second--;
      moveT();
    }
  }
  else if (first == "U") {
    for (int i = 0; i < steps; i++) {
      knots[0].second++;
      moveT();
    }   
  }
  else if (first == "R") {
    for (int i = 0; i < steps; i++) {
      knots[0].first++;
      moveT();
    } 
  }
  else { // L
    for (int i = 0; i < steps; i++) {
      knots[0].first--;
      moveT();
    }
  }
}

int result(const std::vector<std::string>& i_lines, const int& num) {
  knots.clear();
  posT.clear();
  std::pair<int, int> knot = { 0,0 };
  for (int i = 0; i < num; i++) {
    knots.push_back(knot);
  }
  posT.insert(knots[knots.size() - 1]);
  for (auto i : i_lines) {
    moveH(i);
  }
  return posT.size();
}

int main()
{
  using namespace std;

  vector<string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  cout << endl << "Result1: " << result(lines, 2);
  cout << endl << "Result2: " << result(lines,10);
}
