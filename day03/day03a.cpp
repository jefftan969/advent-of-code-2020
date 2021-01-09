#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int check_slope(const std::vector<std::string> &slope, int horizontal_offset, int vertical_offset) {
  int width = slope[0].length();
  int height = slope.size();

  // For each row, use modular arithmetic to determine which column to consider
  int count = 0;
  for(int row = 0; row < height; row += vertical_offset) {
    int col = (horizontal_offset * row / vertical_offset) % width;
    if(slope[row][col] == '#')
      count++;
  }
  return count;
}

int main() {
  // Read input from file
  std::ifstream file("day03.txt");
  std::string line;
  std::vector<std::string> slope;

  while(std::getline(file, line)) {
    slope.push_back(line);
  }
  
  int result31 = check_slope(slope, 3, 1);
  std::cout << result31 << std::endl;

  return 0;
}
