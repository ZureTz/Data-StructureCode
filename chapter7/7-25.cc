#include <functional>
#include <iostream>
using std::cin;
using std::cout;

constexpr int MAX = 1001, n = 100;
static int s[MAX] = {0}, fst[n + 5] = {0}, lst[n + 5] = {0};
static bool isVisited[n + 5] = {false};

bool isCycle() {
  std::function<bool(int)> dfs = [&dfs](int index) -> bool {
    if (isVisited[index]) {
      return true;
    }

    int beginNode = fst[index], endNode = lst[index];
    if (beginNode > endNode) {
      return false;
    }

    isVisited[index] = true;
    bool flag = false;
    for (int i = beginNode; i <= endNode; ++i) {
      flag |= dfs(s[i]);
    }
    return flag;
  };

  bool flag = false;
  for (int i = 1; i <= n; ++i) {
    flag |= dfs(s[i]);
  }
  return flag;
}