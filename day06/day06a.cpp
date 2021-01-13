#include <fstream>
#include <iostream>
#include <set>
#include <string>

int main() {
  // Read input from file
  std::ifstream file("day06.txt");
  std::string line;
  bool continue_loop = true;

  std::set<char> current_group;
  int group_counts = 0;

  while(continue_loop) {
    continue_loop = static_cast<bool>(std::getline(file, line));

    if(line == std::string("")) {
      // If line is empty, find the number of unique characters in the current group, and add to sum
      group_counts += current_group.size();
      current_group.clear();
    } else {
      // If line is nonempty, insert the current line's characters into current group
      for(int i = 0; i < line.length(); i++) {
        current_group.insert(line[i]);
      }
    }
  }

  std::cout << group_counts << std::endl;
  return 0;
}
