// PartAB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// 
// 2020
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <cassert>

#include "NobisTools.h" 

/*******************************************
* star1
*/
template<typename T>
int star1(const std::vector<T>& i_vecPass)
{
  using namespace std;

  int validPass = 0;
  for (auto it = i_vecPass.begin(); it != i_vecPass.end(); ++it) {
    string str = (*it).password;
    const unsigned int c = count(str.begin(), str.end(), (*it).sign);
    if ((*it).min <= c && c <= (*it).max) {
      validPass++;
    }
  }
  return validPass;
}
/*******************************************
* star2
*/
template<typename T>
int star2(const std::vector<T>& i_vecPass)
{
  using namespace std;

  int validPass = 0;
  for (auto it = i_vecPass.begin(); it != i_vecPass.end(); ++it) {
    string str = (*it).password;
    unsigned int foundPass = 0;
    if (str.length() >= (*it).min ) {
      if (str.at((*it).min-1) == (*it).sign) {
        foundPass++;
      }
    }
    if (str.length() >= (*it).max ) {
      if (str.at((*it).max - 1) == (*it).sign) {
        foundPass++;
      }
    }
    if (foundPass == 1) {
      validPass++;
    }
  }
  return validPass;
}
/*********
* main
*/
int main()
{
  using namespace std;

  struct TupelPass {
    unsigned int min;
    unsigned int max;
    char sign;
    std::string password;
  };

  auto lambda = [](const string& i_str, TupelPass& o_p) {
    static std::regex regex(R"((\d+)-(\d+) ([A-z]): ([A-z]+))");
    std::smatch matchResults;  //stands for “std::string match“
    if (std::regex_search(i_str, matchResults, regex)) {
      o_p.min = stoi(matchResults[1].str());
      o_p.max = stoi(matchResults[2].str());
      o_p.sign = matchResults[3].str().front();
      o_p.password = matchResults[4].str();
    }
    else {
      assert(false);
    }
  };

  //vector<PassLine> vecPass;
  vector<TupelPass> vecPass;
  nobistools::readAndSplitAllLines<TupelPass>(R"(.\Input\PartAB.txt)", vecPass, lambda);
 
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << star1<TupelPass>(vecPass);
  cout << endl << "Result star2: " << star2<TupelPass>(vecPass);
  cout << endl << "----------------------------------------";
  return 0;
}
