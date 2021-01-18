#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Extended Euclidean algorithm to compute Bezout coefficients (from Wikipedia)
void extended_gcd(__int128 a, __int128 b, __int128 &a_coeff, __int128 &b_coeff) {
  __int128 old_r = a;
  __int128 old_s = 1;
  __int128 old_t = 0;
  __int128 r = b;
  __int128 s = 0;
  __int128 t = 1;

  while(r != 0) {
    __int128 quotient = old_r / r;
    __int128 temp;

    temp = r;
    r = old_r - quotient * r;
    old_r = temp;

    temp = s;
    s = old_s - quotient * s;
    old_s = temp;

    temp = t;
    t = old_t - quotient * t;
    old_t = temp;
  }

  // Return Bezout coefficients
  a_coeff = old_s;
  b_coeff = old_t;
}

int main() {
  // Read input from file
  std::ifstream file("day13.txt");
  std::string line;
  int start;

  // Parse first line
  std::getline(file, line);
  std::stringstream start_ss(line);
  start_ss >> start;

  // Parse second line, where bus numbers are comma-separated
  std::getline(file, line);
  std::stringstream buses_ss(line);
  std::string bus_str;
  int bus;

  __int128 a = 0;
  __int128 n = 1;
  int i = 0;

  while(std::getline(buses_ss, bus_str, ',')) {
    // Extract the next bus number, if it's not 'x'
    if(bus_str != std::string("x")) {
      std::stringstream bus_str_ss(bus_str);
      bus_str_ss >> bus;

      // Want to find x such that x === a_i mod n_i for all i, by repeatedly using Chinese remainder theorem
      // Here, a_i is the index of the i-th bus line and n_i is the bus number of the i-th line
      // Assumes that all bus numbers are pairwise coprime
      __int128 a_i = (-i) % bus;
      a_i = (bus + a_i) % bus; // Force a_i to be positive, modulo with negative args is implementation defined
      __int128 n_i = bus;

      // Compute Bezout coefficients, find solution, and update a and n
      __int128 m;
      __int128 m_i;
      extended_gcd(n, n_i, m, m_i);
      
      __int128 x = a*m_i*n_i + a_i*m*n;
      n = n*n_i;
      a = x % n;
      a = (n + a) % n; // Force a to be positive, modulo with negative args is implementation defined
    }
    i++;
  }

  std::cout << static_cast<long>(a) << std::endl;
  return 0;
}
