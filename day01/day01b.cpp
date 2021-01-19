#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Algorithm for two-sum, using two pointers into sorted list (one starting on left, one starting on right)
// If sum too small, increment left pointer to increase the sum
// If sum too large, decrement right pointer to decrease the sum
// Eventually, if two numbers exist that add up to 2020, they will be found
bool findPair(const std::vector<int> &nums, int desired_sum, int &x_out, int &y_out) {
  std::vector<int>::const_iterator start_index = nums.begin();
  std::vector<int>::const_iterator end_index = nums.end() - 1;
  while(start_index < end_index) {
    int x = *start_index;
    int y = *end_index;
    int current_sum = x + y;
    if(current_sum < desired_sum)
      start_index++;
    else if(current_sum > desired_sum)
      end_index--;
    else {
      x_out = x;
      y_out = y;
      return true;
    }
  }
  return false;
}

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

  // Scan through input for three numbers that add to 2020
  // For each number in list, subtract that number from desired_sum, and
  // run two-sum algorithm on remainder of the list
  int desired_sum = 2020;
  while(nums.size() > 0) {
    int x = 0;
    int y = 0;
    int z = nums.back();
    nums.pop_back();

    if(findPair(nums, desired_sum - z, x, y)) {
      std::cout << x * y * z << std::endl;
      break;
    }
  }

  return 0;
}
