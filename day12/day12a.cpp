#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  // Read input from file and sort
  std::ifstream file("day12.txt");
  std::string line;
  char action;
  int value;

  double posX = 0;
  double posY = 0;
  double theta = 0;

  while(std::getline(file, line)) {
    std::stringstream line_ss(line);
    line_ss >> action;
    line_ss >> value;

    switch(action) {
      case 'N':
        posY += value;
        break;
      case 'S':
        posY -= value;
        break;
      case 'E':
        posX += value;
        break;
      case 'W':
        posX -= value;
        break;
      case 'L':
        theta += value;
        break;
      case 'R':
        theta -= value;
        break;
      case 'F':
        posX += value * std::cos(theta * 3.1415926535 / 180.0);
        posY += value * std::sin(theta * 3.1415926535 / 180.0);
        break;
    }
  }

  std::cout << static_cast<int>(std::round(std::abs(posX))) +
               static_cast<int>(std::round(std::abs(posY))) << std::endl;
  return 0;
}
