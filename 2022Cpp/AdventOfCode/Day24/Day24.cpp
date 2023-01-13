// Day24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Attention
// change the programm and you will get earlier or later crowdstrike trouble
// -> no beautyfing possible
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
#include <tuple>
#include <set>


typedef std::pair<int, int> Pos;
typedef std::pair<Pos, char> PosVal;
typedef std::multimap<Pos, char> Field;

void print(const Field& field) {
  int maxix = 0;
  int maxiy = 0;
  for (auto i : field) {
    maxix = std::max(i.first.first, maxix);
    maxiy = std::max(i.first.second, maxiy);
  }

  std::cout << std::endl;
  for (int y = 0; y <= maxiy; y++) {
    std::cout << std::endl;
    for (int x = 0; x <= maxix; x++) {
      auto it = field.equal_range({ x,y });
      int dub = std::distance(it.first, it.second);
      if (dub > 1) {
        std::cout << dub;
      }
      else {
        std::cout << (*(it.first)).second;
      }
    }
  }
}

void movblitz( Field& newfield, PosVal cposval, const Pos& maxxy) {

  if (cposval.second == '.') return;

  PosVal mov = cposval;

  if (cposval.second == '<') {
    if (cposval.first.first - 1 == 0 ) {
      mov.first.first = maxxy.first - 1;
    }
    else {
      mov.first.first--;
    }
  }
  else if (cposval.second == '>') {
    if (cposval.first.first + 1 == maxxy.first) {
      mov.first.first = 1;
    }
    else {
      mov.first.first++;
    }
  }
  else if (cposval.second == '^') {
    if (cposval.first.second - 1 == 0) {
      mov.first.second = maxxy.second - 1;
    }
    else {
      mov.first.second--;
    }
  }
  else if (cposval.second == 'v') {
    if (cposval.first.second + 1 == maxxy.second) {
      mov.first.second = 1;
    }
    else {
      mov.first.second++;
    }
  }
  
  newfield.insert(mov);
  return;
}


Field tick( const Field& field, const Pos& start, const Pos& end, const Pos& maxxy) {

  Field newfield;

  // -> flashes, wall
  for (auto i : field) {
    PosVal cposval(i.first, i.second);
    movblitz(newfield, cposval, maxxy);
  }

  // -> add free fields, start,end
  for (int y = 0; y <= maxxy.second; y++) {
    for (int x = 0; x <= maxxy.first; x++) {
      if (newfield.find({ x, y }) == newfield.end()) {
        newfield.insert(PosVal({ x, y }, '.'));
      }
    }
  }
  return newfield;
}

bool isvalid(const Field& field, const Pos& posE, const Pos& start) {
  auto it = field.find(posE);
  if (it != field.end() ) {
    if (it->second == '.') {
      return true;
    }
  }
  return false;
}

std::set<Pos> checkPos(std::set<Pos> old, const Field& fieldAftertick, const Pos& start) {
  std::set<Pos> visit;

  for( auto i : old){
    Pos pos = i;
    Pos newpos;
    if (isvalid(fieldAftertick, { pos.first + 1, pos.second }, start)) {
      Pos newpos = { pos.first + 1, pos.second };
      visit.insert(newpos);
    }
    if (isvalid(fieldAftertick, { pos.first - 1, pos.second }, start)) {
      Pos newpos = { pos.first - 1, pos.second };
      visit.insert(newpos);
    }
    if (isvalid(fieldAftertick, { pos.first, pos.second + 1 }, start)) {
      Pos newpos = { pos.first, pos.second + 1 };
      visit.insert(newpos);
    }
    if (isvalid(fieldAftertick, { pos.first, pos.second - 1 }, start)) {
      Pos newpos = { pos.first, pos.second - 1 };
      visit.insert(newpos);
    }
    if (isvalid(fieldAftertick, { pos.first, pos.second }, start)) {
      Pos newpos = { pos.first, pos.second };
      visit.insert(newpos);
    }
  }

  return visit;
}

int result2(const Field& field, const Pos& start, const Pos& end, const Pos& maxxy) {
  Field fieldAftertick = field;
  //print(fieldAftertick);

  std::set<Pos> visit = { start };
  int minute = 0;
  int toback = 0;

  while (true) {
    minute++;
    fieldAftertick = tick(fieldAftertick, start, end, maxxy);
    std::cout << std::endl << "Minute: " << minute;
    //print(fieldAftertick);

    visit = checkPos(visit, fieldAftertick, start);
    for (auto i : visit) {

      if (toback == 0) {
        if (i == end) {
          toback = 1;
          visit.clear();
          visit.insert(end);
          break;
        }
      }
      else if (toback == 1) {
        if (i == start) {
          toback = 2;
          visit.clear();
          visit.insert(start);
          break;
        }
      }
      else if (toback == 2) {
        if (i == end) {
          return minute;
        }
      }
    }
  }
  return 0;
}

int result1( const Field& field, const Pos& start, const Pos& end, const Pos& maxxy) {
  Field fieldAftertick = field;
  //print(fieldAftertick);

  std::set<Pos> visit = { start };
  int minute = 0;
  bool goal = false;

  while (true) {
    minute++;
    fieldAftertick = tick(fieldAftertick, start, end, maxxy);
    std::cout << std::endl << "Minute: " << minute;
    //print(fieldAftertick);

    visit = checkPos(visit, fieldAftertick, start);
    for( auto i : visit){
      if (i == end) {
        return minute;
      }
    }
  }
  return 0;
}

int main()
{
  using namespace std;
  Field field;
  Pos start;
  Pos end;
  Pos maxxy;
  
  int y = 0;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)"); 

  while (getline(in, line)) {
    if (y == 0) {
      start = { line.find('.', 0), y };   
    }
    for (int x = 0; x < line.size(); x++) {
      field.insert(PosVal({ x, y }, line[x]));
    }
    y++;
  }
  end = { line.find('.', 0), --y };
  maxxy.first = line.size() - 1;
  maxxy.second = y;

  cout << endl << "Result1: " << result1(field, start, end, maxxy);
  cout << endl << "Result2: " << result2(field, start, end, maxxy);
}