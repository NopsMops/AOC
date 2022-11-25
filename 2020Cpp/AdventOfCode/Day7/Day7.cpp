// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2020

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <tuple>


std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> linesV((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return linesV;
}

/*********
* star1
*/
void star1(const std::string& i_start, const std::vector<std::string>& i_linesV, std::set<std::string>& o_colorBagsForGold)
{
  using namespace std;
  for (const auto& l : i_linesV) {
    size_t found = l.find(i_start);
    if (found != string::npos && found > 0) {
      static regex regex_bagf(R"(^([A-z]+ [A-z]+))");
      smatch matchResults;
      if (regex_search(l, matchResults, regex_bagf)) {
        o_colorBagsForGold.insert(matchResults[1].str());
        star1(matchResults[1].str(), i_linesV, o_colorBagsForGold);
      }
    }
  }
}
/********
* splitLineInBags
*/
void splitLineInBags( const std::string& i_foundStr, std::vector<std::tuple<unsigned, std::string>>& i_bags, const std::vector<std::string>& i_linesV)
{
  static std::regex regex(R"(([0-9]) ([A-z]+ [A-z]+) )");
  std::smatch matchResults;
  std::string check = i_foundStr;
  while (std::regex_search(check, matchResults, regex)) {
    i_bags.push_back({ stoi(matchResults[1]) , matchResults[2] });
    check = matchResults.suffix();
  }
}
/*********
* lineStartWithColor
*/
std::string lineStartWithColor(const std::string& i_color, const std::vector<std::string>& i_linesV) 
{
  for (const auto& l : i_linesV)
    if (l.find(i_color) == 0)
      return l;
  return {};
}
/*********
* solve
*/
void solve(const std::tuple<unsigned, std::string>& i_outerBag, unsigned& i_sumbags, const std::vector<std::string>& i_linesV)
{ 
  i_sumbags += std::get<0>(i_outerBag);
  std::string foundStr = lineStartWithColor(std::get<1>(i_outerBag), i_linesV);

  std::vector<std::tuple<unsigned, std::string>> bags;
  splitLineInBags(foundStr, bags, i_linesV);
  for (auto& b : bags) {
    std::get<0>(b) = std::get<0>(b) * std::get<0>(i_outerBag);
    solve(b, i_sumbags, i_linesV);
  }
}
/*********
* star2
*/
unsigned star2(const std::vector<std::string>& i_linesV)
{
  unsigned sumbags = 0;
  std::tuple<unsigned, std::string> line = {1, "shiny gold" };
  solve(line, sumbags, i_linesV);
  return sumbags-1; // do not count shiny gold bag
}

int main()
{
  using namespace std;
  
  vector<string> linesV = readFile(R"(.\Input\PartAB.txt)");
  set<string> colorBagsForGold;
  star1("shiny gold", linesV, colorBagsForGold);
  
  cout << endl << "----------------------------------------";
  cout << endl << "Result star1: " << colorBagsForGold.size();
  cout << endl << "Result star2: " << star2(linesV);
  cout << endl << "----------------------------------------";

  return 0;
}
