// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <valarray>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>
#include <tuple>

std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> seats((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return seats;
}

void trafo(char i_letter, int i_value, int& i_NSpos, int& i_EWpos) {
  using namespace std;
  static std::string allDir("ESWN");
  switch (i_letter) {
  case 'N':
    i_NSpos += i_value;
    break;
  case 'S':
    i_NSpos -= i_value;
    break;
  case 'W':
    i_EWpos -= i_value;
    break;
  case 'E':
    i_EWpos += i_value;
    break;
  case 'L': {
    int ind = (i_value / 90); // left rot 
    rotate(allDir.rbegin(), allDir.rbegin() + ind, allDir.rend());
    break;
  }
  case 'R': {
    int ind = (i_value / 90); // right rot
    rotate(allDir.begin(), allDir.begin() + ind, allDir.end());
    break;
  }
  case 'F':
    trafo(allDir[0], i_value, i_NSpos, i_EWpos);
    break;
  }
}
void trafoWay(char i_letter, int i_value, int& i_NSpos, int& i_EWpos, int& i_shipNSpos, int& i_shipEWpos) {
  using namespace std;

  switch (i_letter) {
  case 'N':
  case 'S':
  case 'W':
  case 'E':
    trafo(i_letter, i_value, i_NSpos, i_EWpos);
    break;
  case 'L': {
    int ind = (i_value / 90); // left rot
    int tmp = i_NSpos;
    if (ind == 1) {
      i_NSpos = i_EWpos;
      i_EWpos = -tmp;
    }
    else if (ind == 2) {
      i_NSpos = -i_NSpos;
      i_EWpos = -i_EWpos;
    }
    else if (ind == 3) {
      i_NSpos = -i_EWpos;
      i_EWpos = tmp;
    }
    break;
  }
  case 'R': {
    int ind = (i_value / 90); // left rot
    int tmp = i_NSpos;
    if (ind == 3) {
      i_NSpos = i_EWpos;
      i_EWpos = -tmp;
    }
    else if (ind == 2) {
      i_NSpos = -i_NSpos;
      i_EWpos = -i_EWpos;
    }
    else if (ind == 1) {
      i_NSpos = -i_EWpos;
      i_EWpos = tmp;
    }
    break;
  }
  case 'F':
    i_shipNSpos += i_value * i_NSpos;
    i_shipEWpos += i_value * i_EWpos;
    break;
  }
}

int result1( std::vector<std::string> lines) {
  int value(0), NSpos(0), EWpos(0);
  char letter('X');

  for (std::string str : lines) {
    std::stringstream ss(str);
    ss >> letter >> value;
    trafo(letter, value, NSpos, EWpos);
  }
  return abs(NSpos) + abs(EWpos);
}

int result2(std::vector<std::string> lines) {
  int value(0), NSpos(1), EWpos(10), shipNSpos(0), shipEWpos(0);
  char letter('X');

  for (std::string str : lines) {
    std::stringstream ss(str);
    ss >> letter >> value;
    trafoWay(letter, value, NSpos, EWpos, shipNSpos, shipEWpos);
  }
  return abs(shipNSpos) + abs(shipEWpos);
}

int main()
{
  using namespace std;
  vector<std::string> lines = readFile(R"(.\Input\PartAB.txt)");
  //vector<std::string> lines{ "F10","N3","F7","R90","F11" };

  cout << endl << "Result1: " << result1(lines);
  cout << endl << "Result2: " << result2(lines);

}

