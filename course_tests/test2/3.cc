#include <iostream>
#include <stack>
using std::cout;
constexpr int MAXN = 1010;

int n, pos = 1, cur = 1, count, nums[MAXN], out[2 * MAXN];
std::stack<int> stk1, stk2, w;

bool checkSeq(int pos) {
  int cur_temp = cur;
  while (!stk2.empty() && stk2.top() == cur_temp++) {
    w.push(stk2.top()), stk2.pop();
  }

  if (stk2.empty()) {
    while (!w.empty())
      stk2.push(w.top()), w.pop();
    return true;
  }
  for (int i = pos + 1; i <= n; i++) {
    if (nums[i] < nums[pos] || nums[i] < stk2.top()) {
      continue;
    }
    for (int j = i + 1; j <= n; j++) {
      if (nums[j] < nums[pos] && nums[j] < stk2.top()) {
        while (!w.empty())
          stk2.push(w.top()), w.pop();
        return false;
      }
    }
    break;
  }
  while (!w.empty())
    stk2.push(w.top()), w.pop();
  ;
  return 1;
}

int main(int argc, char const *argv[]) {

  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> nums[i];
  }

  for (int i = 1; i <= 2 * n; ++i) {
    if (pos <= n && (stk1.empty() || nums[pos] < stk1.top()) && checkSeq(pos)) {
      stk1.push(nums[pos++]), out[++count] = 0;
    } else if (!stk1.empty() && stk1.top() == cur) {
      stk1.pop(), out[++count] = 1, cur++;
    } else if (pos <= n && (stk2.empty() || nums[pos] < stk2.top())) {
      stk2.push(nums[pos++]), out[++count] = 2;
    } else if (!stk2.empty() && stk2.top() == cur) {
      stk2.pop(), out[++count] = 3, cur++;
    } else {
      cout.put('0');
      return 0;
    }
  }

  for (int i = 1; i <= n * 2; i++) {
    cout.put('a' + out[i]).put(' ');
  }

  return 0;
}