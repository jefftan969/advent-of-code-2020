#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  // Read input from file
  std::ifstream file("day08.txt");
  std::string line;
  std::vector<std::string> ops;
  std::vector<int> args;
  std::vector<bool> executed;

  // Parse each line into operation and argument, with array to store whether each command has been executed
  int arg = 0;
  while(std::getline(file, line)) {
    ops.push_back(line.substr(0, 3));

    std::stringstream arg_ss(line.substr(4, std::string::npos));
    arg_ss >> arg;
    args.push_back(arg);

    executed.push_back(false);
  }

  // Keep track of program counter and accumulator
  int pc = 0;
  int acc = 0;

  // Keep executing commands, stopping before any instruction is repeated
  while(!executed[pc]) {
    executed[pc] = true;
    std::string &command = ops[pc];

    if(command == std::string("nop")) {
      pc++;
    } else if(command == std::string("acc")) {
      acc += args[pc];
      pc++;
    } else if(command == std::string("jmp")) {
      pc += args[pc];
    }
  }

  std::cout << acc << std::endl;
  return 0;
}
