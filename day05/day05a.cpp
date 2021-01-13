#include <fstream>
#include <iostream>
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

  int max_seat_id = -1;
  while(std::getline(file, line)) {
    int seat_id = get_seat_id(line);
    if(max_seat_id < seat_id) {
      max_seat_id = seat_id;
    }
  }

  std::cout << max_seat_id << std::endl;
}
