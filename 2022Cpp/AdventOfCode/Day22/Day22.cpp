// Day22.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct Path {
  enum class view{r,d,l,u};
  int x = 0, y = 0;
  std::vector<view> look{ view::r, view::d, view::l, view::u};
};

typedef std::vector<std::string> Field;

void split(const std::string& str, const std::string& splitter, std::queue<std::string>& v) {
  size_t start = 0, pos;
  do {
    pos = str.find_first_of(splitter, start);
    v.push(str.substr(start, pos - start));
    if (pos != std::string::npos) v.push(str.substr(pos, 1));
    start = pos + 1;
  } while (pos != std::string::npos);
}

void print(const Field& field, const Path& path) {
  std::cout << std::endl;
  for (int y = 0; y < field.size(); y++) {
    std::cout << std::endl;
    for (int x = 0; x < field[y].size(); x++) {
      if (y == path.y && x == path.x) {
        std::cout << 'X';
      }
      else {
        std::cout << field[y][x];
      }
    }
  }
}

int newpos(const std::string& str, int cx, int steps) {
  int x = cx;
  for (int i = 0; i < steps; i++) {
 
    if (x+1 < str.size()) {
      if (str[x+1] == '.') {
        x += 1;
      }
      else if(str[x+1] == ' ') {
        int pos = str.find_first_not_of(' ', 0);
        if (str[pos] == '.') {
          x = pos;
        }
      }
      else {
        break;
      }
    }
    else {
      int pos = str.find_first_not_of(' ', 0);
      if (str[pos] == '.') {
        x = pos;
      }
    }
  }
  return x;
}

void walk(const Field& field, int steps, Path& path) {
  Path::view dir = path.look.front();

  std::string str;
  switch (dir) {
  case Path::view::r:
  {
    str = field[path.y];
    path.x = newpos(str, path.x, steps);
    //print(field, path); 
  }
  break;
  
  case Path::view::d:
  {
    for (auto s : field) {
      if (path.x < s.size()) {
        str.push_back(s[path.x]);
      }
    }
    path.y = newpos(str, path.y, steps);
    //print(field, path);
  }
  break;
  
  case Path::view::l:
  {
    str = field[path.y];
    std::reverse(str.begin(), str.end());
    path.x = str.size() - newpos(str, str.size() - path.x -1, steps) -1;
    //print(field, path);
  }
  break;
  
  case Path::view::u:
  {
    for (auto s : field) {
      if (path.x < s.size()) {
        str.push_back(s[path.x]);
      }
    }
    std::reverse(str.begin(), str.end());
    path.y = str.size() - newpos(str, str.size() - path.y - 1, steps) - 1; 
    //print(field, path);
  }
  break; 
  }
}

int result1(const Field& field, std::queue<std::string> ops, Path& path) {

  while (!ops.empty()) {
    std::string op = ops.front();
    ops.pop();
    if (std::isdigit(op[0]) != 0) {
      int steps = std::stoi(op);
      walk(field, steps, path);
    }
    else {
      if (op == "R") {
        std::rotate(path.look.begin(), path.look.begin()+1, path.look.end());   
      }
      else {
        std::rotate(path.look.begin(), path.look.begin() + path.look.size() -1, path.look.end());
      }
    }
  }
  return 1000*(path.y+1)+4*(path.x+1)+static_cast<int>(path.look[0]);
}

int main()
{
  using namespace std;
  Field field;
  
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) field.push_back(line);
  string opsstr = field[field.size() - 1];
  field.erase(field.end() - 2, field.end());

  std::queue<std::string> ops;
  split(opsstr, "LR", ops);

  int startx = 0;
  for (startx = 0; startx < field[0].size(); startx++) {
    if (field[0][startx] != ' ') break;
  }
  Path path{ startx };

  cout << endl << "Result1: " << result1(field,ops,path);
}

