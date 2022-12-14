
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <regex>

#include "pch.h"

#include "NobisTools.h"


namespace nobistools {

  void split(const std::string& str, const std::string& splitter, std::vector<std::string>& v) {
    size_t start = 0, pos;
    do {
      pos = str.find_first_of(splitter, start);
      v.push_back(str.substr(start, pos - start));
      start = pos+1;
    } while (pos != std::string::npos);
  }

 /* void extractDigit(const std::string& str, std::vector<std::string>& v) {
    std::regex digit_regex("(\\d+)");
    auto digits_begin =
      std::sregex_iterator(str.begin(), str.end(), digit_regex);
    auto digits_end = std::sregex_iterator();

    for (std::sregex_iterator i = digits_begin; i != digits_end; ++i) {
      std::smatch match = *i;
      v.push_back(match.str());
    }
  }*/


}