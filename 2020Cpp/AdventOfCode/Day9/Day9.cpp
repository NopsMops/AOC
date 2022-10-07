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
#include <set>
#include <algorithm>

#include "NobisTools.h" 


/*******************************************
* star1
*/
unsigned long star1(const std::vector<unsigned long long>& i_codeV)
{
  using namespace std;
  for (auto it = i_codeV.begin() + 25; it != i_codeV.end(); it++) {
    bool found = false;
    for (auto nt = it - 25; nt != it + 24; nt++) {
      for (auto kt = nt + 1; kt != nt + 25; kt++) {
        if (*it == *kt + *nt) {
          found = true;
          break;
        }
      }
      if (found) break;
    }
    if (found != true) return *it;
  }
  return 0;
}
/*******************************************
* star2
*/
unsigned long star2(const std::vector<unsigned long long>& i_codeV, const unsigned long long& i_goal)
{
  using namespace std;
  for (auto it = i_codeV.begin(); it != i_codeV.end(); it++) { 
    unsigned long long cal = 0;
    vector<unsigned long long> minmax;
    for (auto nt = it; nt != i_codeV.end(); nt++) {
      minmax.push_back(*nt);
      cal += *nt;
      if (cal == i_goal) {
        sort(minmax.begin(), minmax.end());
        return minmax.front() + minmax.back();
      }
      else if (cal > i_goal) break;  
    } 
  }
  return 0;
}

/*********
* main
*/
int main()
{
  using namespace std;

  vector<unsigned long long > codeV;
  auto lambda = [](const string& i_str, unsigned long long& o_p) {
    o_p = stoull(i_str);
  };

  vector<int> vecCoin;
  nobistools::readAndSplitAllLines<unsigned long long >(R"(.\Input\PartAB.txt)", codeV, lambda);
  unsigned long long res1 = star1(codeV);
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << res1;
  cout << endl << "Result star2: " << star2(codeV, res1);
  cout << endl << "----------------------------------------";
  
  return 0;
}





