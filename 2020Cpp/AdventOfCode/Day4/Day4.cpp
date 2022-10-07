// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "NobisTools.h" 


/*******************************************
* presentCheck
*/
bool presentCheck(const std::vector<std::string>& i_toCheck)
{
  using namespace std;

  static regex regex_byr(R"(byr:([0-9]{4}))");
  static regex regex_iyr(R"(iyr:([0-9]{4}))");
  static regex regex_eyr(R"(eyr:([0-9]{4}))");
  static regex regex_hgtcm(R"(hgt:([0-9]{3})cm)");
  static regex regex_hgtin(R"(hgt:([0-9]{2})in)");
  static regex regex_hcl(R"(hcl:#([0-9a-z]{6}))");
  static regex regex_ecl(R"(ecl:(amb|blu|brn|gry|grn|hzl|oth))");
  static regex regex_pid(R"(pid:([0-9]{9}))");
  unsigned numOfOkPresent = 0;
  for (const auto& s : i_toCheck) {
    smatch matchResults;
    if (regex_match(s, matchResults, regex_byr)) {
      unsigned val = stoi(matchResults[1].str());
      if (val >= 1920 && val <= 2002) numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_iyr)) {
      unsigned val = stoi(matchResults[1].str());
      if (val >= 2010 && val <= 2020) numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_eyr)) {
      unsigned val = stoi(matchResults[1].str());
      if (val >= 2020 && val <= 2030) numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_hgtcm)) {
      unsigned val = stoi(matchResults[1].str());
      if (val >= 150 && val <= 193) numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_hgtin)) {
      unsigned val = stoi(matchResults[1].str());
      if (val >= 59 && val <= 76) numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_hcl)) {
      numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_ecl)) {
      numOfOkPresent++;
    }
    else if (regex_match(s, matchResults, regex_pid)) {
      numOfOkPresent++;
    }
  }

  if (numOfOkPresent >= 7) return true;
  return false;
}
/*******************************************
* star1
*/
template<typename T>
unsigned star1(const std::vector<T>& i_vecPass)
{
  unsigned passOk = 0;
  for (auto& i : i_vecPass) {
    if (i.value.size() == 8) passOk++;
    else if (i.value.size() == 7 && !i.cinIsIn()) passOk++;
  }
  return passOk;
}
/*******************************************
* star2
*/
template<typename T>
unsigned star2(const std::vector<T>& i_vecPass)
{
  using namespace std;
  unsigned passOk = 0;
  for (auto& i : i_vecPass) {
    if (i.value.size() == 8 || (i.value.size() == 7 && !i.cinIsIn())) {
      if (presentCheck(i.value)) passOk++;  
    }
  }
  return passOk;
}
/*********
* main
*/
int main()
{
  using namespace std;

  struct passPort {
    vector<string> value;
    bool cinIsIn() const { 
      for (const auto& k : value) {
        if (k.find("cid:") == 0) return true;
      }
      return false;
    }
  };

  auto splitterFunc = [](const string& i_string, vector<string>& o_keyVal) {
    static std::regex regex(R"(([A-z0-9#]+:[A-z0-9#]+))");
    std::smatch matchResults;
    string check = i_string;
    while (std::regex_search(check, matchResults, regex)) {
      o_keyVal.push_back(matchResults[0]);
      check = matchResults.suffix();
    }
  };

  vector<passPort> vecPass;
  nobistools::readAndSplitAllMultiLines<passPort>(R"(.\Input\PartAB.txt)", vecPass, splitterFunc);

  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << star1<passPort>(vecPass);
  cout << endl << "Result star2: " << star2<passPort>(vecPass);
  cout << endl << "----------------------------------------";

  return 0;
}
