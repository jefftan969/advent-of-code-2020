#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Algorithm for two-sum, using two pointers into sorted list (one starting on left, one starting on right)
// If sum too small, increment left pointer to increase the sum
// If sum too large, decrement right pointer to decrease the sum
// Eventually, if two numbers exist that add up to 2020, they will be found
template <class T>
bool findPair(const std::vector<T> &nums, T desired_sum, T &x, T &y) {
  typename std::vector<T>::const_iterator start_index = nums.begin();
  typename std::vector<T>::const_iterator end_index = nums.end() - 1;
  while(start_index < end_index) {
    T x_ = *start_index;
    T y_ = *end_index;
    T current_sum = x_ + y_;
    if(current_sum < desired_sum)
      start_index++;
    else if(current_sum > desired_sum)
      end_index--;
    else {
      x = x_;
      y = y_;
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
  int next_int;

  while(std::getline(file, line)) {
    std::stringstream int_parser(line);
    int_parser >> next_int;
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

    if(findPair<int>(nums, desired_sum - z, x, y)) {
      std::cout << x * y * z << std::endl;
      break;
    }
  }

  return 0;
}
