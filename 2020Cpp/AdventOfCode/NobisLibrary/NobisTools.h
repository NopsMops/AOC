#pragma once


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <deque>

#include "NobisLibrary.h"

namespace nobistools {

  // lambda:  void f(std::function< string(string) >& lambda);  or as template
  template<typename T, typename Functor>
  bool readAndSplitAllLines(const std::string& i_path, std::vector<T>& o_vecStr, Functor i_func)
  {
    using namespace std;

    o_vecStr.clear();
    ifstream in(i_path);
    if (!in.is_open()) {
      return false;
    }
    string line;
    while (getline(in, line)) {
      T tmpTupel;
      i_func(line, tmpTupel);
      o_vecStr.push_back(tmpTupel);
    }

    in.close();
    return true;
  }
  template<typename T, typename Functor>
  bool readAndSplitAllMultiLines(const std::string& i_path, std::vector<T>& o_vecStr, Functor i_func)
  {
    using namespace std;

    o_vecStr.clear();
    ifstream in(i_path);
    if (!in.is_open()) {
      return false;
    }
    string line;
    T first;
    o_vecStr.push_back(first);
    while (getline(in, line)) {
      if (line.empty()) {
       T next;
        o_vecStr.push_back(next);
        continue;
      }
      vector<string> tmpVec;
      i_func(line, tmpVec);
      auto iterEnd = o_vecStr.back().value.end();
      o_vecStr.back().value.insert(iterEnd, tmpVec.begin(), tmpVec.end());     
    }

    in.close();
    return true;
  }
  template <typename T, int MaxLen, typename V = std::deque<T>>
  class FixedQueue : public std::queue<T, V> {
  public:
    void push(const T& value) {
      if (this->size() == MaxLen) {
        this->c.pop_front();
      }
      std::queue<T, V>::push(value);
    }
  };

  void NOBISLIBRARY_API printResult(void);


}