// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>

std::vector<std::string> readFile(const std::string& i_path) {
  std::ifstream f(i_path);
  std::vector<std::string> seats((std::istream_iterator<std::string>(f)), (std::istream_iterator<std::string>()));
  return seats;
}

//size_t countNear(const std::vector<std::string>& i_inSeats, const long long& r, const long long& c ) {
//  size_t occupied = 0;
//  for (long long ir = std::max<long long>(0, r-1); ir <= std::min<long long>(i_inSeats.size() - 1, r+1); ir++) {
//    for (long long ic = std::max<long long>(0, c-1); ic <= std::min<long long>(i_inSeats.front().size() - 1, c+1); ic++){
//      if (ic == c && ir == r) {
//        continue;
//      }
//      if (i_inSeats[ir][ic] == '#') {
//        occupied++;
//      }
//    }
//  }
//  return occupied;
//}
size_t countNear(const std::vector<std::string>& i_inSeats, const long long& r, const long long& c) {
  size_t occupied = 0;
  auto inBorder = [&i_inSeats](const long long r, const long long c) -> bool {
    return r >= 0 && r < i_inSeats.size() && c >= 0 && c < i_inSeats.front().size();
  };
  for (int rStep = -1; rStep <= 1; rStep++) { // direction west and east
    for (int cStep = -1; cStep <= 1; cStep++) { // direction south and north
      if (cStep == 0 && rStep == 0) {
        continue;
      }
      long long ir = r;
      long long ic = c;
      ir += rStep;
      ic += cStep;
      if (inBorder(ir, ic)) {
        if (i_inSeats[ir][ic] == '#') {
          occupied++;
        }
      }
    }
  }
  return occupied;
}

size_t countFar(const std::vector<std::string>& i_inSeats, const long long& r, const long long& c) {
  auto inBorder = [&i_inSeats](const long long r, const long long c) -> bool {
    return r >= 0 && r < i_inSeats.size() && c >= 0 && c < i_inSeats.front().size();
  };
  size_t occupied = 0;
  for (int rStep = -1; rStep <= 1; rStep++) { // direction west and east
    for (int cStep = -1; cStep <= 1; cStep++) { // direction south and north
      if (cStep == 0 && rStep == 0) {
        continue;
      }
      long long ir = r;
      long long ic = c;
      while (true) {
        ir += rStep;
        ic += cStep;
        if (inBorder(ir, ic)) {
          if (i_inSeats[ir][ic] == '#') {
            occupied++;
            break;
          }
          if (i_inSeats[ir][ic] == 'L') {
            break;
          }
        }
        else {
          break;
        }
      }
    }
  }
  return occupied;
}

size_t totalOccupied(const std::vector<std::string>& i_inSeats) {
  size_t total = 0;
  for (auto& line : i_inSeats) {
    total += std::count(line.begin(), line.end(), '#');
  }
  return total;
}

void changeSeats(std::vector<std::string>& i_inSeats, const size_t& i_reSeat, size_t(*count)(const std::vector<std::string>&, const long long&, const long long&)) {
  std::vector<std::string> newSeats = i_inSeats;
  bool changed = true;
  while (changed) {
    changed = false;
    for (size_t r = 0; r < i_inSeats.size(); r++) {
      for (size_t c = 0; c < i_inSeats.front().size(); c++) {
        if (i_inSeats[r][c] == '#' && count(i_inSeats, r, c) > i_reSeat) {
            newSeats[r][c] = 'L';
            changed = true;
        }
        else if(i_inSeats[r][c] == 'L' && count(i_inSeats, r, c) == 0) {
            newSeats[r][c] = '#';
            changed = true;
        }
      }
    }
    i_inSeats = newSeats;
  }
}

size_t result1(std::vector<std::string> i_inSeats) {
  changeSeats(i_inSeats, 3, countNear);
  return totalOccupied(i_inSeats);
}
size_t result2(std::vector<std::string> i_inSeats) {
  changeSeats(i_inSeats, 4, countFar);
  return totalOccupied(i_inSeats);
}

int main()
{
  std::vector<std::string> seats = readFile(R"(.\Input\PartAB.txt)");
  //std::vector<std::string> seats = readFile(R"(.\Input\TestA.txt)");
  std::cout << std::endl << "Result 1: " << result1(seats);
  std::cout << std::endl << "Result 2: " << result2(seats);

  return 0;
}

