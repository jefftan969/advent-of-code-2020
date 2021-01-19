#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Read input from file
  std::ifstream file("day15.txt");
  std::string line;
  std::vector<int> nums;

  while(std::getline(file, line, ',')) {
    int next_int = std::stoi(line);
    nums.push_back(next_int);
  }

  while(nums.size() < 2020) {
    int num = nums[nums.size() - 1];
    int next_num = 0; // If most recent number has not been spoken before, say 0 by default

    // Search backwards to see whether most recent number has been spoken before
    for(int i = 1; i < nums.size(); i++) {
      if(nums[nums.size() - 1 - i] == num) {
        // If most recent number was spoken before, specify how many turns apart the previous occurrence was
        next_num = i;
        break;
      }
    }
    
    nums.push_back(next_num);
  }

  std::cout << nums[nums.size() - 1] << std::endl;
  return 0;
}
