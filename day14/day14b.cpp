#include <bitset>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

void write_to_memory(long value, std::string &addr_str, int scan_index, std::unordered_map<long, long> &mem) {
  if(scan_index == addr_str.length()) {
    // If entire memory address has been scanned for X's, convert value from binary and write to memory
    std::bitset<36> addr(addr_str);
    mem[addr.to_ulong()] = value;

  } else if(addr_str[scan_index] == 'X') {
    // If current bit of memory address is 'X', recursively spawn two instances of write_to_memory,
    // one interpreting the 'X' as 0 and the other interpreting the 'X' as 1
    std::string addr_str_0(addr_str);
    std::string addr_str_1(addr_str);
    addr_str_0[scan_index] = '0';
    addr_str_1[scan_index] = '1';
    write_to_memory(value, addr_str_0, scan_index + 1, mem);
    write_to_memory(value, addr_str_1, scan_index + 1, mem);

  } else {
    // If current bit of memory address is not 'X', continue scanning the next memory address bit for 'X'
    write_to_memory(value, addr_str, scan_index + 1, mem);
  }
}

std::string apply_mask(long value, const std::string &mask) {
  // Convert given value to binary string
  std::string value_str = std::bitset<36>(value).to_string();

  // Apply mask, overwriting the value bit if the mask does not specify 0
  // Note that index 0 is positioned on the left for mask, but on the right for value_bits
  for(int i = 0; i < 36; i++) {
    if(mask[i] != '0') {
      value_str[i] = mask[i];
    }
  }

  return value_str;
}

int main() {
  // Read input from file
  std::ifstream file("day14.txt");
  std::string line;
  std::string mask;
  std::unordered_map<long, long> mem;
  char *mask_temp = new char[37]();

  while(std::getline(file, line)) {
    // Try to parse line as mask command
    if(std::sscanf(line.c_str(), "mask = %36s", mask_temp) == 1) {
      mask = mask_temp;
      continue;
    }

    // Try to parse line as mem command
    long addr = 0;
    long value = 0;
    if(std::sscanf(line.c_str(), "mem[%ld] = %ld", &addr, &value) == 2) {
      std::string addr_str = apply_mask(addr, mask);
      write_to_memory(value, addr_str, 0, mem);
    }
  }

  // Find sum of all values currently stored in memory
  long sum = 0;
  for(std::pair<long, long> elem : mem) {
    sum += elem.second;
  }
  std::cout << sum << std::endl;
  return 0;
}
