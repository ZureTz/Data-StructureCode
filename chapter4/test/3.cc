#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
using std::cin;
using std::cout;

inline size_t hash(const std::string &s1, const std::string &s2) {
  return std::hash<std::string>()(s1) ^ (std::hash<std::string>()(s2) << 1);
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string alpha, beta;
  cin >> alpha >> beta;

  std::string stack;
  bool flag = true;
  std::unordered_set<size_t> duplicateSet;

  while (!alpha.empty() && !beta.empty()) {
    // cout << alpha << ' ' << beta << ' ' << stack << std::endl;
    const size_t hashNum = hash(alpha, beta);
    if (duplicateSet.find(hashNum) != duplicateSet.end()) {
      cout << "-1" << std::endl;
      return 0;
    }

    if (flag) {
      char temp = alpha.front();
      alpha.erase(0, 1);

      size_t find = stack.find(std::string(1, temp));
      if (find != std::string::npos) {
        flag = true;
        alpha.push_back(temp);
        alpha.append(stack.begin(), stack.begin() + find + 1);
        stack.erase(stack.begin(), stack.begin() + find + 1);
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
      beta.append(stack.begin(), stack.begin() + find + 1);
      stack.erase(stack.begin(), stack.begin() + find + 1);
      continue;
    }

    stack.insert(0, 1, temp);
    flag = !flag;
    continue;
  }

  // cout<<alpha<<' '<<beta<<std::endl;
  cout << (alpha.empty() ? beta : alpha) << std::endl;
  return 0;
}