// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <set>

int result(std::string& line, const int compare) {
   std::string::iterator it = line.begin(); 
  for (it = line.begin(); it != line.end(); it++) {
    std::set<char> comp;
    for (int i = 0; i < compare; i++) {
      comp.insert(*(it + i));
    }
    if (comp.size() == compare) break;
  }
  return std::distance(line.begin(), it) + compare;
}

int main()
{
  using namespace std;

  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  in >> line;

  cout << endl << "Result 1: " << result(line, 4);
  cout << endl << "Result 2: " << result(line, 14);
}

