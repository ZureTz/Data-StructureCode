#include <cctype>
#include <iostream>
#include <stack>
#include <string>

inline bool isOperator(const char ch) {
  switch (ch) {
  case '+':
    return true;
  case '-':
    return true;
  case '*':
    return true;
  case '/':
    return true;
  }
  return false;
}

std::string reverseExp(const std::string &src) {
  std::stack<std::string> stack;
  for (auto it = src.end() - 1; it >= src.begin(); --it) {
    if (isdigit(*it) || isalpha(*it)) {
      stack.push(std::string(1, *it));
      continue;
    }
    // else the caracter is operator
    if (isOperator(*it)) {
      const std::string op1 = stack.top();
      stack.pop();
      const std::string op2 = stack.top();
      stack.pop();
      stack.push(op1 + op2 + std::string(1, *it));
      continue;
    }
  }
  return stack.top();
}

int main(int argc, char const *argv[]) {
  std::cout << reverseExp("*-A/BC-/AKL") << '\n';
  return 0;
}