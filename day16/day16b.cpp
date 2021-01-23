#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

bool num_in_range(int num, const std::vector<std::pair<int, int>> &ranges) {
  for(const std::pair<int, int> &subrange : ranges) {
    if(subrange.first <= num && num <= subrange.second) {
      return true;
    }
  }
  return false;
}

// Returns the sum of all invalid numbers on the ticket
int get_invalid_sum(const std::vector<int> &ticket,
                    const std::unordered_map<std::string, std::vector<std::pair<int, int>>> &valid_ranges) {
  int invalid_sum = 0;
  for(int num : ticket) {
    bool is_valid = false;
    // Check whether each number on the ticket is contained within some range
    for(const std::pair<std::string, std::vector<std::pair<int, int>>> &valid_range : valid_ranges) {
      if(num_in_range(num, valid_range.second)) {
        is_valid = true;
      }
    }
    if(!is_valid) {
      invalid_sum += num;
    }
  }
  return invalid_sum;
}

bool position_range_match(const std::vector<std::vector<int>> &valid_tickets,
                          const std::vector<std::pair<int, int>> &ranges,
                          int position) {
  for(const std::vector<int> &ticket : valid_tickets) {
    int num = ticket[position];
    if(!num_in_range(num, ranges)) {
      return false;
    }
  }
  return true;
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

  // Initialize data structure to keep track of valid tickets
  std::vector<std::vector<int>> valid_tickets;
  valid_tickets.push_back(your_ticket);

  // Parse nearby tickets, keeping only the valid tickets
  std::getline(file, line); // Skip empty line
  std::getline(file, line); // Skip the line "nearby tickets: "

  while(std::getline(file, line)) {
    std::vector<int> ticket;
    parse_ticket(line, ticket);
    if(get_invalid_sum(ticket, valid_ranges) == 0) {
      valid_tickets.push_back(ticket);
    }
  }

  // Build position range table
  std::vector<std::unordered_map<std::string, bool>> position_range_table;
  for(int position = 0; position < your_ticket.size(); position++) {
    std::unordered_map<std::string, bool> range_table;
    for(const std::pair<std::string, std::vector<std::pair<int, int>>> &valid_range : valid_ranges) {
      range_table[valid_range.first] = position_range_match(valid_tickets, valid_range.second, position);
    }
    position_range_table.push_back(range_table);
  }

  // Try to find definitive matches between positions and range names
  std::unordered_map<std::string, int> position_range_matches;
  while(true) {
    bool certain_match_found = false;
    for(int position = 0; position < your_ticket.size(); position++) {
      // Find all possible matches
      int num_possible_matches = 0;
      std::string match;
      for(const std::pair<std::string, bool> &row_entry : position_range_table[position]) {
        if(row_entry.second) {
          num_possible_matches++;
          match = row_entry.first;
        }
      }

      // If only one match possible, update position range table to prevent that range from being matched again
      if(num_possible_matches == 1) {
        position_range_matches[match] = position;
        for(int pos = 0; pos < your_ticket.size(); pos++) {
          position_range_table[pos][match] = false;
        }
        certain_match_found = true;
      }
    }

    // Exit if no definitive match found
    if(!certain_match_found) {
      break;
    }
  }

  // Multiply together the numbers on your ticket belonging to fields that start with "departure"
  long your_departure_product = 1;
  for(const std::pair<std::string, int> &match : position_range_matches) {
    if(match.first.find(std::string("departure"), 0) != std::string::npos) {
      your_departure_product *= your_ticket[match.second];
    }
  }

  std::cout << your_departure_product << std::endl;
  return 0;
}
