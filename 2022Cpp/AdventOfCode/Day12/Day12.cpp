// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


typedef std::pair<int, int> Pair;
typedef std::vector<std::vector<int>> Field;
typedef std::vector<std::string> AllLine;

bool stepValid(const Pair& nextPos, const Pair& cPos, const Field& stepF, const int& rowS, const int& colS, const AllLine& lines) {
  int y = nextPos.first;
  int x = nextPos.second;

  if (y < rowS && y >= 0 && x < colS && x >= 0) { // still within field
    
      if (lines[cPos.first][cPos.second] + 1 >= lines[y][x]) { // altitude diff max 1
        if (stepF[y][x] > stepF[cPos.first][cPos.second]+1) { // step reasonable
          return true;
        }
      }
  }
  return false;
}

int go(const AllLine& lines, const int& rowS, const int& colS, const Pair& i_start, const Pair& i_end) {
  std::vector<int> ini(colS, INT32_MAX);
  Field stepField(rowS, ini);
  stepField[i_start.first][i_start.second] = 0;
  std::queue<Pair> visit;
  visit.push(i_start);
  while (!visit.empty()) {
    Pair pos = visit.front();
    visit.pop();
    int cStep = stepField[pos.first][pos.second];
    // up
    if (stepValid(std::make_pair(pos.first + 1, pos.second), pos, stepField, rowS, colS, lines)) {
      visit.push(std::make_pair(pos.first + 1, pos.second));
      stepField[pos.first + 1][pos.second] = cStep + 1;
    }
    // down
    if (stepValid(std::make_pair(pos.first - 1, pos.second), pos, stepField, rowS, colS, lines)) {
      visit.push(std::make_pair(pos.first - 1, pos.second));
      stepField[pos.first - 1][pos.second] = cStep + 1;
    }
    // left
    if (stepValid(std::make_pair(pos.first, pos.second - 1), pos, stepField, rowS, colS, lines)) {
      visit.push(std::make_pair(pos.first, pos.second - 1));
      stepField[pos.first][pos.second - 1] = cStep + 1;
    }
    //right
    if (stepValid(std::make_pair(pos.first, pos.second + 1), pos, stepField, rowS, colS, lines)) {
      visit.push(std::make_pair(pos.first, pos.second + 1));
      stepField[pos.first][pos.second + 1] = cStep + 1;
    }
  }
  return stepField[i_end.first][i_end.second];
}

int result1(const AllLine& lines, const int& rowS, const int& colS, const Pair& i_start, const Pair& i_end) {
  return go(lines, rowS, colS, i_start, i_end);
}

int result2(const AllLine& lines, const int& rowS, const int& colS, const Pair& i_end) {
  int lowest = INT32_MAX;
  for (int y = 0; y < rowS; y++) {
    for (int x = 0; x < colS; x++) {
      if (lines[y][x] == 'a') {
        lowest = std::min(go(lines, rowS, colS, std::make_pair(y,x), i_end), lowest);
      }
    }
  }

  return lowest;
}

int main()
{
  using namespace std;
  vector<std::string> lines;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) lines.push_back(line);

  int RowSize = lines.size();
  int ColSize = lines[0].size();
  Pair start;
  Pair end;

  for (int y = 0; y < RowSize; y++) {
    for (int x = 0; x < ColSize; x++) {
      if (lines[y][x] == 'S') {
        lines[y][x] = 'a';
        start.first = y;
        start.second = x;
      }
      else if (lines[y][x] == 'E') {
        lines[y][x] = 'z';
        end.first = y;
        end.second = x;
      }
    }
  }

  cout << endl << "Result1: " << result1(lines, RowSize, ColSize, start, end);
  cout << endl << "Result2: " << result2(lines, RowSize, ColSize, end);

  return 0;
}