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


std::vector<int> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<int> adaps((std::istream_iterator<int>(f)), (std::istream_iterator<int>()));
  return adaps;
}

/*******************************************
* star1
*/
int star1(std::vector<int>& i_vecAdap)
{
  using namespace std;
  int eins(0), zwei(0), drei(1), last(0);
  std::sort(i_vecAdap.begin(),i_vecAdap.end());
  for (auto i : i_vecAdap) {
    switch (i - last) {
    case 1: eins++; break;
    case 2: zwei++; break;
    case 3: drei++; break;
   }
    last = i;
  }
  return eins*drei;
}
/*******************************************
* star2
*/
unsigned long long star2(std::vector<int>& i_vecAdap)
{
  using namespace std;
  std::sort(i_vecAdap.begin(), i_vecAdap.end());
  i_vecAdap.insert(i_vecAdap.begin(), 0); //  socket always 0
  i_vecAdap.push_back(*(i_vecAdap.end() - 1) + 3); // device last adapter + 3

  vector<unsigned long long> combi{1,0,0,0};
  for (auto it = i_vecAdap.begin() +1; it != i_vecAdap.end(); it++) {
    rotate(combi.rbegin(), combi.rbegin() + 1, combi.rend());
    combi[0] = 0;
    size_t mini = min(static_cast<int>(it - i_vecAdap.begin()), 3);
    for (size_t i = 1; i <= mini; i++) {
      if (*it - *(it - i) <= 3) {
        combi[0] += combi[i];
      }
    }
  }
  return combi.front();
}

/*********
* main
*/
int main()
{
  using namespace std;

  vector<int> vecAdap = readFile(R"(.\Input\PartAB.txt)");
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << star1(vecAdap);
  cout << endl << "Result star2: " << star2(vecAdap);
  cout << endl << "----------------------------------------";

  return 0;
}





