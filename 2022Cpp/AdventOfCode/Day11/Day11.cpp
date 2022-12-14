// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "NobisTools.h"

struct Monkey {
  long inspected = 0;
  std::vector<long long> items;
  bool opOldMul = true;
  long long opVal = 0;
  bool opValvalid = true;
  long long divBy = 1;
  long throwToIfTrue = 0;
  long throwToIfFalse = 0;
};

void extractDigit(const std::string& str, std::vector<long>& v) {
  std::regex digit_regex("(\\d+)");
  auto digits_begin =
    std::sregex_iterator(str.begin(), str.end(), digit_regex);
  auto digits_end = std::sregex_iterator();

  for (std::sregex_iterator i = digits_begin; i != digits_end; ++i) {
    std::smatch match = *i;
    v.push_back(stol(match.str()));
  }
}

void setMonkey(const std::string& s, Monkey& monk) {
  std::string ss = std::regex_replace(s, std::regex("^ +"), "");
  std::vector<long> v;
  extractDigit(ss, v);
  if (ss[0] == 'S') monk.items.insert(monk.items.begin(), v.begin(), v.end());
  else if (ss[0] == 'O') {
    if (v.empty()) monk.opValvalid = false;
    else monk.opVal = v[0];
    if (s.find('+') != std::string::npos) monk.opOldMul = false;
  }
  else if (ss[0] == 'T') monk.divBy = v[0];
  else if (s.find("If true") != std::string::npos) monk.throwToIfTrue = v[0];
  else if (s.find("If false") != std::string::npos) monk.throwToIfFalse = v[0];
}

void keepaway(int id, const long& div, std::vector<Monkey>& monkeyV ) {
  for( auto i: monkeyV[id].items ){
    long long level = 0;
    long long val = monkeyV[id].opVal;
    if (monkeyV[id].opValvalid == false) val = i;
    if (monkeyV[id].opOldMul ) {
      level = val * i;
    }
    else {
      level = monkeyV[id].opVal + i;
    }

    if(div > 3) level = level % div;
    else level = static_cast<long>(level / div);
    if (level % monkeyV[id].divBy > 0) {
      monkeyV[monkeyV[id].throwToIfFalse].items.push_back(level);
    }
    else {
      monkeyV[monkeyV[id].throwToIfTrue].items.push_back(level);
    }
    monkeyV[id].inspected++;
  }
  monkeyV[id].items.clear();
}

long long result1(std::vector<Monkey> monkeyV) {
  for (int i = 0; i < 20; i++) {
    for (int m = 0; m < monkeyV.size(); m++) {
      keepaway(m, 3, monkeyV);
    }
  }
  std::vector<long long> business;
  for (auto i : monkeyV) {
    business.push_back(i.inspected);
  }
  std::sort(business.rbegin(), business.rend());
  return business[0] * business[1];
}

long long result2(std::vector<Monkey> monkeyV) {
  long div = 1;
  for (auto i : monkeyV) {
    div *= i.divBy;
  }

  for (int i = 0; i < 10000; i++) {
    for (int m = 0; m < monkeyV.size(); m++) {
      keepaway(m, div, monkeyV);
    }
  }
  std::vector<long long> business;
  for (auto i : monkeyV) {
    business.push_back(i.inspected);
  }
  std::sort(business.rbegin(), business.rend());
  return business[0] * business[1];
}

int main()
{
  using namespace std;

  vector<Monkey> monkeyV;
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) {
    if (line.find("Monkey ") != std::string::npos) {
      Monkey next;
      monkeyV.push_back(next);
      continue;
    }
    setMonkey(line, monkeyV.back());
  }
  
  cout << endl << "Result1: " << result1(monkeyV);
  cout << endl << "Result2: " << result2(monkeyV);

  return 0;
}



