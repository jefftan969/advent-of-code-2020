#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Returns the sum of all invalid numbers on the ticket
int get_invalid_sum(const std::vector<int> &ticket,
                    const std::unordered_map<std::string, std::vector<std::pair<int, int>>> &valid_ranges) {
  int invalid_sum = 0;
  for(int num : ticket) {
    bool is_valid = false;
    // Check whether each number on the ticket is contained within some range
    for(const std::pair<std::string, std::vector<std::pair<int, int>>> &valid_range : valid_ranges) {
      for(const std::pair<int, int> &subrange : valid_range.second) {
        if(subrange.first <= num && num <= subrange.second) {
          is_valid = true;
        }
      }
    }
    if(!is_valid) {
      invalid_sum += num;
    }
  }
  return invalid_sum;
}

// Parses range bound string (example: "25-727 or 729-1393")
void parse_range_bounds(const std::string &range_bound_str, int start_index,
                        std::vector<std::pair<int, int>> &range_bounds) {
  std::string bound = std::string(" or ");
  int bound_delimiter = range_bound_str.find(bound, start_index);
  int i = range_bound_str.find('-', start_index);

  if(bound_delimiter == std::string::npos) {
    // If this is the last bound, parse it here and return
    int subrange_min = std::stoi(range_bound_str.substr(start_index, i-start_index));
    int subrange_max = std::stoi(range_bound_str.substr(i+1, std::string::npos));
    range_bounds.push_back(std::pair<int, int>(subrange_min, subrange_max));

  } else {
    // Otherwise, parse the first bound here and recursively parse the remaining bounds
    if(i < bound_delimiter) {
      int subrange_min = std::stoi(range_bound_str.substr(start_index, i-start_index));
      int subrange_max = std::stoi(range_bound_str.substr(i+1, bound_delimiter-(i+1)));
      range_bounds.push_back(std::pair<int, int>(subrange_min, subrange_max));
    }
    parse_range_bounds(range_bound_str, bound_delimiter + bound.length(), range_bounds);
  }
}

// Parses a ticket (which is a comma-separated string of numbers)
void parse_ticket(const std::string &ticket_str, std::vector<int> &ticket) {
  std::stringstream ticket_ss(ticket_str);
  std::string ticket_num;
  while(std::getline(ticket_ss, ticket_num, ',')) {
    int num = std::stoi(ticket_num);
    ticket.push_back(num);
  }
}

int main() {
  // Read input from file
  std::ifstream file("day16.txt");
  std::string line;

  // Parse valid ranges for different fields on the ticket
  std::unordered_map<std::string, std::vector<std::pair<int, int>>> valid_ranges;
  while(std::getline(file, line)) {
    if(line == std::string("")) {
      break;
    }

    int delimiter = line.find(std::string(": "), 0);
    if(delimiter == std::string::npos) {
      break;
    }

    std::string range_name = line.substr(0, delimiter);
    std::string range_bounds_str = line.substr(delimiter+2, std::string::npos);
    std::vector<std::pair<int, int>> range_bounds;
    parse_range_bounds(range_bounds_str, 0, range_bounds);
    valid_ranges[range_name] = range_bounds;
  }

  // Parse your ticket
  std::getline(file, line); // Skip the line "your ticket: "
  std::getline(file, line);
  std::vector<int> your_ticket;
  parse_ticket(line, your_ticket);

  // Parse nearby tickets, taking the invalid sum of each nearby ticket
  std::getline(file, line); // Skip empty line
  std::getline(file, line); // Skip the line "nearby tickets: "

  int invalid_sum = 0;
  while(std::getline(file, line)) {
    std::vector<int> ticket;
    parse_ticket(line, ticket);
    invalid_sum += get_invalid_sum(ticket, valid_ranges);
  }

  std::cout << invalid_sum << std::endl;
  return 0;
}
