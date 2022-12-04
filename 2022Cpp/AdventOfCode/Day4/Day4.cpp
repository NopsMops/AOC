// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <sstream>

std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> lines((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return lines;
}

int checkIn(const int& one, const int& two, const int& three, const int& four) {
  if (one >= three && two <= four || one <= three && two >= four) return 1;
  return 0;
}

int checkLap(const int& one, const int& two, const int& three, const int& four) {
  if (one >= three && one <= four) return 1;
  else if (two >= three && two <= four) return 1;
  else if (three >= one && three <= two) return 1;
  else if (four >= one && four <= two) return 1;
  return 0;
}

int result(std::vector<std::string> i_lines, int(*check)(const int&, const int&, const int&, const int&)) {
  int count = 0;
  for (std::string str : i_lines) {
    int one, two, three, four;
    char tmp;
    std::stringstream ss(str);
    ss >> one >> tmp >> two >> tmp >> three >> tmp >> four;
    count += check(one, two, three, four);
  }
  return count;
}


int main()
{
  using namespace std;
  vector<string> lines = readFile(R"(.\Input\PartAB.txt)");
  cout << endl << "Result 1: " << result(lines, checkIn);
  cout << endl << "Result 2: " << result(lines, checkLap);
}

