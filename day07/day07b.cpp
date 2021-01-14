#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Parses plural description string using regex
bool parse_plural_description(const std::string &str, int &bag_amount, std::string &bag_color) {
  static const std::regex plural_regex("([0-9]+) (.+) bags");
  std::smatch plural_match;

  if(std::regex_match(str, plural_match, plural_regex)) {
    // First sub_match is the whole string, the next sub_match is the first parenthesized expression
    if(plural_match.size() == 3) {
      // The first parenthesized expression is bag_amount, convert it to integer
      std::ssub_match bag_amount_match = plural_match[1];
      std::stringstream bag_amount_ss(bag_amount_match.str());
      bag_amount_ss >> bag_amount;

      // The second parenthesized expression is bag_color, save to the given variable
      std::ssub_match bag_color_match = plural_match[2];
      bag_color = bag_color_match.str();

      return true;
    }
  }

  return false;
}

// Parses singular description string using regex
bool parse_singular_description(const std::string &str, std::string &bag_color) {
  static const std::regex singular_regex("1 (.+) bag");
  std::smatch singular_match;

  if(std::regex_match(str, singular_match, singular_regex)) {
    // First sub_match is the whole string, the next sub_match is the first parenthesized expression
    if(singular_match.size() == 2) {
      // The first parenthesized expression is bag_color, save to the given variable
      std::ssub_match bag_color_match = singular_match[1];
      bag_color = bag_color_match.str();

      return true;
    }
  }

  return false;
}

// Parses an input line using regex
bool parse_input_line(const std::string &str, std::string &bag_color, std::string &bag_contents) {
  static const std::regex input_regex("(.+) bags contain (.+).");
  std::smatch input_match;

  if(std::regex_match(str, input_match, input_regex)) {
    // First sub_match is the whole string, the next sub_match is the first parenthesized expression
    if(input_match.size() == 3) {
      // The first parenthesized expression is bag_color, save to the given variable
      std::ssub_match bag_color_match = input_match[1];
      bag_color = bag_color_match.str();

      // The second parenthesized expression is bag_contents, save to the given variable
      std::ssub_match bag_contents_match = input_match[2];
      bag_contents = bag_contents_match.str();

      return true;
    }
  }

  return false;
}

// Recursively finds how many bags are contained within a given bag color
int find_contained_amount(const std::unordered_map<std::string, std::unordered_map<std::string, int>> &bags,
                          const std::string &bag_color) {
  int contained_amt = 0;
  const std::unordered_map<std::string, int> &contained_bags = bags.at(bag_color);
  for(const std::pair<std::string, int> &contained_bag : contained_bags) {
    contained_amt += contained_bag.second * (1 + find_contained_amount(bags, contained_bag.first));
  }
  return contained_amt;
}

// Extracts the bag amount and bag color from the given string description of a bag, and insert it into
// the given bag_contents unordered map
void parse_bag_description(const std::string &bag_description,
                           std::unordered_map<std::string, int> &bag_contents) {
  int bag_amount = 0;
  std::string bag_color;

  // Try to parse as plural description string
  if(parse_plural_description(bag_description, bag_amount, bag_color)) {
    bag_contents.insert(std::pair<std::string, int>(bag_color, bag_amount));
  }

  // Try to parse as singular description string
  if(parse_singular_description(bag_description, bag_color)) {
    bag_contents.insert(std::pair<std::string, int>(bag_color, 1));
  }
}

int main() {
  // Read input from file
  std::ifstream file("day07.txt");
  std::string line;
  std::unordered_map<std::string, std::unordered_map<std::string, int>> bags;
  std::string bag_contents_delim = std::string(", ");

  while(std::getline(file, line)) {
    // Parse the given line, retrieving the color of the specified bags as well as all contained bags
    std::string bag_color;
    std::string bag_contents;
    
    if(!parse_input_line(line, bag_color, bag_contents)) {
      continue;
    }

    bags[bag_color] = std::unordered_map<std::string, int>();

    // If the current bag contains other bags, populate bag_contents with the contained bags
    if(bag_contents == std::string("no other bags")) {
      continue;
    }
    
    int start = 0;
    int end = bag_contents.find(bag_contents_delim);

    while(end != std::string::npos) {
      parse_bag_description(bag_contents.substr(start, end-start), bags[bag_color]);
      start = end + bag_contents_delim.length();
      end = bag_contents.find(bag_contents_delim, start);
    }
    parse_bag_description(bag_contents.substr(start, end), bags[bag_color]);
  }

  // Print result
  std::cout << find_contained_amount(bags, std::string("shiny gold")) << std::endl;
  return 0;
}
