#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>

using std::cout;

namespace Solver {
template <typename T> T decoder(const std::string &exp);
} // namespace Solver

namespace {
const std::unordered_map<char, int> Priority{
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
};
}

template <typename T> T Solver::decoder(const std::string &exp) {
  if (exp.empty()) {
    return 0;
  }
  std::stringstream ss(exp);
#ifdef DEBUG
  cout << "Original string:" << ss.str() << std::endl << std::endl;
#endif

  std::stack<T> numStack;
  std::stack<char> operatorStack;
  operatorStack.push('(');

  auto process = [&](void) {
    const T rhs = numStack.top();
    numStack.pop();
#ifdef DEBUG
    cout << "Processing: " << numStack.top() << ' ' << operatorStack.top()
         << ' ' << rhs;
#endif
    switch (operatorStack.top()) {
    case '+':
      numStack.top() += rhs;
      break;
    case '-':
      numStack.top() -= rhs;
      break;
    case '*':
      numStack.top() *= rhs;
      break;
    case '/':
      numStack.top() /= rhs;
      break;
    default:
      break;
    }
#ifdef DEBUG
    cout << " = " << numStack.top() << std::endl;
#endif
    operatorStack.pop();
  };

  while (ss.peek() != EOF) {
    if (isspace(ss.peek())) {
      ss.ignore();
      continue;
    }

    if (isdigit(ss.peek()) || ss.peek() == '.') {
      T temp;
      ss >> temp;
      numStack.push(temp);
#ifdef DEBUG
      cout << temp << std::endl;
#endif
      continue;
    }

    // else the character to be read is an operator or bracket
    char opTemp = 0;
    ss >> opTemp;
#ifdef DEBUG
    cout << '\"' << opTemp << '\"' << std::endl;
#endif

    // brackets:
    if (opTemp == '(') {
      operatorStack.push(opTemp);
      continue;
    }
    if (opTemp == ')') {
      while (operatorStack.top() != '(') {
        process();
      }
      operatorStack.pop();
      continue;
    }

    // operators:
    if (Priority.find(opTemp) == Priority.end()) {
#ifdef DEBUG
      cout << "error: " << opTemp << std::endl;
#endif
      std::cerr << "Error: Undefined Symbol: " << '\"' << opTemp << '\"'
                << std::endl;
      exit(EXIT_FAILURE);
    }
    while (operatorStack.top() != '(' &&
           (Priority.find(opTemp)->second <=
            Priority.find(operatorStack.top())->second)) {
      process();
    }
    operatorStack.push(opTemp);
  }
  while (operatorStack.top() != '(') {
    process();
  }
  return numStack.top();
}

int main(int argc, char const *argv[]) {
  std::string str;
  std::getline(std::cin, str);

  cout << std::fixed << std::setprecision(2) << Solver::decoder<double>(str);

  return 0;
}