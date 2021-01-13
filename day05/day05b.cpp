#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int get_seat_id(const std::string &line) {
  // Separate into row and column strings
  if(line.length() != 10) {
    return -1;
  }
  const std::string row_str = line.substr(0, 7);
  const std::string col_str = line.substr(7, 3);

  // Do binary search as instructed to find seat row and column
  int row_lo = 0;
  int row_hi = 127;
  for(int i = 0; i < 7; i++) {
    if(row_str[i] == 'B') {
      row_lo = (row_lo + row_hi) / 2 + 1;
    } else if(row_str[i] == 'F') {
      row_hi = (row_lo + row_hi) / 2;
    }
  }

  int col_lo = 0;
  int col_hi = 7;
  for(int i = 0; i < 3; i++) {
    if(col_str[i] == 'R') {
      col_lo = (col_lo + col_hi) / 2 + 1;
    } else if(col_str[i] == 'L') {
      col_hi = (col_lo + col_hi) / 2;
    }
  }
  
  // Compute and return seat ID
  return 8*row_lo + col_lo;
}

int main() {
  // Read input from file
  std::ifstream file("day05.txt");
  std::string line;

  // To find the missing seat ID, find the sum of all seat IDs encountered
  // Then, subtract this sum from <min seat ID> + ... + <max seat ID> to find the missing one
  int min_seat_id = std::numeric_limits<int>::max();
  int max_seat_id = std::numeric_limits<int>::min();
  int seat_id_sum = 0;
  while(std::getline(file, line)) {
    int seat_id = get_seat_id(line);
    if(max_seat_id < seat_id) {
      max_seat_id = seat_id;
    }
    if(min_seat_id > seat_id) {
      min_seat_id = seat_id;
    }
    seat_id_sum += seat_id;
  }

  int expected_sum = (max_seat_id*(max_seat_id+1) - (min_seat_id-1)*(min_seat_id)) / 2;
  int missing_seat_id = expected_sum - seat_id_sum;

  std::cout << missing_seat_id << std::endl;
  return 0;
}
