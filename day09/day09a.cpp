#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Uses two-pointer method through sorted list to find a pair of numbers that adds to desired_sum
bool exists_pair_with_sum(std::deque<long> &nums, long desired_sum) {
  std::deque<long> nums_sorted(nums);
  std::sort(nums_sorted.begin(), nums_sorted.end());

  // Use two pointers into sorted list, one starting on the left and the other starting on the right
  // If sum too small, increment left pointer which increases the sum
  // If sum too large, decrement right pointer which decreases the sum
  // Eventually, if two numbers exist adding to desired_sum, they will be found
  std::deque<long>::iterator start_index = nums_sorted.begin();
  std::deque<long>::iterator end_index = nums_sorted.end() - 1;
  while(start_index < end_index) {
    long x = *start_index;
    long y = *end_index;
    long current_sum = x + y;

    if(current_sum < desired_sum)
      start_index++;
    else if(current_sum > desired_sum)
      end_index--;
    else {
      return true;
    }
  }

  return false;
}

int main() {
  // Read input from file
  std::ifstream file("day09.txt");
  std::string line;
  std::vector<long> nums;

  while(std::getline(file, line)) {
    long next_num = std::stol(line);
    nums.push_back(next_num);
  }

  // Initialize deque of the 25 immediately preceding numbers
  std::deque<long> prev_nums;
  for(int i = 0; i < 25; i++) {
    prev_nums.push_back(nums[i]);
  }

  // Find invalid number that's not a sum of two numbers in the 25 immediately preceding numbers
  for(int i = 25; i < nums.size(); i++) {
    if(!exists_pair_with_sum(prev_nums, nums[i])) {
      std::cout << nums[i] << std::endl;
      break;
    }
    prev_nums.pop_front();
    prev_nums.push_back(nums[i]);
  }
  
  return 0;
}
