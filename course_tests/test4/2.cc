#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using std::cout;

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

const std::unordered_map<char, int> Priority{
    {'(', -1}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
};

std::string conversion(const std::string &sourceExp) {
  std::string resultExp;

  std::stack<char> operatorStack;
  for (auto it = sourceExp.begin(); it != sourceExp.end(); ++it) {
    // cout << resultExp << ' ' << *it << '\n';
    if (isspace(*it)) {
      continue;
    }
    if (isdigit(*it) or isalpha(*it)) {
      resultExp.push_back(*it);
      continue;
    }
    if (*it == '(') {
      operatorStack.push(*it);
      continue;
    }
    if (*it == ')') {
      while (!operatorStack.empty() and operatorStack.top() != '(') {
        const char topOp = operatorStack.top();
        operatorStack.pop();
        resultExp.push_back(topOp);
      }
      if (operatorStack.empty()) {
        continue;
      }
      operatorStack.pop();
      continue;
    }

    auto found = Priority.find(*it);
    if (found == Priority.end()) {
      cout << "Not an valid operator: " << *it << '\n';
      continue;
    }

    // *it is an operator
    while (!operatorStack.empty() and
           (Priority.find(operatorStack.top())->second >= found->second)) {
      const char topOp = operatorStack.top();
      operatorStack.pop();
      resultExp.push_back(topOp);
    }
    operatorStack.push(*it);
  }
  while (!operatorStack.empty()) {
    resultExp.push_back(operatorStack.top());
    operatorStack.pop();
  }
  return resultExp;
}

int main(int argc, char const *argv[]) {

  std::string sourceExp;
  std::getline(std::cin, sourceExp, '#');
  // cout << sourceExp << std::endl;
  cout << conversion(sourceExp) << std::endl;

  return 0;
}