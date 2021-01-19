#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Modifies the given sequence of operations by interchanging "nop" and "jmp" at the specified index
void modify_program(std::vector<std::string> &ops, int index) {
  if(ops[index] == std::string("nop")) {
    ops[index] = std::string("jmp");
  } else if(ops[index] == std::string("jmp")) {
    ops[index] = std::string("nop");
  }
}

int eval_program(std::vector<std::string> &ops, std::vector<int> &args, std::vector<bool> &executed) {
  // Reset executed array to all false
  for(int i = 0; i < executed.size(); i++) {
    executed[i] = false;
  }

  // Keep program counter and accumulator
  int pc = 0;
  int acc = 0;

  // Keep executing commands, stopping before any instruction is repeated, or on program termination
  while(pc < ops.size() && (!executed[pc])) {
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

  // Return accumulator if program terminated normally, otherwise return -1
  if(pc == ops.size()) {
    return acc;
  }
  return -1;
}

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

    int arg = std::stoi(line.substr(4, std::string::npos));
    args.push_back(arg);

    executed.push_back(false);
  }

  // For every line, modify that line and see if program terminates normally
  for(int i = 0; i < ops.size(); i++) {
    modify_program(ops, i);
    int result = eval_program(ops, args, executed);
    if(result != -1) {
      std::cout << result << std::endl;
      break;
    }
    modify_program(ops, i);
  }
  
  return 0;
}
