#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Counts number of occurrences of character <char> in <string>
int count_char(const char *string, char c, int max_len) {
  if(string == NULL)
    return 0;
  
  int iters = 0;
  int count = 0;
  for(const char *i = string; *i != 0 && iters++ < max_len; i++) {
    if(*i == c)
      count++;
  }
  
  return count;
}

bool validate_line(std::string &line) {
  // Parse line into min and max occurrences, desired char, and password
  int min_amt = 0;
  int max_amt = 0;
  char desired_char = 0;
  char *password = new char[line.length() + 1];

  if(std::sscanf(line.c_str(), "%d-%d %c: %s", &min_amt, &max_amt, &desired_char, password) != 4) {
    delete password;
    return false;
  }

  int char_amt = count_char(password, desired_char, line.length() + 1);
  delete password;
  return (min_amt <= char_amt) && (char_amt <= max_amt);
}

int main() {
  // Read input from file
  std::ifstream file("day02.txt");
  std::string line;

  // Count whether each line is valid
  int count = 0;
  while(std::getline(file, line)) {
    if(validate_line(line))
      count++;
  }
  
  std::cout << count << std::endl;

  return 0;
}
