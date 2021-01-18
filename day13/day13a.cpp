#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  // Read input from file
  std::ifstream file("day13.txt");
  std::string line;
  int start;

  // Parse first line
  std::getline(file, line);
  std::stringstream start_ss(line);
  start_ss >> start;

  // Parse second line, where bus numbers are comma-separated
  std::getline(file, line);
  std::stringstream buses_ss(line);
  std::string bus_str;
  int bus;

  int min_diff = start;
  int min_bus = -1;

  while(std::getline(buses_ss, bus_str, ',')) {
    // Extract the next bus number, if it's not 'x'
    if(bus_str != std::string("x")) {
      std::stringstream bus_str_ss(bus_str);
      bus_str_ss >> bus;

      int diff = (bus - (start % bus)) % bus;
      if(min_diff > diff) {
        min_diff = diff;
        min_bus = bus;
      }
    }
  }

  std::cout << min_bus * min_diff << std::endl;
  return 0;
}
