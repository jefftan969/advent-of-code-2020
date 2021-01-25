#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

long evaluate(const std::string &expr) {
  // First, try to parse entire expression as integer
  std::stringstream expr_ss(expr);
  int val = 0;
  if((expr_ss >> val) && (expr_ss.tellg() == -1)) {
    return val;
  }

  // Then, look for first operator from right to left
  // Treat parenthesized values as a single entity
  // Scan right to left, because operator precedence is left-to-right, and due
  // to recursion the operation with least operator precedence comes first
  // Similarly, need to do multiplication before addition, since addition has higher precedence
  // Track location of first addition operator, in case multiplication is not initially found
  int paren_level = 0;
  int first_add = -1;
  for(int i = expr.length() - 1; i >= 0; i--) {
    if(expr[i] == '(') {
      paren_level++;
    } else if(expr[i] == ')') {
      paren_level--;
    } else if(paren_level == 0) {
      if(expr[i] == '+') {
        if(first_add = -1) {
          first_add = i;
        }
      } else if(expr[i] == '*') {
        std::string left_expr = expr.substr(0, i-1);
        std::string right_expr = expr.substr(i+2, std::string::npos);
        return evaluate(left_expr) * evaluate(right_expr);
      }
    }
  }

  // If no multiplication operator found, try to perform addition
  if(first_add != -1) {
    std::string left_expr = expr.substr(0, first_add-1);
    std::string right_expr = expr.substr(first_add+2, std::string::npos);
    return evaluate(left_expr) + evaluate(right_expr);
  }

  // If no operator found, assuming that the entire given expression is parenthesized
  if(expr[0] == '(' && expr[expr.length() - 1] == ')') {
    return evaluate(expr.substr(1, expr.length() - 2));
  }

  std::cout << "Error: expression " << expr << " invalid!\n";
  return 0;
}

int main() {
  // Read input from file
  std::ifstream file("day18.txt");
  std::string line;
  long sum = 0;

  while(std::getline(file, line)) {
    sum += evaluate(std::string(line));
  }

  // Print sum
  std::cout << sum << std::endl;
  return 0;
}
