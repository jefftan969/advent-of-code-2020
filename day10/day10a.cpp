#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Read input from file
  std::ifstream file("day10.txt");
  std::string line;
  std::vector<int> nums;

  while(std::getline(file, line)) {
    int next_int = std::stoi(line);
    nums.push_back(next_int);
  }

  // Include charging outlet and device's built-in adapter
  nums.push_back(0);
  nums.push_back(*std::max_element(nums.begin(), nums.end()) + 3);

  // Sort input
  std::sort(nums.begin(), nums.end());

  // Find pairwise differences to determine number of 1-diffs and 3-diffs
  int num_1diffs = 0;
  int num_3diffs = 0;
  for(int i = 1; i < nums.size(); i++) {
    int diff = nums[i] - nums[i-1];
    if(diff == 1) {
      num_1diffs++;
    } else if(diff == 3) {
      num_3diffs++;
    }
  }
  
  // Print result
  std::cout << num_1diffs * num_3diffs << std::endl;
  return 0;
}
