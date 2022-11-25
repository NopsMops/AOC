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


std::vector<long long> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<long long> codeV((std::istream_iterator<long long>(f)), (std::istream_iterator<long long>()));
  return codeV;
}

/*******************************************
* star1
*/
unsigned long star1(const std::vector<long long>& i_codeV)
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
unsigned long star2(const std::vector<long long>& i_codeV, const unsigned long long& i_goal)
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

  vector<long long > codeV = readFile(R"(.\Input\PartAB.txt)");

  unsigned long long res1 = star1(codeV);
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << res1;
  cout << endl << "Result star2: " << star2(codeV, res1);
  cout << endl << "----------------------------------------";
  
  return 0;
}





