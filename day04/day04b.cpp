#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

bool is_between(const std::string &num_str, int low, int high) {
  // Convert argument to string
  int num;
  std::stringstream int_parser(num_str);
  int_parser >> num;

  return (low <= num) && (num <= high);
}

// Four digits, at least 1920 and at most 2002
bool byr_validfn(const std::string &x) {
  return is_between(x, 1920, 2002);
}

// Four digits, at least 2010 and at most 2020
bool iyr_validfn(const std::string &x) {
  return is_between(x, 2010, 2020);
}

// Four digits, at least 2020 and at most 2030
bool eyr_validfn(const std::string &x) {
  return is_between(x, 2020, 2030);
}

// A number, either 150cm <= x <= 193cm or 59in <= x <= 76in
bool hgt_validfn(const std::string &x) {
  int len = x.length();

  // Reject short strings
  if(len <= 2)
    return false;

  if(x[len-2] == 'c' && x[len-1] == 'm')
    return is_between(x.substr(0, len-2), 150, 193);
  else if(x[len-2] == 'i' && x[len-1] == 'n')
    return is_between(x.substr(0, len-2), 59, 76);

  return false;
}

// A '#' followed by exactly six hexadecimal characters 0-9 or a-f
bool hcl_validfn(const std::string &x) {
  if(x.length() != 7 || x[0] != '#')
    return false;
  
  for(int i = 1; i < 7; i++) {
    if(!std::isxdigit(x[i]))
      return false;
  }
  return true;
}

// Exactly one of the values in a given list
bool ecl_validfn(const std::string &x) {
  static constexpr int num_ecls = 7;
  static std::string valid_ecls[num_ecls] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  for(int i = 0; i < num_ecls; i++) {
    if(x == valid_ecls[i])
      return true;
  }
  return false;
}

// A nine-digit number including leading zeroes
bool pid_validfn(const std::string &x) {
  if(x.length() != 9)
    return false;

  for(int i = 0; i < 9; i++) {
    if(!std::isdigit(x[i]))
      return false;
  }
  return true;
}

int main() {
  // Read input from file
  std::ifstream file("day04.txt");
  std::string line;
  bool continue_loop = true;

  // Construct mappings from each key to its validation function, as well as a bool denoting whether that
  // key had a valid entry in the current passport
  std::unordered_map<std::string, std::function<bool(const std::string &)>> criteria = {
    {"byr:", byr_validfn},
    {"iyr:", iyr_validfn},
    {"eyr:", eyr_validfn},
    {"hgt:", hgt_validfn},
    {"hcl:", hcl_validfn},
    {"ecl:", ecl_validfn},
    {"pid:", pid_validfn}
  };

  std::unordered_map<std::string, bool> field_is_valid = {
    {"byr:", false},
    {"iyr:", false},
    {"eyr:", false},
    {"hgt:", false},
    {"hcl:", false},
    {"ecl:", false},
    {"pid:", false}
  };

  constexpr int num_fields = 7;
  std::string field_keys[num_fields] = {"byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:"};
  int valid_count = 0;

  while(continue_loop) {
    continue_loop = static_cast<bool>(std::getline(file, line));
    if(line == std::string("")) {
      // If line is empty, check if previous passport is valid
      bool is_valid = true;

      for(int i = 0; i < num_fields; i++) {
        if(!field_is_valid[field_keys[i]]) {
          is_valid = false;
        }
        field_is_valid[field_keys[i]] = false;
      }
      if(is_valid) {
        valid_count++;
      }
    } else {
      // Otherwise, check validity of the tokens in that line by calling corresponding validfn
      std::stringstream word_parser(line);
      do {
        // Consider one whitespace-separated token at a time
        std::string token;
        word_parser >> token;

        if(token.length() <= 4) {
          continue;
        }

        // Parse token into key and value, and call corresponding validfn to determine validity
        std::string token_key = token.substr(0, 4);
        std::string token_value = token.substr(4, token.length() - 4);
        try {
          std::function<bool(const std::string &)> validfn = criteria.at(token_key);
          if(validfn(token_value)) {
            field_is_valid[token_key] = true;
          }
        }
        catch(const std::out_of_range &e) {
          // Ignore invalid keys
        }
      } while(word_parser);
    }
  }
  
  std::cout << valid_count << std::endl;
  return 0;
}
