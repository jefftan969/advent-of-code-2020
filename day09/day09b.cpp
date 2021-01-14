#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

// Uses two-pointer method through sorted list to find a pair of numbers that adds to desired_sum
bool exists_pair_with_sum(std::deque<int> &nums, int desired_sum) {
  std::deque<int> nums_sorted(nums);
  std::sort(nums_sorted.begin(), nums_sorted.end());

  // Use two pointers into sorted list, one starting on the left and the other starting on the right
  // If sum too small, increment left pointer which increases the sum
  // If sum too large, decrement right pointer which decreases the sum
  // Eventually, if two numbers exist adding to desired_sum, they will be found
  std::deque<int>::iterator start_index = nums_sorted.begin();
  std::deque<int>::iterator end_index = nums_sorted.end() - 1;
  while(start_index < end_index) {
    int x = *start_index;
    int y = *end_index;
    int current_sum = x + y;

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
  std::vector<int> nums;
  int next_int;

  while(std::getline(file, line)) {
    std::stringstream int_parser(line);
    int_parser >> next_int;
    nums.push_back(next_int);
  }

  // Initialize deque of the 25 immediately preceding numbers
  std::deque<int> prev_nums;
  for(int i = 0; i < 25; i++) {
    prev_nums.push_back(nums[i]);
  }

  // Find invalid number that's not a sum of two numbers in the 25 immediately preceding numbers
  int invalid_num = -1;
  for(int i = 25; i < nums.size(); i++) {
    if(!exists_pair_with_sum(prev_nums, nums[i])) {
      invalid_num = nums[i];
      break;
    }
    prev_nums.pop_front();
    prev_nums.push_back(nums[i]);
  }

  // Find sums of every possible contiguous set of numbers, by accumulating onto the list contiguous_sums
  // Each iteration of outer loop finds all possible contiguous sums of a given quantity of adjacent numbers
  // Each iteration of inner loop considers the contiguous sum that starts at index 0, 1, 2, ...
  std::vector<int> contiguous_sums = std::vector<int>(nums);
  for(int offset = 1; offset < nums.size()-1; offset++) {
    for(int i = 0; i < nums.size() - offset; i++) {
      contiguous_sums[i] += nums[i+offset];
      if(contiguous_sums[i] == invalid_num) {
        // Successfully found a contiguous sum that adds to the invalid number
        // Search for minimum and maximum number within this range
        int range_min = std::numeric_limits<int>::max();
        int range_max = std::numeric_limits<int>::min();

        for(int j = i; j <= i + offset; j++) {
          if(range_min > nums[j]) {
            range_min = nums[j];
          }
          if(range_max < nums[j]) {
            range_max = nums[j];
          }
        }

        // Print encryption weakness
        std::cout << range_min + range_max << std::endl;
        return 0;
      }
    }
  }
  
  return 0;
}
