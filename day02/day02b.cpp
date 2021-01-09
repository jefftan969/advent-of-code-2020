#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool validate_line(std::string &line) {
  // Parse line into min and max occurrences, desired char, and password
  int indexL = 0;
  int indexR = 0;
  char desired_char = 0;
  char *password = new char[line.length() + 1];

  if(std::sscanf(line.c_str(), "%d-%d %c: %s", &indexL, &indexR, &desired_char, password) != 4) {
    return false;
  }

  // Switch from 1-indexing to 0-indexing
  indexL--;
  indexR--;

  int char_amt = (password[indexL] == desired_char) + (password[indexR] == desired_char);
  return (char_amt == 1);
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
