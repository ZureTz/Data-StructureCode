#include <algorithm>
#include <iostream>
using namespace std;
typedef long long gg;

int main() {
  gg n;
  cin >> n;
  gg arr[n];
  for (gg i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  gg dp[n];
  fill(dp, dp + n, 0);
  gg mNum(0ll);
  for (gg i = 1; i < n; ++i) {
    dp[i] = max(0ll, gg(dp[i - 1] + arr[i]));
    mNum = dp[i] > mNum ? dp[i] : mNum;
  }
  cout << mNum << endl;

  return 0;
}