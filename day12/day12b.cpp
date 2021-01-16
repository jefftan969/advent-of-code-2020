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

  double shipX = 0;
  double shipY = 0;
  double wayX = 10;
  double wayY = 1;
  double temp_wayX = 0;
  double temp_wayY = 0;
  double theta = 0.0;

  while(std::getline(file, line)) {
    std::stringstream line_ss(line);
    line_ss >> action;
    line_ss >> value;

    switch(action) {
      case 'N':
        wayY += value;
        break;
      case 'S':
        wayY -= value;
        break;
      case 'E':
        wayX += value;
        break;
      case 'W':
        wayX -= value;
        break;
      case 'L':
        // Rotate (wayX, wayY) counterclockwise by multiplying by 2x2 rotation matrix
        theta = value * 3.1415926535 / 180.0;
        temp_wayX = wayX * std::cos(theta) - wayY * std::sin(theta);
        temp_wayY = wayX * std::sin(theta) + wayY * std::cos(theta);
        wayX = temp_wayX;
        wayY = temp_wayY;
        break;
      case 'R':
        // Rotate (wayX, wayY) clockwise by multiplying by 2x2 rotation matrix
        theta = -value * 3.1415926535 / 180.0;
        temp_wayX = wayX * std::cos(theta) - wayY * std::sin(theta);
        temp_wayY = wayX * std::sin(theta) + wayY * std::cos(theta);
        wayX = temp_wayX;
        wayY = temp_wayY;
        break;
      case 'F':
        shipX += value * wayX;
        shipY += value * wayY;
        break;
    }
  }

  std::cout << static_cast<int>(std::round(std::abs(shipX))) +
               static_cast<int>(std::round(std::abs(shipY))) << std::endl;
  return 0;
}
