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
  bool use_first_line = true;

  while(continue_loop) {
    continue_loop = static_cast<bool>(std::getline(file, line));

    if(line == std::string("")) {
      // If line is empty, find the number of unique characters in the current group, and add to sum
      group_counts += current_group.size();
      current_group.clear();
      use_first_line = true;
    } else {
      // If line is nonempty, take the intersection of the current line's characters with current group
      std::set<char> current_line;
      for(int i = 0; i < line.length(); i++) {
        current_line.insert(line[i]);
      }

      if(use_first_line) {
        // If current group is empty, set it equal to contents of the first line
        use_first_line = false;
        current_group.swap(current_line);
      } else {
        // Otherwise, take intersection of current group and contents of current line
        std::set<char> intersection;
        for(std::set<char>::iterator it = current_line.begin(); it != current_line.end(); it++) {
          if(current_group.find(*it) != current_group.end()) {
            intersection.insert(*it);
          }
        }
        current_group.swap(intersection);
      }
    }
  }

  std::cout << group_counts << std::endl;
  return 0;
}
