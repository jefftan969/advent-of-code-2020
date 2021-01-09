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
  
  int result11 = check_slope(slope, 1, 1);
  int result31 = check_slope(slope, 3, 1);
  int result51 = check_slope(slope, 5, 1);
  int result71 = check_slope(slope, 7, 1);
  int result12 = check_slope(slope, 1, 2);
  std::cout << static_cast<long>(result11) * result31 * result51 * result71 * result12 << std::endl;

  return 0;
}
