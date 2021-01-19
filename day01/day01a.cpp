#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Read input from file and sort
  std::ifstream file("day01.txt");
  std::string line;
  std::vector<int> nums;

  while(std::getline(file, line)) {
    int next_int = std::stoi(line);
    nums.push_back(next_int);
  }
    
  std::sort(nums.begin(), nums.end());

  // Scan through input for two numbers that add to 2020
  // Use two pointers into sorted list, one starting on the left and the other starting on the right
  // If sum too small, increment left pointer to increase the sum
  // If sum too large, decrement right pointer to decrease the sum
  // Eventually, if two numbers exist adding to 2020, they will be found
  int desired_sum = 2020;
  std::vector<int>::iterator start_index = nums.begin();
  std::vector<int>::iterator end_index = nums.end() - 1;
  while(start_index < end_index) {
    int x = *start_index;
    int y = *end_index;
    int current_sum = x + y;
    if(current_sum < desired_sum)
      start_index++;
    else if(current_sum > desired_sum)
      end_index--;
    else {
      std::cout << x * y << std::endl;
      break;
    }
  }

  return 0;
}
