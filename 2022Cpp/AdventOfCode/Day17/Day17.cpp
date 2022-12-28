// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <deque>
#include <numeric>
#include <set>

typedef std::vector < std::pair<int, int>> Shape;
typedef std::vector<std::vector<char>> Tunnel;

void print(const Tunnel& map) {
  std::cout << std::endl << std::endl;
  int max = map[0].size();
  for (int y = max - 1; y >= 0; y--) {
    std::cout << std::endl;
    for (auto c : map) {
      std::cout << c[y];    
    }
  }
}

int freeLine(Tunnel& map, const int freespace){
  int y = 0;
  for (y = 0; y < map[0].size(); y++) {
    int isFree = true;
    for (int x = 0; x < map.size(); x++) {
      if (map[x][y] != '.') {
        isFree = false;
        break;
      }
    }
    if (isFree) break;
  }

  if (y + freespace > map[0].size()) {
    for (int i = 0; i < freespace; i++) {
      for (auto& x : map) {
        x.push_back('.');
      }
    }
  }
  return y;
}

Shape setRockCoo(const int& rockT, const int& dist, const int& freeY) {
  Shape rock;
  switch (rockT) {
  case 0:
    for (auto i : { 0,1,2,3 }) {
      rock.push_back({ dist+i, freeY});
    }
    break;
  case 1:
    for (auto i : { 0,1,2 }) {
      rock.push_back({ dist+i, freeY+1});
    }
    rock.push_back({ dist + 1, freeY});
    rock.push_back({ dist + 1, freeY +2});
    break;
  case 2:
    for (auto i : { 0,1,2 }) {
      rock.push_back({ dist + i, freeY});
    }
    rock.push_back({ dist + 2, freeY+1 });
    rock.push_back({ dist + 2, freeY + 2 });
    break;
  case 3:
    for (auto i : { 0,1,2,3 }) {
      rock.push_back({ dist, freeY+i });
    }
    break;
  case 4:
    rock.push_back({ dist, freeY});
    rock.push_back({ dist+1, freeY });
    rock.push_back({ dist, freeY+1 });
    rock.push_back({ dist+1, freeY + 1 });
    break;
  }
  return rock;
}

bool getGas(const std::string& line) {
  static int c = -1;
  c++;
  if (line[c % line.size()] == '<') {
    return true;
  }
  return false;
}

void gasPush(const std::string& line, const Tunnel& map, Shape& rock) {
  if (getGas(line)) { // left
    bool simOK = true;
    for (const auto& it : rock) {
      if (it.first == 0 || map[it.first - 1][it.second] == '#') {
        simOK = false;
        break;
      }
    }
    if (simOK) {
      for (auto& it : rock) {
        it.first -= 1;
      }
    }
  }
  else { // right
    bool simOK = true;
    for (const auto& it : rock) {
      if (it.first +1 == map.size() || map[it.first + 1][it.second] == '#') {
        simOK = false;
        break;
      }
    }
    if (simOK) {
      for (auto& it : rock) {
        it.first += 1;
      }
    }
  }
}

bool dofall(const Tunnel& map, Shape& rock) {
  bool simOK = true;
  for (const auto& it : rock) {
    if (it.second == 0 || map[it.first][it.second-1] == '#') {
      simOK = false;
      break;
    }
  }
  if (simOK) {
    for (auto& it : rock) {
      it.second -= 1;
    }
  }
  return simOK;
}
void markmap(Tunnel& map, Shape& rock) {
  for (const auto& it : rock) {
    map[it.first][it.second] = '#';
  }
}

int result1(const std::string& line) {
  const int mapwide = 7;
  const int numrock = 2022;
  const int rockTyps = 5;
  const int divBottom = 3;
  const int divLeft = 2;
  const int freespace = 10; // 10 enough for one rock
  std::vector<char> iny(divBottom + freespace, '.');
  Tunnel map(mapwide, iny);
  //print(map);
  int rockC = 0;
  while (rockC < numrock) {
    int freeRockY = freeLine(map, freespace) + divBottom;
    Shape rock = setRockCoo(rockC % rockTyps, divLeft, freeRockY);
    do {
      gasPush(line, map, rock);
      bool isfallen = dofall(map, rock); 
      if (isfallen == false) {
        break;
      }
    } while (true);
    markmap(map, rock);
    //print(map);
    rockC++;
  }
  return freeLine(map, freespace);
}

int main()
{
  using namespace std;

  string line;
  ifstream in(R"(.\Input\TestA1.txt)");
  in >> line;

  cout << endl << "Result 1: " << result1(line);
  
}