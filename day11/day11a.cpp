#include <fstream>
#include <iostream>
#include <string>
#include <vector>

char access_seat(const std::vector<std::string> &seats, int row, int col) {
  if(0 <= row && row < seats.size()) {
    if(0 <= col && col < seats[row].length()) {
      return seats[row][col];
    }
  }
  return 'L';
}

int count_neighbors(const std::vector<std::string> &seats, int row, int col) {
  int num_neighbors = 0;
  for(int row_diff = -1; row_diff <= 1; row_diff++) {
    for(int col_diff = -1; col_diff <= 1; col_diff++) {
      if(row_diff != 0 || col_diff != 0) {
        if(access_seat(seats, row + row_diff, col + col_diff) == '#') {
          num_neighbors++;
        }
      }
    }
  }
  return num_neighbors;
}

bool check_equal(const std::vector<std::string> &seats, const std::vector<std::string> &new_seats) {
  if(seats.size() != new_seats.size()) {
    return false;
  }

  for(int row = 0; row < seats.size(); row++) {
    if(seats[row] != new_seats[row]) {
      return false;
    }
  }
  return true;
}

int main() {
  // Read input from file
  std::ifstream file("day11.txt");
  std::string line;
  std::vector<std::string> seats;

  while(std::getline(file, line)) {
    seats.push_back(line);
  }

  // Keep applying rules until seats no longer change
  std::vector<std::string> new_seats(seats);
  while(true) {
    // Apply rules
    for(int row = 0; row < seats.size(); row++) {
      for(int col = 0; col < seats[row].length(); col++) {
        if(seats[row][col] != '.') {
          int neighbors = count_neighbors(seats, row, col);
          if(neighbors == 0) {
            // Empty seat with no adjacent occupied seats becomes occupied
            new_seats[row][col] = '#';
          } else if(neighbors >= 4) {
            // Occupied seat with >=4 adjacent occupied seats becomes empty
            new_seats[row][col] = 'L';
          } else {
            // Otherwise, seat state does not change
            new_seats[row][col] = seats[row][col];
          }
        }
      }
    }
    
    // Check whether seat pattern has changed, and return result if no change
    if(check_equal(seats, new_seats)) {
      int occupant_count = 0;
      for(int row = 0; row < seats.size(); row++) {
        for(int col = 0; col < seats[row].length(); col++) {
          if(seats[row][col] == '#') {
            occupant_count++;
          }
        }
      }
      std::cout << occupant_count << std::endl;
      return 0;
    }

    seats.swap(new_seats);
  }

  return 0;
}
