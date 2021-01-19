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
  int next_int;

  while(std::getline(file, line)) {
    int next_int = std::stoi(line);
    nums.push_back(next_int);
  }

  // Include charging outlet and device's built-in adapter
  int adapter_voltage = *std::max_element(nums.begin(), nums.end()) + 3;
  nums.push_back(0);
  nums.push_back(adapter_voltage);

  // Sort input
  std::sort(nums.begin(), nums.end());

  // Partition the number of ways to reach a number, by what the most recent jump was
  long *ways_to_reach = new long[adapter_voltage + 1](); // Should be zero-initialized
  ways_to_reach[0] = 1;
  
  for(int i = 1; i < nums.size(); i++) {
    int num = nums[i];
    if(num - 1 >= 0)
      ways_to_reach[num] += ways_to_reach[num - 1];
    if(num - 2 >= 0)
      ways_to_reach[num] += ways_to_reach[num - 2];
    if(num - 3 >= 0)
      ways_to_reach[num] += ways_to_reach[num - 3];
  }
  
  // Print result
  std::cout << ways_to_reach[adapter_voltage] << std::endl;
  return 0;
}
