// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <cmath>

std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> vecL((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return vecL;
}

/*********
* star2
*/
unsigned star2(std::vector<unsigned>& i_seatsV)
{ 
  sort(i_seatsV.begin(), i_seatsV.end());
  unsigned myseat = i_seatsV.at(0);
  for (const auto& i : i_seatsV) {
    if (myseat == i) {
      myseat++;
      continue;
    }
    return myseat;
  }
  return myseat;
}
/*********
* star1
*/
unsigned star1(const std::vector<std::string>& i_vecL, std::vector<unsigned>& i_seatsV )
{
  unsigned highSeat = 0;
  for (const auto& line : i_vecL) {
    unsigned seatR = 0;
    for (unsigned i = 0; i < 7; i++) {
      if (line.at(i) == 'B') {
        seatR += static_cast<unsigned>(pow(2,(7 - i - 1)));
      }
    }
    unsigned seatC = 0;
    for (unsigned i = 0; i < 3; i++) {
      if (line.at(i+7) == 'R') {
        seatC += static_cast<unsigned>(pow(2,(3 - i - 1)));
      }
    }
    unsigned s = seatR * 8 + seatC;
    i_seatsV.push_back(s);
    if (highSeat < s) {
      highSeat = s;
    }
  }
  return highSeat;
}
int main()
{
  using namespace std;

  vector<string> vecL = readFile(R"(.\Input\PartAB.txt)");
  vector<unsigned> seatsV;
 
  unsigned res1 = star1(vecL, seatsV);
  unsigned res2 = star2(seatsV);

  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << res1;
  cout << endl << "Result star2: " << res2;
  cout << endl << "----------------------------------------";

  return 0;


}
