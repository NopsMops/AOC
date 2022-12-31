// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <utility>
#include <functional>
#include <limits>
#include <array>
#include <queue>
#include <map>

struct Job {
  enum class Operation {
    add, sub, div, mul, eq
  };
  Job(std::string name, std::string op1, std::string op2, Operation op):name(name), op1(op1), op2(op2), op(op) {}
  std::string name, op1, op2;
  Operation op;
};

typedef std::map<std::string, long long> Yell;
typedef std::vector<Job> Jobs;


void split(const std::string& str, const std::string& splitter, std::vector<std::string>& v) {
  size_t start = 0, pos;
  do {
    pos = str.find_first_of(splitter, start);
    v.push_back(str.substr(start, pos - start));
    start = pos + 1;
  } while (pos != std::string::npos);
}

long long result1( Yell yell, Jobs jobsV) {
  int oldyellS = 0;
  do {
    oldyellS = yell.size();
    for (int i = 0; i < jobsV.size(); i++) {
      auto it1 = yell.find(jobsV[i].op1);
      auto it2 = yell.find(jobsV[i].op2);
      if (it1 != yell.end() && it2 != yell.end()) {
        switch (jobsV[i].op) {
        case Job::Operation::add:
          yell[jobsV[i].name] = it1->second + it2->second;
          jobsV.erase(jobsV.begin() + i);
          break;
        case Job::Operation::sub:
          yell[jobsV[i].name] = it1->second - it2->second;
          jobsV.erase(jobsV.begin() + i);
          break;
        case Job::Operation::div:
          yell[jobsV[i].name] = it1->second / it2->second;
          jobsV.erase(jobsV.begin() + i);
          break;
        case Job::Operation::mul:
          yell[jobsV[i].name] = it1->second * it2->second;
          jobsV.erase(jobsV.begin() + i);
          break;
        case Job::Operation::eq:
          if (it1->second == it2->second) {
            yell[jobsV[i].name] = 0;
            jobsV.erase(jobsV.begin() + i);
          }
          break;
        }
      }
      if (oldyellS < yell.size()) break;
    }
  } while (oldyellS < yell.size());
  
  return yell.find("root")->second;
}

int main()
{
  using namespace std;
  vector<std::string> lines;
  Yell yell;
  Jobs jobsV;
  map<string, Job::Operation> operate{ {"+",Job::Operation::add}, {"-",Job::Operation::sub}, {"*",Job::Operation::mul}, {"/",Job::Operation::div} };
  string line;
  ifstream in(R"(.\Input\PartAB.txt)");
  while (getline(in, line)) {
    vector<string> pieces;
    split(line, ": ", pieces);
    if (pieces.size() == 3) {
      yell[pieces[0]] = stoi(pieces[2]);
    }
    else {
      jobsV.push_back({ pieces[0], pieces[2], pieces[4], operate.find(pieces[3])->second });
    }
  }
  cout << endl << "Result1: " << result1(yell, jobsV);

  // part 2 humn
  /*for (auto& i : jobsV) {
    if (i.name == "root") {
      i.op = Job::Operation::eq;
    }
  }
  */

}
