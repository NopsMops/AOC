// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>


std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> vecX((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return vecX;
}

/*********
* star (part A and B)
* linear -> recursive not necessary
*/
unsigned star(const std::vector<std::string>& i_vecX, unsigned i_moveX, unsigned i_moveY )
{
  unsigned trees = 0, curX = 0, curY = 0;
  while (true) {
    curX = (curX + i_moveX) % i_vecX.at(0).length();
    curY = curY + i_moveY;
    if (curY > (i_vecX.size() - 1)) {
      break;
    }
    if (i_vecX.at(curY).at(curX) == '#') trees++;
  } 
  return trees;
}

/*********
* main
*/
int main()
{
  using namespace std;

  vector<string> vecX  = readFile(R"(.\Input\PartAB.txt)");
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << star(vecX, 3, 1);
  cout << endl << "Result star2: " << static_cast<long long>(star(vecX, 1, 1)) * star(vecX, 3, 1) * star(vecX, 5, 1) * star(vecX, 7, 1) * star(vecX, 1, 2);
  cout << endl << "----------------------------------------";

  return 0;
}
