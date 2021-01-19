#include <bitset>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

long apply_mask(long value, const std::string &mask) {
  // Convert given value to binary
  std::bitset<36> value_bits = std::bitset<36>(value);

  // Apply mask, overwriting the value bit if the mask specifies 0 or 1
  // Note that index 0 is positioned on the left for mask, but on the right for value_bits
  for(int i = 0; i < 36; i++) {
    if(mask[i] == '0') {
      value_bits[35-i] = 0;
    } else if(mask[i] == '1') {
      value_bits[35-i] = 1;
    }
  }

  // Convert result back from binary
  return static_cast<long>(value_bits.to_ulong());
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
      mem[addr] = apply_mask(value, mask);
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
