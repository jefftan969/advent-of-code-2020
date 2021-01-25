#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// If the start of the message matches the given rule, return a list of indices at which matching possibly stops
// Otherwise, returns the empty list
std::vector<int> match_helper(const std::unordered_map<std::string,std::vector<std::vector<std::string>>> &rules,
                              const std::string &message,
                              const std::string &rule,
                              int start_index) {
  // Matching fails if trying to match beyond end of the string
  if(start_index >= message.length()) {
    return std::vector<int>();
  }

  // If rule is a single character enclosed by quotes (e.g. "a" or "b"), try to match a single character
  std::vector<int> matches_found;
  if(rule[0] == '"' && rule[2] == '"') {
    if(message[start_index] == rule[1]) {
      matches_found.push_back(start_index + 1);
    }
    return matches_found;
  }

  // Otherwise, proceed through definition of rule, recursively calling match
  for(const std::vector<std::string> &rule_seq : rules.at(rule)) {
    // Apply rules in sequence, where matched_indices keeps track of the list of indices at which
    // matching could possibly continue after successfully matching up to the current rule
    std::vector<int> matched_indices;
    matched_indices.push_back(start_index);
    std::vector<int> new_matched_indices;
    for(int rule_id = 0; rule_id < rule_seq.size(); rule_id++) {
      new_matched_indices.clear();
      for(int matched_index : matched_indices) {
        for(int match : match_helper(rules, message, rule_seq[rule_id], matched_index)) {
          new_matched_indices.push_back(match);
        }
      }
      matched_indices.swap(new_matched_indices);
    }
    for(int match : matched_indices) {
      matches_found.push_back(match);
    }
  }
  return matches_found;
}

// Returns true if the message matches the given rule
bool match(const std::unordered_map<std::string, std::vector<std::vector<std::string>>> &rules,
           const std::string &message,
           const std::string &rule) {
  for(int match : match_helper(rules, message, rule, 0)) {
    if(match == message.length()) {
      return true;
    }
  }
  return false;
}

int main() {
  // Read input from file
  std::ifstream file("day19.txt");
  std::string line;
  std::unordered_map<std::string, std::vector<std::vector<std::string>>> rules;

  // Parse rules
  while(std::getline(file, line)) {
    if(line == std::string("")) {
      break;
    }

    // Separate the rule's name from its definition which contains a list of rule sequences to match
    int name_delimiter = line.find(std::string(": "));
    std::string rule_name = line.substr(0, name_delimiter);

    // For each rule sequence to match in the rule definition, represent it as a vector
    int match_start = name_delimiter + 2;
    int match_end;
    std::vector<std::vector<std::string>> rule_def;
    do {
      match_end = line.find(std::string(" | "), match_start);
      std::stringstream rule_seq_ss = std::stringstream(line.substr(match_start, match_end - match_start));
      std::string rule_seq_elem;
      std::vector<std::string> rule_seq;

      while(std::getline(rule_seq_ss, rule_seq_elem, ' ')) {
        rule_seq.push_back(rule_seq_elem);
      }
      rule_def.push_back(rule_seq);
      match_start = match_end + 3;

    } while(match_end != std::string::npos);

    rules[rule_name] = rule_def;
  }
  
  // Parse messages
  int valid_count = 0;
  while(std::getline(file, line)) {
    if(match(rules, line, "0")) {
      valid_count++;
    }
  }

  std::cout << valid_count << std::endl;
  return 0;
}
