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

}