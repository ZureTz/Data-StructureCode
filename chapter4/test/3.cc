#include <cstddef>
#include <deque>
#include <iostream>
#include <string>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string alpha, beta;
  cin >> alpha >> beta;

  std::string stack;
  // auto opA = [&]() {
  //   stack.push_back(alpha.back());
  //   alpha.pop_back();
  // };
  // auto opB = [&]() {
  //   stack.push_back(beta.back());
  //   beta.pop_back();
  // };

  bool flag = true;

  while (!alpha.empty() && !beta.empty()) {
    if (flag) {
      char temp = alpha.front();
      alpha.erase(0, 1);

      size_t find = stack.find(std::string(1, temp));
      if (find != std::string::npos) {
        flag = true;
        alpha.push_back(temp);
        alpha.append(stack.begin(), stack.begin() + find);
        stack.erase(stack.begin(), stack.begin() + find);
        continue;
      }

      stack.insert(0, 1, temp);
      flag = !flag;
      continue;
    }

    char temp = beta.front();
    beta.erase(0, 1);
    size_t find = stack.find(std::string(1, temp));
    if (find != std::string::npos) {
      flag = false;
      beta.push_back(temp);
      beta.append(stack.begin(), stack.begin() + find);
      stack.erase(stack.begin(), stack.begin() + find);
      continue;
    }
    stack.insert(0, 1, temp);
    flag = !flag;
    continue;
  }

  cout << std::string(stack.rbegin(), stack.rend());

  return 0;
}