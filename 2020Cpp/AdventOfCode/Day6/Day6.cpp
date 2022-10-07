// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <regex>
#include <cmath>

#include "NobisTools.h" 

/*********
* star1
*/
template<typename T>
unsigned star1(const std::vector<T>& i_answerV)
{
  using namespace std;
  size_t yesanswers = 0;
  for (const auto& block : i_answerV) {
    set<char> yesOfBlock;
    for (const auto& s : block.value) {
      for (const auto& c : s) {
        yesOfBlock.insert(c);
      }
    }
    yesanswers += yesOfBlock.size();
  }
  return static_cast<unsigned>(yesanswers);
}
/*********
* star2
*/
template<typename T>
unsigned star2(const std::vector<T>& i_answerV)
{
  using namespace std;
  size_t count = 0;
  for (const auto& block : i_answerV) {
    count += block.value[0].size(); 

    for (const auto& c : block.value[0]) {
      for (const auto& s : block.value) {
        if (s.find(c) == string::npos) {
          count--;
          break;
        }
      }
    }
  }
  return count;
}

int main()
{
  using namespace std;

  struct answer {
    vector<string> value;
  };

  auto splitterFunc = [](const string& i_string, vector<string>& o_ansVal) {
    o_ansVal.push_back(i_string); 
  };

  vector<answer> answerV;
  nobistools::readAndSplitAllMultiLines<answer>(R"(.\Input\PartAB.txt)", answerV, splitterFunc);

  unsigned res1 = star1<answer>(answerV);
  unsigned res2 = star2<answer>(answerV);;

  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << res1;
  cout << endl << "Result star2: " << res2;
  cout << endl << "----------------------------------------";

  return 0;


}
