#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
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

  // Track when each number was last spoken, to avoid linear search
  std::unordered_map<int, int> last_spoken;
  for(int i = 0; i < nums.size() - 1; i++) {
    last_spoken[nums[i]] = i;
  }

  while(nums.size() < 30000000) {
    int num = nums[nums.size() - 1];
    int next_num = 0; // If most recent number has not been spoken before, say 0 by default

    // Use last_spoken to see whether most recent number has been spoken before
    std::unordered_map<int, int>::iterator last_spoken_entry = last_spoken.find(num);
    if(last_spoken_entry != last_spoken.end()) {
      // If most recent number was spoken before, specify how many turns apart the previous occurrence was
      next_num = nums.size() - 1 - last_spoken_entry->second;
    }
   
    last_spoken[num] = nums.size() - 1;
    nums.push_back(next_num);
  }

  std::cout << nums[nums.size() - 1] << std::endl;
  return 0;
}
