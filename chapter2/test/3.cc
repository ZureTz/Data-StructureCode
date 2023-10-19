#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
typedef long long ll;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nSize;
  cin >> nSize;
  std::vector<ll> array(nSize);
  for (auto &num : array) {
    cin >> num;
  }

  std::vector<ll> dp(nSize);
  int max = 0;
  for (size_t i = 1; i < nSize; ++i) {
    dp[i] = std::max(0ll, dp[i - 1] + array[i]);
    if (dp[i] > max) {
      max = dp[i];
    }
  }

  cout << max;

  return 0;
}