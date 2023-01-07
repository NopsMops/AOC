// Day23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <utility>
#include <functional>
#include <limits>
#include <array>
#include <queue>
#include <map>
#include <deque>

enum class Dirs { n,s,w,e,none };

std::map< Dirs, std::vector< std::pair<int, int>>> Env{ {Dirs::n, { {-1,-1},{-1,0},{-1,+1} }},
                                                        {Dirs::s, { {1,-1},{1,0},{1,+1} }},
                                                        {Dirs::w, { {-1,-1},{0,-1},{1,-1} }},
                                                        {Dirs::e, { {-1,1},{0,1},{1,+1} }} };

typedef std::map<std::pair<int, int>, Dirs> Elfen;
typedef std::map<std::pair<int, int>, int> Occupy;

Dirs simMotion(const Elfen& elfs, std::pair<int, int> coo, std::deque<Dirs> globalDir) {

  bool stay = true; 
  Dirs mov = Dirs::none;

  while (!globalDir.empty()) {
    Dirs propdir = globalDir.front();
    globalDir.pop_front();

    bool free = true;
    for (auto p : Env[propdir]) {
      std::pair<int, int> check{ coo.first + p.first , coo.second + p.second };
      if (elfs.find(check) != elfs.end()) {
        free = false;
        stay = false;
      }
    }
    if (free && mov == Dirs::none) {
      mov = propdir;
    }
  }
  if (stay) return Dirs::none;
  return mov;
}

int result1(Elfen elfs, bool endless = false ) {

  std::deque<Dirs> globalDir = { Dirs::n, Dirs::s, Dirs::w, Dirs::e };
  int count = 0;
  bool motion = true;
 
  while (motion){
    count++;
    motion = false;
    Occupy occupy;

    // simulation
    Dirs propdir = globalDir.front();
    for (auto& elf : elfs) {
      elf.second = simMotion(elfs, elf.first, globalDir);
      if (elf.second != Dirs::none) {
        motion = true;
        auto p= Env[elf.second][1];
        std::pair<int, int> check{ elf.first.first + p.first , elf.first.second + p.second };

        if (occupy.find(check) != occupy.end()) {
          occupy[check] += 1;
        }
        else {
          occupy[check] = 1;
        }
      }
    }

    // move
    Elfen movedelfs;
    for (auto& elf : elfs) {
      if (elf.second != Dirs::none) {
        auto p = Env[elf.second][1];
        std::pair<int, int> check{ elf.first.first + p.first , elf.first.second + p.second };
        if (occupy.find(check) != occupy.end()) {
          if (occupy[check] == 1) {
            movedelfs[check] = Dirs::none;
          }
          else {
            movedelfs[elf.first] = Dirs::none;
          }
        } 
      }
      else {
        movedelfs.insert(elf);
      }
    }
    elfs = movedelfs;
    globalDir.pop_front();
    globalDir.push_back(propdir);
    if (endless == false && count == 10) break;
  }

  // calc square
  int miny = (*elfs.begin()).first.first, minx = (*elfs.begin()).first.second, maxy = miny, maxx = minx;
  for (auto& elf : elfs) {
    miny = std::min(elf.first.first, miny);
    maxy = std::max(elf.first.first, maxy);
    minx = std::min(elf.first.second, minx);
    maxx = std::max(elf.first.second, maxx);
  }

  int ret = std::abs((maxx - minx + 1) * (maxy - miny + 1)) - elfs.size();
  if (endless == true) ret = count;
  return ret;
}

int main()
{
  using namespace std;
  vector<std::string> lines;
  Elfen elfs;

  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  int y = 0;
  while (getline(in, line)) {
    for (int x = 0; x < line.size(); x++) {
      if (line[x] == '#') {
        elfs[{y, x}] = Dirs::none;
      }
    }
    y++;
  }

  cout << endl << "Result1: " << result1(elfs);
  cout << endl << "Result2: " << result1(elfs, true);

}
