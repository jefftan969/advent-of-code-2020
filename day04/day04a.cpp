#include <fstream>
#include <iostream>
#include <string>

int main() {
  // Read input from file
  std::ifstream file("day04.txt");
  std::string line;
  bool continue_loop = true;

  constexpr int num_fields = 7;
  std::string field_keys[num_fields] = {"byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:"};
  bool field_is_valid[num_fields] = {0};
  int valid_count = 0;

  while(continue_loop) {
    continue_loop = static_cast<bool>(std::getline(file, line));
    if(line == std::string("")) {
      // If line is empty, check if previous passport is valid
      bool is_valid = true;
      for(int i = 0; i < num_fields; i++) {
        if(!field_is_valid[i]) {
          is_valid = false;
        }
        field_is_valid[i] = false;
      }
      if(is_valid) {
        valid_count++;
      }
    } else {
      // If line is nonempty, find any valid tokens in that line
      for(int i = 0; i < num_fields; i++) {
        if(!field_is_valid[i] && line.find(field_keys[i]) != std::string::npos) {
          field_is_valid[i] = true;
        }
      }
    }
  }

  std::cout << valid_count << std::endl;
  return 0;
}
