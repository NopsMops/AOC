// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>

std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> lines((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return lines;
}

int prio(int charval) {
  static int a = static_cast<int>('a');
  static int A = static_cast<int>('A');
  if (charval >= a) return charval - a + 1;
  return charval - A + 27;
}

char searchBadge(const std::string& l1, const std::string& l2, const std::string l3) {
  for (auto i : l1) {
    if (l2.find(i) != std::string::npos) {
      if (l3.find(i) != std::string::npos) return i;
    }
  }
}

int result1(std::vector<std::string> i_lines) {
  int sum = 0;
  for (auto line : i_lines) {
    int half = line.size() / 2;
    char found = line[line.find_first_of(line.substr(0, half), half)];
    sum += prio(static_cast<int>(found));
  }
  return sum;
}

int result2(std::vector<std::string> i_lines) {
  int sum = 0;
  for (int i = 0; i < i_lines.size(); i += 3) {
    char found = searchBadge(i_lines[i], i_lines[i + 1], i_lines[i + 2]);
    sum += prio(static_cast<int>(found));
  } 
  return sum;
}

int main()
{
  using namespace std;
  vector<string> lines = readFile(R"(.\Input\PartAB.txt)");
  cout << endl << "Result 1: " << result1(lines);
  cout << endl << "Result 2: " << result2(lines);
  return 0;
}
