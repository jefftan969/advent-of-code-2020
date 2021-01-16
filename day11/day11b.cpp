#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Returns whether there exists an occupied seat in the given direction from seats[row][col]
bool occupied_in_direction(const std::vector<std::string> &seats, int row, int col,
                           int row_stride, int col_stride) {
  int seek_row = row + row_stride;
  int seek_col = col + col_stride;

  while(0 <= seek_row && seek_row < seats.size() && 0 <= seek_col && seek_col < seats[seek_row].length()) {
    if(seats[seek_row][seek_col] == '#')
      return true;
    else if(seats[seek_row][seek_col] == 'L')
      return false;
    seek_row += row_stride;
    seek_col += col_stride;
  }
  return false;
}

// Consider the first visible seat in all eight directions
int count_neighbors(const std::vector<std::string> &seats, int row, int col) {
  int num_neighbors = 0;
  for(int row_stride = -1; row_stride <= 1; row_stride++) {
    for(int col_stride = -1; col_stride <= 1; col_stride++) {
      if(row_stride != 0 || col_stride != 0) {
        if(occupied_in_direction(seats, row, col, row_stride, col_stride)) {
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
            // Empty seat that sees no occupied seats becomes occupied
            new_seats[row][col] = '#';
          } else if(neighbors >= 5) {
            // Occupied seat that sees >=5 occupied seats becomes empty
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
